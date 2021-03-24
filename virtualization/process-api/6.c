#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// waitpid waits for child with matching pid. useful when you have more than one child
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
        printf("child\n");
    }
    else
    {
        printf("parent: fork returns child pid: %d\n", pid);
        int rc = waitpid(pid, NULL, 0);
        printf("parent: wait returns %d\n", rc);
    }

    return 0;
}