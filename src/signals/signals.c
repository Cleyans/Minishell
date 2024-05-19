#include "../../include/Minishell.h"

void	handler_c(int signal)
{
    (void)signal;
    printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void signal_check(void)
{
	signal(SIGINT, handler_c);
	// signal(SIGQUIT, SIG_IGN);
}