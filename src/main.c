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

int	main(int ac, char **av, char **env)
{
	t_input		terminal;
	t_command	*command;
	t_command	*first;

	(void)ac;
	(void)av;
	command = malloc(sizeof(t_command));
	if (command == NULL)
		error_message("Error: malloc failed\n");
	init_env(&terminal, env);
	init_export(&terminal);
	first = command;
	signal_check();
	while (1)  // faire une fonction qui free a chaque iteration.
	{
		init(&terminal, command);
		terminal.input = readline("\033[0;35mMinihell\033[0;37m$\033[0m ");
		add_history(terminal.input);
		if (verif_input(&terminal) == 0)
		{
			cheking_input(&terminal, command);
			command = first;
			// advanced_print(command);
			// command = first;
			executing(&terminal, command);
			command = first;
			command->next = NULL;
		}
		free(terminal.input);
	}
	return (terminal.status);
}

void	init(t_input *terminal, t_command *command)
{
	terminal->input = NULL;
	// if (env != NULL)
	// 	terminal->env = env; //call fonction init env
	terminal->nb_cmd = 1;
	terminal->status = 0;
	terminal->nb_pipe = 0;
	terminal->echo.d_quotes = 0;
	terminal->echo.s_quotes = 0;
	terminal->echo.i = 0;
	terminal->echo.search_s2 = 0;
	terminal->echo.close = 0;
	command->command = malloc(sizeof(char) * 100);
	command->command[0] = '\0';
	command->arguments = malloc(sizeof(char *) * 100);
	command->arguments[0] = NULL;
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
}

// void	print_commands(t_command *command)
// {
// 	int	i;
// 	int	cmd_count;

// 	cmd_count = 0;
// 	while (command->next != NULL)
// 	{
// 		if (command->command[0] != '\0')
// 			printf("Commande[%d] = %s\n",cmd_count, command->command);
// 		i = 0;
// 		while (command->arguments[i] != NULL && command->arguments[i][0] != '\0')
// 		{
// 			printf("Arguments[%d] de la commande[%d] : %s\n",i, cmd_count, command->arguments[i]);
// 			i++;
// 		}
// 		printf("Pipe: %d\n", command->pipe);
// 		printf("Redirection: %d\n", command->redirection);
// 		printf("\n");
// 		cmd_count++;
// 		command = command->next;
// 	}
// }
