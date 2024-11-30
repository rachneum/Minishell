/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachou <rachou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 17:56:11 by rachou            #+#    #+#             */
/*   Updated: 2024/11/30 17:56:55 by rachou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

static t_cmd	*cmd_node_pipe_short(t_all *all, t_cmd *cmd_l, int *i)
{
	all->token = all->token->next;
	cmd_l->cmd[*i] = NULL;
	cmd_l = new_c_node(cmd_l, all->token);
	if (!cmd_l)
		return (g_err_global = 1, NULL);
	*i = 0;
	return (cmd_l);
}

static t_all	*cmd_part2(t_all *all, t_token *leftover, int *i, t_cmd *cmd_l)
{
	all->token = redirect_finder(all->token, cmd_l);
	if (!all->token)
		return (NULL);
	if (all->token && all->token->type > PIPE
		&& (!all->token->previous || all->token->previous->type > 4))
		leftover = all->token;
	if (all->token->type != PIPE)
		cmd_l->cmd[(*i)++] = all->token->content;
	return (all);
}

static t_all	*cmd_part1(t_all *all, t_token *leftover, int *i, t_cmd *cmd_l)
{
	while (all->token && all->token->next != NULL)
	{
		if (all->token->type != PIPE)
			if (!cmd_part2(all, leftover, i, cmd_l))
				return (all);
		if (all->token->type != PIPE && all->token->next)
			all->token = all->token->next;
		if (all->token && all->token->type == PIPE)
			cmd_l = cmd_node_pipe_short(all, cmd_l, i);
	}
	cmd_l->cmd[*i] = NULL;
	if (all->token && all->token->type != PIPE)
	{
		cmd_l->cmd[(*i)++] = all->token->content;
		cmd_l->cmd[*i] = NULL;
	}
	if (leftover)
		all->token = leftover;
	return (all);
}

t_cmd	*cmd_node(t_all *all, t_cmd *cmd_l)
{
	int		i;
	t_cmd	*first;
	t_token	*leftover;

	i = 0;
	cmd_l->cmd = malloc(sizeof(char *) * (word_count(all->token) + 1));
	leftover = NULL;
	if (!cmd_l->cmd)
		return (g_err_global = 1, NULL);
	first = cmd_l;
	all = cmd_part1(all, leftover, &i, cmd_l);
	return (first);
}
