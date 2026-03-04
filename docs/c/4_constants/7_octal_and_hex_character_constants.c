#include <stdio.h>

int main() {
    char x = '\x41';  // 0x41 = 65
    char y = '\101';  // 0101 = 65
    printf("x=%c (%d), y=%c (%d)\n", x, x, y, y);
    return 0;
}