/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brclemen <brclemen@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:31:56 by brclemen          #+#    #+#             */
/*   Updated: 2024/08/19 17:31:56 by brclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Minishell.h"

void	advanced_print(t_command *command)
{
	int	i;

	i = 0;
	while (command->next != NULL)
	{
		printf("command = %s\n", command->command);
		while (command->arguments[i] != NULL)
		{
			printf("arguments[%d] = %s\n", i, command->arguments[i]);
			i++;
		}
		if (command->redir_out == 1)
			printf("outfile = %s\n", command->outfile);
		if (command->redir_in == 1)
			printf("infile = %s\n", command->infile);
		if (command->hd_out == 0)
			printf("outfile = %s\n", command->outfile);
		if (command->hd_in == 1)
			printf("infile = %s\n", command->infile);
		if (command->pipe == 0)
			printf("pipe = 0\n");
		command = command->next;
	}
}

void	advanced_print_deux(t_command *command)
{
	if (command->pipe != 0)
		printf("pipe = -1\n");
	if (command->int_dollar == 1 || command->int_dollar == 0)
		printf("int_dollar = %d\n", command->int_dollar);
	if (command->int_dollar == 0)
		printf("int_dollar = %s\n", command->dollar);
	if (command->redir_in == 1)
		printf("redir_in = 1\n");
	else if (command->redir_out == 1)
		printf("redir_out = 1\n");
	else
		printf("redir_in = -1\nredir_out = -1\n");
	if (command->hd_in == 1)
		printf("hd_in = 1\n");
	else if (command->hd_out == 1)
		printf("hd_out = 1\n");
	else
		printf("hd_in = -1\nhd_out = -1\n");
	printf("Command out dollar : %s\n", command->out_dollar);
	printf("builtins = %d\n", command->builtins);
	printf("\n");
	printf("G_SINGAL = %d\n", g_signal);
}
