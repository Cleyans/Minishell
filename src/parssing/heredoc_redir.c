/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brclemen <brclemen@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:37:40 by brclemen          #+#    #+#             */
/*   Updated: 2024/08/19 16:37:40 by brclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Minishell.h"

void	check_redir(t_input *terminal, t_command *command, t_parss *parss) //CORR
{
	if (terminal->input[parss->i] == '<'
		&& terminal->input[parss->i + 1] == '<')
	{
		parss->i = parss->i + 2;
		command->hd_in = 1;
		call_heredoc_in(terminal, command, parss);
	}
	else if (terminal->input[parss->i] == '>'
		&& terminal->input[parss->i + 1] == '>')
	{
		parss->i = parss->i + 2;
		command->hd_out = 1;
		call_heredoc_out(terminal, command, parss);
	}
	else if (terminal->input[parss->i] == '<')
	{
		command->redir_in = 1;
		call_redir_infile(terminal, command, parss);
	}
	else if (terminal->input[parss->i] == '>')
	{
		command->redir_out = 1;
		call_outfile(terminal, command, parss);
	}
	// else if (terminal->input[parss->i] == '$')
	// 	call_dollar(terminal, command, parss);
}

void	call_heredoc_in(t_input *terminal, t_command *command, t_parss *parss)
{
	int	i;
	int	len;
	int	mem;

	i = 0;
	mem = 0;
	while (terminal->input[parss->i] == ' ')
		parss->i++;
	len = parss->i;
	while (terminal->input[len] != ' ' && terminal->input[len] != '\0')
	{
		len++;
		mem++;
	}
	command->word = malloc(sizeof(char) * (mem + 1));
	while (terminal->input[parss->i] != ' '
		&& terminal->input[parss->i] != '\0')
	{
		command->word[i] = terminal->input[parss->i];
		parss->i++;
		i++;
	}
	command->word[i] = '\0';
	printf("word = %s\n", command->word);
}

void	call_heredoc_out(t_input *terminal, t_command *command, t_parss *parss)
{
	int	i;
	int	len;
	int	mem;

	i = 0;
	mem = 0;
	while (terminal->input[parss->i] == ' ')
		parss->i++;
	len = parss->i;
	while (terminal->input[len] != ' '
		&& terminal->input[len] != '\0')
	{
		len++;
		mem++;
	}
	command->outfile = malloc(sizeof(char) * (mem + 1));
	while (terminal->input[parss->i] != ' '
		&& terminal->input[parss->i] != '\0')
	{
		command->outfile[i] = terminal->input[parss->i];
		parss->i++;
		i++;
	}
	command->outfile[i] = '\0';
}

void	call_redir_infile(t_input *terminal, t_command *command, t_parss *parss)
{
	int	i;
	int	len;
	int	mem;

	i = 0;
	mem = 0;
	parss->i++;
	while (terminal->input[parss->i] == ' ')
		parss->i++;
	len = parss->i;
	while (terminal->input[len] != ' '
		&& terminal->input[len] != '\0')
	{
		len++;
		mem++;
	}
	command->infile = malloc(sizeof(char) * (mem + 1));
	printf("parsss->i = %d\ni = %d\n", parss->i, i);
	while (terminal->input[parss->i] != ' '
		&& terminal->input[parss->i] != '\0')
	{
		command->infile[i] = terminal->input[parss->i];
		parss->i++;
		i++;
	}
	command->infile[i] = '\0';
}

void	call_outfile(t_input *terminal, t_command *command, t_parss *parss)
{
	int	i;
	int	len;
	int	mem;

	i = 0;
	mem = 0;
	parss->i++;
	while (terminal->input[parss->i] == ' ')
		parss->i++;
	len = parss->i;
	while (terminal->input[len] != ' '
		&& terminal->input[len] != '\0')
	{
		len++;
		mem++;
	}
	command->outfile = malloc(sizeof(char) * (mem + 1));
	while (terminal->input[parss->i] != ' '
		&& terminal->input[parss->i] != '\0')
	{
		command->outfile[i] = terminal->input[parss->i];
		parss->i++;
		i++;
	}
	command->outfile[i] = '\0';
}
