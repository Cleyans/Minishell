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
	else if (ft_strcmp(command->command, "echo") == 0)
		return (1);
	else if (ft_strcmp(command->command, "cd") == 0)
		return (1);
	else if (ft_strcmp(command->command, "pwd") == 0)
		return (1);
	else if (ft_strcmp(command->command, "exit") == 0)
		return (1);
	return (0);
}
