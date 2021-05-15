#include <stdlib.h>

int main(int argc, char *argv[])
{
    int size = (1024 * 1024 * atoi(argv[1]));
    char *arr = malloc(size);
    for (;;)
    {
        for (int i = 0; i < size; i++)
        {
            arr[i] += 1;
        }
    }
}