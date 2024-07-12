/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brclemen <brclemen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:02:01 by brclemen          #+#    #+#             */
/*   Updated: 2023/10/23 11:30:56 by brclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char		*temp;
	size_t		index;

	temp = (char *)s;
	index = 0;
	while (n > index)
	{
		*temp = (char)c;
		temp++;
		index++;
	}
	return (s);
}
