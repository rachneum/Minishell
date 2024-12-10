/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomvan- <thomvan-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 21:42:19 by thomvan-          #+#    #+#             */
/*   Updated: 2024/12/08 13:26:01 by thomvan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

static char	*var_maker(char *var, int i, char *str)
{
	var = malloc(sizeof(char) * (i + 2));
	if (!var)
		return (printf("malloc error\n"), g_err_global = 1, NULL);
	ft_strlcpy(var, str + 1, i + 1);
	ft_strlcat(var, "=", ft_strlen(var) + 2);
	return (var);
}

char	*var_pfetch(t_env_list *e, char *str)
{
	int			flag;
	int			i;
	t_env_list	*cpy;
	char		*var;

	flag = 0;
	i = 0;
	cpy = env_rewinder(e);
	while (str[i + 1] != ' ' && str[i + 1] != 34 && str[i + 1] != '\0'
		&& sym_check(str + i + 1) == 6)
		i++;
	var = var_maker(var, i, str);
	if (!var)
		return (g_err_global = 1, NULL);
	while (cpy != NULL)
	{
		if (ft_strncmp(cpy->var, var, i + 1) == 0)
		{
			flag = 1;
			break ;
		}
		cpy = cpy->next;
	}
	if (flag)
		return (free(var), cpy->var + (i + 1));
	return (free(var), NULL);
}

char	*increment_shlvl(t_env_list *envl, char *var)
{
	int		i;
	char	*s;
	char	*tmp;
	int		j;

	i = 0;
	s = NULL;
	while (var[i] != '=' && var[i])
		i++;
	if (var[i] == '=')
	{
		j = ft_atoi(var + i + 1) + 1;
		tmp = ft_itoa(j);
		s = ft_strjoin("SHLVL=", tmp);
		free(tmp);
	}
	return (s);
}

t_env_list	*env_empty(t_env_list *e)
{
	char	*cwd;
	char	*tmp;

	cwd = malloc(sizeof(char) * 1024);
	e->previous = NULL;
	getcwd(cwd, 1024);
	e->var = ft_strdup("OLDPWD=");
	e = new_node(e);
	e->var = ft_strjoin("PWD=", cwd);
	e = new_node(e);
	e->var = ft_strdup("SHLVL=1");
	e = new_node(e);
	tmp = ft_strjoin("_=", cwd);
	e->var = ft_strjoin(tmp, "/./minishell");
	e = new_node(e);
	e->var = ft_calloc(142, sizeof(char));
	ft_strlcat(e->var, "PATH=", 6);
	ft_strlcat(e->var, "/home/thomvan-/bin:/home/thomvan-/bin:", 44);
	ft_strlcat(e->var, "/usr/local/sbin:/usr/local/bin:", 75);
	ft_strlcat(e->var, "/usr/sbin:/usr/bin:/sbin:/bin:", 105);
	ft_strlcat(e->var, "/usr/games:/usr/local/games:/snap/bin", 142);
	free(tmp);
	free(cwd);
	e = env_rewinder(e);
	return (e);
}
