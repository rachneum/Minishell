/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachou <rachou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:26:22 by rachou            #+#    #+#             */
/*   Updated: 2024/10/10 15:43:30 by rachou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

//Still need to implement $ handling

t_token	*tokenizer(char	*input, t_all *all)
{
	char	**chop;
	t_token	*token_list;

	input = spacer(input, all);
	chop = s_split(input, ' ');
	token_list = token_node(chop);
	if (token_list == NULL)
		return (NULL);
	type_assign(token_list);
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

	tok = (t_token *)malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
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
			return (NULL);
	}
	return (first);
}

/*creates a new token node for the list*/

t_token	*new_t_node(t_token *l)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
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

/*creates a new string with ' ' separating each elements for further splitting*/

char	*spacer(char *s, t_all *all)
{
	char	*spaced;
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	spaced = malloc(sizeof(char) * (size_count(s, all) + 1));
	while (s[i] && spaced)
	{
		if (s[i] == '$' && var_pfetch(all->env, s + i) && !simple_quoted(s, i))
		{
			tmp = var_pfetch(all->env, s + i);
			spaced[j++] = ' ';
			while (*tmp)
				spaced[j++] = *(tmp++);
			while (s[i] != ' ')
				i++;
		}
		if (sym_check(s + i) < GENERAL && !quoted(s, i))
			spacer_shortcut(spaced, s, &i, &j);
		else
			spaced[j++] = s[i++];
	}
	//free(s);
	if (spaced)
		spaced[j] = '\0';
	return (spaced);
}

/*frees the token list*/

void	token_l_free(t_token *t)
{
	t_token	*tmp;

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
