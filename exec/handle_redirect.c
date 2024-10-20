/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachou <rachou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 09:33:59 by rachou            #+#    #+#             */
/*   Updated: 2024/10/20 09:44:15 by rachou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.c"

/*void	handle_redirections(t_cmd *cmd)
{

}

void	handle_heredoc(char *delimiter)//Lit l'entrée utilisateur jusqu'à ce que le délimiteur spécifié soit rencontré, puis redirige cette entrée vers l'entrée standard (stdin) via un tube (pipe).
{
    int tube[2];
    char *line;

    if (pipe(tube) == -1)
        perror("pipe");
    while (1)
	{
        line = readline("> ");
        if (ft_strcmp(line, delimiter) == 0) {
            free(line);
            break;
        }
        write(tube[1], line, ft_strlen(line));
        write(tube[1], "\n", 1);
        free(line);
    }
    close(tube[1]);
    dup2(tube[0], STDIN_FILENO); //Remplace l'entrée standard par le contenu du heredoc.
    close(tube[0]);
}*/
