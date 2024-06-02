/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brclemen <brclemen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:55:08 by brclemen          #+#    #+#             */
/*   Updated: 2024/05/20 12:55:08 by brclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Minishell.h"

void    redir_in(t_input *terminal, t_command *command, int i)
{
    close(terminal->p_fd[i][0]);
    command->fd = open(command->infile, O_RDONLY);
    if (command->fd == -1)
        error_message("Error: open failed\n");
    dup2(command->fd, STDIN_FILENO);
    close(command->fd);
}

void    redir_out(t_input *terminal, t_command *command, int i)
{
    close(terminal->p_fd[i][1]);
    command->fd = open(command->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (command->fd == -1)
        error_message("Error: open failed\n");
    dup2(command->fd, STDOUT_FILENO);
    close(command->fd);
}

// void    here_in(t_input *terminal, t_command *command, int i)
// {
//     //
// }

void    here_out(t_input *terminal, t_command *command, int i)
{
    close(terminal->p_fd[i][1]);
    command->fd = open(command->outfile, O_WRONLY | O_CREAT | O_APPEND, 0777);
    if (command->fd == -1)
        error_message("Error: open failed\n");
    dup2(command->fd, STDOUT_FILENO);
    close(command->fd);
}