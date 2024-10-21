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

void	redirect_finder(t_token *t, t_cmd *c)
{
	t_cmd	*first;
	int		in_flag;
	int		out_flag;

	c->n_redirection = 0;
	in_flag = 0;
	out_flag = 0;
	if ((t->type == SMALLER)
		&& t->next->type > PIPE && t->next)
		in_red(t, c);
	if ((t->type == GREATER || t->type == DOUBLE_GREAT)
		&& t->next->type > PIPE && t->next)
		out_red(t, c);
	return ;
}

void	in_red(t_token *t, t_cmd *c)
{
	int	round;

	round = 2;
	while (round)
	{
		c->in_red = new_t_node(c->in_red);
		c->in_red->content = ft_strdup(t->content);
		t = token_delete(t);
		round--;
	}
}

void	out_red(t_token *t, t_cmd *c)
{
	int	round;

	round = 2;
	while (round)
	{
		c->out_red = new_t_node(c->in_red);
		c->out_red->content = ft_strdup(t->content);
		t = token_delete(t);
		round--;
	}
}
