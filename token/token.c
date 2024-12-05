/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 13:10:50 by marvin            #+#    #+#             */
/*   Updated: 2024/09/14 13:10:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

t_token	*tokenizer(char	*input, t_all *all)
{
	char	**chop;
	t_token	*token_list;

	if (!input)
		return (NULL);
	input = spacer(input, all);
	chop = s_split(input, ' ');
	token_list = token_node(chop);
	if (token_list == NULL)
		return (g_err_global = 1, NULL);
	type_assign(token_list);
	all->token = token_list;
	free(input);
	free(chop);
	return (token_list);
}

/*adds the elements of the double array into the token list*/

t_token	*token_node(char **chopped)
{
	t_token	*tok;
	t_token	*first;
	int		i;

	if (!(*chopped))
		return (g_err_global = 1, NULL);
	tok = (t_token *)malloc(sizeof(t_token));
	if (!tok)
		return (g_err_global = 1, NULL);
	tok->previous = NULL;
	tok->next = NULL;
	i = 0;
	first = tok;
	while (chopped[i])
	{
		tok->content = chopped[i];
		tok->type = 0;
		tok->index = i;
		i++;
		if (chopped[i])
			tok = new_t_node(tok);
		if (!tok)
			return (g_err_global = 1, NULL);
	}
	return (first);
}

/*creates a new token node for the list*/

t_token	*new_t_node(t_token *l)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (g_err_global = 1, NULL);
	if (!l)
	{
		new->next = NULL;
		new->previous = NULL;
		return (new);
	}
	l->next = new;
	new->next = NULL;
	new->previous = l;
	return (new);
}

static void	spacer_short(char *sp, char *s, t_pair *p, t_all *all)
{
	char	*tmp;
	int		flag;
	char	*cpy;

	flag = 0;
	if (s[(p->i) + 1] == '?')
	{
		tmp = ft_itoa(g_err_global);
		cpy = tmp;
		flag = 1;
	}
	else
		tmp = var_pfetch(all->env, s + (p->i));
	while (tmp && *tmp)
		sp[(p->j)++] = *(tmp++);
	while (s[p->i] != ' ' && s[p->i] && s[p->i] != 34)
		(p->i)++;
	if (flag)
		free(cpy);
}

/*creates a new string with ' ' separating each elements for further splitting*/

char	*spacer(char *s, t_all *all)
{
	char	*spaced;
	t_pair	p;

	p.i = 0;
	p.j = 0;
	spaced = malloc(sizeof(char) * (size_count(s, all) + 1));
	while (s[p.i] && spaced)
	{
		if (s[p.i] == '$' && !simple_quoted(s, p.i))
			spacer_short(spaced, s, &p, all);
		if (sym_check(s + p.i) < GENERAL && !quoted(s, p.i))
			spacer_shortcut(spaced, s, &p.i, &p.j);
		else if (s[p.i])
			spaced[p.j++] = s[p.i++];
	}
	free(s);
	if (spaced)
		spaced[p.j] = '\0';
	else
		return (g_err_global = 1, NULL);
	return (spaced);
}
