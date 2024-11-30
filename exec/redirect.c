/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachou <rachou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:54:18 by rachou            #+#    #+#             */
/*   Updated: 2024/11/30 16:55:26 by rachou           ###   ########.fr       */
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
		perror("OPEN ");
		exit (1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("DUP2 ");
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
