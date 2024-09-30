/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brclemen <brclemen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:55:08 by brclemen          #+#    #+#             */
/*   Updated: 2024/05/20 12:55:08 by brclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Minishell.h"

void	redir_in(t_command *command) //CORR
{
	command->fd = open(command->infile, O_RDONLY);
	if (command->fd == -1)
		error_message(strerror(errno));
	dup2(command->fd, STDIN_FILENO);
	close(command->fd);
}

void	redir_out(t_command *command)
{
	command->fd = open(command->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (command->fd == -1)
		error_message(strerror(errno));
	dup2(command->fd, STDOUT_FILENO);
	close(command->fd);
}

void	here_in( t_command *command) //CORR
{
	char	*line;
	char	*join;
	char	*rline;

	rline = ft_strdup("");
	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(command->word, line) == 0)
			break ;
		join = ft_strjoin(rline, line);
		free(line);
		free(rline);
		rline = ft_strjoin(join, "\n");
		free(join);
	}
	if (ft_strcmp(command->command, "cat") == 0)
		ft_putstr_fd(rline, STDOUT_FILENO);
	else if (ft_strcmp(command->command, "echo") == 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
	else if (command->command[0] > 0 && command->command[0] < 127)
	{
		if (verif_absolute_path(command) == 0)
			ft_putstr_fd(rline, STDOUT_FILENO);
	}
	if (rline)
		free(rline);
	exit(0);
}

int	verif_absolute_path(t_command *command) //CORR
{
	int		end;
	int		i;
	char	*verif;

	i = 0;
	end = ft_strlen(command->command);
	while (command->command[end - 1] != '/')
		end--;
	verif = malloc(sizeof(char) * (ft_strlen(command->command) - end));
	while (command->command[end] != '\0')
	{
		verif[i] = command->command[end];
		i++;
		end++;
	}
	verif[i] = '\0';
	printf("verif = %s\n", verif);
	if (ft_strcmp(verif, "cat") == 0)
	{
		free(verif);
		return (0);
	}
	else if (ft_strcmp(verif, "echo") == 0)
	{
		free(verif);
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (2);
	}
	return (1);
}

void	here_out(t_command *command)
{
	command->fd = open(command->outfile, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (command->fd == -1)
		error_message(strerror(errno));
	dup2(command->fd, STDOUT_FILENO);
	close(command->fd);
}
