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

void	args_quotes(t_input *terminal, t_command *command, t_parss *parss) //CORR
{
	int	len;
	int	mem;

	parss->i++;
	len = parss->i;
	mem = 0;
	while (terminal->input[len] != '\"' && terminal->input[len] != '\0')
	{
		len++;
		mem++;
	}
	if (terminal->input[len] == '\"')
		command->arguments[parss->j] = malloc(sizeof(char *) * (mem + 1));
	else
		return ;
	len = 0;
	while (terminal->input[parss->i] != '\"'
		&& terminal->input[parss->i] != '\0')
	{
		command->arguments[parss->j][len] = terminal->input[parss->i];
		len++;
		parss->i++;
	}
	command->arguments[parss->j][len] = '\0';
	if (terminal->input[parss->i] == '\"')
		parss->i++;
	parss->j++;
}

void	args_quote(t_input *terminal, t_command *command, t_parss *parss) //CORR
{
	int	len;
	int	mem;

	parss->i++;
	len = parss->i;
	mem = 0;
	while (terminal->input[len] != '\'' && terminal->input[len] != '\0')
	{
		len++;
		mem++;
	}
	if (terminal->input[len] == '\'')
		command->arguments[parss->j] = malloc(sizeof(char *) * (mem + 1));
	else
		return ;
	len = 0;
	while (terminal->input[parss->i] != '\''
		&& terminal->input[parss->i] != '\0')
	{
		command->arguments[parss->j][len] = terminal->input[parss->i];
		len++;
		parss->i++;
	}
	command->arguments[parss->j][len] = '\0';
	if (terminal->input[parss->i] == '\'')
		parss->i++;
	parss->j++;
}

int	is_quote_nb_args(t_input *terminal, char c, int i)
{
	i++;
	while (terminal->input[i] != c && terminal->input[i] != '\0')
		i++;
	if (terminal->input[i] == '\0')
		return (42);
	return (0);
}

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
