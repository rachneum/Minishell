/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomvan- <thomvan-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:51:28 by thomvan-          #+#    #+#             */
/*   Updated: 2023/10/24 16:42:36 by thomvan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, unsigned long n)
{
	unsigned long	i;
	unsigned char	*d;
	unsigned char	*s;

	if (!dst && !src)
		return (0);
	if (!n)
		return (dst);
	i = 0;
	d = (unsigned char *) dst;
	s = (unsigned char *) src;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}
