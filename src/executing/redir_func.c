/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brclemen <brclemen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 01:34:00 by brclemen          #+#    #+#             */
/*   Updated: 2024/05/08 01:34:00 by brclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Minishell.h"

// void    redirection_input(t_input *terminal, t_command *command, int i)
// {
//     int fd;

//     fd = open(command->file, O_RDONLY);
//     if (fd == -1)
//         error_message("open");
//     dup2(fd, STDIN_FILENO);
//     close(fd);
//     exec_cmd(command, terminal);
// }

// void    redirection_output(t_input *terminal, t_command *command, int i)
// {
//     int fd;

//     fd = open(command->file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
//     if (fd == -1)
//         error_message("open");
//     dup2(fd, STDOUT_FILENO);
//     close(fd);
//     exec_cmd(command, terminal);
// }