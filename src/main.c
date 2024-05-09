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

#include "../Include/Minishell.h"

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
	first = command;
	while (1)
	{
		init(&terminal, command, env);
		terminal.input = readline("\033[0;35mMinihell\033[0;37m$\033[0m ");
		if (verif_input(&terminal) == 0)
		{
			checking_input(&terminal, command);
			command = first;
			if (builtins_parent(&terminal, command) == 0)
				executing(&terminal, command);
			command = malloc(sizeof(t_command));
			if (command == NULL)
				error_message("Error: malloc failed\n");
			command = first;
			command->next = NULL;
		}
		free(terminal.input);
	}
	return (terminal.status);
}

void	init(t_input *terminal, t_command *command, char **env)
{
	terminal->input = NULL;
	terminal->env = env;
	terminal->nb_cmd = 1;
	terminal->status = 0;
	command->command = malloc(sizeof(char) * 10000);
	command->command[0] = '\0';
	command->arguments = malloc(sizeof(char *) * 10000);
	command->arguments[0] = NULL;
	command->next = NULL;
	command->pipe = -1;
	command->builtins = 0;
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
// 		cmd_count++;
// 		command = command->next;
// 	}
// }
