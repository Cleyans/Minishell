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
	int	flag;

	flag = 0;
	if (command->arguments[0])
	{
		if (ft_strcmp("-n", command->arguments[0]) == 0)
			flag = 1;
		printf_echo_s(terminal, command);
	}
	if (flag == 0)
		printf("\n");
	return (0);
}

// arg_q not used

void	printf_echo_s(t_input *terminal, t_command *command)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (command->arguments[i])
	{
		j = 0;
		while (command->arguments[i][j])
		{
			if (command->arguments[i][j] == '$'
				&& command->arguments[i][j + 1] == '?')
				j = j + status_print();
			else if (command->arguments[i][j] == '$'
				&& command->arguments[i][j + 1]
					&& command->arg_q[i] == 34)
				j = j + ft_dollar_echo(terminal, command->arguments[i], j);
			write(1, &command->arguments[i][j], 1);
			j++;
		}
		i++;
		if (command->arguments[i])
			write(1, " ", 1);
	}
}

int	status_print(void)
{
	int		i;
	char	*status;

	status = ft_itoa(g_signal);
	while (status[i] != '\0')
	{
		write(1, &status[i], 1);
		i++;
	}
	return (2);
}

int	ft_dollar_echo(t_input *terminal, char *arg, int there) //CORR
{
	int		i;
	int		lmalloc;
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

void	ft_call_dollar_env(t_input *terminal, char *dollar) //CORR
{
	int	i;
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
