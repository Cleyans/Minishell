#include "../Include/Minishell.h"

int main(int ac, char **av, char **env)
{
    s_input terminal;
    t_command command;

    init(&terminal, &command, env);
    while (1)
    {
        // terminal.input = readline("> ");
        terminal.input = readline("8==D >");
        if (terminal.input)
            chekingInput(&terminal, &command);
        free(terminal.input);
    } 
    return 0;
}

void    init(s_input *terminal, t_command *command, char **env)
{
    terminal->input = NULL;
    terminal->stockCommand = NULL;
    terminal->env = env;

}

void chekingInput(s_input *terminal, t_command *command) // check all the command in input to malloc
{
    int i;
    int j;
    int k;

    j = 0;
    k = 0;
    i = 0;
    if (terminal->input[i])
    {
        while (terminal->input[i] == ' ' && terminal->input[i] != '\0')
            i++;
        while (terminal->input[i] != ' ' && terminal->input[i] != '\0')
        {
            command->command[j] = terminal->input[i];
            j++;
            i++;
        }
        while (terminal->input[i] == ' ')
            i++;
        if (terminal->input[i] == '-' && terminal->input[i] != '\0')
        {
            while (terminal->input[i] != ' ' && terminal->input[i] != '\0')
            {
                command->arguments[k] = terminal->input[i];
                k++;
                i++;
            }
        }
        command->command[j] = '\0';
        command->arguments[k] = '\0';
        j = 0;
        k = 0;
    }
    printCommand(command);
}

void    printCommand(t_command *command)
{
        printf("command: %s ", command->command);
        printf("arguments: %s", command->arguments);
        printf("\n");
}