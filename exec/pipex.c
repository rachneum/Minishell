/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachou <rachou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:48:07 by raneuman          #+#    #+#             */
/*   Updated: 2024/10/29 11:52:09 by rachou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void ft_pipe(int arc, t_cmd *cmd, t_env_list *env_list)
{
    int tube[2];
    int prev_tube;
	int cmd_count;
    int i;
    t_cmd *current_cmd;
	t_cmd *tmp;
    pid_t pid;
    pid_t *pids;
    
    prev_tube = -1;
    current_cmd = cmd;
    i = 0;
    tmp = cmd;
    cmd_count = 0;
    while (tmp)
    {
        cmd_count++;
        tmp = tmp->next;
    }
    pids = malloc(sizeof(pid_t) * cmd_count);
    if (!pids)
        return;
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
        pid = fork();
        if (pid == -1)
		{
            perror("FORK");
            free(pids);
            return;
        } 
        if (pid == 0)
        {
            if (current_cmd->out_red || current_cmd->in_red)
                handle_redirections(current_cmd);
            else
                child_pipe_redirect(current_cmd, tube, prev_tube, env_list);
            ft_exec(current_cmd->cmd, env_list);
            exit(1);
        }
        pids[i++] = pid;
        if (prev_tube != -1)
            close(prev_tube);
        if (current_cmd->next)
        {
            close(tube[1]);
            prev_tube = tube[0];
        }
        current_cmd = current_cmd->next;
    }
    i = 0;
    while (i < cmd_count)
    {
        waitpid(pids[i], NULL, 0);
        i++;
    }
    free(pids);
}

void	child_pipe_redirect(t_cmd *current_cmd, int *tube, int prev_tube, t_env_list *env_list)
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
