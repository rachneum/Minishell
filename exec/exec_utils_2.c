/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachou <rachou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 17:40:18 by rachou            #+#    #+#             */
/*   Updated: 2024/12/05 15:57:24 by rachou           ###   ########.fr       */
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

int	pipes_limit(t_all *all)
{
	t_token	*current;
	int		count;

	current = all->token;
	count = 0;
	while (current->previous)
		current = current->previous;
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
}
