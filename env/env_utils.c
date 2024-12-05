/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomvan- <thomvan-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 21:42:19 by thomvan-          #+#    #+#             */
/*   Updated: 2024/11/30 12:52:35 by thomvan-         ###   ########.fr       */
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
	while (str[i + 1] != ' ' && str[i + 1] != 34 && str[i + 1] != '\0')
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
