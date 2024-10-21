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

	while (c->previous != NULL)
		c = c->previous;
	while (c->next != NULL)
	{
		if (c->in_red)
			token_l_free(c->in_red);
		if (c->out_red)
			token_l_free(c->out_red);
		//if (c->cmd);
			free(c->cmd);
		tmp = c;
		c = c->next;
		free(tmp);
	}
	if (c->in_red)
		free(c->in_red);
	if (c->out_red)
		free(c->out_red);
	free(c->cmd);
	free(c);
	// c->cmd = 0;
	// c->next = 0;
	// c->previous = 0;
	// system("leaks minishell");
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
