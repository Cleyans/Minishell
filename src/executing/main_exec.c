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

extern int g_signal;

void	executing(t_input *terminal, t_command *command)
{
	int		i;
	int		*pid;

	i = 0;
	pid = malloc(sizeof(int) * 4096);
	if (pid == NULL)
		error_message("Error: malloc failed\n");
	while ( i < terminal->count_cmd)
	{
		if (pipe(terminal->p_fd[i]) == -1)
			error_message("Error: pipe failed\n");
		if ((builtins_check(command) == 0) || (builtins_check(command) == 1 && check_builtins_call(command) == 1))
			pid[i] = fork();
		else
			pid[i] = NOTCHILD;
		if (pid[i] == -1)
			error_message("Error: fork failed\n");
		else if (pid[i] == 0 || pid[i] == NOTCHILD)
			calling_function(terminal, command, i, pid[i]);
		else
			parent_process(terminal, i, pid[i]);
		if (pid[i] == 0)
			exit (g_signal);
		i++;
		if (command->next)
			command = command->next;
		terminal->nb_cmd++;
	}
	free(pid);
}

void	calling_function(t_input *terminal, t_command *command, int i, int pid)
{
	if ((command->pipe == 0 && i == 0) || (command->pipe == 0 && i == 0 && pid == NOTCHILD))
		first_command(terminal, command, i);
	else if ((command->pipe == 0 && i > 0) || (command->pipe == 0 && i > 0 && pid == NOTCHILD))
		middle_command(terminal, command, i);
	else if ((command->pipe == -1))
	{
		if (terminal->nb_cmd > 1)
			last_command(terminal, command, i);
		else
			only_one_command(terminal, command, i);
	}
}

void	exec_cmd(t_command *command, t_input *terminal)
{
	char	*cmd_path;
	char	**cmd_split;
	int		i;
	int		j;

	i = 0;
	j = 0;
	cmd_split = ft_calloc(command->args + 2, sizeof(char *));
	if (cmd_split == NULL)
		error_message("Error: malloc failed\n");
	args_alloc(command, cmd_split);
	cmd_split[j++] = ft_strdup(command->command);
	if (command->arguments && command->arguments[i])
		args_dup(command, cmd_split);
	if (access(command->command, F_OK) == 0)
	{
		cmd_path = command->command;
		execve(cmd_path, cmd_split, terminal->env);
		exec_error(command, cmd_path, cmd_split);
	}
	cmd_path = search_path(terminal->env, command->command);
	if (execve(cmd_path, cmd_split, terminal->env) == -1)
		exec_error(command, cmd_path, cmd_split);
}

void	args_dup(t_command *command, char **cmd_split)
{
	int		i;
	int		j;

	i = 0;
	j = 1;
	printf("comand->args = %d\n", command->args);
	while (command->arguments[i] != NULL)
	{
		printf("ARGUMENT[%d] = %s\n", i, command->arguments[i]);
		cmd_split[j] = ft_strdup(command->arguments[i]);
		i++;
		j++;
	}
	cmd_split[j] = NULL;
}

void	args_alloc(t_command *command, char **cmd_split)
{
	int i;

	i = 0;

	while (command->arguments && command->arguments[i] != NULL)
	{
		cmd_split[i] = malloc(sizeof(char) * (ft_strlen(command->arguments[i]) + 1));
		if (cmd_split[i] == NULL)
			error_message("Error: malloc failed\n");
		i++;
	}
}

void	exec_error(t_command *command, char *cmd_path, char **cmd_split)
{
	fprintf(stderr, "Minishell: %s: command not found\n", command->command);
	free_exec_error(cmd_path, cmd_split);
	exit(EXIT_FAILURE);
}

void	error_message(char *message)
{
	fprintf(stderr, "Minishell: %s\n", message);
	exit(EXIT_FAILURE);
}