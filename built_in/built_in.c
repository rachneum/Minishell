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

int	my_pwd(t_cmd *cmd)
{
	char	*wd;

	(void)cmd;
	wd = NULL;
	wd = getcwd(wd, sizeof(size_t));
	printf("%s\n", wd);
	return (0);
}

/*void	my_echo(char **arg)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (arg[i] == ft_strncmp(arg[i], "-n", 2))
		flag = 1;
	while (arg[i + flag] != NULL)
	{
		printf("%s", arg[i]);
		i++;
		if (arg[i + flag] != NULL)
			printf("' '");
	}
	if (!flag)
		printf("\n");
}*/

void	my_env(t_cmd *cmd, t_all *all)
{
	//if (cmd->cmd[1])
	//	printf("too many arguments\n");
	while (all->env != NULL)
	{
		printf("%s\n", all->env->var);
		all->env = all->env->next;
	}
}
