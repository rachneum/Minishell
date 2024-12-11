/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomvan- <thomvan-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:33:43 by thomvan-          #+#    #+#             */
/*   Updated: 2024/12/05 00:38:29 by thomvan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

static void	swapper(t_env_list *a, t_env_list *b)
{
	char	*tmp;

	tmp = a->var;
	a->var = b->var;
	b->var = tmp;
}

t_env_list	*env_sort_cpy(t_env_list *env)
{
	t_env_list	*sorted;
	t_env_list	*sort_cpy;
	t_env_list	*first;
	char		*tmp;
	int			i;

	i = 0;
	sorted = env_cpy(env);
	if (!sorted)
		return (NULL);
	first = sorted;
	while (sorted)
	{
		sort_cpy = first;
		while (sort_cpy)
		{
			if (ft_strncmp(sorted->var, sort_cpy->var, 5) < 0)
				swapper(sorted, sort_cpy);
			sort_cpy = sort_cpy->next;
		}
		sorted = sorted->next;
	}
	return (first);
}

t_env_list	*env_cpy(t_env_list *env)
{
	t_env_list	*envl;
	t_env_list	*first;
	t_env_list	*cpy;

	cpy = env_rewinder(env);
	envl = (t_env_list *)malloc(sizeof(t_env_list));
	if (!envl)
		return (g_err_global = 1, NULL);
	first = envl;
	envl->previous = NULL;
	while (cpy)
	{
		envl->var = ft_strdup(cpy->var);
		cpy = cpy->next;
		if (!cpy)
			break ;
		envl = new_node(envl);
		if (!envl)
			return (g_err_global = 1, NULL);
	}
	return (first);
}

char	*get_value(t_env_list *env, char *str)
{
	int	i;

	if (!str)
	{
		i = 0;
		while (env->var[i] != '=' && env->var[i])
			i++;
		return (env->var + i + 1);
	}
	else
	{
		i = 0;
		while (str[i] != '=' && str[i])
			i++;
		return (str + i + 1);
	}
}
