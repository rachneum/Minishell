/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomvan- <thomvan-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 14:24:19 by thomvan-          #+#    #+#             */
/*   Updated: 2024/10/08 15:51:39 by thomvan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	spacer_shortcut(char *spac, char *s, int *i, int *j)
{
	spac[(*j)++] = ' ';
	spac[(*j)++] = s[(*i)++];
	if (s[(*i) - 1] == s[(*i)] && sym_check(s + (*i)) < 3)
		spac[(*j)++] = s[(*i)++];
	spac[(*j)++] = ' ';
}

int	alone_quote(char *s, int index)
{
	int	i;

	i = 1;
	if (quoted(s, index))
	{
		while (s[index + i] == ' ' && s[index + i] != 34
			&& s[index + i])
			i++;
		if (s[index + i] == 34)
			return (1);
	}
	return (0);
}

int	is_c_digit(char c)
{
	if (c < 48 || c > 57)
		return (0);
	return (1);
}
