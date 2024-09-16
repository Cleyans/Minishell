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
	free(terminal->input);
	free_terminal(terminal);
	free_nodes(command);
	exit(0);
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

void	ft_cd(t_command *command) // ne pas oublier le status
{
	char	*path;

	if (command->arguments[0] == NULL)
	{
		path = getenv("HOME");
		if (chdir(path) == -1)
		{
			fprintf(stderr, "Minishell: cd: %s:\
 No such file or directory\n", path);
			return ;
		}
	}
	else
	{
		if (chdir(command->arguments[0]) == -1)
		{
			fprintf(stderr, "Minishell: cd: %s: No such file or\
 directory\n", command->arguments[0]);
			return ;
		}
	}
}

void	ft_pwd(t_command *command) // ne pas oublier le status //CORR
{
	char	*buffer;
	int		buffer_size;

	buffer_size = 1024;
	buffer = malloc(sizeof(char) * buffer_size);
	if (buffer == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		return ;
	}
	if (getcwd(buffer, 1024) == NULL)
	{
		fprintf(stderr, "Error: getcwd failed\n");
		free(buffer);
		return ;
	}
	ft_printf("%s\n", buffer);
	free(buffer);
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
