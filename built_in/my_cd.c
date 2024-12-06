/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/10/10 16:54:44 by marvin            #+#    #+#             */
/*   Updated: 2024/10/10 16:54:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

static char	*new_empty_string(char *cwd)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = malloc(sizeof(char) * (ft_strlen(cwd) + 5));
	if (!tmp)
		return (g_err_global = 1, NULL);
	while (i < (ft_strlen(cwd) + 5))
		tmp[i++] = '\0';
	return (tmp);
}

static void	cd_short(char *tmp, char *cwd, t_env_list *cpy)
{
	tmp = strncpy(tmp, "PWD=", 4);
	ft_strlcat(tmp, cwd, ft_strlen(cwd) + 5);
	free(cpy->var);
	cpy->var = tmp;
}

static void	old_pwd_update(t_all *all)
{
	t_env_list	*old;
	t_env_list	*pwd;

	old = env_rewinder(all->env);
	pwd = old;
	while (old && ft_strncmp(old->var, "OLDPWD=", 7) != 0)
		old = old->next;
	while (pwd && ft_strncmp(pwd->var, "PWD=", 4) != 0)
		pwd = pwd->next;
	if (ft_strncmp(old->var, "OLDPWD=", 7) == 0
		&& ft_strncmp(pwd->var, "PWD=", 4) == 0)
	{
		free(old->var);
		old->var = ft_strjoin("OLDPWD=", var_fetch(pwd, "PWD="));
	}
}

int	my_cd(char **cmd, t_all *all)
{
	int			err;
	char		*tmp;
	t_env_list	*cpy;
	static char	cwd[1024];

	cpy = all->env;
	if (!cmd[1])
		return (printf("please insert path\n"), g_err_global = 1, 1);
	else
		err = chdir(cmd[1]);
	if (err == -1)
		return (printf("No such file or directory\n"), g_err_global = 1, 1);
	getcwd(cwd, sizeof(cwd));
	tmp = new_empty_string(cwd);
	if (!tmp)
		return (printf("malloc error\n"), g_err_global = 1, 1);
	while (ft_strncmp(cpy->var, "PWD", 3) != 0 && cpy != NULL)
		cpy = cpy->next;
	if (cpy)
		cd_short(tmp, cwd, cpy);
}
