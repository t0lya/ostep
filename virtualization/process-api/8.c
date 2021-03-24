#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int pipefd[2];
    pipe(pipefd);

    int pid = fork();

    if (pid < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (pid == 0)
    {
        close(pipefd[0]);
        char msg[] = "child 1 says hello";
        write(pipefd[1], msg, sizeof(msg));
    }
    else
    {
        int pid2 = fork();

        if (pid2 < 0)
        {
            fprintf(stderr, "fork failed\n");
            exit(1);
        }
        else if (pid2 == 0)
        {
            close(pipefd[1]);
            char readbuffer[80];
            read(pipefd[0], readbuffer, sizeof(readbuffer));
            printf("received a message from child 1: %s\n", readbuffer);
        }
    }

    return 0;
}