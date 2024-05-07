/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brclemen <brclemen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:30:44 by brclemen          #+#    #+#             */
/*   Updated: 2023/10/30 11:04:19 by brclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"  

char	*ft_strrchr(const char *s, int c)
{
	const char	*dernier;
	size_t		index;

	dernier = NULL;
	index = 0;
	if ((char)c == '\0')
	{
		while (s[index])
			index++;
		return ((char *)&s[index]);
	}
	while (s[index])
	{
		if (s[index] == (char)c)
			dernier = &s[index];
		index++;
	}
	return ((char *)dernier);
}
