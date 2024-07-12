/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brclemen <brclemen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:36:59 by brclemen          #+#    #+#             */
/*   Updated: 2023/10/30 10:45:16 by brclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	index;
	int	resultat;
	int	sign;

	index = 0;
	resultat = 0;
	sign = 1;
	while (nptr[index] == ' ' || (nptr[index] >= '\t' && nptr[index] <= '\r'))
		index++;
	if (nptr[index] == '-')
	{
		sign = -1;
		index++;
	}
	else if (nptr[index] == '+')
		index++;
	while (nptr[index] != '\0')
	{
		if (nptr[index] >= '0' && nptr[index] <= '9')
			resultat = resultat * 10 + nptr[index] - '0';
		else
			break ;
		index++;
	}
	return (sign * resultat);
}
