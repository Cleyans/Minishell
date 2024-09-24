/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brclemen <brclemen@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:58:11 by brclemen          #+#    #+#             */
/*   Updated: 2024/08/19 16:58:11 by brclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Minishell.h"

void	exec_error(t_command *command, char *cmd_path, char **cmd_split)
{
	fprintf(stderr, "Minishell: %s: command not found\n", command->command);
	free_exec_error(cmd_path, cmd_split);
	exit(1);
}

void	error_message(char *message)
{
	fprintf(stderr, "Minishell: %s\n", message);
	exit(1);
}
