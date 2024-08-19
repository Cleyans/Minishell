/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 12:46:12 by marvin            #+#    #+#             */
/*   Updated: 2024/06/13 12:46:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Minishell.h"

void	init_env(t_input *terminal, char **env)
{
	int	i;

	terminal->env_size = 0;
	i = 0;
	if (env != NULL)
	{
		while (env[i] != NULL)
			i++;
		terminal->env = ft_calloc(i + 1, sizeof(char *));
		if (terminal->env == NULL)
			return ;
		i = 0;
		while (env[i] != NULL)
		{
			terminal->env[terminal->env_size] = ft_strdup(env[i]);
			i++;
			terminal->env_size++;
		}
		terminal->env[i] = NULL;
		i = 0;
	}
}

void	add_to_env(t_input *terminal, t_command *command, int arg_index)
{
	terminal->env = realloc(terminal->env,
			(terminal->env_size + 2) * sizeof(char *));
	if (terminal->env == NULL)
		return ;
	terminal->env[terminal->env_size]
		= ft_strdup(command->arguments[arg_index]);
	terminal->env[terminal->env_size + 1] = NULL;
	terminal->env_size++;
}

void	env(t_input *terminal)
{
	int	i;

	i = 0;
	while (terminal->env[i] != NULL)
	{
		printf("%s\n", terminal->env[i]);
		i++;
	}
}
