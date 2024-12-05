/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomvan- <thomvan-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:38:29 by thomvan-          #+#    #+#             */
/*   Updated: 2024/11/30 17:35:17 by thomvan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

static int	is_digit(char *s)
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

int	my_exit(t_all *all, t_cmd *c)
{
	int	i;
	int	j;
	int	tmp;

	i = 1;
	tmp = 0;
	j = 0;
	while (c->cmd[j])
		j++;
	if (j > 1)
		return (printf("too many arguments\n"), g_err_global = 1, 1);
	if (c->cmd[i])
	{
		while (c->cmd[i])
		{
			if (!is_digit(c->cmd[i]))
				return (printf("argument is not a number\n"), g_err_global = 1,
					1);
			i++;
		}
		tmp = ft_atoi(c->cmd[1]) % 256;
		g_err_global = tmp;
		total_free(all);
	}
	exit(tmp);
}
