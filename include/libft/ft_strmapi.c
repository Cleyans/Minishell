/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brclemen <brclemen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:38:57 by brclemen          #+#    #+#             */
/*   Updated: 2023/10/23 11:32:14 by brclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*resultat;
	unsigned int	index;

	index = 0;
	resultat = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!resultat)
		return (NULL);
	while (s[index])
	{
		resultat[index] = f(index, s[index]);
		index++;
	}
	resultat[index] = '\0';
	return (resultat);
}
