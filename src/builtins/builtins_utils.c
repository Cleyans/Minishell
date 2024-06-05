/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brclemen <brclemen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 22:45:18 by brclemen          #+#    #+#             */
/*   Updated: 2024/05/31 22:45:18 by brclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Minishell.h"

int	builtins_check(t_command *command)
{
	if (ft_strcmp(command->command, "export") == 0)
		return (1);
	else if (ft_strcmp(command->command, "unset") == 0)
		return (1);
	else if (ft_strcmp(command->command, "env") == 0)
		return (1);
	else if (ft_strcmp(command->command, "cd") == 0)
		return (1);
	else if (ft_strcmp(command->command, "pwd") == 0)
		return (1);
	else if (ft_strcmp(command->command, "exit") == 0)
		return (1);
	return (0);
}

int	check_builtins_call(t_command *command)
{
	if (command->redir_in == 1 || command->redir_out == 1
		|| command->hd_in == 1 || command->hd_out == 1)
		return (1);
	else
		return (0);
}

void	builtins_call(t_input *terminal, t_command *command)
{
	if (command->redir_in == 1 || command->redir_out == 1
		|| command->hd_in == 1 || command->hd_out == 1)
		builtins_child(terminal, command);
	else
		builtins_parent(terminal, command);
}