/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parss.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brclemen <brclemen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 06:03:58 by brclemen          #+#    #+#             */
/*   Updated: 2024/05/09 06:03:58 by brclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Minishell.h"

void	checking_input(t_input *terminal, t_command *command)
{
	int	i;
	int	j;
	int	k;
	int	input_length;
	int	token_index;

	i = -1;
	input_length = ft_strlen(terminal->input);
	token_index = 0;
	if (!terminal->input)
		return ;
	while (i++ < input_length)
	{
		j = 0;
		while (i < input_length && terminal->input[i] == ' ')
			i++;
		while (i < input_length && white_space(terminal->input[i]) == 0
			&& find_pipe(terminal->input[i]) == 0)
		{
			command->command[j] = terminal->input[i];
			i++;
			j++;
		}
		command->command[j] = '\0';
		k = 0;
		command->arguments[k] = malloc(100 * sizeof(char));
		while (i < input_length && terminal->input[i] == ' ')
			i++;
		while (i < input_length && find_pipe(terminal->input[i]) == 0)
		{
			if (white_space(terminal->input[i]) == 1)
			{
				command->arguments[k][token_index] = '\0';
				token_index = 0;
				k++;
				command->arguments[k] = malloc(100 * sizeof(char));
			}
			else
			{
				command->arguments[k][token_index] = terminal->input[i];
				token_index++;
			}
			i++;
		}
		command->arguments[k][token_index] = '\0';
		command->arguments[k + 1] = NULL;
		if (terminal->input[i] == '|')
			command->pipe = 0;
		else if (terminal->input[i] == '<')
			command->pipe = 1;
		else if (terminal->input[i] == '>')
			command->pipe = 2;
		else
			command->pipe = -1;
		ft_lstadd_back_m(&command, ft_lstnew_m());
		command = command->next;
		i++;
	}
	command->arguments = remove_empty_args(command->arguments);
}

int	verif_input(t_input *terminal)
{
	if (terminal->input[0] != '\0' && terminal->input[0] != '\n'
		&& terminal->input[0] != '\t'
		&& terminal->input[0] != ' ' && terminal->input[0] != '\v'
		&& terminal->input[0] != '\f' && terminal->input[0] != '\r')
		return (0);
	return (1);
}

int	find_pipe(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	white_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}
