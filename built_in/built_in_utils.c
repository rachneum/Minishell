/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomvan- <thomvan-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:00:20 by thomvan-          #+#    #+#             */
/*   Updated: 2024/11/30 12:32:07 by thomvan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	update_equal(char *c, t_env_list *e)
{
	char	*tmp;

	tmp = get_name(NULL, c);
	while (ft_strncmp(e->var, tmp, ft_strlen(tmp)) != 0 && e->next)
		e = e->next;
	if (ft_strncmp(e->var, tmp, ft_strlen(tmp)) == 0)
	{
		free(e->var);
		e->var = ft_strdup(c);
	}
	else
	{
		e = new_node(e);
		e->var = ft_strdup(c);
	}
	free(tmp);
}

void	update_append(char *c, t_env_list *e)
{
	char	*tmp;
	char	*cpy;
	int		i;

	i = 0;
	tmp = get_name(NULL, c);
	while (ft_strncmp(e->var, tmp, ft_strlen(tmp)) != 0 && e->next)
		e = e->next;
	if (ft_strncmp(e->var, tmp, ft_strlen(tmp)) == 0 && has_equal(e->var))
	{
		cpy = e->var;
		e->var = ft_strjoin(e->var, get_value(e, c));
		free(cpy);
	}
	else if (!e->next || !has_equal(e->var))
	{
		if (ft_strncmp(e->var, tmp, ft_strlen(tmp)) != 0)
			e = new_node(e);
		cpy = ft_strjoin(tmp, "=");
		e->var = ft_strjoin(cpy, get_value(e, c));
		free(cpy);
	}
	free(tmp);
}

static void	stopper(t_env_list *e, char *str, int *i)
{
	*i = 0;
	if (!str)
	{
		while (e->var[*i] != '=' && e->var[*i])
		{
			if (e->var[*i] == '+' && e->var[(*i) + 1] == '=')
				break ;
			(*i)++;
		}
		return ;
	}
	else
	{
		while (str[*i] != '=' && str[*i])
		{
			if (str[*i] == '+' && str[(*i) + 1] == '=')
				break ;
			(*i)++;
		}
		return ;
	}
}

static char	*writer(char *name, t_env_list *e, int i, char *str)
{
	if (!str)
	{
		name = malloc(sizeof(char) * (i + 1));
		if (!name)
			return (g_err_global = 1, NULL);
		ft_strlcpy(name, e->var, i + 1);
	}
	else
	{
		name = malloc(sizeof(char) * (i + 1));
		if (!name)
			return (g_err_global = 1, NULL);
		ft_strlcpy(name, str, i + 1);
	}
	return (name);
}

char	*get_name(t_env_list *env, char *str)
{
	int		i;
	char	*name;

	if (!str)
	{
		stopper(env, NULL, &i);
		if (env->var[i] == '=' || (env->var[i] == '+'
				&& env->var[i + 1] == '='))
			return (writer(name, env, i, NULL));
		return (NULL);
	}
	else
	{
		stopper(NULL, str, &i);
		if (str[i] == '=' || (str[i] == '+' && str[i + 1] == '='))
			return (writer(name, NULL, i, str));
		return (NULL);
	}
}
