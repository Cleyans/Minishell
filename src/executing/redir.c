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

// Redir

void    redir_in(t_input *terminal, t_command *command, int i)
{
    close(terminal->p_fd[i][0]);
    command->fd = open(command->infile, O_RDONLY);
    if (command->fd == -1)
        error_message("Error: open failed\n");
    dup2(command->fd, STDIN_FILENO);
    close(command->fd);
}

void    redir_out(t_input *terminal, t_command *command, int i)
{
    close(terminal->p_fd[i][1]);
    command->fd = open(command->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (command->fd == -1)
        error_message("Error: open failed\n");
    dup2(command->fd, STDOUT_FILENO);
    close(command->fd);
}

// Heredoc

void    hd_out(t_input *terminal, t_command *command, int i)
{
    close(terminal->p_fd[i][0]);
    command->fd = open(command->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (command->fd == -1)
        error_message("Error: open failed\n");
    dup2(command->fd, STDIN_FILENO);
    close(command->fd);
}

void	hd_in(t_input *terminal, t_command *command, int i)
{
    char *eof;
    char *buff;

    signal(SIGINT, SIG_DFL);
    close(terminal->p_fd[i][0]);
    eof = ft_strdup(command->word);
    rl_clear_history();
    buff = readline_here_doc(eof);
    free(eof);
    ft_putstr_fd(buff, terminal->p_fd[i][1]);
    free(buff);
    close(terminal->p_fd[i][1]);
}

char    *readline_here_doc(char *eof)
{
	char	*buf;
	char	*buff;
	char	*bufff;

	buff = ft_strdup("");
	while (1)
	{
		buf = readline("> ");
		if (!buf || !ft_strncmp(buf, eof, -1))
			break ;
		bufff = ft_strjoin(buff, buf);
		free(buf);
		buff = ft_strjoin(bufff, "\n");
	}
	return (buff);
}
