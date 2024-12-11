/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomvan- <thomvan-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:38:29 by thomvan-          #+#    #+#             */
/*   Updated: 2024/12/08 13:41:14 by thomvan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	is_digit(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i])
	{
		if (s[i] < 48 || s[i] > 57)
			return (0);
		i++;
	}
	return (1);
}

static int	pipe_exist(t_cmd *c)
{
	int	i;

	i = 0;
	while (c->previous != NULL)
		c = c->previous;
	while (c->next)
	{
		c = c->next;
		i++;
	}
	if (i > 0)
		return (1);
	return (0);
}

static int	is_too_big(t_cmd *c)
{
	int	j;

	j = 0;
	while (c->cmd[j])
		j++;
	if (j > 2)
		return (1);
	return (0);
}

static int	moduler(t_cmd *c, int *tmp)
{
	*tmp = ft_atoi(c->cmd[1]);
	if (tmp < 0)
		*tmp = (256 - (*tmp)) % 256;
	else
		*tmp = *tmp % 256;
}

int	my_exit(t_all *all, t_cmd *c)
{
	int	i;
	int	tmp;

	i = 1;
	tmp = 0;
	if (c->cmd[i])
		moduler(c, &tmp);
	if (pipe_exist(c))
		return (g_err_global = tmp, 1);
	if (is_too_big(c))
		return (printf("too many arguments\n"), g_err_global = 1, 1);
	if (c->cmd[i])
	{
		while (c->cmd[i])
		{
			if (!is_digit(c->cmd[i++]))
				return (printf("exit\nnot a number\n"), exit(1), 1);
		}
		g_err_global = tmp;
		total_free(all);
	}
	exit(tmp);
}
