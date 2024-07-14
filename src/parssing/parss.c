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

extern int g_singal;

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

void	all_init_malloc(t_command *command, t_input *terminal, t_parss *parss)
{
	// int i;

	// arg_q not used !!!!!!!!! solve the problem


	init_parss(parss);
	// count_nb_args(terminal, command);
	command->arguments = malloc(sizeof(char *) * command->args + 1);
	command->command = malloc(sizeof(char) * command->mem_cmd + 1);
	// command->arg_q = (int *)malloc((command->args + 1) * sizeof(int));
	// i = 0;
	// while (i < command->args + 1)
	// {
	// 	command->arg_q[i] = 0;
	// 	i++;
	// }
}

void	cheking_input(t_input *terminal, t_command *command) // if echo and betweneen "" everything goes into argument even if > < 
{
	t_parss	parss;

	all_init_malloc(command, terminal, &parss);
	while (terminal->input[parss.i] && terminal->input[parss.i] != '\0')
	{
		while (terminal->input[parss.i] != '\0' && terminal->input[parss.i] != '|')
		{
			while (terminal->input[parss.i] == ' ')
				parss.i++;
			if (terminal->input[parss.i] == '<' || terminal->input[parss.i] == '>')
			{
				check_redir(terminal, command, &parss);
				parss.i++;
				if (terminal->input[parss.i] == '<' || terminal->input[parss.i] == '>')
					parss.i++;
			}	
			if (parss.cmd_c == 1 && terminal->input[parss.i])
				put_arg_cmd(terminal, command, &parss);
			if ((parss.cmd_c == 0) || parss.cmd_c == -1)
				put_command(terminal, command, &parss);
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
			command->pipe = 0;
			parss.i++;
		}
		else
			command->pipe = -1;
		command->arguments[parss.j] = NULL;
		parss.j = 0;
		parss.cmd_c = -1;
		terminal->count_cmd++;
		ft_lstadd_back_m(&command, ft_lstnew_m());
		command->arguments = remove_empty_args(command->arguments);
		command = command->next;
	}
	command->arguments[parss.j] = NULL;
}

void	args_quotes(t_input *terminal, t_command *command, t_parss *parss)
{
	int	len;
	int	mem;
	parss->i++;

	len = parss->i;
	mem = 0;
	while (terminal->input[len] != '\"' && terminal->input[len] != '\0')
	{
		len++;
		mem++;
	}
	if (terminal->input[len] == '\"')
		command->arguments[parss->j] = malloc(sizeof(char *) * (mem + 1));
	else
		return ;
	len = 0;
	while (terminal->input[parss->i] != '\"' && terminal->input[parss->i] != '\0')
	{
		command->arguments[parss->j][len] = terminal->input[parss->i];
		len++;
		parss->i++;
	}
	command->arguments[parss->j][len] = '\0';
	if (terminal->input[parss->i] == '\"')
		parss->i++;
	parss->j++;
}

void	args_quote(t_input *terminal, t_command *command, t_parss *parss)
{
	int	len;
	int	mem;
	parss->i++;

	len = parss->i;
	mem = 0;
	while (terminal->input[len] != '\'' && terminal->input[len] != '\0')
	{
		len++;
		mem++;
	}
	if (terminal->input[len] == '\'')
		command->arguments[parss->j] = malloc(sizeof(char *) * (mem + 1));
	else
		return ;
	len = 0;
	while (terminal->input[parss->i] != '\'' && terminal->input[parss->i] != '\0')
	{
		command->arguments[parss->j][len] = terminal->input[parss->i];
		len++;
		parss->i++;
	}
	command->arguments[parss->j][len] = '\0';
	if (terminal->input[parss->i] == '\'')
		parss->i++;
	parss->j++;
}

void	put_command(t_input *terminal, t_command *command, t_parss *parss)
{
	int	i;
	int	mem;

	i = parss->i;
	mem = 0;
	while (terminal->input[i] != ' ' && terminal->input[i] != '\0')
	{
		i++;
		mem++;
	}
	command->command = malloc(sizeof(char) * mem + 1);
	while (terminal->input[parss->i] != ' ' && terminal->input[parss->i] != '\0')
	{
		command->command[parss->j] = terminal->input[parss->i];
		parss->i++;
		parss->j++;
		parss->cmd_c = 0;
	}
	command->command[parss->j] = '\0';
}


void	check_redir(t_input *terminal, t_command *command, t_parss *parss)
{
	if (terminal->input[parss->i] == '<' && terminal->input[parss->i + 1] == '<')
	{
		command->hd_in = 1;
		call_heredoc_in(terminal, command, parss);
	}
	else if (terminal->input[parss->i] == '>' && terminal->input[parss->i + 1] == '>')
	{
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
		call_redir_outfile(terminal, command, parss);
	}
	// else if (terminal->input[parss->i] == '$')
	// 	call_dollar(terminal, command, parss);
}

void		call_heredoc_in(t_input *terminal, t_command *command, t_parss *parss)
{
	int i;
	int	len;
	int mem;

	i = 0;
	len = parss->i;
	mem = 0;
	parss->i = parss->i + 2;
	while (terminal->input[parss->i] == ' ')
		parss->i++;
	while (terminal->input[len] != ' ' && terminal->input[len] != '\0')
	{
		len++;
		mem++;
	}
	command->word = malloc(sizeof(char) * mem + 1);
	while (terminal->input[parss->i] != ' ' && terminal->input[parss->i] != '\0')
	{
		command->word[i] = terminal->input[parss->i];
		parss->i++;
		i++;
	}
	command->word[i] = '\0';
}

