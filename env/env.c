/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachou <rachou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 17:50:00 by rachou            #+#    #+#             */
/*   Updated: 2024/11/30 17:50:06 by rachou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

t_env_list	*envellope(char **env)
{
	t_env_list	*envl;
	t_env_list	*first;
	int			i;

	envl = (t_env_list *)malloc(sizeof(t_env_list));
	if (!envl)
		return (g_err_global = 1, NULL);
	i = 0;
	first = envl;
	envl->previous = NULL;
	while (env[i])
	{
		envl->var = ft_strdup(env[i]);
		i++;
		if (env[i])
			envl = new_node(envl);
		if (!envl)
			return (g_err_global = 1, NULL);
	}
	return (first);
}

t_env_list	*new_node(t_env_list *l)
{
	t_env_list	*new;

	new = (t_env_list *)malloc(sizeof(t_env_list));
	if (!new)
		return (g_err_global = 1, NULL);
	if (!l)
		return (new);
	l->next = new;
	new->previous = l;
	new->next = NULL;
	return (new);
}

void	env_l_free(t_env_list *l)
{
	t_env_list	*tmp;

	while (l->previous != NULL)
		l = l->previous;
	while (l->next != NULL)
	{
		tmp = l->next;
		free(l->var);
		free(l);
		l = tmp;
	}
	free(l->var);
	free(l);
	return ;
}

char	*var_fetch(t_env_list *e, char *str)
{
	int	flag;

	flag = 0;
	e = env_rewinder(e);
	while (e != NULL)
	{
		if (ft_strncmp(e->var, str, ft_strlen(str)) == 0)
		{
			flag = 1;
			break ;
		}
		e = e->next;
	}
	if (flag)
		return (e->var);
	return (NULL);
}

char	*var_bfetch(t_env_list *e, char *str)
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
