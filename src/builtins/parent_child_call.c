/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_child_call.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brclemen <brclemen@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:04:41 by brclemen          #+#    #+#             */
/*   Updated: 2024/08/19 17:04:41 by brclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Minishell.h"

int	builtins_parent(t_input *terminal, t_command *command)
{
	check_redirs(command);
	if (ft_strcmp(command->command, "export") == 0)
		return (g_signal = ft_export(terminal, command));
	else if (ft_strcmp(command->command, "unset") == 0)
		return (g_signal = ft_unset(terminal, command));
	else if (ft_strcmp(command->command, "cd") == 0)
		return (g_signal = ft_cd(command));
	else if (ft_strcmp(command->command, "exit") == 0)
		ft_exit(terminal, command);
	return (builtins_parent_s(terminal, command));
}

int	builtins_parent_s(t_input *terminal, t_command *command)
{
	if (ft_strcmp(command->command, "env") == 0) // exit
		return (g_signal = env(terminal));
	else if (ft_strcmp(command->command, "cd") == 0) // exit
		return (g_signal = ft_cd(command));
	else if (ft_strcmp(command->command, "pwd") == 0) // exit 
		return (g_signal = ft_pwd(command));
	else if (ft_strcmp(command->command, "echo") == 0)
		return (g_signal = ft_echo(terminal, command));
	return (g_signal);
}