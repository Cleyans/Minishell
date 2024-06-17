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
	t_command	*first;

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
			// advanced_print(command);
			executing(&terminal, command);
			free_nodes(command);
		}
		free(terminal.input);
	}
	return (terminal.status);
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
