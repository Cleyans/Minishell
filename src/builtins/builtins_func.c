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
	int	i;

	i = 0;
	if (command->arguments[0] != NULL)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("Minishell: exit: too many arguments\n", 2);
		return ;
	}
	free(terminal->input);
	free(command->command);
	while (command->arguments[i] != NULL)
	{
		free(command->arguments[i]);
		i++;
	}
	free(command->arguments);
	exit(0);
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

void	ft_pwd(t_command *command) // ne pas oublier le status
{
	char	*buffer;
	int		buffer_size;

	buffer_size = 1024;
	buffer = malloc(sizeof(char) * buffer_size);
	if (command->arguments[0] != NULL)
	{
		fprintf(stderr, "Error: pwd: too many arguments\n");
		return ;
	}
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
