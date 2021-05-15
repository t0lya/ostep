#include <stdlib.h>
#include <stdio.h>

int main() {
	int *data = (int *) malloc(100 * sizeof(int));
	free(data);
	printf("array value: %d\n", data[50]);
}
