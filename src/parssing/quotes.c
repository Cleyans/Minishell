/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brclemen <brclemen@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:27:58 by brclemen          #+#    #+#             */
/*   Updated: 2024/08/19 16:27:58 by brclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Minishell.h"

int	is_quote(t_input *terminal, t_command *command, t_parss *parss)
{
	char	c;

	c = terminal->input[parss->i];
	parss->i++;
	while (terminal->input[parss->i] && terminal->input[parss->i] != c)
	{
			command->arguments[parss->j][parss->k] = terminal->input[parss->i];
			parss->i++;
			parss->k++;
	}
	if (terminal->input[parss->i] == '\0')
		return (42);
	else if (terminal->input[parss->i] == c)
	{
		if (c == '\'')
			command->s_quotes = 1;
		else if (c == '\"')
			command->s_quotes = 2;
		else
			command->s_quotes = 0;
	}
	parss->i++;
	return (0);
}

int	is_quote_len(t_input *terminal, t_parss *parss, char c, int lenght)
{
	int	i;
	int	len;

	len = 0;
	i = lenght + 1;
	while (terminal->input[i] != c && terminal->input[i] != '\0')
	{
		len++;
		i++;
	}
	return (len);
}
