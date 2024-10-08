/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachou <rachou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:25:55 by rachou            #+#    #+#             */
/*   Updated: 2024/10/08 12:01:28 by rachou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

static char	*get_path(char *argv, char **env, int i)//Vérifie si la cmd est exécutable et, si ce n'est pas le cas, extrait et divise la variable d'environnement PATH pour rechercher le chemin de la commande.
{
	char	**split_path;
	char	*path;
	char	*full_path;

	if (!access(argv, X_OK))
		return (argv);
	if (check_path(env) == -1)
		perror("PATH: ");
	if (!env[check_path(env)])
		return (argv);
	split_path = ft_split(env[check_path(env)] + 5, ':');
	if (!split_path)
		return (NULL);
	while (split_path[++i])
	{
		path = ft_strjoin(split_path[i], "/");
		full_path = ft_strjoin(path, argv);
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

static void	ft_exec(char *argv, char **env)//Divise la commande en arguments, cherche le chemin de la commande dans l'environnement, et exécute la commande, affichant un message d'erreur et sortant avec un code d'erreur approprié si la commande ne peut pas être trouvée ou exécutée.
{
	char	**split_cmd;
	char	*path;

	split_cmd = NULL;
	path = NULL;
	split_cmd = ft_split(argv, ' ');
	if (!split_cmd)
		exit(EXIT_FAILURE);
	path = get_path(split_cmd[0], env, -1);
	if (!path)
	{
		perror("CMD: ");
		ft_free_tab(split_cmd);
		exit(127);//Cmd exécuté est introuvable.
	}
	if (execve(path, split_cmd, env) == -1)
	{
		perror("EXEC: ");
		ft_free_tab(split_cmd);
		exit(126);
	}
}

int	main(int argc, char **argv, char **env)
{
	int		i;
	int		tube[2];//Mon pipe.
	int		prev_tube;//Va me permettre de lire le pipe précédent.
	pid_t	pid;

	i = 1;
	prev_tube = -1;
	while (argv[i])
	{
		if (i < argc - 1)//Tant que != dernière cmd.
		{
			if (pipe(tube) == -1)//Crée un pipe. Important de le créer avant de forker.
                perror("Pipe: ");
		}
		if ((pid = fork()) == -1)//Fork à chaque cmd pour créer des processus enfants.
			perror("Fork: ");
		if (pid == 0)//Si on se trouve bien dans l'enfant.
		{
			if (i < argc - 1)
			{
				dup2(tube[1], 1);//Redirige écriture dans le pipe.
				close(tube[1]);
			}
			if (i > 1)//Tant que != première cmd.
			{
				dup2(prev_tube, 0);//Redirige lecture du pipe (lire dans le pipe précédent).
				close(prev_tube);
			}
			close(tube[0]);
			ft_exec(argv[i], env);
		}
		if (prev_tube != -1)
			close(prev_tube);
		if (i < argc - 1)
		{
			close(tube[1]);//Ferme l'extrémité d'écriture du pipe dans le parent.
			prev_tube = tube[0];//Conserve l'extrémité de lecture pour la prochaine commande.
		}
		waitpid(pid, NULL, 0);
		i++;
	}
}
