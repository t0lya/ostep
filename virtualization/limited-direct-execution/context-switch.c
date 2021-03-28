#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <mach/mach.h>
#include <pthread.h>

#define LOOP_SIZE 50000

// Context switch cost is overestimated, as read/write cost is included
int main()
{
    // Make sure to run in single processor only (works for macOS)
    thread_affinity_policy_data_t policy = {1};
    thread_policy_set(pthread_mach_thread_np(pthread_self()), THREAD_AFFINITY_POLICY, (thread_policy_t)&policy, 1);

    int pipefd1[2];
    int pipefd2[2];
    pipe(pipefd1);
    pipe(pipefd2);

    int pid = fork();

    if (pid < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (pid == 0) // child
    {
        struct timeval start = {};
        struct timeval end = {};

        gettimeofday(&start, NULL);
        for (int i = 0; i < LOOP_SIZE; i++)
        {
            char c = 'c';
            write(pipefd1[1], &c, 1);
            read(pipefd2[0], NULL, 0);
        }
        gettimeofday(&end, NULL);
        printf("context switch cost: %lf usec", (float)(((end.tv_sec - start.tv_sec) * 1e6) + end.tv_usec - start.tv_usec) / (LOOP_SIZE * 2));

        char s = 's';
        write(pipefd1[1], &s, 1);
    }
    else //parent
    {
        for (;;)
        {
            char readbuffer;
            read(pipefd1[0], &readbuffer, 1);
            if (readbuffer == 's')
                break;
            write(pipefd2[1], NULL, 0);
        }
    }

    return 0;
}