#include "../Include/Minishell.h"

// only for one command || if we want to do more then one and more
//then one pipe, we have to know the amouth of pipe before the execution

void	executing(t_input *terminal, t_command *command)
{
	pid_t	pid;
	char	**cmd_split;
	char	*cmd_path;
	int		i;
	int		j;

	i = 0;
	j = 0;
	cmd_split = malloc(sizeof(char **) * 100);
	cmd_path = malloc(sizeof(char) * 100);
	cmd_path = search_path(terminal->env, command->command);
	cmd_split[j++] = ft_strdup(command->command);
	if (command->arguments[i])
	{
		while (command->arguments[i])
			cmd_split[j++] = ft_strdup(command->arguments[i++]);
	}
	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd_path, cmd_split, terminal->env) == -1)
			perror("execve");
	}
	else
		waitpid(pid, NULL, 0);
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
