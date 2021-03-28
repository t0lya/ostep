#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

int main()
{
    struct timeval start = {};
    struct timeval end = {};
    int count = 12000000;

    gettimeofday(&start, NULL);
    for (int i = 0; i < count; i++)
    {
        read(0, NULL, 0);
    }
    gettimeofday(&end, NULL);

    printf("system call cost: %lf usec", (float)(((end.tv_sec - start.tv_sec) * 1000000) + end.tv_usec - start.tv_usec) / count);
}