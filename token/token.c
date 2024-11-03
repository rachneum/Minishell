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

/*int	main(int arc, char **arv, char **env)
{
	t_token *t;
	t_cmd	*c;
	int		i;
	t_all	*all;
	char	*str;
	

	all = (t_all *)malloc(sizeof(t_all));
	all->env = envellope(env);
	str = NULL;
	printf("He<<$SHELL |l\"omy  |'love'\"|baby||bubble <look >out >wow <gril \n");
	t = tokenizer("He<<$SHELL |l\"omy  |'love'\"|baby||bubble <look >out >wow <gril", all);
	all->token = t;
	token_list_visualizer(all);
	t = all->token;
	c = parser(t);
	all->cmd = c;
	cmd_list_visualizer(all);
	total_free(all);
}*/

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
		return (NULL);
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
		return (NULL);
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
		if (s[i] == '$' && var_pfetch(all->env, s + i) && !simple_quoted(s, i)
			&& s[i + 1] != '?')
		{
			tmp = var_pfetch(all->env, s + i);
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
