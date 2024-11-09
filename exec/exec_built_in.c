/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachou <rachou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 09:53:47 by rachou            #+#    #+#             */
/*   Updated: 2024/11/09 08:54:57 by rachou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	handle_built_in(t_token *token, t_cmd *cmd, t_all *all)
{
	built_in_subshell(token, cmd, all);
	built_in_shell(token, cmd, all);
}

void	built_in_subshell(t_token *token, t_cmd *cmd, t_all *all)//Fork et apl fonction.
{
	t_token	*tok;
	pid_t	pid;

	tok = token;
	while (tok->previous)
		tok = tok->previous;
    while (tok)
    {
		/*if ((ft_strcmp(tok->content, "cd") == 0) && (ft_strlen(tok->content) == 2))
		{
			fork_built_in();
			if (pid == 0)
				my_cd(cmd->cmd, all);
		}
		if ((ft_strcmp(tok->content, "export") == 0) && (ft_strlen(tok->content) == 6))
		{
			fork_built_in();
			if (pid == 0)
				my_export(cmd, all);
		}
		else if ((ft_strcmp(tok->content, "unset") == 0) && (ft_strlen(tok->content) == 5))
		{
			fork_built_in();
			if (pid == 0)
				my_unset(all);
		}
		else if ((ft_strcmp(tok->content, "exit") == 0) && (ft_strlen(tok->content) == 4))
		{
			fork_built_in();
			if (pid == 0)
				my_exit();
		}*/
        printf("%s\n", tok->content);
        tok = tok->next;
    }
}

void	built_in_shell(t_token *token, t_cmd *cmd, t_all *all)//Fork, pipe si cmd->next != NULL, exec.
{
	t_token	*tok;
	pid_t	pid;

	tok = token;
	while (tok->previous)
		tok = tok->previous;
    while (tok)
	{
		//if ((ft_strcmp(tok->content, "echo") == 0) && (ft_strlen(tok->content) == 4))
		//	my_echo();
		//else if ((ft_strcmp(tok->content, "pwd") == 0) && (ft_strlen(tok->content) == 3))
		//	my_pwd(cmd);
		//else if ((ft_strcmp(tok->content, "env") == 0) && (ft_strlen(tok->content) == 3))
		//	my_env(cmd, all);
	}
}

pid_t	fork_built_in(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror("FORK");
	return (pid);
}

static void    exec_built_in()
{
    
}

