/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachou <rachou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 10:35:48 by thomvan-          #+#    #+#             */
/*   Updated: 2024/12/05 12:14:07 by rachou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	o_size(char *tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		i++;
	}
	return (i);
}

size_t	ft_strlcat(char *dest, char *src, size_t size)
{
	unsigned long	j;
	unsigned long	ogsize;
	unsigned long	k;

	j = 0;
	k = 0;
	if (!dest && size == 0)
		return (0);
	ogsize = o_size(dest);
	while (src[k])
		k++;
	if (!(size <= 0))
	{
		while ((ogsize + j) < size - 1 && src[j])
		{
			dest[ogsize + j] = src[j];
			j++;
		}
	}
	dest[ogsize + j] = '\0';
	if (ogsize > size)
		return (k + size);
	else
		return (k + ogsize);
}
