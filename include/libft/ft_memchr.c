/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brclemen <brclemen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:30:32 by brclemen          #+#    #+#             */
/*   Updated: 2023/10/23 11:28:00 by brclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*source;
	size_t			index;

	source = (unsigned char *)s;
	index = 0;
	while (index < n)
	{
		if (source[index] == (unsigned char)c)
			return ((void *)&source[index]);
		index++;
	}
	return (NULL);
}
