/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachou <rachou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 09:33:59 by rachou            #+#    #+#             */
/*   Updated: 2024/10/31 14:19:10 by rachou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

static int ft_strcmp(char *str1, char *str2)
{
    int i;

	i = 0;
    while (str1[i] != '\0' && str2[i] != '\0')
    {
        if (str1[i] != str2[i])
        {
            return (str1[i] - str2[i]);
        }
        i++;
    }
    return (str1[i] - str2[i]);
}


static void	handle_output_red(t_token *out_red)
{
	int	fd;
	
	t_token	*current;

	current = out_red;
	fd = open(out_red->content, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (fd == -1)
	{
		perror("open");
		return;
	}
	printf ("WESH");
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		return;
	}
	close(fd);
	printf ("HHEHO");
}

static void	handle_append_red(t_token *out_red)
{
	int	fd;

	fd = open(out_red->content, O_WRONLY | O_CREAT | O_APPEND, 0777);
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
	char	*delimiter;

	
    delimiter = in_red->content;
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

void	handle_redirections(t_cmd *cmd)
{
	int	fd;
	
	while (cmd->n_redirection > 0)
	{
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
				handle_heredoc(cmd->in_red);
		}
		cmd->n_redirection--;
	}
}
