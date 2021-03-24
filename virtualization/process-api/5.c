#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// wait in parent returns process ID of child process
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
        int rc = wait(NULL);
        // Child process has no child process, so wait() returns immediately “-1”.
        printf("child: wait returns %d\n", rc);
    }
    else
    {
        printf("parent: fork returns child pid: %d\n", pid);
        int rc = wait(NULL);
        printf("parent: wait returns %d\n", rc);
    }

    return 0;
}