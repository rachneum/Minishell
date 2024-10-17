/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raneuman <raneuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:48:07 by raneuman          #+#    #+#             */
/*   Updated: 2024/10/17 14:24:56 by raneuman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

static int	check_path(char **env)//Check si le PATH existe dans l'environnement.
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

static char	*get_path(char **cmd, char **env, int i)//Vérifie si la cmd est exécutable et, si ce n'est pas le cas, extrait et divise la variable d'environnement PATH pour rechercher le chemin de la commande.
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

static void	ft_exec(char **cmd, char **env)//Cherche le chemin de la commande dans l'environnement, et exécute la commande, affichant un message d'erreur et sortant avec un code d'erreur approprié si la commande ne peut pas être trouvée ou exécutée.
{
	char	*path;

	path = NULL;
	path = get_path(&cmd[0], env, -1);
	if (!path)
	{
		perror("CMD");
		ft_free_tab(cmd);
		exit(127);//Cmd exécuté est introuvable.
	}
	if (execve(path, cmd, env) == -1)
	{
		perror("EXEC");
		ft_free_tab(cmd);
		exit(126);//Erreur d'exécution.
	}
}

static void    child_pipe_redirect(t_cmd *current_cmd, int *tube, int prev_tube, char **env)
{
    if (current_cmd->next)
	{
		close(tube[0]);
		dup2(tube[1], 1);//Redirige écriture dans le pipe.
		close(tube[1]);
	}
	if (current_cmd->previous != NULL)//Tant que != première cmd.
	{
		close(tube[1]);
		dup2(prev_tube, 0);//Redirige lecture du pipe (lire dans le pipe précédent).
		close(prev_tube);
	}
	close(tube[0]);
}

void	ft_pipe(int arc, t_cmd *cmd, char **env)
{
	int		tube[2];//Mon pipe.
	int		prev_tube;//Va me permettre de lire le pipe précédent.
	pid_t	pid;
	t_cmd	*current_cmd;

	prev_tube = -1;
	current_cmd = cmd;
	while (current_cmd)
	{
		if (current_cmd->next)//Tant que != dernière cmd.
		{
			if (pipe(tube) == -1)//Crée un pipe. Important de le créer avant de forker.
                perror("PIPE");
		}
		if ((pid = fork()) == -1)//Fork à chaque cmd pour créer des processus enfants.
			perror("FORK");
		if (pid == 0)//Si on se trouve bien dans l'enfant.
		{
			child_pipe_redirect(current_cmd, tube, prev_tube, env);
			ft_exec(current_cmd->cmd, env);
		}
		//if (prev_tube != -1)//Vérifie si le processus précédent est ouvert.
		//	close(prev_tube);
		if (current_cmd->next)
		{
			close(tube[1]);//Ferme l'extrémité d'écriture du pipe dans le parent.
			prev_tube = tube[0];//Conserve l'extrémité de lecture pour la prochaine commande.
		}
		waitpid(pid, NULL, 0);
		current_cmd = current_cmd->next;
	}
}
