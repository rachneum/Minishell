/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raneuman <raneuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:57:54 by rachou            #+#    #+#             */
/*   Updated: 2024/12/01 11:56:24 by raneuman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"


static int	open_and_cleanup_heredoc_file(void)
{
	int	fd;

	fd = open(".surprise.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("open ");
		g_err_global = 1;
		return (-1);
	}
	unlink(".surprise.txt");
	return (fd);
}

static void	prompt_heredoc(t_token *current, int heredoc_count, int i, int fd)
{
	while (1)
	{
		current->input = readline("> ");
		if (!current->input || !ft_strcmp(current->input, current->delimiter))
		{
			free(current->input);
			break ;
		}
		if (i == heredoc_count)
			ft_putendl_fd(current->input, fd);
		free(current->input);
	}
}

static int	open_file(void)
{
	int	fd;

	fd = open(".surprise.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open ");
		g_err_global = 1;
		return (-1);
	}
	return (fd);
}

static int	process_heredoc(t_token *current, int heredoc_count, int fd, int i)
{
	while (current)
	{
		if (ft_strcmp(current->content, "<<") == 0)
		{
			i++;
			current->delimiter = current->next->content;
			if (i == heredoc_count)
			{
				fd = open_file();
				if (fd == -1)
					break ;
			}
			prompt_heredoc(current, heredoc_count, i, fd);
		}
		current = current->next;
	}
	if (fd != -1)
	{
		close(fd);
		fd = open_and_cleanup_heredoc_file();
	}
	return (fd);
}

void	handle_heredoc(t_token *in_red, int *heredoc_fd)
{
	t_token	*current;
	t_token	*tmp;
	int		heredoc_count;
	int		fd;

	fd = -1;
	current = in_red;
	heredoc_count = 0;
	while (current->previous)
		current = current->previous;
	tmp = current;
	while (tmp)
	{
		if (ft_strcmp(tmp->content, "<<") == 0)
			heredoc_count++;
		tmp = tmp->next;
	}
	fd = process_heredoc(current, heredoc_count, fd, 0);
	if (fd != -1)
		*heredoc_fd = fd;
}
