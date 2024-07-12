/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brclemen <brclemen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 09:22:13 by brclemen          #+#    #+#             */
/*   Updated: 2024/05/10 09:22:13 by brclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Minishell.h"

int	ft_echo(t_input *terminal, t_command *command)
{
	int	i;
	int flag;

	flag = 0;
	i = 0;
	if (command->arguments[0])
	{
		if (ft_strcmp("-n", command->arguments[0]) == 0)
			flag = 1; // to print the \n
		printf_echo_s(terminal, command);
	}
	if (flag == 0)
		printf("\n");
	return (0);
}

void	printf_echo_s(t_input *terminal, t_command *command) // 34 == double quotes, 39 == single quotes
{
	// printf("CMD = %s\n", command->command);
	// for (int i = 0; command->arguments[i]; i++)
	// {
	// 	printf("ARGUMENT[%d] = %s\n", i, command->arguments[i]);
	// 	printf("arg_q[%d] = %d\n", i, command->arg_q[i]);
	// }
	int	i;
	int	j;
	int skip;

	i = 0;
	j = 0;
	while (command->arguments[i])
	{
		j = 0;
		while (command->arguments[i][j])
		{
			if (command->arguments[i][j] == '$' && command->arguments[i][j + 1] == '?' && command->arg_q[i] == 0)
				j = j + status_print(terminal);
			else if (command->arguments[i][j] == '$' && command->arguments[i][j + 1]
					&& command->arg_q[i] == 34) // c'est le moment ou faut print tout le env $
				j = j + ft_dollar_echo(terminal, command->arguments[i], j);
			write(1, &command->arguments[i][j], 1);
			j++;
		}
		i++;
		if (command->arguments[i])
			write(1, " ", 1);
	}
}

int	status_print(t_input *terminal)
{
	int	i;
	char	*status;
	
	status = ft_itoa(terminal->status);
	while (status[i] != '\0')
	{
		write(1, &status[i], 1);
		i++;
	}
	return (2);
}

int	ft_dollar_echo(t_input *terminal, char *arg, int there)
{
	int i;
	int lmalloc;
	char	*dollar;

	i = there;
	lmalloc = 0;
	while (arg[i] != ' ' && arg[i] != '\0')
	{
		lmalloc++;
		i++;
	}
	dollar = malloc(sizeof(char *) * (lmalloc - 1));
	if (!dollar)
		error_message("Error : Malloc failed\n");
	i = 0;
	there++;
	while (arg[there] != ' ' && arg[there] != '\0')
	{
		dollar[i] = arg[there];
		there++;
		i++;
	}
	dollar[i] = '\0';
	ft_call_dollar_env(terminal, dollar);
	free(dollar);
	return ((lmalloc));
}

void	ft_call_dollar_env(t_input *terminal, char *dollar)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while (terminal->env[i])
	{
		if (ft_memcmp(dollar, terminal->env[i], ft_strlen(dollar)) == 0)
		{
			while (terminal->env[i][j] != '=')
				j++;
			if (terminal->env[i][j] == '=' && terminal->env[i][j + 1])
			{
				j++;
				while (terminal->env[i][j])
				{
					write(1, &terminal->env[i][j], 1);
					j++;
				}
			}
			else
				break ;
		}
		j = 0;
		i++;
	}
}

// CUT


// void	printf_echo(char *s, char c, t_input *terminal, t_command *command)
// {
// 	size_t	index;
// 	int skip;
// 	char *status;
// 	int	i_s;

// 	i_s = 0;
// 	skip = 0;
// 	index = 0;
// 	while (s[index])
// 	{
// 		if (s[index] == '$' && s[index + 1])
// 		{
// 			if ((s[index + 1] == '?') && (s[index + 2] == ' ' || s[index + 2] == '\0') && (command->sd != 1 || command->sd == 0))
// 			{
// 				status = ft_itoa(terminal->status);
// 				while (status[i_s])
// 				{
// 					write(1, &status[i_s], 1);
// 					i_s++;
// 				}
// 				i_s = 0;
// 			}
// 			if (command->sd != 1)
// 			{
// 				skip = ft_dollar_echo(terminal, s, index);
// 				while (skip > 0)
// 				{
// 					skip--;
// 					index++;
// 				}
// 			}
// 		}
// 		if (s[index] != c)
// 			write(1, &s[index], 1);
// 		index++;
		
// 	}
// }

// int	ft_echo(t_input *terminal, t_command *command)
// {
// 	int		i;
// 	int		flag;
// 	char	*arg;
// 	char	*oline;

// 	i = 0;
// 	flag = 0;
// 	if (ft_echo_check(command->arguments[i], "-n", terminal, command) == 0)
// 	{
// 		i++;
// 		flag = 1;
// 	}
// 	if (flag == 1)
// 		i++;
// 	oline = put_all_that_shit(command);
// 	arg = ft_quote(oline, command);
// 	if (arg)
// 	{
// 		printf_echo(arg, command->sd, terminal, command);
// 		free(arg);
// 	}
// 	if (flag == 0 && terminal->echo.close == 0)
// 		printf("\n");
// 	return (0);
// }

// char *put_all_that_shit(t_command *command)
// {
// 	int		i;
// 	int		j;
// 	int		il;
// 	char	*line;

// 	il = 0;
// 	j = 0;
// 	i = 0;
// 	while (command->arguments[i])
// 	{
// 		if (command->arguments[i + 1])
// 			j = j + (ft_strlen(command->arguments[i]) + 1);
// 		else
// 			j = j + (ft_strlen(command->arguments[i]));
// 		i++;
// 	}
// 	line = malloc(sizeof(char) * (j + 1));
// 	i = 0;
// 	j = 0;
// 	while (command->arguments[i])
// 	{
// 		while (command->arguments[i][j])
// 		{
// 			line[il] = command->arguments[i][j];
// 			il++;
// 			j++;
// 		}
// 		if (command->args > 1)
// 		{
// 			line[il] = ' ';
// 			il++;
// 			command->args--;
// 		}
// 		j = 0;
// 		i++;
// 	}
// 	line[il] = '\0';
// 	return (line);
// }

// char	*ft_quote(char *s, t_command *command)
// {
// 	char *arg;
// 	int s_quote;
// 	int d_quote;
// 	int i;

// 	command->sd = 0;
// 	s_quote = 0;
// 	d_quote = 0;
// 	i = 0;
// 	arg = NULL;
// 	while (s[i] != '\0')
// 	{
// 		if (s[i] == '\'')
// 			s_quote = !s_quote;
// 		if (s[i] == '\"')
// 			d_quote = !d_quote;
// 		i++; 
// 	}
// 	if (s_quote == 1 && d_quote == 0)
// 		command->sd = ft_quote_close_verif(s, '\"', '\'');
// 	else if (d_quote == 1 && s_quote == 0)
// 		command->sd = ft_quote_close_verif(s, '\'', '\"');
// 	else if (d_quote == 1 && s_quote == 1)
// 		error_message("Quotes not closed\n");
// 	else
// 		command->sd = quote_zero(s);
// 	arg = ft_put_arg_echo(s, command->sd);
// 	return (arg == NULL ? s : arg);
// }

// int	quote_zero(char *s)
// {
// 	int	i;
	
// 	i = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == '\'')
// 			return (1);
// 		else if (s[i] == '\"')
// 			return (0);
// 		i++;
// 	}
// 	return (0);
// }

// char *ft_put_arg_echo(char *s, int c)
// {
// 	int	i;
// 	int len;
// 	char *arg;

// 	i = 0;
// 	len = 0;
// 	if (c == 0) // if c = 0 call another function to handle it
// 	{
// 		arg = malloc(sizeof(char) * (ft_strlen(s) + 1));
// 		while (s[i])
// 		{
// 			if (s[i] != '\'' && s[i] != '\"')
// 			{
// 				arg[len] = s[i];
// 				len++;
// 			}
// 			i++;
// 		}
// 	}
// 	else if (c == '\"')
// 	{
// 		arg = malloc (sizeof(char) * (ft_strlen(s)));
// 		while (s[i])
// 		{
// 			if (s[i] != '\'')
// 			{
// 				arg[len] = s[i];
// 				len++;
// 			}
// 			i++;
// 		}
// 	}
// 	else if (c == '\'')
// 	{
// 		while (s[i])
// 		{
// 			if (s[i] != 34)
// 				len++;
// 			i++;
// 		}
// 		arg = malloc(sizeof(char) * len + 1);
// 		len = 0;
// 		i = 0;
// 		while (s[i])
// 		{
// 			if (s[i] != 34)
// 			{
// 				arg[len] = s[i];
// 				len++;
// 			}
// 			i++;
// 		}
// 	}
// 	arg[len] = '\0';
// 	return (arg);
// }

// char	ft_quote_close_verif(char *s, char around, char between)
// {
// 	int fquote;
// 	int equote;
// 	int check;
// 	int i;

// 	fquote = -1;
// 	equote = -1;
// 	check = -1;
// 	i = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == around && fquote == -1)
// 			fquote = i;
// 		if (s[i] == around && fquote != -1)
// 			equote = i;
// 		if (s[i] == between)
// 			check = i;
// 		i++;
// 	}
// 	if (check < equote && check > fquote && around == '\'')
// 		return ('\''); // to not print
// 	else if (check < equote && check > fquote && around == '\"')
// 		return ('\"'); // to not print
// 	else
// 		return (0); 
// }


// int	ft_echo_check(char *s, char *s2, t_input *terminal, t_command *command)
// {
// 	terminal->echo.len_s2 = ft_strlen(s2);
// 	while (s[terminal->echo.i] != '\0')
// 	{
// 		if (s[terminal->echo.i] == '\'')
// 			terminal->echo.s_quotes = !terminal->echo.s_quotes;
// 		else if (s[terminal->echo.i] == '\"')
// 			terminal->echo.d_quotes = !terminal->echo.d_quotes;
// 		else if (s[terminal->echo.i] != '\'' && s[terminal->echo.i] != '\"')
// 		{
// 			if (s[terminal->echo.i] == s2[terminal->echo.search_s2])
// 				terminal->echo.search_s2++;
// 			else
// 				terminal->echo.search_s2 = 0;
// 		}
// 		terminal->echo.i++;
// 	}
// 	if ((terminal->echo.len_s2 == terminal->echo.search_s2))
// 	{
// 		if (terminal->echo.s_quotes == 0 && terminal->echo.d_quotes == 0)
// 			return (check_echo_args(command, terminal, 1, 0));
// 		else if (terminal->echo.s_quotes == 1 || terminal->echo.d_quotes == 1)
// 			return (check_echo_args(command, terminal, 1, 1));
// 	}
// 	return (1);
// }

// int	check_echo_args(t_command *command, t_input *terminal, int i, int valid)
// {
// 	int	j;

// 	j = -1;
// 	while (command->arguments[i] != NULL)
// 	{
// 		j = 0;
// 		while (command->arguments[i][j] != '\0')
// 		{
// 			if (command->arguments[i][j] == '\'')
// 				terminal->echo.s_quotes = !terminal->echo.s_quotes;
// 			else if (command->arguments[i][j] == '\"')
// 				terminal->echo.d_quotes = !terminal->echo.d_quotes;
// 			j++;
// 		}
// 		i++;
// 	}
// 	if (terminal->echo.s_quotes == 1 || terminal->echo.d_quotes == 1)
// 	{
// 		fprintf(stderr, "echo: quotes not closed\n");
// 		exit (1);
// 	}
// 	else if (valid == 1)
// 		return (1);
// 	return (0);
// }

