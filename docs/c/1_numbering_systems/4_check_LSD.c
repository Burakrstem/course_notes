#include <stdio.h>

int main() {
    unsigned char x = 0b01011101; // 93
    printf("MSD: %d\n", (x >> 7) & 1);
    printf("LSD: %d\n", x & 1);

    // 2. with check number is odd or even?
    int num = 87; // ...0101 0111
    // LSD check: Is the number odd or even?
    if (num & 1) { // 87 & 1 = 1 (Odd)
        // LSD is 1.
    }


    return 0;
}

