/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brclemen <brclemen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 01:32:43 by brclemen          #+#    #+#             */
/*   Updated: 2024/05/08 01:32:43 by brclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Minishell.h"



void	first_command(t_input *terminal, t_command *command, int i)
{
	if (command->redir_in == 1)
		redir_in(terminal, command, i);
	else if (command->hd_in == 1)
		here_in(terminal, command, i);
	else
		close(terminal->p_fd[i][0]);
	if (command->redir_out == 1)
		redir_out(terminal, command, i);
	else if (command->hd_out == 1)
		here_out(terminal, command, i);
	else
	{
		dup2(terminal->p_fd[i][1], STDOUT_FILENO);
		close(terminal->p_fd[i][1]);
	}
	if (builtins_check(command) == 1)
		g_signal = builtins_call(terminal, command);
	else
		exec_cmd(command, terminal);
}

void	middle_command(t_input *terminal, t_command *command, int i)
{
	if (command->redir_in == 1)
		redir_in(terminal, command, i);
	else if (command->hd_in == 1)
		here_in(terminal, command, i);
	else
	{
		close(terminal->p_fd[i][0]);
		dup2(terminal->p_fd[i - 1][0], STDIN_FILENO);
		close(terminal->p_fd[i - 1][0]);
	}
	if (command->redir_out == 1)
		redir_out(terminal, command, i);
	else if (command->hd_out == 1)
		here_out(terminal, command, i);
	else
	{
		dup2(terminal->p_fd[i][1], STDOUT_FILENO);
		close(terminal->p_fd[i][1]);
	}
	if (builtins_check(command) == 1)
		g_signal = builtins_call(terminal, command);
	else
		exec_cmd(command, terminal);
}

void	last_command(t_input *terminal, t_command *command, int i)
{
	if (command->redir_in == 1)
		redir_in(terminal, command, i);
	else if (command->hd_in == 1)
		here_in(terminal, command, i);
	else
	{
		close(terminal->p_fd[i][0]);
		dup2(terminal->p_fd[i - 1][0], STDIN_FILENO);
		close(terminal->p_fd[i - 1][0]);
	}
	if (command->redir_out == 1)
		redir_out(terminal, command, i);
	else if (command->hd_out == 1)
		here_out(terminal, command, i);
	else
	{
		close(terminal->p_fd[i][1]);
		dup2(terminal->p_fd[i - 1][1], STDIN_FILENO);
		close(terminal->p_fd[i - 1][1]);
	}
	if (builtins_check(command) == 1)
		g_signal = builtins_call(terminal, command);
	else
		exec_cmd(command, terminal);
}

void	only_one_command(t_input *terminal, t_command *command, int i)
{
	if (command->redir_in == 1)
		redir_in(terminal, command, i);
	else if (command->hd_in == 1)
		here_in(terminal, command, i);
	else
		close(terminal->p_fd[i][0]);
	if (command->redir_out == 1)
		redir_out(terminal, command, i);
	else if (command->hd_out == 1)
		here_out(terminal, command, i);
	else
		close(terminal->p_fd[i][1]);
	if (builtins_check(command) == 1)
		g_signal = builtins_call(terminal, command);
	else
		exec_cmd(command, terminal);
}

void	parent_process(t_input *terminal, int i, pid_t pid)
{
	waitpid(pid, &g_signal, 0);
	close(terminal->p_fd[i][1]);
}
