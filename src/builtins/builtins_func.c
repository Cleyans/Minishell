/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brclemen <brclemen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 06:02:30 by brclemen          #+#    #+#             */
/*   Updated: 2024/05/09 06:02:30 by brclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Minishell.h"

void	ft_exit(t_input *terminal, t_command *command)
{
	if (command->arguments[1] != NULL)
	{
		fprintf(stderr, "Minishell: exit: too many arguments\n");
		exit(1);
	}
	if(command->arguments[0] != NULL)
	{
		if (ft_stris_numeric(command->arguments[0]) == 1)
		{
			fprintf(stderr, "Minishell: exit: %s: numeric argument required\n", command->arguments[0]);
			exit(2);
		}
		else
			exit(ft_atoi(command->arguments[0]));
	}
	exit(1);
}

int ft_stris_alpha(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

int ft_stris_numeric(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

void	free_terminal(t_input *terminal)
{
	int	i;

	i = 0;
	if (terminal->env)
	{
		while (terminal->env[i] != NULL)
		{
			free(terminal->env[i]);
			i++;
		}
		free(terminal->env);
	}
	i = 0;
	if (terminal->export)
	{
		while (terminal->export[i] != NULL)
		{
			free(terminal->export[i]);
			i++;
		}
		free(terminal->export);
	}
}

int	ft_cd(t_command *command) //CORR EXIT
{
	char	*path;

	if (command->arguments[1] != NULL)
	{
		fprintf(stderr, "Minishell: cd: too many arguments\n");
		return (1);
	}
	if (command->arguments[0] == NULL)
	{
		path = getenv("HOME");
		if (chdir(path) == -1)
			return (0);
	}
	else
	{
		if (chdir(command->arguments[0]) == -1)
		{
			if (ft_stris_numeric(command->arguments[0]) == 0)
			{
				fprintf(stderr, "Minishell: cd: %s: No such file or\
 directory\n", command->arguments[0]);
				return (1);
			}
			else if (ft_stris_alpha(command->arguments[0]) == 0)
				return (0);
		}
	}
	return (0);
}

int	ft_pwd(t_command *command) // ne pas oublier le status //CORR
{
	char	*buffer;
	int		buffer_size;

	buffer_size = 1024;
	buffer = malloc(sizeof(char) * buffer_size);
	if (buffer == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		return (1);
	}
	if (getcwd(buffer, 1024) == NULL)
	{
		fprintf(stderr, "Error: getcwd failed\n");
		free(buffer);
		return (EXIT_FAILURE);
	}
	ft_printf("%s\n", buffer);
	free(buffer);
	return (EXIT_SUCCESS);
}

void	print_export(t_input *terminal)
{
	int	i;

	i = 0;
	while (terminal->export[i])
	{
		printf("%s\n", terminal->export[i]);
		i++;
	}
	g_signal = 0;
}
