/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brclemen <brclemen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:40:16 by brclemen          #+#    #+#             */
/*   Updated: 2023/12/11 13:58:13 by brclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n, size_t *index)
{
	if (n == -2147483648)
	{
		ft_putstr("-2147483648", index);
		return ;
	}
	if (n < 0)
	{
		ft_putchar('-', index);
		n = -n;
	}
	if (n <= 9)
	{
		ft_putchar(n + '0', index);
	}
	else
	{
		ft_putnbr(n / 10, index);
		ft_putnbr(n % 10, index);
	}
}

void	ft_unsignedputnbr(unsigned int n, size_t *index)
{
	if (n <= 9)
	{
		ft_putchar(n + '0', index);
	}
	else
	{
		ft_putnbr(n / 10, index);
		ft_putnbr(n % 10, index);
	}
}
