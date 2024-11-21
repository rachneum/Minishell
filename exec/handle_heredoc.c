/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachou <rachou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:57:54 by rachou            #+#    #+#             */
/*   Updated: 2024/11/20 23:23:22 by rachou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	handle_heredoc(t_token *in_red)
{
	int		fd;
	char	*input;
	char	*delimiter;

    delimiter = in_red->content;
	//printf("Délimiteur: %s\n", delimiter);
	//printf("Heredoc: %s\n", in_red->previous->content);
	if (!delimiter)
		return ;
	fd = open(".surprise.txt", O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (fd == -1)
	{
		perror("open");
		return;
	}
	while(1)
	{
		input = readline("> ");
		if (!input)
		{
			printf("EMPTY INPUT HEREDOC\n");
			break;
		}
		if (ft_strcmp(input, delimiter) == 0)
		{
	    	free(input);
	    	break ;
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
	unlink(".surprise.txt");//Suprime mon fichier une fois fini.
}
