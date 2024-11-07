/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachou <rachou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:48:07 by raneuman          #+#    #+#             */
/*   Updated: 2024/11/07 10:43:39 by rachou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void ft_pipe(int arc, t_cmd *cmd, t_env_list *env_list)
{
    t_cmd *current_cmd;
    int tube[2];
    int prev_tube;//Garde la sortie du pipe précédent pour connecter les cmd en série.
	int cmd_count;
    int i;
    pid_t *pids;//Tableau pour stocker les PID des processus enfants, utilisé pour attendre leur terminaison plus tard.
    
    current_cmd = cmd;
    prev_tube = -1;//Initialisé à -1 pour indiqué qu'il n'y a pas de tube précédent au début.
    cmd_count = init_pids_and_count(cmd, &pids);
    i = 0;
    if (cmd_count == -1)
        return ;
    while (current_cmd)
    {
        if (current_cmd->next)
        {
            if (pipe(tube) == -1)
			{
                perror("PIPE");
                free(pids);
                return;
            }
        }
        pids[++i] = create_process(current_cmd, tube, prev_tube, env_list);
        if (pids[i] == -1)
		{
            free(pids);
            return;
        }
        close_unused_pipes(&prev_tube, tube, current_cmd);
        current_cmd = current_cmd->next;
    }
    wait_for_children(pids, cmd_count);
}

int init_pids_and_count(t_cmd *cmd, pid_t **pids)
{
    int     cmd_count;
    t_cmd   *tmp;

    cmd_count = 0;
    tmp = cmd;
    while (tmp)
    {
        cmd_count++;
        tmp = tmp->next;
    }
    *pids = malloc(sizeof(pid_t) * cmd_count);
    if (!*pids)
    {
        perror("PIDS malloc");
        return (-1);
    }
    return (cmd_count);
}

pid_t create_process(t_cmd *current_cmd, int *tube, int prev_tube, t_env_list *env_list)
{
    pid_t pid;

    pid = fork();
    if (pid == -1)
    {
        perror("FORK");
        return -1;
    }
    if (pid == 0)
    {
        handle_pipe_redirect(current_cmd, tube, prev_tube, env_list);
        ft_exec(current_cmd->cmd, env_list);
        exit(1);
    }
    return pid;
}

void handle_pipe_redirect(t_cmd *current_cmd, int *tube, int prev_tube, t_env_list *env_list)
{
    if (current_cmd->out_red || current_cmd->in_red)
        handle_redirections(current_cmd);
    else
        pipe_redirect(current_cmd, tube, prev_tube, env_list);
}

void	pipe_redirect(t_cmd *current_cmd, int *tube, int prev_tube, t_env_list *env_list)
{
	if (current_cmd->next)
	{
		dup2(tube[1], 1);//Redirige écriture dans le pipe.
		close(tube[1]);
	}
	if (current_cmd->previous != NULL)//Tant que != première cmd.
	{
		dup2(prev_tube, 0);//Redirige lecture du pipe (lire dans le pipe précédent).
		close(prev_tube);
	}
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

void close_unused_pipes(int *prev_tube, int *tube, t_cmd *current_cmd)
{
    if (*prev_tube != -1)
        close(*prev_tube);
    if (current_cmd->next)
    {
        close(tube[1]);
        *prev_tube = tube[0]; //Met à jour prev_tube pour la prochaine commande.
    }
}

void wait_for_children(pid_t *pids, int cmd_count)
{
    int i;

    i = 0;
    while (i < cmd_count)
    {
        waitpid(pids[i], NULL, 0);
        i++;
    }
    free(pids);
}
