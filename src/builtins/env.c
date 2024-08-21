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

#include <stdlib.h>
#include <string.h>

void	init_env(t_input *terminal, char **env)
{
	int i = 0;

	if (env == NULL)
		return ;
	while (env[i])
		i++;
	terminal->env = malloc(sizeof(char **) * (i + 1));
	if (terminal->env == NULL)
		return ;
	i = 0;
	while (env[i] != NULL)
	{
		terminal->env[i] = env[i];
		i++;
	}
	terminal->env[i] = NULL;
	terminal->env_size = i;
}

void	add_to_env(t_input *terminal, t_command *command, int arg_index)
{
    char	**new_env;
    int		i;

    new_env = malloc((terminal->env_size + 2) * sizeof(char *));
    if (new_env == NULL)
        return ;
    i = 0;
    while (i < terminal->env_size)
    {
        new_env[i] = terminal->env[i];
        i++;
    }
    new_env[i] = ft_strdup(command->arguments[arg_index]);
    new_env[i + 1] = NULL;
    free(terminal->env);
    terminal->env = new_env;
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
