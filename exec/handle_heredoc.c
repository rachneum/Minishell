/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachou <rachou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:57:54 by rachou            #+#    #+#             */
/*   Updated: 2024/11/09 08:50:41 by rachou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void handle_heredoc(t_token *in_red, t_cmd *cmd) 
{
    int fd;
    char *input;
    t_token *delimiter;

	
    delimiter = in_red;
    //printf("Dernier délimiteur: %s\n", delimiter);
	while (delimiter->previous != NULL)
		delimiter = delimiter->previous;
	while (delimiter != NULL)
	{
		if (!delimiter)
        	return;
		if (cmd->n_redirection > 1)
		{
        	cmd->n_redirection--;//Ce n'est pas le dernier heredoc, on décrémente et on ignore.
        	return;
    	}
		else if (cmd->n_redirection == 1)
		{
			if (ft_strcmp(delimiter->content, "<<") != 0)
			{
    			fd = open(".surprise.txt", O_WRONLY | O_TRUNC | O_CREAT, 0777);
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
         			   	printf("EMPTY INPUT HEREDOC\n");
            			break;
        			}
					//printf("%s\n", delimiter->content);
        			if (strcmp(input, delimiter->content) == 0)
					{
            			free(input);
            			break;
        			}
       				ft_putendl_fd(input, fd);
    			}
    			close(fd);
    			fd = open(".surprise.txt", O_RDONLY);
    			if (fd == -1)
				{
        			perror("open");
        			return;
    			}
    			if (dup2(fd, 0) == -1)
				{
        			close(fd);
        			perror("dup2");
        			return;
    			}
    			close(fd);
    			unlink(".surprise.txt");//Supprime le fichier une fois fini.
			}
		}
		delimiter = delimiter->next;
	}
}
