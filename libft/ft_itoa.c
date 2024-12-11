/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomvan- <thomvan-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 09:39:51 by thomvan-          #+#    #+#             */
/*   Updated: 2023/11/08 17:53:09 by thomvan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	numsize(long num)
{
	int	i;

	i = 0;
	while (num > 9)
	{
		num /= 10;
		i++;
	}
	return (i);
}

static char	*filler(char *str, size_t min, size_t i, long new)
{
	str[i + 1] = '\0';
	while (new > 9)
	{
		str[i--] = (new % 10) + '0';
		new /= 10;
	}
	str[i] = new + '0';
	if (min)
		str[i - 1] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	size_t	minus;
	size_t	i;
	long	newn;
	char	*str;

	minus = 0;
	newn = (long)n;
	if (n < 0)
	{
		minus = 1;
		newn *= -1;
	}
	i = numsize(newn) + minus;
	str = malloc(sizeof(char) * (numsize(newn) + 2 + minus));
	if (!str)
		return (0);
	return (filler(str, minus, i, newn));
}
