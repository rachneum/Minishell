/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:54:44 by marvin            #+#    #+#             */
/*   Updated: 2024/10/10 16:54:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	my_unset(t_all *all)
{
	if (all->cmd[2])
		return (printf("syntax error", ));
	while (strncmp(all->env->var, all->cmd[1], ft_strlen(all->cmd[1])) != 0
		&& all->env != NULL)
		all->env = all->env->next;
	if (all->env != NULL)
		all->env = env_node_delete(all->env);
}

void	env_n_free(t_env_list *t)
{
	free(t->var);
	free(t);
	return ;
}

t_env_list	*env_node_delete(t_env_list *env)
{
	t_env_list	*tmp;

	if (env->next == NULL && env->previous == NULL)
		return (env_n_free(t), NULL);
	else if (env->previous == NULL)
	{
		tmp = env->next;
		tmp->previous = NULL;
		return (env_n_free(t), tmp);
	}
	else if (env->next == NULL)
	{
		tmp = env->previous;
		env_n_free(t);
		tmp->next = NULL;
		return (NULL);
	}
	else
	{
		tmp = env->next;
		env->previous->next = tmp;
		tmp->previous = env->previous;
		return (env_n_free(t), tmp);
	}
}
