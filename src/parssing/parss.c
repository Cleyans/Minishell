/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parss.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brclemen <brclemen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 06:03:58 by brclemen          #+#    #+#             */
/*   Updated: 2024/05/09 06:03:58 by brclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Minishell.h"

extern int	g_singal;

void	cheking_input(t_input *terminal, t_command *command) //CORR
{
	t_parss	parss;

	init_parss(&parss);
	while (terminal->input[parss.i] && terminal->input[parss.i] != '\0')
	{
		all_init_malloc(command, terminal, &parss);
		while (terminal->input[parss.i] != '\0'
			&& terminal->input[parss.i] != '|')
		{
			while (terminal->input[parss.i] == ' ')
				parss.i++;
			if (terminal->input[parss.i] == '<'
				|| terminal->input[parss.i] == '>')
				check_redir(terminal, command, &parss);
			if (parss.cmd_c == 1 && terminal->input[parss.i])
				put_arg_cmd(terminal, command, &parss);
			if ((parss.cmd_c == 0) || parss.cmd_c == -1)
				put_command(terminal, command, &parss);
			if (parss.cmd_c == 0)
			{
				command->command[parss.j] = '\0';
				parss.cmd_c = 1;
				parss.j = 0;
			}
			if (terminal->input[parss.i] == '\0')
				break ;
			parss.i++;
		}
		if (terminal->input[parss.i] == '|')
		{
			command->pipe = 0;
			parss.i++;
		}
		else
			command->pipe = -1;
		command->arguments[parss.j] = NULL;
		parss.j = 0;
		parss.cmd_c = -1;
		terminal->count_cmd++;
		ft_lstadd_back_m(&command, ft_lstnew_m());
		command = command->next;
	}
}

void	call_dollar(t_input *terminal, t_command *command, t_parss *parss)
{
	int i;

	i = 0;
	while (terminal->input[parss->i] != '\0')
	{
		command->dollar = malloc(sizeof(char) * 1); //CORR
		if ((terminal->input[parss->i] == '$')
			&& terminal->input[parss->i + 1] == '?'
			&& terminal->input[parss->i + 1] != '\0')
		{
			command->int_dollar = 1;
			return ;
		}
		parss->i++;
		while (terminal->input[parss->i] != ' '
			&& terminal->input[parss->i] != '\0')
		{
			command->dollar[i] = terminal->input[parss->i];
			parss->i++;
			i++;
			command->int_dollar = 0;
		}
		if (command->int_dollar == 0)
		{
			search_path_dollar(terminal, command);
			parss->i++;
		}
		command->dollar[i] = '\0';
		parss->i++;
	}
}

void	*search_path_dollar(t_input *terminal, t_command *command)
{
	int			i;
	int			j;
	int			k;
	int			l;

	command->out_dollar = malloc(sizeof(char) * 10000); //CORR
	if (command->out_dollar == NULL)
		return (NULL);
	l = 0;
	i = 0;
	while (terminal->env[i] != NULL)
	{
		j = 0;
		k = 0;
		while (terminal->env[i][j] != '\0')
		{
			while (terminal->env[i][j] == command->dollar[k]
				&& terminal->env[i][j] != '\0')
			{
				j++;
				k++;
				if (terminal->env[i][j] == '=')
				{
					j++;
					while (terminal->env[i][j] != '\0')
						command->out_dollar[l++] = terminal->env[i][j++];
					command->out_dollar[l] = '\0';
					return (command->out_dollar);
				}
			}
			if (command->dollar[k] != '\0')
				break ;
			j++;
		}
		i++;
	}
	free(command->out_dollar);
	command->out_dollar = NULL;
	return (NULL);
}
