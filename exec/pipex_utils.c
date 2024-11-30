/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachou <rachou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:32:13 by rachou            #+#    #+#             */
/*   Updated: 2024/11/30 16:52:12 by rachou           ###   ########.fr       */
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
		perror("PIDS malloc");
		return (-1);
	}
	return (cmd_count);
}

int	create_pipe(int tube[2], pid_t *pids, t_cmd *current_cmd)
{
	if (current_cmd->next)
	{
		if (pipe(tube) == -1)
		{
			perror("PIPE");
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
		perror("FORK ");
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

	i = 0;
	while (i < cmd_count)
	{
		waitpid(pids[i], NULL, 0);
		i++;
	}
	free(pids);
}
