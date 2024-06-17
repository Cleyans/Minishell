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

extern int g_signal;

void	first_command(t_input *terminal, t_command *command, int i)
{
    // printf("first_command\n");
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

void	middle_command(t_input *terminal, t_command *command, int i) // verif si redirection envoyer pipe resultat
{
    // printf("middle_command\n\n");
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
    // printf("last_command\n\n");
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
    // printf("only_one_command\n\n");
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
	    close(terminal->p_fd[i][1]);\
    if (builtins_check(command) == 1)
        g_signal = builtins_call(terminal, command);
    else
	    exec_cmd(command, terminal);
}

void	parent_process(t_input *terminal, int i, pid_t pid)
{
        waitpid(pid, &terminal->status, 0);
        close(terminal->p_fd[i][1]);
}
