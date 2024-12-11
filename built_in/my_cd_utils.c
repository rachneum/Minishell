/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomvan- <thomvan-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:22:12 by thomvan-          #+#    #+#             */
/*   Updated: 2024/12/11 16:42:57 by thomvan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	cd_minus(t_all *all, char **cmd, int *flag, char *buff)
{
	char		*cpy;
	t_env_list	*e;

	e = env_rewinder(all->env);
	while (ft_strncmp(e->var, "OLDPWD=", 6) != 0)
		e = e->next;
	free(e->var);
	e->var = ft_strjoin("OLDPWD=", var_fetch(all->env, "PWD="));
	cmd[1] = buff;
	*flag = 1;
}
