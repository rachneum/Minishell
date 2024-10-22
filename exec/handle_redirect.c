/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachou <rachou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 09:33:59 by rachou            #+#    #+#             */
/*   Updated: 2024/10/22 14:07:44 by rachou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char *handle_heredoc(char *delimiter)
{
    int tube[2];
    char    *line;
    char    *heredoc_content;
    size_t  content_size;
    size_t  line_len;
    pid_t   pid;

    heredoc_content = NULL;
    content_size = 0;
    if (pipe(tube) == -1)
    {
        perror("PIPE_HEREDOC");
        return (NULL);
    }
    while (1)
    {
        line = readline("> ");
        if (!line)//Gère EOF.
            break;
        if (strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }
        line_len = strlen(line);
        heredoc_content = realloc(heredoc_content, content_size + line_len + 2);//+2 pour \n et \0.
        if (!heredoc_content)
        {
            perror("REALLOC_HEREDOC");
            free(line);
            close(tube[0]);//Fermer le pipe vu que le heredoc est vide.
            close(tube[1]);
            return NULL;
        }
        memcpy(heredoc_content + content_size, line, line_len);
        content_size += line_len;
        heredoc_content[content_size++] = '\n';
        heredoc_content[content_size] = '\0';
        free(line);
    }
    if ((pid = fork()) == -1)
    {
        perror("FORK_HEREDOC");
        free(heredoc_content);
        close(tube[0]);
        close(tube[1]);
        return NULL;
    }
    if (pid == 0)//Processus enfant.
    {
        close(tube[0]);
        if (write(tube[1], heredoc_content, content_size) == -1)
        {
            perror("WRITE_HEREDOC");
            close(tube[1]);
            free(heredoc_content);
            exit(EXIT_FAILURE);
        }
        close(tube[1]);//Fermer l'écriture après avoir écrit.
        exit(EXIT_SUCCESS);//L'enfant se termine ici.
    }
    else//Processus parent.
    {
        close(tube[1]);//Fermer l'écriture dans le parent.
        if (dup2(tube[0], STDIN_FILENO) == -1)//Rediriger stdin vers le tube.
        {
            perror("DUP2_HEREDOC");
            free(heredoc_content);
            close(tube[0]);
            return NULL;
        }
        close(tube[0]);//Fermer la lecture après redirection.
        waitpid(pid, NULL, 0);//Attendre la fin du processus enfant.
    }

    return heredoc_content;//Ne libère que dans le parent après l'utilisation.
}
