/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachou <rachou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:52:57 by raneuman          #+#    #+#             */
/*   Updated: 2024/12/11 00:17:48 by rachou           ###   ########.fr       */
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

/*char	*get_path(char **cmd, t_env_list *env_list, int i)
{
	char	**split_path;
	char	*env_path;
	char	*result;

	// Vérification de cmd[0]
	if (!cmd || !cmd[0])
	{
		write(2, "Error: Command is NULL\n", 23);
		return (NULL);
	}

	// Vérification si cmd[0] est déjà un chemin valide
	if (!access(cmd[0], X_OK))
	{
		return (ft_strdup(cmd[0])); // Retourne une copie pour éviter des conflits.
	}

	// Récupération de la variable PATH
	env_path = var_bfetch(env_list, "PATH");
	if (!env_path)
	{
		write(2, "Error: PATH variable not found\n", 31);
		return (NULL);
	}

	// Split PATH en un tableau de chemins
	split_path = ft_split(env_path, ':');
	if (!split_path)
	{
		write(2, "Error: Failed to split PATH\n", 28);
		return (NULL);
	}

	// Recherche de l'exécutable dans les chemins
	result = find_executable_path(split_path, cmd[0]);
	ft_free_tab(split_path);

	// Vérifie si un chemin valide a été trouvé
	if (!result)
	{
		write(2, "Error: Command not found: ", 26);
		write(2, cmd[0], ft_strlen(cmd[0]));
		write(2, "\n", 1);
		return (NULL);
	}

	// Retourne le chemin trouvé
	return (result);
}*/


char	*get_path(char **cmd, t_env_list *env_list, int i)
{
	char	**split_path;
	char	*env_path;
	char	*result;


	if (!cmd || !cmd[0])
		exit (1);
	if (!access(cmd[0], X_OK))
		return (cmd[0]);
	env_path = var_bfetch(env_list, "PATH");
	if (!env_path || check_path(env_list) == -1)
		return (NULL);
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
