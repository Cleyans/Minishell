/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brclemen <brclemen@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:42:31 by brclemen          #+#    #+#             */
/*   Updated: 2024/08/19 16:42:31 by brclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Minishell.h"

void	put_command(t_input *terminal, t_command *command, t_parss *parss)
{
	int	i;
	int	mem;

	i = parss->i;
	mem = 0;
	while (terminal->input[i] != ' '
		&& terminal->input[i] != '\0')
	{
		i++;
		mem++;
	}
	command->command = malloc(sizeof(char) * (mem + 1)); //LEAK
	if (!command->command)
		error_message(strerror(errno));
	while (terminal->input[parss->i] != ' '
		&& terminal->input[parss->i] != '\0')
	{
		command->command[parss->j] = terminal->input[parss->i];
		parss->i++;
		parss->j++;
		parss->cmd_c = 0;
	}
	command->command[parss->j] = '\0';
	if (builtins_check(command) == 1)
		terminal->builtins++;
}

void	put_arg_cmd(t_input *terminal, t_command *command, t_parss *parss) //CORR
{
	int	len;
	int mem;
	int quote_len;

	len = parss->i;
	mem = 0;
	quote_len = 0;
	while (terminal->input[len] != ' ' && terminal->input[len])
	{
		if (terminal->input[len] == '\'' || terminal->input[len] == '\"')
		{
			quote_len += is_quote_len(terminal, parss, terminal->input[len], len); // moche a ameliorer
			mem += quote_len;
			len += quote_len;
		}
		else
			mem++;
		len++;
	}
	command->arguments[parss->j] = malloc(sizeof(char) * (mem + 1));
	if (!command->arguments[parss->j])
		error_message(strerror(errno));
	while (terminal->input[parss->i] != ' ' && terminal->input[parss->i])
	{
		if ((terminal->input[parss->i] == '\''
				|| terminal->input[parss->i] == '\"'))
			if (is_quote(terminal, command, parss) == 42)
				break ;
		if (parss->k < mem)
		{
			command->arguments[parss->j][parss->k] = terminal->input[parss->i];
			parss->i++;
			parss->k++;
		}
	}
	command->arguments[parss->j][parss->k] = '\0';
	parss->k = 0;
	parss->j++;
}

// doesn't word with pipe, because start at the begin of the input

void count_nb_args(t_input *terminal, t_command *command, t_parss *parss)
{
    int i = parss->i;

    command->args = 0;
    command->mem_cmd = 0;

while (terminal->input[i] && terminal->input[i] == ' ')
	i++;
while (terminal->input[i] && terminal->input[i] != ' ')
{
	command->mem_cmd++;
	i++;
}
while (terminal->input[i] && terminal->input[i] != '|')
{
    while (terminal->input[i] == ' ')
        i++;
    if (terminal->input[i] != '\0' && terminal->input[i] != '|')
	{
		while (terminal->input[i] != '\0' && terminal->input[i] != ' ')
        	i++;
        command->args++;
    }
}
}
