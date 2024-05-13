/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brclemen <brclemen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 06:02:30 by brclemen          #+#    #+#             */
/*   Updated: 2024/05/09 06:02:30 by brclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Minishell.h"

void	ft_exit(t_input *terminal, t_command *command)
{
	int	i;

	i = 0;
	if (command->arguments[0] != NULL)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("Minishell: exit: too many arguments\n", 2);
		return ;
	}
	free(terminal->input);
	free(command->command);
	while (command->arguments[i] != NULL)
	{
		free(command->arguments[i]);
		i++;
	}
	free(command->arguments);
	exit(0);
}
