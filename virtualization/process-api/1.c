#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int test = 100;
    int pid = fork();

    if (pid < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (pid == 0)
    {
        // fork gives child separate registers and memory, i.e. its own `test` variable
        printf("child before: %d\n", test);
        test = 20;
        printf("child after: %d\n", test);
    }
    else
    {
        printf("parent before: %d\n", test);
        test = 50;
        printf("parent after: %d\n", test);
    }

    return 0;
}