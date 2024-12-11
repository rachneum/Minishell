/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomvan- <thomvan-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:44:22 by thomvan-          #+#    #+#             */
/*   Updated: 2024/11/27 18:52:55 by thomvan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	token_l_free(t_token *t)
{
	t_token	*tmp;

	if (!t)
		return ;
	while (t->previous != NULL)
		t = t->previous;
	while (t->next != NULL)
	{
		tmp = t->next;
		free(t->content);
		free(t);
		t = tmp;
	}
	free(t->content);
	free(t);
	return ;
}
