/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:37:46 by marvin            #+#    #+#             */
/*   Updated: 2024/11/28 11:37:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

static void	env_n_free(t_env_list *t)
{
	free(t->var);
	free(t);
	return ;
}

static t_env_list	*del_first_node(t_env_list *e)
{
	t_env_list	*tmp;

	tmp = e->next;
	env_n_free(e);
	tmp->previous = NULL;
	return (tmp);
}

static t_env_list	*env_node_delete(t_env_list *env)
{
	t_env_list	*tmp;

	if (!env)
		return (NULL);
	if (env->next == NULL && env->previous == NULL)
		return (env_n_free(env), NULL);
	else if (env->previous == NULL)
		return (del_first_node(env));
	else if (env->next == NULL)
	{
		tmp = env->previous;
		env_n_free(env);
		tmp->next = NULL;
		return (tmp);
	}
	else
	{
		tmp = env->next;
		env->previous->next = tmp;
		tmp->previous = env->previous;
		return (env_n_free(env), tmp);
	}
}

void	my_unset(t_all *all)
{
	char		*tmp;
	t_env_list	*e;
	int			i;

	i = 1;
	e = all->env;
	while (all->cmd->cmd[i])
	{
		e = env_rewinder(e);
		if (has_equal(all->cmd->cmd[i]))
			tmp = ft_strjoin(all->cmd->cmd[i], "=");
		else
			tmp = all->cmd->cmd[i];
		while (strncmp(e->var, tmp, ft_strlen(all->cmd->cmd[i]) + 1) != 0
			&& e->next != NULL)
			e = e->next;
		if (strncmp(e->var, tmp, ft_strlen(all->cmd->cmd[i]) + 1) == 0)
			e = env_node_delete(e);
		if (has_equal(all->cmd->cmd[i]))
			free(tmp);
		i++;
	}
}
