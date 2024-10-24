/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachou <rachou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:48:07 by raneuman          #+#    #+#             */
/*   Updated: 2024/10/24 16:16:13 by rachou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	ft_pipe(int arc, t_cmd *cmd, t_env_list *env_list)
{
	int		tube[2];//Mon pipe.
	int		prev_tube;//Va me permettre de lire le pipe précédent.
	pid_t	pid;
	t_cmd	*current_cmd;
	t_all	*all;

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
			child_pipe_redirect(current_cmd, tube, prev_tube, env_list);
			handle_redirections(current_cmd);
			ft_exec(current_cmd->cmd, env_list);
		}
		if (current_cmd->next)
		{
			close(tube[1]);//Ferme l'extrémité d'écriture du pipe dans le parent.
			prev_tube = tube[0];//Conserve l'extrémité de lecture pour la prochaine commande.
		}
		waitpid(pid, NULL, 0);
		current_cmd = current_cmd->next;
	}
}

void	child_pipe_redirect(t_cmd *current_cmd, int *tube, int prev_tube, t_env_list *env_list)
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

void	ft_exec(char **cmd, t_env_list *env_list)
{
	char	*path;
	char	**env_array;

	path = NULL;
	path = get_path(&cmd[0], env_list, -1);
	if (!path)
	{
		perror("CMD");
		ft_free_tab(cmd);
		exit(127);//Commande executée n'est pas trouvée.
	}
	env_array = env_list_to_array(env_list, 0);
	if (env_array)
	{
		if (execve(path, cmd, env_array) == -1)
		{
			perror("EXEC");
			ft_free_tab(cmd);
			ft_free_tab(env_array);
			exit(126);//Erreur d'exec.
		}
		ft_free_tab(env_array);
	}
}
