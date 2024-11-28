/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachou <rachou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:43:30 by rachou            #+#    #+#             */
/*   Updated: 2024/11/28 12:43:42 by rachou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

/*frees the token list*/

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
