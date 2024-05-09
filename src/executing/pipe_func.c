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

#include "../../include/Minishell.h" // executer dans le main pipe le builtins enfant et si pas trouver parent

void	first_command(t_input *terminal, t_command *command, int i)
{
	close(terminal->p_fd[i][0]);
	dup2(terminal->p_fd[i][1], STDOUT_FILENO);
	close(terminal->p_fd[i][1]);
	builtins_child(command);
	exec_cmd(command, terminal);
}

void	middle_command(t_input *terminal, t_command *command, int i)
{
	close(terminal->p_fd[i][0]);
	dup2(terminal->p_fd[i - 1][0], STDIN_FILENO);
	close(terminal->p_fd[i - 1][0]);
	dup2(terminal->p_fd[i][1], STDOUT_FILENO);
	close(terminal->p_fd[i][1]);
	builtins_child(command);
	exec_cmd(command, terminal);
}

void	last_command(t_input *terminal, t_command *command, int i)
{
	close(terminal->p_fd[i][0]);
	close(terminal->p_fd[i][1]);
	dup2(terminal->p_fd[i - 1][0], STDIN_FILENO);
	close(terminal->p_fd[i - 1][0]);
	builtins_child(command);
	exec_cmd(command, terminal);
}

void	only_one_command(t_input *terminal, t_command *command, int i)
{
	close(terminal->p_fd[i][0]);
	close(terminal->p_fd[i][1]);
	builtins_child(command);
	exec_cmd(command, terminal);
}

void	parent_process(t_input *terminal, int i, pid_t pid)
{
	waitpid(pid, NULL, 0);
	close(terminal->p_fd[i][1]);
}
