#include "../../include/Minishell.h"

// only for one command || if we want to do more then one and more
//then one pipe, we have to know the amouth of pipe before the execution

void	executing(t_input *terminal, t_command *command) // utiliser deux cmd par pipe
{
	int		i;
	int		*pid;

	i = 0;
	pid = malloc(sizeof(int) * 4096);
	while (command->command[0] != '\0' && command->next != NULL)
	{
		if (pipe(terminal->p_fd[i]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		pid[i] = fork();
		if (pid[i] == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid[i] == 0)
		{
			if (command->pipe == 0 && terminal->nb_cmd == 1) // 0 lire et 1 ecrire
			{
				close(terminal->p_fd[i][0]);
				dup2(terminal->p_fd[i][1], STDOUT_FILENO);
				close(terminal->p_fd[i][1]);
				exec_cmd(command, terminal);
			}
			else if (command->pipe == 0 && terminal->nb_cmd > 1)
			{
				close(terminal->p_fd[i][0]);
				dup2(terminal->p_fd[i - 1][0], STDIN_FILENO);
				close(terminal->p_fd[i - 1][0]);
				dup2(terminal->p_fd[i][1], STDOUT_FILENO);
				close(terminal->p_fd[i][1]);
				exec_cmd(command, terminal);
			}
			else if (command->pipe == -1)
			{
				if (terminal->nb_cmd > 1)
				{
					close(terminal->p_fd[i][0]);
					close(terminal->p_fd[i][1]);
					dup2(terminal->p_fd[i - 1][0], STDIN_FILENO);
					close(terminal->p_fd[i - 1][0]);
					exec_cmd(command, terminal);
				}
				else
				{
					close(terminal->p_fd[i][0]);
					close(terminal->p_fd[i][1]);
					exec_cmd(command, terminal);
				}
			}
		}
		else
		{
			waitpid(pid[i], NULL, 0);
			close(terminal->p_fd[i][1]);
		}
		i++;
		command = command->next;
		terminal->nb_cmd++;
	}
	free(pid);
}


void	exec_cmd(t_command *command, t_input *terminal)
{
	char	*cmd_path;
	char	**cmd_split;
	int		i;
	int		j;

	i = 0;
	j = 0;
	cmd_split = malloc(sizeof(char **) * 100);
	cmd_path = malloc(sizeof(char) * 100);
	cmd_split[j++] = ft_strdup(command->command);
	command->arguments = remove_empty_args(command->arguments);
	if (command->arguments[i])
	{
		while (command->arguments[i])
			cmd_split[j++] = ft_strdup(command->arguments[i++]);
	}
	if (access(command->command, F_OK) == 0)
	{
		execve(command->command, command->arguments, terminal->env);
		perror("execve");
	}
	cmd_path = search_path(terminal->env, command->command);
	if (execve(cmd_path, cmd_split, terminal->env) == -1)
		perror("execve");
}

char **remove_empty_args(char **args)
{
    int i = 0;
    int j = 0;
	int k = 0;
	while (args[k])
		k++;
    char **new_args = malloc(sizeof(char *) * (k + 1));

    while (args[i])
    {
        if (args[i][0] != '\0')
        {
            new_args[j] = ft_strdup(args[i]);
            j++;
        }
        i++;
    }
    new_args[j] = NULL;
    return new_args;
}

char	*search_path(char **env, char *cmd_split)
{
	int			i;
	char		**paths;
	char		*cmd_final;
	char		*cmd_join;

	i = 0;
	while (env[i] && ft_strnstr(env[i], "PATH", 4) == NULL)
		i++;
	paths = ft_split(env[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		cmd_join = ft_strjoin_pipex(paths[i], "/");
		cmd_final = ft_strjoin_pipex(cmd_join, cmd_split);
		free(cmd_join);
		if (access(cmd_final, F_OK) == 0)
		{
			ft_free(paths);
			return (cmd_final);
		}
		free(cmd_final);
		i++;
	}
	ft_free(paths);
	return (NULL);
}
