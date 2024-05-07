/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brclemen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:45:15 by brclemen          #+#    #+#             */
/*   Updated: 2023/10/19 14:45:20 by brclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned const char	*strs1;
	unsigned const char	*strs2;
	size_t				index;

	strs1 = (unsigned const char *)s1;
	strs2 = (unsigned const char *)s2;
	index = 0;
	while (index < n)
	{
		if (*strs1 != *strs2)
			return (*strs1 - *strs2);
		strs1++;
		strs2++;
		index++;
	}
	return (0);
}
