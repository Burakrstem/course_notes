#include <stdio.h>

int main() {
    int num = 450; // 0x1C2 in Hex, 0702 in Octal

    printf("Decimal: %d\n", num);

    // Hexadecimal output format
    printf("Hexadecimal (Lower): %x\n", num); 
    printf("Hexadecimal (Upper): %X\n", num);

    // Octal output format
    printf("Octal: %o\n", num); 

    // Formatting with prefix 0x
    printf("Hex with prefix: %#X\n", num); 

    return 0;
}