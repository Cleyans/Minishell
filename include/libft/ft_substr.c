/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brclemen <brclemen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:46:02 by brclemen          #+#    #+#             */
/*   Updated: 2023/10/23 12:55:42 by brclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*resultat;
	char	*source;
	size_t	resultatlen;

	if (!s)
		return (NULL);
	if ((size_t)ft_strlen(s) < (size_t)start)
		return (ft_strdup(""));
	source = (char *)s + start;
	if ((size_t)ft_strlen(source) < len)
		resultatlen = ft_strlen(source) + 1;
	else
		resultatlen = len + 1;
	resultat = malloc(resultatlen * sizeof(char));
	if (!resultat)
		return (NULL);
	ft_strlcpy(resultat, source, resultatlen);
	return (resultat);
}
