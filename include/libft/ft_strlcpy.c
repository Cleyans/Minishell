/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brclemen <brclemen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:43:56 by brclemen          #+#    #+#             */
/*   Updated: 2023/10/30 11:01:56 by brclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	index;

	index = 0;
	if (size != 0)
	{
		while (src[index] && size > 1)
		{
			dst[index] = src[index];
			size--;
			index++;
		}
		dst[index] = '\0';
	}
	while (src[index] != '\0')
		index++;
	return (index);
}
