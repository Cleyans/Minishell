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
    int input_length = strlen(terminal->input);
    int token_index = 0;

    if (!terminal->input)
        return;

    while (i < input_length)
    {
        j = 0; // Reset j for each command

        // Find command
        while (i < input_length && terminal->input[i] == ' ')
            i++;
        while (i < input_length && terminal->input[i] != ' ' && terminal->input[i] != '|' && terminal->input[i] != '<' && terminal->input[i] != '>')
        {
            command->command[j] = terminal->input[i];
            i++;
            j++;
        }
        command->command[j] = '\0';

        // Find arguments
        k = 0;
        command->arguments[k] = malloc(100 * sizeof(char)); // Allocate space for argument
        while (i < input_length && terminal->input[i] == ' ')
            i++;
        while (i < input_length && terminal->input[i] != '|' && terminal->input[i] != '<' && terminal->input[i] != '>')
        {
            if (terminal->input[i] == ' ')
            {
                command->arguments[k][token_index] = '\0';
                k++;
                token_index = 0;
                command->arguments[k] = malloc(100 * sizeof(char));
            }
            else
            {
                command->arguments[k][token_index] = terminal->input[i];
                token_index++;
            }
            i++;
        }
        command->arguments[k][token_index] = '\0';
        command->arguments[k + 1] = NULL; // Null-terminate the arguments array

        printCommand(command);
        i++;
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