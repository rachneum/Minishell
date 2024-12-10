/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raneuman <raneuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 17:40:18 by rachou            #+#    #+#             */
/*   Updated: 2024/12/08 11:45:07 by raneuman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char	*ft_free_tab(char **cmd)
{
	int	i;

	if (!cmd)
		return (NULL);
	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
	return (NULL);
}

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] != '\0' && str2[i] != '\0')
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (str1[i] - str2[i]);
}

/*int	pipes_limit(t_all *all)
{
	t_token	*current;
	int		count;

	current = all->token;
	count = 0;
	while (current->previous)
	{
		printf("prout\n");
		current = current->previous;
	}
	while (current)
	{
		if (ft_strcmp(current->content, "|") == 0)
		{
			count++;
			if (count > 200)
			{
				printf("ERROR: Too many pipes\n");
				return (1);
			}
		}
		current = current->next;
	}
	return (0);
}*/

int	pipes_limit(t_all *all)
{
	t_cmd	*c;
	int		count;

	c = all->cmd;
	count = 0;
	while (c->previous)
		c = c->previous;
	while (c)
	{
		count++;
		if (count > 200    )
		{
			printf("ERROR: Too many pipes\n");
			return (1);
		}
		c = c->next;
	}
	return (0);
}