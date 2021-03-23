#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

// Child should write before parent
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
        printf("hello\n");
    }
    else
    {
        wait(NULL);
        printf("goodbye\n");
    }

    return 0;
}