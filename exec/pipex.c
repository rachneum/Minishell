/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raneuman <raneuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:48:07 by raneuman          #+#    #+#             */
/*   Updated: 2024/12/01 10:05:44 by raneuman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

static int	ft_exec(char **cmd, t_env_list *env_list)
{
	char	*path;
	char	**env_array;

	path = NULL;
	path = get_path(&cmd[0], env_list, -1);
	if (!path)
	{
		perror("CMD");
		ft_free_tab(cmd);
		return (g_err_global = 127, 1);
	}
	env_array = env_list_to_array(env_list, 0);
	if (env_array)
	{
		reset_signal();
		if (execve(path, cmd, env_array) == -1)
		{
			perror("EXEC");
			ft_free_tab(cmd);
			ft_free_tab(env_array);
			return (g_err_global = 126, 1);
		}
		ft_free_tab(env_array);
	}
}

static int	pipe_redirect(t_cmd *current_cmd, t_env_list *env_list)
{
	if (!current_cmd->out_red)
	{
		if (current_cmd->next)
		{
			dup2(current_cmd->tube[1], 1);
			close(current_cmd->tube[1]);
		}
	}
	if (current_cmd->previous != NULL)
	{
		dup2(current_cmd->prev_tube, 0);
		close(current_cmd->prev_tube);
	}
}

static void	pipe_redi(t_cmd *current_cmd, t_env_list *env_list, int *heredoc_fd)
{
	if (current_cmd->out_red || current_cmd->in_red)
		handle_redirections(current_cmd, heredoc_fd);
	pipe_redirect(current_cmd, env_list);
}

static pid_t	ft_process(t_cmd *current_cmd, t_env_list *env_list, t_all *all)
{
	pid_t	pid;
	int		heredoc_fd;

	heredoc_fd = -1;
	if (built_in_subshell(current_cmd, all))
		return (0);
	pid = create_fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		pipe_redi(current_cmd, env_list, &heredoc_fd);
		if ((heredoc_fd != -1))
		{
			dup2(heredoc_fd, 0);
			close(heredoc_fd);
		}
		if (built_in_shell(current_cmd, all))
			exit(0);
		else
			ft_exec(current_cmd->cmd, env_list);
		exit(1);
	}
	wait(NULL);
	return (pid);
}

void	ft_pipex(t_cmd *cmd, t_env_list *env_list, t_all *all)
{
	pid_t	*pids;
	t_cmd	*current_cmd;
	int		cmd_count;
	int		i;

	current_cmd = cmd;
	cmd->prev_tube = -1;
	cmd_count = init_pids_and_count(cmd, &pids);
	if (cmd_count == -1)
	{
		g_err_global = 1;
		return ;
	}
	i = 0;
	while (current_cmd)
	{
		if (create_pipe(current_cmd->tube, pids, current_cmd) == -1)
			return ;
		pids[i++] = ft_process(current_cmd, env_list, all);
		close_unused_pipes(current_cmd);
		if (current_cmd->next)
			current_cmd->next->prev_tube = current_cmd->tube[0];
		current_cmd = current_cmd->next;
	}
	wait_for_children(pids, cmd_count);
}
