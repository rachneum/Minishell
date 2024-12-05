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
	c->n_redirection = 0;
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
