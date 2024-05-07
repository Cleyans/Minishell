/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brclemen <brclemen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:01:42 by brclemen          #+#    #+#             */
/*   Updated: 2023/11/04 15:16:16 by brclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char		*dest;
	size_t		index;

	index = ft_strlen(s);
	dest = malloc(index + 1 * sizeof(char));
	if (dest == NULL)
		return (NULL);
	index = 0;
	while (s[index])
	{
		dest[index] = s[index];
		index++;
	}
	dest[index] = '\0';
	return (dest);
}
