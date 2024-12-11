/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomvan- <thomvan-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:18:55 by thomvan-          #+#    #+#             */
/*   Updated: 2024/12/08 13:29:31 by thomvan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

static void	naked_export(t_env_list *e)
{
	char	*tmp;

	while (e)
	{
		if (has_equal(e->var) && e->var[0] != '_')
		{
			tmp = get_name(e, NULL);
			printf("declare -x %s", tmp);
			free(tmp);
			printf("=\"%s\"\n", get_value(e, NULL));
		}
		else if (e->var[0] != '_')
			printf("declare -x %s\n", e->var);
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
		while (cm->cmd[i][0] != '=' && cm->cmd[i][j] && cm->cmd[i][j] != '=')
			j++;
		if (cm->cmd[i][0] != '=' && (!cm->cmd[i][j - 1] || cm->cmd[i][j
				- 1] == '-' || cm->cmd[i][j - 1] == '*'))
			return (0);
		i++;
	}
	return (1);
}

int	has_equal(char *s)
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

static void	my_export_part(t_env_list *e, t_all *all, t_cmd *cm, int *i)
{
	char	*tmp;

	if (has_equal(cm->cmd[*i]))
	{
		tmp = get_name(e, cm->cmd[*i]);
		e = all->env;
		if (ft_strnstr(cm->cmd[*i], "+=", ft_strlen(tmp) + 2))
			update_append(cm->cmd[*i], e);
		else
			update_equal(cm->cmd[*i], e);
		free(tmp);
	}
	else
	{
		while (e->next != NULL && ft_strncmp(e->var, cm->cmd[*i],
				ft_strlen(cm->cmd[*i])) != 0)
			e = e->next;
		if (ft_strncmp(e->var, cm->cmd[*i], ft_strlen(cm->cmd[*i])) == 0)
			return ;
		e = new_node(e);
		e->var = ft_strdup(cm->cmd[*i]);
	}
}

int	my_export(t_all *all, t_cmd *cm)
{
	t_env_list	*e;
	int			i;
	char		*tmp;

	i = 1;
	e = env_rewinder(all->env);
	if (!cm->cmd[1])
	{
		e = env_sort_cpy(e);
		return (naked_export(e), env_l_free(e), 0);
	}
	if (is_c_digit(cm->cmd[1][0]))
		return (printf("not a valid identifier\n"), g_err_global = 1, 1);
	if (!is_valid(cm))
		return (printf("not a valid identifier\n"), g_err_global = 1, 1);
	while (cm->cmd[i])
	{
		my_export_part(e, all, cm, &i);
		i++;
	}
}
