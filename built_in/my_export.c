/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomvan- <thomvan-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:18:55 by thomvan-          #+#    #+#             */
/*   Updated: 2024/11/29 21:31:57 by thomvan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char	*get_value(t_env_list *env, char *str)
{
	int	i;

	if (!str)
	{
		i = 0;
		while (env->var[i] != '=' && env->var[i])
			i++;
		return (env->var + i + 1);
	}
	else
	{
		i = 0;
		while (str[i] != '=' && str[i])
			i++;
		return (str + i + 1);
	}
}

static void	naked_export(t_env_list *e)
{
	char	*tmp;

	while (e)
	{
		tmp = get_name(e, NULL);
		printf("declare -x %s", tmp);
		free(tmp);
		printf("=\"%s\"\n", get_value(e, NULL));
		e = e->next;
	}
}

static int	is_valid(t_cmd *cm)
{
	int	i;
	int	j;

	i = 1;
	while (cm->cmd[i])
	{
		j = 0;
		while (cm->cmd[i][j] && cm->cmd[i][j] != '=')
			j++;
		if ((!cm->cmd[i][j - 1] || cm->cmd[i][j - 1] == '-' || cm->cmd[i][j
				- 1] == '*'))
			return (0);
		i++;
	}
	return (1);
}

static int	has_equal(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	my_export(t_all *all, t_cmd *cm)
{
	t_env_list	*e;
	int			i;
	char		*tmp;

	i = 1;
	all->env = env_rewinder(all->env);
	e = all->env;
	if (!cm->cmd[1])
		return (naked_export(e), 0);
	if (!is_valid(cm))
		return (printf("not a valid identifier\n"), g_err_global = 1, 1);
	while (cm->cmd[i])
	{
		if (has_equal(cm->cmd[i]))
		{
			tmp = get_name(e, cm->cmd[i]);
			e = all->env;
			if (ft_strnstr(cm->cmd[i], "+=", ft_strlen(tmp) + 2))
				update_append(cm->cmd[i], e);
			else
				update_equal(cm->cmd[i], e);
			free(tmp);
		}
		i++;
	}
}
