/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomvan- <thomvan-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:20:25 by thomvan-          #+#    #+#             */
/*   Updated: 2024/10/20 17:21:38 by thomvan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char	*var_value(char *var)
{
	if (!var)
		return (NULL);
	while (*var != '=' && *var != '\0')
		var++;
	return (var);
}

t_token	*redirect_finder(t_token *t, t_cmd *c)
{
	while (t && t->type < PIPE)
	{
		if (((t->type == SMALLER || t->type == DOUBLE_SMALL)
				&& (t->next->type != GREATER
					&& t->next->type != DOUBLE_GREAT))
			|| (t && (t->type == GREATER
					|| t->type == DOUBLE_GREAT)
				&& (t->next->type != SMALLER
					&& t->next->type != DOUBLE_SMALL)))
		{
			if ((t->type == SMALLER || t->type == DOUBLE_SMALL)
				&& (t->next->type != GREATER
					&& t->next->type != DOUBLE_GREAT))
				t = (in_red(t, c));
			if (t && (t->type == GREATER || t->type == DOUBLE_GREAT)
				&& (t->next->type != SMALLER
					&& t->next->type != DOUBLE_SMALL))
				t = (out_red(t, c));
		}
		else
			t = t->next;
	}
	return (t);
}

t_token	*in_red(t_token *t, t_cmd *c)
{
	int	round;

	round = 2;
	while (round)
	{
		c->in_red = new_t_node(c->in_red);
		if (!c)
			return (NULL);
		if (t->type == PIPE || !t)
			c->in_red->content = NULL;
		else
		{
			c->in_red->content = ft_strdup(t->content);
			c->in_red->type = t->type;
			t = token_delete(t);
		}
		round--;
	}
	return (t);
}

t_token	*out_red(t_token *t, t_cmd *c)
{
	int	round;

	round = 2;
	while (round)
	{
		c->out_red = new_t_node(c->out_red);
		if (!c)
			return (NULL);
		if (t->type == PIPE || !t)
			c->out_red->content = NULL;
		else
		{
			c->out_red->content = ft_strdup(t->content);
			c->out_red->type = t->type;
			t = token_delete(t);
		}
		round--;
	}
	return (t);
}
