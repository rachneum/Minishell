/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachou <rachou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:57:54 by rachou            #+#    #+#             */
/*   Updated: 2024/11/27 16:38:58 by rachou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void handle_heredoc(t_token *in_red, int *heredoc_fd)
{
    char *input;
    char *delimiter;
    int fd;//Fichier temporaire pour le Heredoc.
	
    delimiter = in_red->content;
    if (!delimiter)
        return;
    fd = open(".surprise.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) 
	{
        perror("open");
        return;
    }
    while (1) 
	{
        input = readline("> ");
        if (!input || ft_strcmp(input, delimiter) == 0) 
		{
            free(input);
            break;
        }
        ft_putendl_fd(input, fd);
        free(input);
    }
    close(fd);
    fd = open(".surprise.txt", O_RDONLY);
    if (fd == -1)
	{
        perror("open");
        return;
    }
    *heredoc_fd = fd;
    unlink(".surprise.txt");
}
