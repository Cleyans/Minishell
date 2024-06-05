#include "../include/Minishell.h"

void	free_str_tab(char **strtab)
{
	size_t	i;

	i = 0;
	if (!strtab)
		return ;
	while (strtab[i])
		free(strtab[i++]);
	free(strtab);
}

void	free_exec_error(t_command *command, char *cmd_path, char **cmd_split)
{
	int	i;

	i = 0;
	free(cmd_path);
	while (cmd_split[i])
	{
		free(cmd_split[i]);
		i++;
	}
	free(cmd_split);
}

void free_nodes(t_command *first)
{
	t_command	*tmp;
	t_command	*next_node;

	if (first != NULL) {
		tmp = first->next;
		while (tmp != NULL)
		{
			next_node = tmp->next;
			free(tmp);
			tmp = next_node;
		}
		first->next = NULL;
	}
	free_str_tab(first->arguments);
	free(first);
}