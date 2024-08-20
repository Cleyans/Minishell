/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_pipex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brclemen <brclemen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:37:17 by brclemen          #+#    #+#             */
/*   Updated: 2024/04/04 16:13:12 by brclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strjoin_pipex(char const *s1, char const *s2)
{
	size_t	total_len;
	char	*result;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	total_len = (ft_strlen(s1) + ft_strlen(s2));
	result = (char *)malloc(total_len + 1);
	if (result == NULL)
		return (NULL);
	if (s1 != NULL)
		ft_memcpy(result, s1, ft_strlen(s1));
	if (s2 != NULL)
		ft_memcpy(result + ft_strlen(s1), s2, ft_strlen(s2));
	result[total_len] = '\0';
	return (result);
}
