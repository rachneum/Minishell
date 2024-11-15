/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:07:24 by marvin            #+#    #+#             */
/*   Updated: 2024/09/13 15:07:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

t_env_list	*envellope(char **env)
{
	t_env_list	*envl;
	t_env_list	*first;
	int			i;

	envl = (t_env_list *)malloc(sizeof(t_env_list));
	if (!envl)
		return (NULL);
	i = 0;
	first = envl;
	while (env[i])
	{
		envl->var = env[i];
		i++;
		if (env[i])
			envl = new_node(envl);
		if (!envl)
			return (NULL);
	}
	return (first);
}

t_env_list	*new_node(t_env_list *l)
{
	t_env_list	*new;

	new = (t_env_list *)malloc(sizeof(t_env_list));
	if (!new)
		return (NULL);
	if (!l)
		return (new);
	l->next = new;
	new->next = NULL;
	return (new);
}

void	env_l_free(t_env_list *l)
{
	t_env_list	*tmp;

	while (l->next != NULL)
	{
		tmp = l->next;
		free(l);
		l = tmp;
	}
	free(l);
	return ;
}

char	*var_fetch(t_env_list *e, char *str)
{
	int	flag;

	flag = 0;
	while (e != NULL)
	{
		if (ft_strnstr(e->var, str, ft_strlen(str)))
		{
			flag = 1;
			break ;
		}
		e = e->next;
	}
	if (flag)
		return (e->var + (ft_strlen(str) + 1));
	return (NULL);
}

char	*var_pfetch(t_env_list *e, char *str)
{
	int	flag;
	int	i;

	flag = 0;
	i = ft_strlen("PATH");
	while (e != NULL)
	{
		if (!ft_strncmp(e->var, str, i))
		{
			flag = 1;
			break ;
		}
		e = e->next;
	}
	if (flag)
		return (e->var + (i + 1));
	return (NULL);
}