void	call_heredoc_out(t_input *terminal, t_command *command, t_parss *parss)
{
	int i;
	int	len;
	int mem;

	i = 0;
	len = parss->i;
	mem = 0;
	parss->i = parss->i + 2;
	while (terminal->input[parss->i] == ' ')
		parss->i++;
	while (terminal->input[len] != ' ' && terminal->input[len] != '\0')
	{
		len++;
		mem++;
	}
	command->outfile = malloc(sizeof(char) * mem + 1);
	while (terminal->input[parss->i] != ' ' && terminal->input[parss->i] != '\0')
	{
		command->outfile[i] = terminal->input[parss->i];
		parss->i++;
		i++;
	}
	command->outfile[i] = '\0';
}

void	call_redir_infile(t_input *terminal, t_command *command, t_parss *parss)
{
	int i;
	int len;
	int mem;

	i = 0;
	len = parss->i;
	mem = 0;
	parss->i++;
	while (terminal->input[parss->i] == ' ')
		parss->i++;
	while (terminal->input[len] != ' ' && terminal->input[len] != '\0')
	{
		len++;
		mem++;
	}
	command->infile = malloc(sizeof(char) * mem + 1);
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
	int len;
	int mem;

	i = 0;
	len = parss->i;
	mem = 0;
	parss->i++;
	while (terminal->input[parss->i] == ' ')
		parss->i++;
	while (terminal->input[len] != ' ' && terminal->input[len] != '\0')
	{
		len++;
		mem++;
	}
	command->outfile = malloc(sizeof(char) * mem + 1);
	while (terminal->input[parss->i] != ' ' && terminal->input[parss->i] != '\0')
	{
		command->outfile[i] = terminal->input[parss->i];
		parss->i++;
		i++;
	}
	command->outfile[i] = '\0';
}

void	put_arg_cmd(t_input *terminal, t_command *command, t_parss *parss) // si tu trouves " tu mets dans le meme arguments jusqua trouver la fermeture
{
	int	len;
	int	mem;

	len = parss->i;
	mem = 0;
	while (terminal->input[len] != ' ' && terminal->input[len]) // verif if ' "" are closed amd then malloc... br
	{
		if (terminal->input[len] == '\'' || terminal->input[len] == '\"')
			len = len + is_quote_len(terminal, parss, terminal->input[len]);
		len++;
		mem++;
	}
	command->arguments[parss->j] = malloc(sizeof(char) * mem + 1);
	while (terminal->input[parss->i] != ' ' && terminal->input[parss->i])
	{
		if ((terminal->input[parss->i] == '\'' || terminal->input[parss->i] == '\"') && (terminal->input[parss->i] != '\0'))
			if (is_quote(terminal, command, parss) == 42)
				break;
		if (terminal->input[parss->i] != ' ' && terminal->input[parss->i] != '\0')
		{
			command->arguments[parss->j][parss->k] = terminal->input[parss->i];
			parss->i++;
			parss->k++;
		}
		if (terminal->input[parss->i] == '\0')
			break;
		// else
		// 	parss->i++;
	}
	command->arguments[parss->j][parss->k] = '\0';
		// if (command->arg_q[parss->j] != '\'' && command->arg_q[parss->j] != '\"')
		// 	command->arg_q[parss->j] = 0;
	parss->k = 0;
	parss->j++;
}

void	count_nb_args(t_input *terminal, t_command *command, t_parss *parss) // doesn't word with pipe, because start at the begin of the input
{
	int i;
	int k;
	int flag;

	flag = 0;
	i = parss->i;
	k = 0;
	while (terminal->input[i] == ' ')
	{
		i++;
		command->mem_cmd++;
	}
	while (terminal->input[i] != '\0')
	{
		while (terminal->input[i] != ' ' && terminal->input[i])
		{
			if (terminal->input[i] == '\'' || terminal->input[i] == '\"')
				if (is_quote_nb_args(terminal, command, terminal->input[i], i) == 42)
				{
					flag = 1;
					break;
				}
			if (terminal->input[i] != ' ')
				i++;
		}
		if (terminal->input[i] != '\0')
			i++;
		if (flag != 0)
			break;
		command->args++;
	}
}

int	is_quote_nb_args(t_input *terminal, t_command *command, char c, int i)
{
	i++;
	while (terminal->input[i] != c && terminal->input[i] != '\0')
		i++;
	if (terminal->input[i] == '\0')
		return (42);
	return (0);
}

int	is_quote(t_input *terminal, t_command *command, t_parss *parss)
{
	char	c;

	c = terminal->input[parss->i];
	parss->i++;
	while (terminal->input[parss->i] != c && terminal->input[parss->i] != '\0')
	{
		command->arguments[parss->j][parss->k] = terminal->input[parss->i];
		parss->i++;
		parss->k++;
	}
	command->arg_q[parss->j] = c;
	if (terminal->input[parss->i] == '\0')
		return (42);
	else if (terminal->input[parss->i] == c)
		parss->i++;
	return (0);
}

int	is_quote_len(t_input *terminal, t_parss *parss, char c)
{
	int	i;
	int len;

	len = 0;
	i = parss->i;
	while (terminal->input[i] != c && terminal->input[i] != '\0')
	{
		len++;
		i++;
	}
	return (len);
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
		printf("G_SINGAL = %d\n", g_singal);
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