/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 02:27:26 by marvin            #+#    #+#             */
/*   Updated: 2024/10/21 02:27:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	cmd_l_free(t_cmd *c)
{
	t_cmd	*tmp;

	if (!c)
		return ;
	while (c->previous != NULL)
		c = c->previous;
	while (c->next != NULL)
	{
		token_l_free(c->in_red);
		token_l_free(c->out_red);
		free(c->cmd);
		tmp = c;
		c = c->next;
		free(tmp);
	}
	token_l_free(c->in_red);
	token_l_free(c->out_red);
	free(c->cmd);
	free(c);
}

/*counts the number of words before the next PIPE*/

int	word_count(t_token *t)
{
	int	i;

	i = 0;
	while (t->next != NULL && t->type != PIPE)
	{
		t = t->next;
		i++;
	}
	if (t->type != PIPE)
		i++;
	return (i);
}
