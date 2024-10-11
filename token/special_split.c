/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachou <rachou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:17:05 by rachou            #+#    #+#             */
/*   Updated: 2024/10/10 13:17:23 by rachou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

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
		if (not_a_split(str, set, i))
		{
			counter++;
			while (not_a_split(str, set, i) && str[i])
				i++;
		}
		while (!not_a_split(str, set, i) && str[i])
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
		while ((not_a_split(str, set, i) && str[i] && flag++))
			i++;
		if ((!not_a_split(str, set, i) && flag > 1) || str[i] == '\0')
		{
			piec[j] = malloc((flag) * sizeof(char));
			if (!piec[j])
				return (ft_free(piec));
			flag = 1;
			j++;
		}
		while (!not_a_split(str, set, i) && str[i])
			i++;
	}
	return (1);
}

static char	**ft_maker(char **piec, char set, char *str)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (str[i])
	{
		k = 0;
		if (not_a_split(str, set, i))
		{
			while (not_a_split(str, set, i) && str[i])
				piec[j][k++] = str[i++];
			piec[j][k] = '\0';
			j++;
		}
		while (!not_a_split(str, set, i) && str[i])
			i++;
	}
	piec[j] = 0;
	return (piec);
}

char	**s_split(char const *str, const char charset)
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
