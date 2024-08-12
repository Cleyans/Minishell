/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brclemen <brclemen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 01:22:34 by brclemen          #+#    #+#             */
/*   Updated: 2024/05/08 01:22:34 by brclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Minishell.h"

int	g_singal = 0;

int	main(int ac, char **av, char **env)
{
	t_input		terminal;
	t_command	*command;

	(void)ac;
	(void)av;
	command = malloc(sizeof(t_command));
	if (command == NULL)
		error_message("Error: malloc failed\n");
	init_env(&terminal, env);
	init_export(&terminal);
	terminal.status = 0;
	while (1)
	{
		init(&terminal, command);
		terminal.input = readline("\033[0;35mMinihell\033[0;37m$\033[0m ");
		add_history(terminal.input);
		if (verif_input(&terminal) == 0)
		{
			cheking_input(&terminal, command);
			advanced_print(command);
			executing(&terminal, command);
			free_nodes(command);
		}
		free(terminal.input);
	}
	return (terminal.status);
}
