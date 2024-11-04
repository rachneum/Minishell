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

/*pwd*/

void my_pwd(t_cmd *c)
{
    static char cwd[1024];
	if (c->cmd[1])
	{
		perror("pwd: too many arguments\n");
		return ;
	}
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf(stdout, "%s", cwd);
	else 
        perror("getcwd error");
}

/*echo*/

void	my_echo(char **arg)
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
}

/* cd */

void	my_cd(char **cmd, t_all *all)
{
	int			err;
	char*		tmp;
	static char	cwd[1024];	

	err = chdir(cmd[1]);
	if (err == -1)
		perror("chdir :");
	getcwd(cwd, sizeof(cwd));
	tmp = malloc(sizeof(char) * (ft_strlen(cwd) + 5));
	while (ft_strncmp(all->env->var, PWD, 3) != 0
		&& all->env != NULL)
		all->env = all->env->next;
	if (all->env)
	{
		tmp = strncpy(tmp, "PWD=", 4);
		ft_strlcat(tmp, cwd, ft_strlen(cwd + 4));
		free(all->env->var);
		all->env->var = tmp;
		return ;
	}
	free(tmp)
}

/*export*/

void	my_export(t_all *all,t_cmd *c)
{
	int	i;

	if (!c->cmd[1])
	{
		my_env(all, c);
		return ;
	}
	i = 1;
	while (all->env->next != NULL)
		all->env = all->env->next;
	while (all->c[i] != NULL && var_value(all->c[i]))
	{
		all->env = new_node(all->env);
		all->env->var = all->c[i];
		i++;
	}
	if (!var_value(all->c[i]))
		printf("syntax error");
}

/*env*/

void	my_env(t_all *all, t_cmd *cmd)
{
	if (cmd[1])
		return (printf("too many arguments\n"), );
	while (all->env != NULL)
	{
		printf("%s\n", all->env->var);
		all->env = all->env->next;
	}
}
