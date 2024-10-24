/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomvan- <thomvan-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 02:45:34 by marvin            #+#    #+#             */
/*   Updated: 2024/10/22 17:28:23 by thomvan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	token_list_visualizer(t_all *all)
{
	t_token *first;

	while (all->token->previous != NULL)
		all->token = all->token->previous;
	first = all->token;
	printf("\nTOKEN LIST\n\n");
	while (all->token)
	{
		printf("%d. [\033[34m%s\033[0m] type = %d\n", all->token->index, all->token->content, all->token->type);
		all->token = all->token->next;
	}
	printf("\n");
	all->token = first;
}

void	cmd_list_visualizer(t_all *all)
{
	t_cmd	*first;
	int		i;

	while (all->cmd->previous != NULL)
		all->cmd = all->cmd->previous;
	first = all->cmd;
	printf("\nCOMMAND LIST\n\n");
	while (all->cmd)
	{
		i = -1;
		printf("[");
		while (all->cmd->cmd && all->cmd->cmd[++i])
		{
			printf("\033[34m%s\033[0m", all->cmd->cmd[i]);
			if (all->cmd->cmd && all->cmd->cmd[i + 1])
				printf(" ");
		}
		printf("] ");
		if (all->cmd->in_red)
		{
			while (all->cmd->in_red->previous)
				all->cmd->in_red = all->cmd->in_red->previous;
			printf("in_red :{");
			while (all->cmd->in_red)
			{
				printf("\033[31m%s\033[0m", all->cmd->in_red->content);
				if (all->cmd->in_red->next)
					printf(" ");
				all->cmd->in_red = all->cmd->in_red->next;
			}
			printf("} ");
		}
		if (all->cmd->out_red)
		{
			while (all->cmd->out_red->previous)
				all->cmd->out_red = all->cmd->out_red->previous;
			printf("out_red :{");
			while (all->cmd->out_red)
			{
				printf("\033[31m%s\033[0m", all->cmd->out_red->content);
				if (all->cmd->out_red->next)
					printf(" ");
				all->cmd->out_red = all->cmd->out_red->next;
			}
			printf("} ");
		}
		printf("n_redirections = %d\n", all->cmd->n_redirection);
		all->cmd = all->cmd->next;
	}
	printf("\n");
	all->cmd = first;
}