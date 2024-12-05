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
	t_all	*cpy;

	cpy = all;
	if (!cpy->token)
		return;
	if (cpy->token->previous)
		printf("%p, %s\n", cpy->token->previous, cpy->token->previous->content);
	while (cpy->token->previous != NULL)//
		cpy->token = cpy->token->previous;
	first = cpy->token;
	printf("\nTOKEN LIST\n\n");
	while (cpy->token)
	{
		printf("%d. [\033[34m%s\033[0m] type = %d\n", cpy->token->index, cpy->token->content, cpy->token->type);
		cpy->token = cpy->token->next;
	}
	printf("\n");
	cpy->token = first;
}

void	cmd_list_visualizer(t_all *all)
{
	t_cmd	*first;
	int		i;
	t_all	*cpy;

	cpy = all;
	if (!cpy->cmd)
		return;
	while (cpy->cmd->previous != NULL)
		cpy->cmd = cpy->cmd->previous;
	first = cpy->cmd;
	printf("\nCOMMAND LIST\n\n");
	while (cpy->cmd)
	{
		i = -1;
		printf("[");
		while (cpy->cmd->cmd && cpy->cmd->cmd[++i])
		{
			printf("\033[34m%s\033[0m", cpy->cmd->cmd[i]);
			if (cpy->cmd->cmd && cpy->cmd->cmd[i + 1] && cpy->cmd->cmd[i + 1][0])
				printf(" ");
		}
		printf("] ");
		if (cpy->cmd->in_red)
		{
			while (cpy->cmd->in_red->previous)
				cpy->cmd->in_red = cpy->cmd->in_red->previous;
			printf("in_red :{");
			while (cpy->cmd->in_red)
			{
				printf("\033[31m%s\033[0m", cpy->cmd->in_red->content);
				if (cpy->cmd->in_red->next)
					printf(" ");
				cpy->cmd->in_red = cpy->cmd->in_red->next;
			}
			printf("} ");
		}
		if (cpy->cmd->out_red)
		{
			while (cpy->cmd->out_red->previous)
				cpy->cmd->out_red = cpy->cmd->out_red->previous;
			printf("out_red :{");
			while (cpy->cmd->out_red)
			{
				printf("\033[31m%s\033[0m", cpy->cmd->out_red->content);
				if (cpy->cmd->out_red->next)
					printf(" ");
				cpy->cmd->out_red = cpy->cmd->out_red->next;
			}
			printf("} ");
		}
		printf("\n");
		cpy->cmd = cpy->cmd->next;
	}
	printf("\n");
	cpy->cmd = first;
}