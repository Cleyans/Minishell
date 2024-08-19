/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_white_space.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brclemen <brclemen@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:27:20 by brclemen          #+#    #+#             */
/*   Updated: 2024/08/19 16:27:20 by brclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Minishell.h"

int	find_p_r(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	white_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	verif_input(t_input *terminal)
{
	if (terminal->input[0] != '\0' && terminal->input[0] != '\n'
		&& terminal->input[0] != '\t'
		&& terminal->input[0] != ' ' && terminal->input[0] != '\v'
		&& terminal->input[0] != '\f' && terminal->input[0] != '\r')
		return (0);
	return (1);
}

int	check_char(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}
