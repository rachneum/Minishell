/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachou <rachou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:52:57 by raneuman          #+#    #+#             */
/*   Updated: 2024/10/21 18:09:38 by rachou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char	*get_path(char **cmd, t_env_list *env_list, int i)//Vérifie si la cmd est exécutable et, si ce n'est pas le cas, extrait et divise la variable d'environnement PATH pour rechercher le chemin de la commande.
{
	char	**split_path;
	char	*path;
	char	*full_path;
	char	*env_path;

	if (!access(cmd[0], X_OK))
		return (cmd[0]);
	env_path = var_pfetch(env_list, "PATH");
	if (!env_path || check_path(env_list) == -1)
	{
		perror("PATH");
		return (cmd[0]);
	}
	split_path = ft_split(env_path, ':');
	if (!split_path)
		return (NULL);
	while (split_path[++i])//Recherche le chemin dans chaque répertoire de PATH.
	{
		path = ft_strjoin(split_path[i], "/");
		full_path = ft_strjoin(path, cmd[0]);
		if (!path)
			free(path);
		if (!full_path)
			free(full_path);
		if (!access(full_path, X_OK))//Vérifie si le chemin construit est exécutable.
			return (full_path);//Retourne le chemin complet si exécutable.
		if (full_path)
			free(full_path);
	}
	return (ft_free_tab(split_path));//Libère le tableau des chemins.
}

int	check_path(t_env_list *env_list)//Check si le PATH existe dans l'environnement.
{
	while (env_list)
	{
	    if (ft_strncmp("PATH", env_list->var, 4) == 0)
	        return (1);
	    env_list = env_list->next;
	}
	return (-1);
}

char **env_list_to_array(t_env_list *env_list, int i)
{
    char		**env_array;
    t_env_list *current;
    int 		count;

    current = env_list;//Compte le nbr d'éléments dans env_list.
    count = 0;
    if (current)
    {
        count++;
        current = current->next;
	}
    env_array = (char **)malloc(sizeof(char *) * (count + 1));//Allocation de mémoire pour env_array.
    if (!env_array)
        return NULL;
    current = env_list;
    if (current)
    {
        env_array[i] = ft_strjoin("&", current->var);
        if (!env_array[i])
            return (free(env_array), NULL);
        current = current->next;
		i++;
    }
    env_array[i] = NULL;//Terminate env_array.
    return env_array;
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
