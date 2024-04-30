#include "../Include/Minishell.h"

int main(int ac, char **av, char **env)
{
    s_input terminal;
    s_command command;

    init(&terminal, &command, env);
    // while (1)
    // {
        // terminal.input = readline("> ");
        scanf("%s", (char *)terminal.input);
        chekingInput(&terminal, &command);
        free(terminal.input);
    // } 
    return 0;
}

void    init(s_input *terminal, s_command *command, char **env)
{
    terminal->input = NULL;
    terminal->stockCommand = NULL;
    terminal->env = env;

}

void chekingInput(s_input *terminal, s_command *command) // check all the command in input to malloc
{
    int i;

    i = 0;
    while (terminal->input[i])
    {
        while (terminal->input[i] == ' ' && terminal->input[i] != '\0')
            i++;
        while (terminal->input[i] != ' ' && terminal->input[i] != '\0')
        {
            command->command[i] = terminal->input[i];
            i++;
        }
        while (terminal->input[i] == ' ')
            i++;
        if (terminal->input[i] != ' ' && terminal->input[i] != '\0' && terminal->input[i] == '-')
        {
            while (terminal->input[i] != ' ' && terminal->input[i] != '\0')
            {
                command->arguments[i] = terminal->input[i];
                i++;
            }
        }
        command->command[i] = '\0';
        command->arguments[i] = '\0';
        ft_lstadd_back(&command, ft_lstnew(command));
        command = command->next;
    }
    printCommand(command);
}

void    printCommand(s_command *command)
{
    while (command)
    {
        printf("command: %s ", command->command);
        printf("arguments: %s", command->arguments);
        printf("\n");
        command = command->next;
    }
}