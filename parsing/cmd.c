/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomvan- <thomvan-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:41:47 by thomvan-          #+#    #+#             */
/*   Updated: 2024/12/03 20:41:38 by thomvan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

static t_cmd	*cmd_node_pipe_short(t_all *all, t_cmd *cmd_l, int *i)
{
	all->token = all->token->next;
	cmd_l->cmd[*i] = NULL;
	cmd_l = new_c_node(cmd_l, all->token);
	if (!cmd_l)
		return (NULL);
	*i = 0;
	return (cmd_l);
}

static t_cmd	*cmd_part1(t_all *all, int *i, t_token **left, t_cmd *cmd)
{
	while (all->token && all->token->next != NULL)
	{
		if (all->token->type != PIPE)
		{
			all->token = redirect_finder(all->token, cmd);
			if (!all->token)
				break ;
			if (all->token && all->token->type > PIPE && (!all->token->previous
					|| all->token->previous->type > DOUBLE_GREAT))
				*left = all->token;
			if (all->token->type != PIPE)
				cmd->cmd[(*i)++] = all->token->content;
		}
		if (all->token->type != PIPE && all->token->next)
			all->token = all->token->next;
		if (all->token && all->token->type == PIPE)
			cmd = cmd_node_pipe_short(all, cmd, i);
	}
	return (cmd);
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
		return (NULL);
	first = cmd_l;
	cmd_l = cmd_part1(all, &i, &leftover, cmd_l);
	cmd_l->cmd[i] = NULL;
	if (all->token && all->token->type != PIPE)
	{
		cmd_l->cmd[i++] = all->token->content;
		cmd_l->cmd[i] = NULL;
	}
	if (leftover)
		all->token = leftover;
	return (first);
}

int	syntax_police(t_token *tok)
{
	t_token	*t;

	t = tok;
	if (!tok)
		return (0);
	while (t->previous != NULL)
		t = t->previous;
	while (t)
	{
		if ((t->type == SMALLER || t->type == DOUBLE_SMALL) && (!t->next
				|| (t->next->type == GREATER || t->next->type == DOUBLE_GREAT)))
			return (ft_putstr_fd("syntax error\n", 2), g_err_global = 2, 1);
		if ((t->type == GREATER || t->type == DOUBLE_GREAT) && (!t->next
				|| t->next->type == SMALLER || t->next->type == DOUBLE_SMALL))
			return (ft_putstr_fd("syntax error\n", 2), g_err_global = 2, 1);
		if (t->type == PIPE && (!t->next || t->next->type == PIPE))
			return (ft_putstr_fd("syntax error\n", 2), g_err_global = 2, 1);
		t = t->next;
	}
	return (0);
}
