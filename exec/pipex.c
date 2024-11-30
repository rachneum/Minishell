/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachou <rachou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:48:07 by raneuman          #+#    #+#             */
/*   Updated: 2024/11/30 16:50:57 by rachou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

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
		return ;
	i = 0;
	while (current_cmd)
	{
		if (create_pipe(current_cmd->tube, pids, current_cmd) == -1)
			return ;
		pids[i++] = create_process(current_cmd, env_list, all);
		close_unused_pipes(current_cmd);
		if (current_cmd->next)
			current_cmd->next->prev_tube = current_cmd->tube[0];
		current_cmd = current_cmd->next;
	}
	wait_for_children(pids, cmd_count);
}

pid_t	create_process(t_cmd *current_cmd, t_env_list *env_list, t_all *all)
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

void	pipe_redi(t_cmd *current_cmd, t_env_list *env_list, int *heredoc_fd)
{
	if (current_cmd->out_red || current_cmd->in_red)
		handle_redirections(current_cmd, heredoc_fd);
	pipe_redirect(current_cmd, env_list);
}

void	pipe_redirect(t_cmd *current_cmd, t_env_list *env_list)
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
		exit(127);
	}
	env_array = env_list_to_array(env_list, 0);
	if (env_array)
	{
		if (execve(path, cmd, env_array) == -1)
		{
			perror("EXEC");
			ft_free_tab(cmd);
			ft_free_tab(env_array);
			exit(126);
		}
		ft_free_tab(env_array);
	}
}
