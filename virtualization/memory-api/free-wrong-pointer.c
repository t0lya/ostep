#include <stdlib.h>
#include <stdio.h>

int main() {
	int *data = (int *) malloc(100 * sizeof(int));
	free(data + 50);
	printf("array value: %d\n", data[50]);
}
