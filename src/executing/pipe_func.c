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
    printf("first_command\n");
    if (command->redirection == 0)
    {
        close(terminal->p_fd[i][0]);
        command->fd = open(command->infile, O_RDONLY);
        if (command->fd == -1)
            error_message("Error: open failed\n");
        dup2(command->fd, STDIN_FILENO);
        close(command->fd);
    }
    else
	    close(terminal->p_fd[i][0]);
    if (command->redirection == 1)
    {
        close(terminal->p_fd[i][1]);
        command->fd = open(command->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (command->fd == -1)
            error_message("Error: open failed\n");
        dup2(command->fd, STDOUT_FILENO);
        close(command->fd);
    }
    else
    {
	    dup2(terminal->p_fd[i][1], STDOUT_FILENO);
        close(terminal->p_fd[i][1]);
    }
	builtins_child(terminal, command);
	exec_cmd(command, terminal);
}

void	middle_command(t_input *terminal, t_command *command, int i) // verif si redirection envoyer pipe resultat
{
    printf("middle_command\n\n");
    if (command->redirection == 0)
    {
        command->fd = open(command->infile, O_RDONLY);
        if (command->fd == -1)
            error_message("Error: open failed\n");
        dup2(command->fd, STDIN_FILENO);
        close(command->fd);
    }
    else
    {
        close(terminal->p_fd[i][0]);
        dup2(terminal->p_fd[i - 1][0], STDIN_FILENO);
        close(terminal->p_fd[i - 1][0]);
    }
    if (command->redirection == 1)
    {
        command->fd = open(command->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (command->fd == -1)
            error_message("Error: open failed\n");
        dup2(command->fd, STDOUT_FILENO);
        close(command->fd);
    }
    else
    {
        dup2(terminal->p_fd[i][1], STDOUT_FILENO);
        close(terminal->p_fd[i][1]);
    }
	exec_cmd(command, terminal);
}

void	last_command(t_input *terminal, t_command *command, int i)
{
    printf("last_command\n\n");
    if (command->redirection == 0)
    {
        close(terminal->p_fd[i][0]);
        command->fd = open(command->infile, O_RDONLY);
        if (command->fd == -1)
            error_message("Error: open failed\n");
        dup2(command->fd, STDIN_FILENO);
        close(command->fd);
    }
    else
    {
        close(terminal->p_fd[i][0]);
        dup2(terminal->p_fd[i - 1][0], STDIN_FILENO);
        close(terminal->p_fd[i - 1][0]);
    }
    if (command->redirection == 1)
    {
        close(terminal->p_fd[i][1]);
        command->fd = open(command->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (command->fd == -1)
            error_message("Error: open failed\n");
        dup2(command->fd, STDOUT_FILENO);
        close(command->fd);
    }
    else
    {
        close(terminal->p_fd[i][1]);
        dup2(terminal->p_fd[i - 1][1], STDIN_FILENO);
        close(terminal->p_fd[i - 1][1]);
    }
    builtins_child(terminal, command);
	exec_cmd(command, terminal);
}

void	only_one_command(t_input *terminal, t_command *command, int i)
{
    printf("only_one_command\n\n");
    if (command->redirection == 0)
    {
        close(terminal->p_fd[i][0]);
        command->fd = open(command->infile, O_RDONLY);
        if (command->fd == -1)
            error_message("Error: open failed\n");
        dup2(command->fd, STDIN_FILENO);
        close(command->fd);
    }
    else
	    close(terminal->p_fd[i][0]);
    if (command->redirection == 1)
    {
        close(terminal->p_fd[i][1]);
        command->fd = open(command->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (command->fd == -1)
            error_message("Error: open failed\n");
        dup2(command->fd, STDOUT_FILENO);
        close(command->fd);
    }
    else
	    close(terminal->p_fd[i][1]);
	builtins_child(terminal, command);
	exec_cmd(command, terminal);
}

void	parent_process(t_input *terminal, int i, pid_t pid)
{
	waitpid(pid, NULL, 0);
	close(terminal->p_fd[i][1]);
}
