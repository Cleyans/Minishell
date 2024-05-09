#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int ac , char *av[], char **env) // 0 lire 1 ecrire
{
    char infile[100] = "../..Makefile";
    char outfile[100] = "/dev/stdout";
    char cmd[100] = "cat";

    int pfd[2];
    pid_t pid;

    if (pipe(pfd) == -1)
    {
        perror("pipe");
        return (1);
    }
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return (1);
    }
    if (pid == 0)
    {
        close(pfd[1]);
        int fd = open(infile, O_RDONLY, 0777);
        if (fd == -1)
        {
            perror("open");
            close(pfd[0]);
            return (1);
        }
        dup2(fd, STDIN_FILENO);
        close(fd);
        dup2(pfd[1], STDOUT_FILENO);
        close(pfd[1]);
        execlp(cmd, cmd, infile, NULL);
        perror("execlp");
        return (1);
    }
}