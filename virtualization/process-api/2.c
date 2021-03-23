#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

// Both child and parent will write to file
int main()
{
    close(STDOUT_FILENO);
    open("./test.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    int pid = fork();

    if (pid < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (pid == 0)
    {
        printf("writing to file from child process\n");
    }
    else
    {
        // wait(NULL);
        printf("writing to file from parent process\n");
    }

    return 0;
}