/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brclemen <brclemen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:20:39 by brclemen          #+#    #+#             */
/*   Updated: 2023/11/13 14:10:33 by brclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char		*temp;
	size_t		index;

	temp = (char *)s;
	index = 0;
	while (n > index)
	{
		*temp = 0;
		temp++;
		index++;
	}
}
