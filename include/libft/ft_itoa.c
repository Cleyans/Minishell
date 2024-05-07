/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brclemen <brclemen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:38:30 by brclemen          #+#    #+#             */
/*   Updated: 2023/10/23 17:18:52 by brclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	digit(int n)
{
	int	count;

	count = 0;
	if (n < 0 && n > -2147483647)
	{
		count++;
		n = -n;
	}
	else if (n == 0)
		return (1);
	while (n >= 1)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static char	*convertion(char *resultat, int n, int nlen)
{
	int		index;
	int		index2;

	index = 0;
	index2 = nlen - 1;
	if (n < 0)
	{
		n = -n;
		resultat[0] = '-';
		nlen = nlen -1;
	}
	while (nlen > 0)
	{
		if (n > 9)
		{
			resultat[index2 - index] = n % 10 + 48;
			n = n / 10;
		}
		else
			resultat[index2 - index] = n + 48;
		nlen--;
		index++;
	}
	return (resultat);
}

char	*ft_itoa(int n)
{
	int		nlen;
	char	*resultat;

	if (n == -2147483648)
	{
		resultat = malloc(12);
		if (resultat)
			ft_strlcpy(resultat, "-2147483648", 12);
	}
	else
	{
		nlen = digit(n);
		resultat = (char *)malloc(sizeof(char) * (nlen + 1));
		if (!resultat)
			return (NULL);
		resultat[nlen] = '\0';
		resultat = convertion(resultat, n, nlen);
	}
	return (resultat);
}
