#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void forkCallback(void (*f)())
{
    int rc = fork();

    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        (*f)();
    }
    else
    {
        wait(NULL);
        printf("fork done\n");
    }
}

void tryExecL()
{
    printf("\nexecl: with args as list\n");
    execl("/bin/ls", "/bin/ls", (char *)NULL);
}

void tryExecLe()
{
    printf("\nexecle: with args as list and env array\n");
    char *env[] = {"EXAMPLEVAR=somevalue", NULL};
    execle("/bin/ls", "/bin/ls", (char *)NULL, env);
}

void tryExecV()
{
    printf("\nexecv: with args as vector/array\n");
    char *argv[] = {"/bin/ls", NULL};
    execv("/bin/ls", argv);
}
void tryExecVp()
{
    printf("\nexecvp: with args as vector/array and using PATH env variable\n");
    char *argv[] = {"ls", NULL};
    execvp("ls", argv);
}

int main()
{
    forkCallback(tryExecL);
    forkCallback(tryExecLe);
    forkCallback(tryExecV);
    forkCallback(tryExecVp);

    return 0;
}