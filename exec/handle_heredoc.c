/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachou <rachou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:57:54 by rachou            #+#    #+#             */
/*   Updated: 2024/11/27 20:15:46 by rachou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void handle_heredoc(t_token *in_red, int *heredoc_fd)
{
    char *input;
    char    *delimiter;
    t_token *current;
    int fd;//Fichier temporaire pour le Heredoc.
	
    //delimiter = in_red->content;
    current = in_red;
    while (current->previous)
    {
        current = current->previous;
    }
    if (!current)
        return ;
    while (1)
    {
        while (ft_strcmp(current->previous->content, "<<") == 0)
        {
            current = current->next;
        }
        printf("%p\n", current);
        delimiter = current->content;
        fd = open(".surprise.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1) 
	    {
            perror("open");
            return;
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
            printf("%s\n", current->content);
            if (current->next == NULL)
            {
                //if (ft_strcmp(current->next->content, "<<"))
                    ft_putendl_fd(input, fd);
            }
            free(input);
        }
        current = current->next;
    }
    close(fd);
    fd = open(".surprise.txt", O_RDONLY);
    /*if (current->next != NULL)
    {
        if (ft_strcmp(current->next->content, "<<"))
        {
            unlink(".surprise.txt"); // Supprime le fichier intermédiaire si ce n'est pas le dernier heredoc
            return;
        }
    }*/
    if (fd == -1)
	{
        perror("open");
        return;
    }
    *heredoc_fd = fd;
    unlink(".surprise.txt");
}

/*void handle_heredoc(t_token *in_red, int *heredoc_fd)
{
    char *input;
    char *delimiter;
    int fd;//Fichier temporaire pour le Heredoc.
	
    delimiter = in_red->content;
    printf ("%s\n", delimiter);
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
}*/
