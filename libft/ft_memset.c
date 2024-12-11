/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomvan- <thomvan-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:27:23 by thomvan-          #+#    #+#             */
/*   Updated: 2023/10/17 18:39:51 by thomvan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, unsigned long len)
{
	unsigned long	i;
	unsigned char	*mem;

	mem = b;
	i = 0;
	while (i < len)
	{
		mem[i] = (unsigned char) c;
		i++;
	}
	return (b);
}
