/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brclemen <brclemen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 05:52:36 by brclemen          #+#    #+#             */
/*   Updated: 2024/05/09 05:52:36 by brclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Minishell.h"

void	builtins_child(t_command *command)
{
	command->arguments = remove_empty_args(command->arguments);
	if (ft_strcmp(command->command, "echo") == 0)
	{
		ft_echo(command);
		exit(1);
	}
}

int	builtins_parent(t_input *terminal, t_command *command)
{
	command->arguments = remove_empty_args(command->arguments);
	// if (ft_strcmp(command->command, "export") == 0)
	// {
	//     ft_export(command);
	//     return (1);
	// }
	// if (ft_strcmp(command->command, "unset") == 0)
	// {
	//     ft_unset(command);
	//     return (1);
	// }
	// else if (ft_strcmp(command->command, "env") == 0)
	// {
	//     ft_env(command);
	//     return (1);
	// }
	if (ft_strcmp(command->command, "cd") == 0)
	{
		ft_cd(command);
		return (1);
	}
	else if (ft_strcmp(command->command, "pwd") == 0)
	{
		ft_pwd(command);
		return (1);
	}
	else if (ft_strcmp(command->command, "exit") == 0)
		ft_exit(terminal, command);
	return (0);
}

void	ft_echo(t_command *command)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (ft_strcmp(command->arguments[i], "-n") == 0)
	{
		i++;
		flag = 1;
	}
	while (command->arguments[i] != NULL)
	{
		ft_putstr_fd(command->arguments[i], 2);
		if (command->arguments[i + 1] != NULL)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (flag == 0)
		ft_putstr_fd("\n", 1);
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
