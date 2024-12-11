/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raneuman <raneuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:32:13 by rachou            #+#    #+#             */
/*   Updated: 2024/12/08 13:32:19 by raneuman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	init_pids_and_count(t_cmd *cmd, pid_t **pids)
{
	int		cmd_count;
	t_cmd	*tmp;

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
		perror("pid ");
		return (g_err_global = 1, -1);
	}
	return (cmd_count);
}

int	create_pipe(int tube[2], pid_t *pids, t_cmd *current_cmd)
{
	if (current_cmd->next)
	{
		if (pipe(tube) == -1)
		{
			perror("pipe ");
			g_err_global = 3;
			free(pids);
			return (-1);
		}
	}
	return (0);
}

pid_t	create_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork ");
		g_err_global = 3;
		return (-1);
	}
	return (pid);
}

void	close_unused_pipes(t_cmd *current_cmd)
{
	if (current_cmd->prev_tube != -1)
		close(current_cmd->prev_tube);
	if (current_cmd->next)
		close(current_cmd->tube[1]);
}

void	wait_for_children(pid_t *pids, int cmd_count)
{
	int	i;
	int	w_status;

	i = 0;
	while (i < cmd_count)
	{
		waitpid(pids[i], &w_status, 0);
		if (WIFEXITED(w_status))
			g_err_global = WEXITSTATUS(w_status);
		i++;
	}
	free(pids);
}
