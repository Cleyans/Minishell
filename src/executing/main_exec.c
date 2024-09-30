/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brclemen <brclemen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 01:29:31 by brclemen          #+#    #+#             */
/*   Updated: 2024/05/08 01:29:31 by brclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Minishell.h"

// create the right number of pid ?? if the process need to go through the parent??
// create the right number of pipe
// fork if needed
// dup2 / open / the output or input if needed
// executing the command ?

void executing(t_input *terminal, t_command *command)//CORR
{
	pid_t   *pid;
	int     i;
	int     p_fd[2];  // Pipe descripteur (0 = read, 1 = write)
	// prev_fd = stocke la sortie du pipe précédent
	if ((terminal->count_cmd > 1) || (terminal->count_cmd == 1 && builtins_check(command) == 0))
		pid = malloc(sizeof(pid_t) * (terminal->count_cmd));
	i = 0;
	while (i < terminal->count_cmd)
	{
		// Créer un pipe pour les commandes sauf la dernière
		if (i < terminal->count_cmd - 1)
		{
			if (pipe(p_fd) == -1)
				error_message(strerror(errno));
		}
		if ((terminal->count_cmd > 1) || (terminal->count_cmd == 1 && builtins_check(command) == 0))
		{
			pid[i] = fork();
			if (pid[i] == -1)
				error_message(strerror(errno));
			if (pid[i] == 0)
				child_process(terminal, command, p_fd, i);
		}
		parent_process(terminal, command, p_fd, i); // fork tout le temps mais si builtins juste attendre l'enfant et rien exec??
		if (command->next)
		{
			if (ft_strcmp(command->command, "export") == 0 && command->next->command) // MDR?? ca fonctionne mais bizarre de faire comme ca ig?
			{
				g_signal = 256;
				return;
			}
			command = command->next;
		}
		i++;
	}
	if ((terminal->count_cmd - terminal->builtins) > 0 && pid) //mieux gerer probeme parfois
	{
		waitingall(terminal, pid);
		free(pid);
	}
}

void	waitingall(t_input *terminal, pid_t *pid)
{
	int i;

	i = 0;
	while (i < terminal->count_cmd)
	{
		waitpid(pid[i], &g_signal, 0);
		i++;
	}
}

void    child_process(t_input *terminal, t_command *command, int *p_fd, int i) // un truc comme ca si pipe avec parent??
{
	if (i > 0) // Si ce n'est pas la première commande
	{
		// Rediriger l'entrée de la commande actuelle vers la sortie du pipe précédent
		dup2(terminal->prev_fd, STDIN_FILENO);
		close(terminal->prev_fd);
	}
	if (i < terminal->count_cmd - 1) // Si ce n'est pas la dernière commande
	{
		// Rediriger la sortie de la commande actuelle vers l'entrée du prochain pipe
		dup2(p_fd[1], STDOUT_FILENO);
		close(p_fd[0]);
		close(p_fd[1]);
	}
	check_redirs(command);
	if (builtins_check(command) == 1)
	{
		builtins_parent(terminal, command);
		exit (g_signal);
	}
	exec_cmd(command, terminal);
	exit(EXIT_FAILURE);  // Si exec échoue
}

void   	parent_process(t_input *terminal, t_command *command, int *p_fd, int i) // "echo hi | echo bye" renvoies les deux hi et bye, mauvaise gestion des pipes avec le parent si plusieurs commandes
{
	int save_in;
	int save_out;
	// Attendre l'enfant
	// Fermer les descripteurs de fichiers inutiles dans le parent
	if (terminal->prev_fd != -1)
		close(terminal->prev_fd);
	if (i < terminal->count_cmd - 1)
	{
		terminal->prev_fd = p_fd[0];
		close(p_fd[1]);
	}
	// Le descripteur de lecture du pipe devient le précédent pour la prochaine commande
	if (builtins_check(command) == 1 && terminal->count_cmd == 1)
	{
		save_and_redir(&save_in, &save_out, command);
		builtins_parent(terminal, command);
		restore_fds(save_in, save_out);
	}
}

void	save_and_redir(int *save_in, int *save_out, t_command *command)
{
	*save_in = dup(STDIN_FILENO);
	*save_out = dup(STDOUT_FILENO);
	check_redirs(command);
}

void	restore_fds(int save_in, int save_out)
{
	dup2(save_in, STDIN_FILENO);
	dup2(save_out, STDOUT_FILENO);
	close(save_in);
	close(save_out);
}

void	check_redirs(t_command *command)
{
	if (command->redir_in == 1)
		redir_in(command);
	if (command->redir_out == 1)
		redir_out(command);
	if (command->hd_in == 1)
		here_in(command);
	if (command->hd_out == 1)
		here_out(command);
}

void	exec_cmd(t_command *command, t_input *terminal)
{
	char	*cmd_path;
	char	**cmd_split;
	int		i;
	int		j;

	i = 0;
	j = 0;
	cmd_split = ft_calloc(command->args + 2, sizeof(char *));
	if (cmd_split == NULL)
		error_message(strerror(errno));
	cmd_split[j++] = ft_strdup(command->command);
	if (command->arguments && command->arguments[i])
		args_dup(command, cmd_split);
	if (access(command->command, F_OK) == 0)
	{
		cmd_path = command->command;
		execve(cmd_path, cmd_split, terminal->env);
		exec_error(command, cmd_path, cmd_split);
	}
	cmd_path = search_path(terminal->env, command->command);
	if (cmd_path == NULL)
		exec_error(command, NULL, cmd_split);
	else if (execve(cmd_path, cmd_split, terminal->env) == -1) //LEAK
		exec_error(command, cmd_path, cmd_split);
}

void	args_dup(t_command *command, char **cmd_split)
{
	int		i;
	int		j;

	i = 0;
	j = 1;
	while (command->arguments[i] != NULL)
	{
		cmd_split[j] = ft_strdup(command->arguments[i]);
		i++;
		j++;
	}
	cmd_split[j] = NULL;
}
