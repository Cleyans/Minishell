/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brclemen <brclemen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:03:09 by brclemen          #+#    #+#             */
/*   Updated: 2023/12/11 13:57:33 by brclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar(char c, size_t *index)
{
	write(1, &c, 1);
	(*index)++;
}

void	ft_putpercent(size_t *index)
{
	ft_putchar('%', index);
}

void	ft_putstr(char *str, size_t *index)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		ft_putchar(str[i], index);
		i++;
	}
}

void	ft_printstr(char *str, size_t *index)
{
	if (str == NULL)
		ft_putstr("(null)", index);
	else
		ft_putstr(str, index);
}
