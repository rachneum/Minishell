/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachou <rachou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 09:33:59 by rachou            #+#    #+#             */
/*   Updated: 2024/11/27 16:35:54 by rachou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	handle_redirections(t_cmd *cmd, int *heredoc_fd)
{	
	//while (cmd->n_redirection > 0)
	//{
		if (cmd->out_red && cmd->out_red->content)
		{
			if ((cmd->out_red->previous->content) && (ft_strcmp(cmd->out_red->previous->content, ">") == 0) && (ft_strlen(cmd->out_red->previous->content) == 1))
				handle_output_red(cmd->out_red);
			if ((cmd->out_red->previous->content) && (ft_strcmp(cmd->out_red->previous->content, ">>") == 0) && (ft_strlen(cmd->out_red->previous->content) == 2))
				handle_append_red(cmd->out_red);
		}
		else if (cmd->in_red && cmd->in_red->content)
		{
			if ((cmd->in_red->previous->content) && (ft_strcmp(cmd->in_red->previous->content, "<") == 0) && (ft_strlen(cmd->in_red->previous->content) == 1))
				handle_input_red(cmd->in_red);
			if ((cmd->in_red->previous->content) && (ft_strcmp(cmd->in_red->previous->content, "<<") == 0) && (ft_strlen(cmd->in_red->previous->content) == 2))
				handle_heredoc(cmd->in_red, heredoc_fd);
		}
	//	cmd->n_redirection--;
	//}
}

void handle_output_red(t_token *out_red)
{
    int fd;
    t_token *current;
	
	current = out_red;
    while (current->previous)
        current = current->previous;
    while (current)
	{
        if ((ft_strcmp(current->content, ">") != 0) && (ft_strcmp(current->content, ">>") != 0))
		{
            fd = open(current->content, O_CREAT | O_WRONLY | O_TRUNC, 0777);
            if (fd == -1)
			{
                perror("open");
                return;
            }
            if (current->next != NULL)
                close(fd);
        }
        current = current->next;
    }
    if (dup2(fd, STDOUT_FILENO) == -1)
	{
        perror("dup2");
        return;
    }
    close(fd);
}

void	handle_append_red(t_token *out_red)
{
	int	fd;
	t_token	*current;

	current = out_red;
	while (current->previous)
		current = current->previous;
	while (current)
	{
		if ((ft_strcmp(current->content, ">>") != 0) && (ft_strcmp(current->content, ">") != 0))
		{
			fd = open(current->content, O_WRONLY | O_CREAT | O_APPEND, 0777);
			if (fd == -1)
			{
				perror("open");
				return;
			}
			if (current->next != NULL)
        	    close(fd);
		}
		current = current->next;
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		return;
	}
	close(fd);
}

void	handle_input_red(t_token *in_red)
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
