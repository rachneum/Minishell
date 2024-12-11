/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomvan- <thomvan-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:35:57 by thomvan-          #+#    #+#             */
/*   Updated: 2023/11/16 16:56:46 by thomvan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hay, const char *needle, size_t len)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	if (!hay && len == 0)
		return (0);
	if (*needle == '\0')
		return ((char *)hay);
	if (ft_strlen(needle) > ft_strlen(hay) || *hay == '\0')
		return (NULL);
	while (i < len && hay[i])
	{
		if (hay[i] == needle[k])
		{
			while (hay[i + k] == needle[k] && hay[i + k] && (i + k) < len)
				k++;
			if (needle[k] == '\0')
				return ((char *)hay + i);
		}
		i++;
		k = 0;
	}
	return (NULL);
}
