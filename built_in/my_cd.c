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
	{
		tmp = strncpy(tmp, "PWD=", 4);
		ft_strlcat(tmp, cwd, ft_strlen(cwd) + 5);
		free(cpy->var);
		cpy->var = tmp;
	}
}
