#include <stdio.h>

void fill_array(int arr[], int size) {
    for (int i = 0; i < size; i++)
        arr[i] = i * 10;
}

int main(void) {
    int nums[5];
    fill_array(nums, 5);
    for (int i = 0; i < 5; i++)
        printf("%d ", nums[i]);
    return 0;
}
