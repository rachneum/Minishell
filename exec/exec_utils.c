/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raneuman <raneuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:52:57 by raneuman          #+#    #+#             */
/*   Updated: 2024/12/01 12:08:29 by raneuman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

static char	*find_executable_path(char **split_path, char *cmd)
{
	char	*path;
	char	*full_path;
	int		i;

	i = 0;
	while (split_path[i])
	{
		path = ft_strjoin(split_path[i], "/");
		if (path)
		{
			full_path = ft_strjoin(path, cmd);
			free(path);
			if (full_path)
			{
				if (!access(full_path, X_OK))
					return (full_path);
				free(full_path);
			}
		}
		i++;
	}
	return (NULL);
}

static int	check_path(t_env_list *env_list)
{
	while (env_list)
	{
		if (ft_strncmp("PATH", env_list->var, 4) == 0)
			return (1);
		env_list = env_list->next;
	}
	return (g_err_global = 1, -1);
}

char	*get_path(char **cmd, t_env_list *env_list, int i)
{
	char	**split_path;
	char	*env_path;
	char	*result;

	if (!access(cmd[0], X_OK))
		return (cmd[0]);
	env_path = var_bfetch(env_list, "PATH");
	if (!env_path || check_path(env_list) == -1)
	{
		perror("PATH");
		return (cmd[0]);
	}
	split_path = ft_split(env_path, ':');
	if (!split_path)
		return (NULL);
	result = find_executable_path(split_path, cmd[0]);
	ft_free_tab(split_path);
	return (result);
}

char	**env_list_to_array(t_env_list *env_list, int i)
{
	t_env_list	*current;
	char		**env_array;
	int			count;

	current = env_list;
	count = 0;
	while (current)
	{
		count++;
		current = current->next;
	}
	env_array = (char **)malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);
	current = env_list;
	while (current)
	{
		env_array[i] = ft_strdup(current->var);
		if (!env_array[i])
			return (free(env_array), NULL);
		current = current->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}
