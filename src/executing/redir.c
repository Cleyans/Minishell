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

void    here_in(t_input *terminal, t_command *command, int i)
{
    char   *line;
    int     nb;

    nb = 0;
    close(terminal->p_fd[i][0]);
    while (1)
    {
        line = readline("> ");
        if (ft_strcmp(command->word, line) == 0)
            break ;
        command->arguments[nb] = ft_strdup(line);
        nb++;
        free(line);
    }
}

void    here_out(t_input *terminal, t_command *command, int i)
{
    close(terminal->p_fd[i][1]);
    command->fd = open(command->outfile, O_WRONLY | O_CREAT | O_APPEND, 0777);
    if (command->fd == -1)
        error_message("Error: open failed\n");
    dup2(command->fd, STDOUT_FILENO);
    close(command->fd);
}