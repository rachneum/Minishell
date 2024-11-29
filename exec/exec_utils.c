/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachou <rachou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:52:57 by raneuman          #+#    #+#             */
/*   Updated: 2024/11/29 19:21:50 by rachou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char	*get_path(char **cmd, t_env_list *env_list, int i)
{
	char	**split_path;
	char	*path;
	char	*full_path;
	char	*env_path;

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
	while (split_path[++i])
	{
		path = ft_strjoin(split_path[i], "/");
		full_path = ft_strjoin(path, cmd[0]);
		if (!path)
			free(path);
		if (!full_path)
			free(full_path);
		if (!access(full_path, X_OK))
			return (full_path);
		if (full_path)
			free(full_path);
	}
	return (ft_free_tab(split_path));
}

int	check_path(t_env_list *env_list)
{
	while (env_list)
	{
		if (ft_strncmp("PATH", env_list->var, 4) == 0)
			return (1);
		env_list = env_list->next;
	}
	return (-1);
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

char	*ft_free_tab(char **cmd)
{
	int	i;

	if (!cmd)
		return (NULL);
	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
	return (NULL);
}

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] != '\0' && str2[i] != '\0')
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (str1[i] - str2[i]);
}
