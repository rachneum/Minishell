/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:02:12 by marvin            #+#    #+#             */
/*   Updated: 2024/09/24 14:02:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

static void	cmd_init(t_cmd *c)
{
	c->previous = NULL;
	c->next = NULL;
	c->in_red = NULL;
	c->out_red = NULL;
}

t_cmd	*parser(t_all *all)
{
	t_cmd	*command;
	int		how_many;
	int		pipes;

	if (!all->token)
		return (NULL);
	how_many = 0;
	command = (t_cmd *)malloc(sizeof(t_cmd));
	if (!command)
		return (NULL);
	cmd_init(command);
	command = cmd_node(all, command);
	return (command);
}

/*factorisation of next function (cmd_node)*/

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

/*creates cmd_nodes and fills them with the commands*/

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
	while (all->token && all->token->next != NULL)
	{
		if (all->token->type != PIPE)
		{
			all->token = redirect_finder(all->token, cmd_l);
			if (!all->token)
				break ;
			if (all->token && all->token->type > PIPE
				&& (!all->token->previous
					|| all->token->previous->type > DOUBLE_GREAT))
				leftover = all->token;
			if (all->token->type != PIPE)
				cmd_l->cmd[i++] = all->token->content;
		}
		if (all->token->type != PIPE && all->token->next)
			all->token = all->token->next;
		if (all->token && all->token->type == PIPE)
			cmd_l = cmd_node_pipe_short(all, cmd_l, &i);
	}
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

/*creates a new cmd_node and returns it*/

t_cmd	*new_c_node(t_cmd *c, t_token *t)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->cmd = malloc(sizeof(char *) * (word_count(t) + 1));
	if (!new->cmd)
		return (NULL);
	c->next = new;
	new->next = NULL;
	new->in_red = NULL;
	new->out_red = NULL;
	new->previous = c;
	return (new);
}
