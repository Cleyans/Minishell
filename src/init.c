/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brclemen <brclemen@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:22:24 by brclemen          #+#    #+#             */
/*   Updated: 2024/08/19 17:22:24 by brclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Minishell.h"

// arg_q not used !!!!!!!!! solve the problem
// je sais plus pourquoi j'avais ecris ca anyways

void	all_init_malloc(t_command *command, t_input *terminal)
{
	count_nb_args(terminal, command);
	command->arguments = malloc(sizeof(char *) * (command->args + 1)); //LEAK
	if (command->arguments == NULL)
		error_message("Error: malloc failed\n");
// 	command->command = malloc(sizeof(char) * (command->mem_cmd + 1));
// 	if (command->command == NULL)
// 		error_message("Error: malloc failed\n");
}

void	init_parss(t_parss *parss)
{
	parss->i = 0;
	parss->j = 0;
	parss->k = 0;
	parss->cmd_c = -1;
}

void	init(t_input *terminal, t_command *command)
{
	signal_check();
	init_terminal(terminal);
	init_command(command);
}

void	init_terminal(t_input *terminal)
{
	terminal->input = NULL;
	terminal->nb_cmd = 1;
	terminal->count_cmd = 0;
	terminal->echo.d_quotes = 0;
	terminal->echo.s_quotes = 0;
	terminal->echo.i = 0;
	terminal->echo.search_s2 = 0;
	terminal->echo.close = 0;
}

void	init_command(t_command *command)
{
	command->command = NULL;
	command->arguments = NULL;
	command->mem_cmd = 0;
	command->next = NULL;
	command->pipe = -1;
	command->redir_in = -1;
	command->redir_out = -1;
	command->hd_in = -1;
	command->hd_out = -1;
	command->builtins = 0;
	command->dollar = NULL;
	command->int_dollar = -1;
	command->out_dollar = NULL;
	command->args = 0;
	command->sd = 0;
}
