/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachou <rachou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:52:57 by raneuman          #+#    #+#             */
/*   Updated: 2024/10/21 15:07:36 by rachou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char	*get_path(char **cmd, char **env, int i)//Vérifie si la cmd est exécutable et, si ce n'est pas le cas, extrait et divise la variable d'environnement PATH pour rechercher le chemin de la commande.
{
	char	**split_path;
	char	*path;
	char	*full_path;

	if (!access(cmd[0], X_OK))
		return (cmd[0]);
	if (check_path(env) == -1)
		perror("PATH");
	if (!env[check_path(env)])
		return (cmd[0]);
	split_path = ft_split(env[check_path(env)] + 5, ':');
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

int	check_path(char **env)//Check si le PATH existe dans l'environnement.
{
	int	i;

	i = 0;
	if (!env)
		return (-1);
	while (env[i])
	{
		if (ft_strncmp("PATH", env[i], 4) == 0)
			return (i);
		i++;
	}
	return (-1);
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
