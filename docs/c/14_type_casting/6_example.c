#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // malloc returns void*
    int *arr = (int *)malloc(5 * sizeof(int));

    if (!arr) {
        printf("Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < 5; i++) {
        arr[i] = (int)(i * 2.5); // explicit casting from double to int
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    free(arr);
    return 0;
}
