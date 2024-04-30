#include "../Include/Minishell.h"

int main(int ac, char **av)
{
    s_input terminal;

    init(&terminal);
    while (1)
    {
        terminal.input = readline("> ");
        if (strcmp(terminal.input, "exit") == 0)
            break;
            
        add_history(terminal.input);
        free(terminal.input);
    } 
    return 0;
}

void    init(s_input *terminal)
{
    terminal->input = NULL;
}