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

	while (terminal->input[parss.i] && terminal->input[parss.i] != '\0')
	{
		while (terminal->input[parss.i] != '\0' && terminal->input[parss.i] != '|' && terminal->input[parss.i] != '$')
		{
			while (terminal->input[parss.i] == ' ')
				parss.i++;
			if (terminal->input[parss.i] == '<' || terminal->input[parss.i] == '>' || terminal->input[parss.i] == '$')
			{
				check_redir(terminal, command, &parss);
				parss.i++;
				if (terminal->input[parss.i] == '<' || terminal->input[parss.i] == '>')
					parss.i++;
			}	
			if (parss.cmd_c == 1 && terminal->input[parss.i])
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
			if(terminal->input[parss.i] == '\0')
				break;
			parss.i++;

		}
		if (terminal->input[parss.i] == '|')
		{
			terminal->nb_pipe++;
			command->pipe = 0;
			parss.i++;
		}
		else
			command->pipe = -1;
		parss.cmd_c = -1;
		parss.j = 0;
		// parss.i++;
		ft_lstadd_back_m(&command, ft_lstnew_m());
		command->arguments = remove_empty_args(command->arguments);
		command = command->next;
	}
}

void	check_redir(t_input *terminal, t_command *command, t_parss *parss)
{
	if (terminal->input[parss->i] == '<' && terminal->input[parss->i + 1] == '<')
	{
		command->hd_in = 1;
		call_heredoc(terminal, command, parss);
	}
	else if (terminal->input[parss->i] == '>' && terminal->input[parss->i + 1] == '>')
	{
		command->hd_out = 1;
		call_heredoc(terminal, command, parss);
	}
	else if (terminal->input[parss->i] == '<')
	{
		command->redir_in = 1;
		call_redir_infile(terminal, command, parss);
	}
	else if (terminal->input[parss->i] == '>')
	{
		command->redir_out = 1;
		call_redir_outfile(terminal, command, parss);
	}
	else if (terminal->input[parss->i] == '$')
		call_dollar(terminal, command, parss);
}

void		call_heredoc(t_input *terminal, t_command *command, t_parss *parss)
{
	int i;

	i = 0;
	parss->i++;
	parss->i++;
	while (terminal->input[parss->i] == ' ')
		parss->i++;
	command->infile = malloc(sizeof(char) * 100);
	// command->infile[0] = terminal->input[parss->i];
	// parss->i++;
	while (terminal->input[parss->i] != ' ' && terminal->input[parss->i] != '\0')
	{
		command->infile[i] = terminal->input[parss->i];
		parss->i++;
		i++;
	}
	command->infile[i] = '\0';
}

void	call_redir_infile(t_input *terminal, t_command *command, t_parss *parss)
{
	int i;

	i = 0;
	parss->i++;
	while (terminal->input[parss->i] == ' ')
		parss->i++;
	command->infile = malloc(sizeof(char) * 100);
	// command->infile[0] = terminal->input[parss->i];
	// parss->i++;
	while (terminal->input[parss->i] != ' ' && terminal->input[parss->i] != '\0')
	{
		command->infile[i] = terminal->input[parss->i];
		parss->i++;
		i++;
	}
	command->infile[i] = '\0';
}

void	call_redir_outfile(t_input *terminal, t_command *command, t_parss *parss)
{
	int i;

	i = 0;
	parss->i++;
	while (terminal->input[parss->i] == ' ')
		parss->i++;
	command->outfile = malloc(sizeof(char) * 100);
	// command->outfile[i] = terminal->input[parss->i];
	// parss->i++;
	while (terminal->input[parss->i] != ' ' && terminal->input[parss->i] != '\0')
	{
		command->outfile[i] = terminal->input[parss->i];
		parss->i++;
		i++;
	}
	command->outfile[i] = '\0';
	// parss->j = 0;
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
	command->arguments[parss->j + 1] = '\0';
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
		if (command->redir_out == 1)
			printf("outfile = %s\n", command->outfile);
		if (command->redir_in == 1)
			printf("infile = %s\n", command->infile);
		if (command->hd_out == 0)
			printf("outfile = %s\n", command->outfile);
		if (command->hd_in == 1)
			printf("infile = %s\n", command->infile);
		if (command->pipe == 0)
			printf("pipe = 0\n");
		else
			printf("pipe = -1\n");
		if (command->int_dollar == 1 || command->int_dollar == 0)
			printf("int_dollar = %d\n", command->int_dollar);
		if(command->int_dollar == 0)
			printf("int_dollar = %s\n", command->dollar);
		if (command->redir_in == 1)
			printf("redir_in = 1\n");
		else if (command->redir_out == 1)
			printf("redir_out = 1\n");
		else
			printf("redir_in = -1\nredir_out = -1\n");
		if (command->hd_in == 1)
			printf("hd_in = 1\n");
		else if (command->hd_out == 1)
			printf("hd_out = 1\n");
		else
			printf("hd_in = -1\nhd_out = -1\n");
		printf("Command out dollar : %s\n", command->out_dollar);
		printf("builtins = %d\n", command->builtins);
		printf("\n");
		command = command->next;
	}
}

void call_dollar(t_input *terminal, t_command *command, t_parss *parss)
{
	printf("HERE 0\n");
	while(terminal->input[parss->i] != '\0')
	{
		printf("HERE 1\n");
		command->dollar = malloc(sizeof(char) * 100);
		int i;

		i = 0;
		if ((terminal->input[parss->i] == '$') && terminal->input[parss->i + 1] == '?' && terminal->input[parss->i + 1] != '\0')
		{
			// call_dollar_interogation(input, command, parss);
			command->int_dollar = 1;
			return;
		}
		parss->i++;
		while (terminal->input[parss->i] != ' ' && terminal->input[parss->i] != '\0')
		{
			command->dollar[i] = terminal->input[parss->i];
			parss->i++;
			i++;
			command->int_dollar = 0;
		}
		if (command->int_dollar == 0)
		{
			printf("HERE 2\n");
			search_path_dollar(terminal, command);
			parss->i++;
		}
		command->dollar[i] = '\0';
		parss->i++;
		// print_commands(command);
	}
}


void	*search_path_dollar(t_input *terminal, t_command *command)
{	
    int			i;
    int			j;
    int			k;
    int			l;
	printf("HERE 1\n");
    command->out_dollar = malloc(sizeof(char) * 10000);
    if (command->out_dollar == NULL) {
        return NULL;
    }
	printf("HERE 2\n");
    l = 0;
    i = 0;
    while (terminal->env[i] != NULL)
    {
		printf("HERE 3\n");
        j = 0;
        k = 0;
        while (terminal->env[i][j] != '\0')
        {
			printf("HERE 4\n");
            while (terminal->env[i][j] == command->dollar[k] && terminal->env[i][j] != '\0')
            {
				printf("HERE 5\n");
                j++;
                k++;
                if (terminal->env[i][j] == '=')
                {
					printf("HERE 6\n");
                    j++;
                    while (terminal->env[i][j] != '\0') {
                        command->out_dollar[l++] = terminal->env[i][j++];
                    }
                    command->out_dollar[l] = '\0';
                    return command->out_dollar;
                }
            }
            if (command->dollar[k] != '\0') {
                break;
            }
            j++;
        }
        i++;
    }
	printf("HERE 7\n");
	printf("out_dollar = %s\n", command->out_dollar);
    free(command->out_dollar);
    command->out_dollar = NULL;
    return NULL;
}


int check_char(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}