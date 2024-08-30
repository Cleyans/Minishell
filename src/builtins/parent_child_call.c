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
	if (ft_strcmp(command->command, "export") == 0)
	{
		ft_export(terminal, command);
		return (0);
	}
	else if (ft_strcmp(command->command, "unset") == 0)
	{
		ft_unset(terminal, command);
		return (0);
	}
	else if (ft_strcmp(command->command, "exit") == 0)
		ft_exit(terminal, command);
	if (ft_strcmp(command->command, "cd") == 0)
	{
		ft_cd(command);
		return (0);
	}
	return (builtins_parent_s(terminal, command));
}

int	builtins_parent_s(t_input *terminal, t_command *command)
{
	if (ft_strcmp(command->command, "env") == 0) // exit
	{
		env(terminal);
		return (0);
	}
	else if (ft_strcmp(command->command, "cd") == 0) // exit
	{
		ft_cd(command);
		return (g_signal);
	}
	else if (ft_strcmp(command->command, "pwd") == 0) // exit 
	{
		ft_pwd(command);
		return (g_signal);
	}
	else if (ft_strcmp(command->command, "echo") == 0)
	{
		g_signal = ft_echo(terminal, command);
		return (g_signal);
	}
	return (g_signal);
}