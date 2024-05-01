#include "../Include/Minishell.h"

int main(int ac, char **av, char **env)
{
    s_input terminal;
    t_command command;

    init(&terminal, &command, env);
    while (1)
    {
        terminal.input = readline("8==D >");
        if (terminal.input)
            checkingInput(&terminal, &command);
        free(terminal.input);
    } 
    return 0;
}

void init(s_input *terminal, t_command *command, char **env)
{
    terminal->input = NULL;
    terminal->env = env;
    command->isCommand = 1;
    command->command = malloc(sizeof(char) * 10000);
    command->arguments = malloc(sizeof(char *) * 10000);
    command->next = NULL;
}

void checkingInput(s_input *terminal, t_command *command)
{
    int i = 0;
    int j, k;
    char *token;

    if (!terminal->input)
        return;

    // Split input by pipes
    token = strtok(terminal->input, "|");
    while (token != NULL)
    {
        j = 0; // Reset j for each command

        // Find command
        while (*token == ' ')
            token++;
        while (token[j] && token[j] != ' ' && token[j] != '|' && token[j] != '<' && token[j] != '>')
        {
            command->command[j] = token[j];
            j++;
        }
        command->command[j] = '\0';

        // Find arguments
        k = 0;
        command->arguments[k] = malloc(100 * sizeof(char)); // Allocate space for argument
        while (token[j] == ' ')
            j++;
        while (token[j])
        {
            if (token[j] == ' ')
            {
                command->arguments[k][i] = '\0';
                k++;
                command->arguments[k] = malloc(100 * sizeof(char));
                i = 0;
            }
            else
            {
                command->arguments[k][i] = token[j];
                i++;
            }
            j++;
        }
        command->arguments[k][i] = '\0';
        command->arguments[k + 1] = NULL; // Null-terminate the arguments array
        token = strtok(NULL, "|");

        printCommand(command);
    }
}

void printCommand(t_command *command)
{
    printf("Command: %s\n", command->command);
    printf("Arguments: ");
    int i = 0;
    while (command->arguments[i] != NULL)
    {
        printf("%s ", command->arguments[i]);
        i++;
    }
    printf("\n");
}