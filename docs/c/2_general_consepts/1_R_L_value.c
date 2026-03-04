#include <stdio.h>

int main() {
    int x = 10;
    int y = 5;

    // L-value: x (persistent memory location)
    // R-value: y + 2 (temporary value calculated on the fly)
    x = y + 2; 

    printf("x = %d, y = %d\n", x, y);
    return 0;
}