/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachou <rachou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:57:54 by rachou            #+#    #+#             */
/*   Updated: 2024/11/29 18:23:19 by rachou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

static int	open_and_cleanup_heredoc_file(void)
{
	int	fd;
    
	fd = open(".surprise.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("OPEN ");
		return -1;
	}
	unlink(".surprise.txt");
	return (fd);
}

static int process_heredoc(t_token *current, int heredoc_count)
{
    char    *input;
    char    *delimiter;
    int     current_index;
    int     fd;

    current_index = 0;
    fd = -1;
    while (current)
    {
        if (ft_strcmp(current->content, "<<") == 0)
        {
            current_index++;
            delimiter = current->next->content;
            if (current_index == heredoc_count)
            {
                fd = open(".surprise.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
                if (fd == -1)
                {
                    perror("OPEN ");
                    return -1;
                }
            }
            while (1)
            {
                input = readline("> ");
                if (!input)
                {
                    free(input);
                    break;
                }
                if (ft_strcmp(input, delimiter) == 0)
                {
                    free(input);
                    break;
                }
                if (current_index == heredoc_count)
                    ft_putendl_fd(input, fd);
                free(input);
            }
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
	t_token *current;
	t_token *tmp;
	int heredoc_count;

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
	int fd = process_heredoc(current, heredoc_count);
	if (fd != -1)
		*heredoc_fd = fd;
}
