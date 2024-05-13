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

// void	checking_input(t_input *terminal, t_command *command)
// {
// 	int	i;
// 	int	j;
// 	int	k;
// 	int	input_length;
// 	int	token_index;

// 	i = -1;
// 	input_length = ft_strlen(terminal->input);
// 	token_index = 0;
// 	if (!terminal->input)
// 		return ;
// 	while (i++ < input_length)
// 	{
// 		j = 0;
// 		while (i < input_length && terminal->input[i] == ' ')
// 			i++;
// 		while (i < input_length && white_space(terminal->input[i]) == 0
// 			&& find_p_r(terminal->input[i]) == 0)
// 		{
// 			if (command->redirection == 1)
// 				command->infile[j] = terminal->input[i];
// 			else if (command->redirection == 0)
// 				command->outfile[j] = terminal->input[i];
// 			else
// 				command->command[j] = terminal->input[i];
// 			i++;
// 			j++;
// 		}
// 		command->command[j] = '\0';
// 		k = 0;
// 		command->arguments[k] = malloc(100 * sizeof(char));
// 		while (i < input_length && terminal->input[i] == ' ')
// 			i++;
// 		while (i < input_length && find_p_r(terminal->input[i]) == 0)
// 		{
// 			if (white_space(terminal->input[i]) == 1)
// 			{
// 				command->arguments[k][token_index] = '\0';
// 				token_index = 0;
// 				k++;
// 				command->arguments[k] = malloc(100 * sizeof(char));
// 			}
// 			else
// 			{
// 				command->arguments[k][token_index] = terminal->input[i];
// 				token_index++;
// 			}
// 			i++;
// 		}
// 		command->arguments[k][token_index] = '\0';
// 		command->arguments[k + 1] = NULL;
// 		if (terminal->input[i] == '|')
// 			command->pipe = 0;
// 		else if (terminal->input[i] == '<')
// 			command->redirection = 0;
// 		else if (terminal->input[i] == '>')
// 			command->redirection = 1;
// 		else
// 			command->pipe = -1;
// 		ft_lstadd_back_m(&command, ft_lstnew_m());
// 		command->arguments = remove_empty_args(command->arguments);
// 		command = command->next;
// 		i++;
// 	}
// }


int	find_p_r(char c)
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

int	verif_input(t_input *terminal)
{
	if (terminal->input[0] != '\0' && terminal->input[0] != '\n'
		&& terminal->input[0] != '\t'
		&& terminal->input[0] != ' ' && terminal->input[0] != '\v'
		&& terminal->input[0] != '\f' && terminal->input[0] != '\r')
		return (0);
	return (1);
}

void	cheking_input(t_input *terminal, t_command *command) // doit pouvoir prendre outfile et infile dans la meme commande, pour l'instant il ne prend que le premier, quand redirection la commande ne veux pas se mettre dedans
{
	t_parss	parss;
	init_parss(&parss);
	while (terminal->input[parss.i])
	{
		while (terminal->input[parss.i] && terminal->input[parss.i] != '|')
		{
			while (terminal->input[parss.i] == ' ')
				parss.i++;
			if (terminal->input[parss.i] == '<' || terminal->input[parss.i] == '>')
				check_redir(terminal, command, &parss);
			if (parss.cmd_c == 1)
				put_arg_cmd(terminal, command, &parss);
			while ((terminal->input[parss.i] != ' ' && terminal->input[parss.i] != '\0' && parss.cmd_c == 0) || (terminal->input[parss.i] != ' ' && terminal->input[parss.i] != '\0' && parss.cmd_c == -1))
			{
				command->command[parss.j] = terminal->input[parss.i];
				parss.i++;
				parss.j++;
				parss.cmd_c = 0;
			}
			if (parss.cmd_c == 0)
			{
				command->command[parss.j] = '\0';
				parss.cmd_c = 1;
				parss.j = 0;
			}
			parss.i++;
		}
		if (terminal->input[parss.i] == '|')
			command->pipe = 0;
		else
			command->pipe = -1;
		parss.cmd_c = -1;
		parss.j = 0;
		ft_lstadd_back_m(&command, ft_lstnew_m());
		command->arguments = remove_empty_args(command->arguments);
		command = command->next;
		parss.i++;
	}
}

void	check_redir(t_input *terminal, t_command *command, t_parss *parss)
{
	if (terminal->input[parss->i] == '<')
	{
		command->redirection = 0;
		call_redir_infile(terminal, command, parss);
	}
	else if (terminal->input[parss->i] == '>')
	{
		command->redirection = 1;
		call_redir_outfile(terminal, command, parss);
	}
}

void	call_redir_infile(t_input *terminal, t_command *command, t_parss *parss)
{
	parss->i++;
	while (terminal->input[parss->i] == ' ')
		parss->i++;
	command->infile = malloc(sizeof(char) * 100);
	command->infile[0] = '\0';
	while (terminal->input[parss->i] != ' ' && terminal->input[parss->i] != '\0')
	{
		command->infile[parss->j] = terminal->input[parss->i];
		parss->i++;
		parss->j++;
	}
	command->infile[parss->j] = '\0';
}

void	call_redir_outfile(t_input *terminal, t_command *command, t_parss *parss)
{
	parss->i++;
	while (terminal->input[parss->i] == ' ')
		parss->i++;
	command->outfile = malloc(sizeof(char) * 100);
	command->outfile[0] = '\0';
	while (terminal->input[parss->i] != ' ' && terminal->input[parss->i] != '\0')
	{
		command->outfile[parss->j] = terminal->input[parss->i];
		parss->i++;
		parss->j++;
	}
	command->outfile[parss->j] = '\0';
	parss->j = 0;
}

void	put_arg_cmd(t_input *terminal, t_command *command, t_parss *parss)
{
	command->arguments[parss->j] = malloc(sizeof(char) * 100);
	while (terminal->input[parss->i] != ' ' && terminal->input[parss->i])
	{
		command->arguments[parss->j][parss->k] = terminal->input[parss->i];
		parss->i++;
		parss->k++;
	}
	command->arguments[parss->j][parss->k] = '\0';
	parss->k = 0;
	parss->j++;
}

void	init_parss(t_parss *parss)
{
	parss->i = 0;
	parss->j = 0;
	parss->k = 0;
	parss->cmd_c = -1;
}

void	advanced_print(t_command *command)
{
	while (command->next != NULL)
	{
		int	i;

		i = 0;
		printf("command = %s\n", command->command);
		while (command->arguments[i] != NULL)
		{
			printf("arguments[%d] = %s\n", i, command->arguments[i]);
			i++;
		}
		if (command->redirection == 1)
			printf("outfile = %s\n", command->outfile);
		else if (command->redirection == 0)
			printf("infile = %s\n", command->infile);
		if (command->pipe == 0)
			printf("pipe = 0\n");
		else
			printf("pipe = -1\n");
		if (command->redirection == 0)
			printf("redirection = 0\n");
		else if (command->redirection == 1)
			printf("redirection = 1\n");
		else
			printf("redirection = -1\n");
		printf("builtins = %d\n", command->builtins);
		printf("\n");
		command = command->next;
	}
}