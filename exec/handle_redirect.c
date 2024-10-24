/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachou <rachou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 09:33:59 by rachou            #+#    #+#             */
/*   Updated: 2024/10/24 16:14:26 by rachou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"


static void	handle_output_red(t_token *out_red)
{
	int	fd;

	fd = open(out_red->content, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (fd == -1)
	{
		perror("open");
		return;
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		return;
	}
	close(fd);
}

static void	handle_append_red(t_token *out_red)
{
	int	fd;

	fd = open(out_red->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("open");
		return;
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		return;
	}
	close(fd);
}

static void	handle_input_red(t_token *in_red)
{
	int	fd;
    
	fd = open(in_red->content, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return;
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		return;
	}
	close(fd);
}

static void	handle_heredoc(t_token *in_red)
{
	int		fd;
	char	*input;
    
	fd = open(".suprise.txt", O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (fd == -1)
	{
		perror("open");
		return;
	}
	while(1)
	{
		input = readline("> ");
		if (ft_strncmp(input, in_red->content, ft_strlen(input)) == 0)
		{
	    	free(input);
	    	break ;
		}
		ft_putendl_fd(input, fd);
	}
	fd = open(".suprise.txt", O_RDONLY);
	if (dup2(fd, 0) == -1)
	{
		perror("dup2");
		return;
	}
	close(fd);
}

void	handle_redirections(t_cmd *cmd)
{
	while (cmd->n_redirection > 0)
	{
		if (cmd->out_red && cmd->out_red->content)
		{
			if (cmd->out_red->previous->content && strcmp(cmd->out_red->previous->content, ">") == 0)
				handle_output_red(cmd->out_red);
			if (cmd->out_red->previous->content && strcmp(cmd->out_red->previous->content, ">>") == 0)
				handle_append_red(cmd->out_red);
		}
		else if (cmd->in_red && cmd->in_red->content)
		{
			if (cmd->in_red->previous->content && strcmp(cmd->in_red->previous->content, "<") == 0)
				handle_input_red(cmd->in_red);
			if (cmd->in_red->previous->content && strcmp(cmd->in_red->previous->content, "<<") == 0)
				handle_heredoc(cmd->in_red);
		}
		cmd->n_redirection--;
	}
}
