/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachou <rachou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:25:25 by rachou            #+#    #+#             */
/*   Updated: 2024/10/10 13:25:34 by rachou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

/*indentifies the special character*/

int	sym_check(char *input)
{
	int	i;

	i = 0;
	if (input[i] == '<' && input[i + 1] == '<')
		return (4);
	if (input[i] == '>' && input[i + 1] == '>')
		return (5);
	if (input[i] == '<')
		return (1);
	if (input[i] == '>')
		return (2);
	if (input[i] == '|')
		return (3);
	return (6);
}

/*detects if the character is between quotes or double-quotes*/

int	quoted(char *s, int index)
{
	int	i;
	int	dquotes_open;
	int	dquotes_closed;
	int	quote;

	i = 0;
	dquotes_open = 0;
	dquotes_closed = 0;
	while (s[i])
	{
		if ((s[i] == 34 && ft_strchr(s + (i + 1), 34))
			|| (s[i] == 39 && ft_strchr(s + (i + 1), 39)))
		{
			quote = s[i];
			dquotes_open = i++;
			while (s[i] != quote)
				i++;
			dquotes_closed = i;
		}
		if (index < dquotes_closed && index > dquotes_open)
			return (1);
		dquotes_closed = 0;
		i++;
	}
	return (0);
}

/*copies the string without the quotes*/

static char	*no_quote_cpy(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[i])
	{
		if ((src[i] != 34 && src[i] != 39) || quoted(src, i))
			dest[j++] = src[i];
		i++;
	}
	dest[j] = '\0';
	free(src);
	return (dest);
}

static char	*no_quote_node(char *s)
{
	int		i;
	int		j;
	char	*tmp;
	int		flag;

	i = -1;
	j = 0;
	flag = 0;
	while (s[++i])
	{
		if ((s[i] != 34 && s[i] != 39) || quoted(s, i))
			j++;
		if (((s[i] == 34 || s[i] == 39) && !quoted(s, i))
			&& ft_strchr(s + (i + 1), s[i]))
			flag = 1;
	}
	if (flag)
	{
		tmp = malloc(sizeof(char) * (j + 1));
		if (!s)
			return (NULL);
		s = no_quote_cpy(tmp, s);
	}
	return (s);
}

/*replaces the tokens with their version without quotes*/

void	quote_erase(t_token *l)
{
	int		i;
	int		j;
	char	*s;

	while (l->previous != NULL)
		l = l->previous;
	while (l->next != NULL)
	{
		l->content = no_quote_node(l->content);
		l = l->next;
	}
	l->content = no_quote_node(l->content);
}
