/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 12:47:46 by marvin            #+#    #+#             */
/*   Updated: 2024/06/13 12:47:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Minishell.h"

static void	unset_env(t_input *terminal, char *arg)
{
	int		j;
	char	*arg_start;

	j = 0;
	while (terminal->env[j] != NULL)
	{
		arg_start = terminal->env[j];
		if (ft_strncmp(arg_start, arg, ft_strlen(arg)) == 0
			&& (arg_start[ft_strlen(arg)] == '='
				|| arg_start[ft_strlen(arg)] == '\0'))
		{
			free(terminal->env[j]);
			while (terminal->env[j] != NULL)
			{
				terminal->env[j] = terminal->env[j + 1];
				j++;
			}
			terminal->env[j - 1] = NULL;
			terminal->env_size--;
			break ;
		}
		j++;
	}
}

void	ft_unset(t_input *terminal, t_command *command) //CORR
{
	int		i;
	int		j;
	char	*arg_start;
	char	*prefix;

	prefix = "declare -x ";
	i = 0;
	while (command->arguments[i] != NULL)
	{
		j = 0;
		while (terminal->export[j] != NULL)
		{
			arg_start = terminal->export[j] + ft_strlen(prefix);
			if (ft_strncmp(arg_start, command->arguments[i],
					ft_strlen(command->arguments[i])) == 0
				&& (arg_start[ft_strlen(command->arguments[i])] == '='
					|| arg_start[ft_strlen(command->arguments[i])] == '\0'))
			{
				free(terminal->export[j]);
				while (terminal->export[j] != NULL)
				{
					terminal->export[j] = terminal->export[j + 1];
					j++;
				}
				terminal->export[j - 1] = NULL;
				terminal->i--;
				break ;
			}
			j++;
		}
		unset_env(terminal, command->arguments[i]);
		i++;
	}
}

char	*create_new_str(char *str, char *equal_pos)
{
	char	*new_str;
	int		i;
	int		j;

	new_str = malloc((equal_pos - str) + (ft_strlen(equal_pos) + 3));
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (str + i != equal_pos)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i++] = '=';
	j = 0;
	while (equal_pos[j + 1] != '\0')
	{
		new_str[i] = equal_pos[j + 1];
		i++;
		j++;
	}
	new_str[i] = '\0';
	return (new_str);
}
