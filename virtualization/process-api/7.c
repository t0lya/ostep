#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

// Child stops printing to stdout
int main()
{
    int pid = fork();

    if (pid < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (pid == 0)
    {
        close(STDOUT_FILENO);
        printf("hello\n");
    }
    else
    {
        printf("goodbye\n");
    }

    return 0;
}