/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brclemen <brclemen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 01:29:31 by brclemen          #+#    #+#             */
/*   Updated: 2024/05/08 01:29:31 by brclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Minishell.h"

// only for one command || if we want to do more then one and more
//then one pipe, we have to know the amouth of pipe before the execution

void	executing(t_input *terminal, t_command *command) // builtins if not = 0, if for child 1 and if for parent 2 | a voir je sais pas encore si je fais ca
{
	int		i;
	int		*pid;

	i = 0;
	pid = malloc(sizeof(int) * 4096);
	if (pid == NULL)
		error_message("Error: malloc failed\n");
	while (command->command[0] != '\0' && command->next != NULL)
	{
		if (pipe(terminal->p_fd[i]) == -1)
			error_message("Error: pipe failed\n");
		pid[i] = fork();
		if (pid[i] == -1)
			error_message("Error: fork failed\n");
		else if (pid[i] == 0)
			calling_function(terminal, command, i);
		else
			parent_process(terminal, i, pid[i]);
		i++;
		command = command->next;
		terminal->nb_cmd++;
	}
	free(pid);
}

void	error_message(char *message)
{
	fprintf(stderr, "Minishell: %s\n", message);
	exit(EXIT_FAILURE);
}

void	calling_function(t_input *terminal, t_command *command, int i)
{
	if (command->pipe == 0 && terminal->nb_cmd == 1)
		first_command(terminal, command, i);
	else if (command->pipe == 0 && terminal->nb_cmd > 1)
		middle_command(terminal, command, i);
	else if (command->pipe == -1)
	{
		if (terminal->nb_cmd > 1)
			last_command(terminal, command, i);
		else
			only_one_command(terminal, command, i);
	}
	free(command->command);
	for (int j = 0; command->arguments[j]; j++)
		free(command->arguments[j]);
	free(command->arguments);
	// else if (command->pipe == 1)
	// 	redirection_input(terminal, command, i);
	// else if (command->pipe == 2)
	// 	redirection_output(terminal, command, i);
}

void	exec_cmd(t_command *command, t_input *terminal)
{
	char	*cmd_path;
	char	**cmd_split;
	int		i;
	int		j;

	i = 0;
	j = 0;
	cmd_split = malloc(sizeof(char **) * 100);
	cmd_path = malloc(sizeof(char) * 100);
	cmd_split[j++] = ft_strdup(command->command);
	if (command->arguments[i])
	{
		while (command->arguments[i])
			cmd_split[j++] = ft_strdup(command->arguments[i++]);
	}
	if (access(command->command, F_OK) == 0)
	{
		execve(command->command, command->arguments, terminal->env);
		fprintf(stderr, "Minishell: %s: command not found\n", command->command);
		exit(EXIT_FAILURE);
	}
	cmd_path = search_path(terminal->env, command->command);
	if (execve(cmd_path, cmd_split, terminal->env) == -1)
	{
		fprintf(stderr, "Minishell: %s: command not found\n", command->command);
		free_exec_error(command, cmd_path, cmd_split);
		exit(EXIT_FAILURE);
	}
}
