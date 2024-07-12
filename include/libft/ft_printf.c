/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brclemen <brclemen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:22:29 by brclemen          #+#    #+#             */
/*   Updated: 2023/12/11 13:56:11 by brclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_format(va_list args, char *str, size_t *index)
{
	if (*str == 'c')
		ft_putchar(va_arg(args, int), index);
	else if (*str == 's')
		ft_printstr(va_arg(args, char *), index);
	else if (*str == 'i' || *str == 'd')
		ft_putnbr(va_arg(args, int), index);
	else if (*str == '%')
		ft_putpercent(index);
	else if (*str == 'u')
		ft_unsignedputnbr(va_arg(args, unsigned int), index);
	else if (*str == 'x')
		ft_print_hex(va_arg(args, unsigned int), *str, index);
	else if (*str == 'X')
		ft_print_hex(va_arg(args, unsigned int), *str, index);
	else if (*str == 'p')
		ft_print_ptr(va_arg(args, void *), index);
	else
		ft_putchar('%', index);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	size_t	index;

	index = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			ft_format(args, (char *)str, &index);
		}
		else
			ft_putchar(*str, &index);
		str++;
	}
	va_end(args);
	return (index);
}
