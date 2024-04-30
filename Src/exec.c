// #include "../Include/Minishell.h"

// void executeCommand(struct Input input)
// {
//     if (input.isCommand)
//     {
//         pid_t pid = fork();

//         if (pid == -1)
//         {
//             perror("fork");
//             exit(EXIT_FAILURE);
//         }
//         else if (pid == 0)
//         {
//             execvp(input.command, input.arguments);
//             perror("execvp");
//             exit(EXIT_FAILURE);
//         }
//         else
//         {
//             int status;
//             waitpid(pid, &status, 0);

//             if (WIFEXITED(status)) {
//                 int exitStatus = WEXITSTATUS(status);
//                 printf("Child process exited with status: %d\n", exitStatus);
//             }
//         }
//     }
//     else
//     {
//         // Handle other types of input
//         // ...
//     }
// }

// int isCommand(char *input)
// {
//     if (access(cmd, F_OK) == 0)
// 		execve(cmd, cmd_split, env);
//     return 1;
// }

// int main() {
//     // Create an example input structure
//     struct Input input;
//     input.isCommand = true;
//     input.command = "ls";
//     input.arguments = (char*[]){"-l", NULL};

//     // Call the executeCommand function
//     executeCommand(input);

//     return 0;
// }