/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brclemen <brclemen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:49:02 by brclemen          #+#    #+#             */
/*   Updated: 2024/05/01 14:04:45 by brclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/Minishell.h"


void	ft_lstadd_back_m(t_command **lst, t_command *new)
{
	t_command	*current;

	if (*lst == NULL)
		*lst = new;
	else
	{
		current = *lst;
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
}
