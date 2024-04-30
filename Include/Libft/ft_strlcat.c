/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brclemen <brclemen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:49:47 by brclemen          #+#    #+#             */
/*   Updated: 2023/10/30 11:00:43 by brclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	index;
	size_t	j;
	size_t	destinationlen;
	size_t	sourcelen;

	sourcelen = ft_strlen(src);
	destinationlen = ft_strlen(dst);
	j = destinationlen;
	index = 0;
	if (destinationlen < size - 1 && size > 0)
	{
		while (src[index] && destinationlen + index < size - 1)
		{
			dst[j] = src[index];
			index++;
			j++;
		}
		dst[j] = '\0';
	}
	if (destinationlen >= size)
		destinationlen = size;
	return (destinationlen + sourcelen);
}
