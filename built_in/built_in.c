/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 04:11:24 by marvin            #+#    #+#             */
/*   Updated: 2024/10/10 04:11:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	my_pwd(t_all *all)
{
	char		*wd;
	t_env_list	*cpy;

	cpy = all->env;
	if (all->cmd->cmd[1])
	{
		printf("Too many arguments !\n");
		exit (1);
		return (1);
	}
	wd = NULL;
	wd = var_fetch(cpy, "PWD");
	if (!wd)
	{
		printf("var doesn't exist\n");
		exit (1);
	}
	printf("%s\n", wd);
	return (0);
}

void	my_echo(char **arg)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (!arg[1])
	{
		printf("\n");
		return ;
	}
	if (!ft_strncmp(arg[i], "-n", 2))
		flag = 1;
	while (arg[i + flag] != NULL)
	{
		printf("%s", arg[i + flag]);
		i++;
		if (arg[i + flag] != NULL && arg[i + flag][0])
			printf(" ");
	}
	if (!flag)
		printf("\n");
}

void	my_env(t_cmd *cmd, t_all *all)
{
	t_env_list	*current;

	current = all->env;
	if (cmd->cmd[1])
	{
		printf("Too many arguments !\n");
		exit (1);
		return ;
	}
	while (current)
	{
		if (current->var[0] != '_' && has_equal(current->var))
			printf("%s\n", current->var);
		current = current->next;
	}
	printf("_=/usr/bin/env\n");
}

t_env_list	*env_rewinder(t_env_list *e)
{
	while (e->previous != NULL)
		e = e->previous;
	return (e);
}
