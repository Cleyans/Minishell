/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brclemen <brclemen@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:21:40 by brclemen          #+#    #+#             */
/*   Updated: 2024/08/19 17:21:40 by brclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Minishell.h"

void	free_args(char **argument)
{
	size_t	i;

	i = 0;
	if (!argument)
		return ;
	while (argument[i])
	{
		free(argument[i]);
		i++;
	}
	free(argument);
}



void	free_exec_error(char *cmd_path, char **cmd_split)
{
	int	i;

	i = 0;
	if (cmd_path)
		free(cmd_path);
	while (cmd_split[i])
	{
		free(cmd_split[i]);
		i++;
	}
	free(cmd_split);
}


void	free_nodes(t_command *command)
{
	t_command	*tmp;
	t_command	*next_node;

	if (command != NULL)
	{
		free(command->command);
		free_args(command->arguments);
		tmp = command->next;
		while (tmp != NULL)
		{
			next_node = tmp->next;
			free(tmp->command);
			free_args(tmp->arguments);
			free(tmp);
			tmp = next_node;
		}
		command->next = NULL;
	}
}
