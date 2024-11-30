/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:58:55 by marvin            #+#    #+#             */
/*   Updated: 2024/09/20 16:58:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	total_free(t_all *all)
{
	token_l_free(all->token);
	cmd_l_free(all->cmd);
	env_l_free(all->env);
	free(all);
	return ;
}

t_token	*token_delete(t_token *t)
{
	t_token	*tmp;

	if (!t)
		return (NULL);
	if (t->next == NULL && t->previous == NULL)
		return (token_free(t), NULL);
	else if (t->previous == NULL)
	{
		tmp = t->next;
		tmp->previous = NULL;
		return (token_free(t), tmp);
	}
	else if (t->next == NULL)
	{
		tmp = t->previous;
		tmp->next = NULL;
		return (token_free(t), NULL);
	}
	else
	{
		tmp = t->next;
		t->previous->next = tmp;
		tmp->previous = t->previous;
		return (token_free(t), tmp);
	}
}

void	token_free(t_token *t)
{
	free(t->content);
	free(t);
	return ;
}

int	not_a_split(char *s, char sep, int index)
{
	if (quoted(s, index) || s[index] != sep)
		return (1);
	else
		return (0);
}

int	simple_quoted(char *s, int index)
{
	int	i;
	int	squotes_open;
	int	squotes_closed;
	int	quote;

	i = 0;
	squotes_open = 0;
	squotes_closed = 0;
	while (s[i])
	{
		if ((s[i] == 39 && ft_strchr(s + (i + 1), 39)))
		{
			quote = s[i];
			squotes_open = i++;
			while (s[i] != quote)
				i++;
			squotes_closed = i;
		}
		if (index < squotes_closed && index > squotes_open)
			return (1);
		squotes_closed = 0;
		i++;
	}
	return (0);
}
