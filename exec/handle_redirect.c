/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachou <rachou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 09:33:59 by rachou            #+#    #+#             */
/*   Updated: 2024/11/29 19:25:57 by rachou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

static int	open_file_append_red(t_token *current, int append_mode)
{
	int	fd;

	fd = open(current->content, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (fd == -1)
	{
		perror("OPEN ");
		return (-1);
	}
	if (current->next != NULL)
		close(fd);
	return (fd);
}
static int	open_file_output_red(t_token *current, int append_mode)
{
	int	fd;

	fd = open(current->content, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd == -1)
	{
		perror("OPEN ");
		return (-1);
	}
	if (current->next != NULL)
		close(fd);
	return (fd);
}

void	handle_input_red(t_token *in_red)
{
	int	fd;

	fd = open(in_red->content, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return ;
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		return ;
	}
	close(fd);
}

void	handle_append_red(t_token *out_red)
{
	int		fd;
	t_token	*current;

	current = out_red;
	while (current->previous)
		current = current->previous;
	while (current)
	{
		if ((ft_strcmp(current->content, ">>") != 0)
			&& (ft_strcmp(current->content, ">") != 0))
		{
			fd = open_file_append_red(current, 0);
			if (fd == -1)
				return ;
		}
		current = current->next;
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("DUP2 ");
		return ;
	}
	close(fd);
}

void	handle_output_red(t_token *out_red)
{
	int		fd;
	t_token	*current;

	current = out_red;
	while (current->previous)
		current = current->previous;
	while (current)
	{
		if ((ft_strcmp(current->content, ">") != 0)
			&& (ft_strcmp(current->content, ">>") != 0))
		{
			fd = open_file_output_red(current, 0);
			if (fd == -1)
				return ;
		}
		current = current->next;
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("DUP2 ");
		return ;
	}
	close(fd);
}

void	handle_redirections(t_cmd *cmd, int *heredoc_fd)
{
	if (cmd->out_red && cmd->out_red->content)
	{
		if ((cmd->out_red->previous->content)
			&& (ft_strcmp(cmd->out_red->previous->content, ">") == 0)
			&& (ft_strlen(cmd->out_red->previous->content) == 1))
			handle_output_red(cmd->out_red);
		if ((cmd->out_red->previous->content)
			&& (ft_strcmp(cmd->out_red->previous->content, ">>") == 0)
			&& (ft_strlen(cmd->out_red->previous->content) == 2))
			handle_append_red(cmd->out_red);
	}
	else if (cmd->in_red && cmd->in_red->content)
	{
		if ((cmd->in_red->previous->content)
			&& (ft_strcmp(cmd->in_red->previous->content, "<") == 0)
			&& (ft_strlen(cmd->in_red->previous->content) == 1))
			handle_input_red(cmd->in_red);
		if ((cmd->in_red->previous->content)
			&& (ft_strcmp(cmd->in_red->previous->content, "<<") == 0)
			&& (ft_strlen(cmd->in_red->previous->content) == 2))
			handle_heredoc(cmd->in_red, heredoc_fd);
	}
}
