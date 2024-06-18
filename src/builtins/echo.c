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
	int	flag;

	i = 0;
	flag = 0;
	if (ft_echo_check(command->arguments[i], "-n", terminal, command) == 0)
	{
		i++;
		flag = 1;
	}
	while (command->arguments[i] != NULL && terminal->echo.close == 0)
	{
		printf_echo(command->arguments[i]);
		if (command->arguments[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (flag == 0 && terminal->echo.close == 0)
		printf("\n");
	return (0);
}

int	ft_echo_check(char *s, char *s2, t_input *terminal, t_command *command)
{
	terminal->echo.len_s2 = ft_strlen(s2);
	while (s[terminal->echo.i] != '\0')
	{
		if (s[terminal->echo.i] == '\'')
			terminal->echo.s_quotes = !terminal->echo.s_quotes;
		else if (s[terminal->echo.i] == '\"')
			terminal->echo.d_quotes = !terminal->echo.d_quotes;
		else if (s[terminal->echo.i] != '\'' && s[terminal->echo.i] != '\"')
		{
			if (s[terminal->echo.i] == s2[terminal->echo.search_s2])
				terminal->echo.search_s2++;
			else
				terminal->echo.search_s2 = 0;
		}
		terminal->echo.i++;
	}
	if ((terminal->echo.len_s2 == terminal->echo.search_s2))
	{
		if (terminal->echo.s_quotes == 0 && terminal->echo.d_quotes == 0)
			return (check_echo_args(command, terminal, 1, 0));
		else if (terminal->echo.s_quotes == 1 || terminal->echo.d_quotes == 1)
			return (check_echo_args(command, terminal, 1, 1));
	}
	return (1);
}

int	check_echo_args(t_command *command, t_input *terminal, int i, int valid)
{
	int	j;

	j = -1;
	while (command->arguments[i] != NULL)
	{
		j = 0;
		while (command->arguments[i][j] != '\0')
		{
			if (command->arguments[i][j] == '\'')
				terminal->echo.s_quotes = !terminal->echo.s_quotes;
			else if (command->arguments[i][j] == '\"')
				terminal->echo.d_quotes = !terminal->echo.d_quotes;
			j++;
		}
		i++;
	}
	if (terminal->echo.s_quotes == 1 || terminal->echo.d_quotes == 1)
	{
		fprintf(stderr, "echo: quotes not closed\n");
		exit (1);
	}
	else if (valid == 1)
		return (1);
	return (0);
}

void	printf_echo(char *s)
{
	size_t	index;

	index = 0;
	while (s[index])
	{
		if (s[index] != '\'' && s[index] != '\"')
			printf("%c", s[index]);
		index++;
	}
}
