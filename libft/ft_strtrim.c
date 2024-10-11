/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomvan- <thomvan-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:06:10 by thomvan-          #+#    #+#             */
/*   Updated: 2023/11/16 17:35:07 by thomvan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isin(char const *st, char c)
{
	int	i;

	i = 0;
	while (st[i])
	{
		if (c == st[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		i;
	size_t		j;
	size_t		k;
	char		*cpy;

	i = 0;
	k = 0;
	if (!s1 || !set)
		return (0);
	j = ft_strlen(s1);
	while (isin(set, s1[i]) && (s1[i] != '\0'))
		i++;
	while ((j > 0) && isin(set, s1[j - 1]) && j > i && (s1[j - 1] != '\0'))
		j--;
	cpy = malloc(sizeof(char) * (j - i + 1));
	if (!cpy)
		return (0);
	while ((i + k) < j)
	{
		cpy[k] = s1[i + k];
		k++;
	}
	cpy[k] = '\0';
	return (cpy);
}
