/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomvan- <thomvan-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 17:53:43 by thomvan-          #+#    #+#             */
/*   Updated: 2023/11/17 17:30:09 by thomvan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_free(char **piec)
{
	int	i;

	i = -1;
	while (piec[++i])
		free(piec[i]);
	free(piec);
	return (0);
}

static int	space_counter(char set, char *str)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (!(str[i] == set))
		{
			counter++;
			while (!(str[i] == set) && str[i])
				i++;
		}
		while ((str[i] == set) && str[i])
			i++;
	}
	return (counter);
}

static int	space_maker(char **piec, char set, char *str)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	j = 0;
	flag = 1;
	while (str[i])
	{
		while (!(str[i] == set) && str[i] && flag++)
			i++;
		if ((str[i] == set && flag > 1) || str[i] == '\0')
		{
			piec[j] = malloc((flag) * sizeof(char));
			if (!piec[j])
				return (ft_free(piec));
			flag = 1;
			j++;
		}
		while (str[i] == set && str[i])
			i++;
	}
	return (1);
}

char	**ft_maker(char **piec, char set, char *str)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (str[i])
	{
		k = 0;
		if (!(str[i] == set))
		{
			while (!(str[i] == set) && str[i])
				piec[j][k++] = str[i++];
			piec[j][k] = '\0';
			j++;
		}
		while (str[i] == set && str[i])
			i++;
	}
	piec[j] = 0;
	return (piec);
}

char	**ft_split(char const *str, const char charset)
{
	char	**pieces;
	int		how_many;
	int		safe;

	if (!str)
		return (NULL);
	how_many = space_counter(charset, (char *)str);
	pieces = malloc((how_many + 1) * sizeof(char *));
	if (!pieces)
		return (NULL);
	safe = space_maker(pieces, charset, (char *)str);
	if (!safe)
		return (NULL);
	return (ft_maker(pieces, charset, (char *)str));
}
