#include <stdio.h>

int main() {
    // default system is decimal
    int decimal_num = 255;
    // Octal (prefixed with '0')
    int octal_num = 0377; 
    // Hexadecimal (prefixed with '0x' or '0X')
    int hex_num = 0xFF; 

    printf("Decimal (10)   : %d\n", decimal_num);
    printf("Octal (8)      : %o\n", octal_num);
    printf("Hexadecimal(16): %X\n", hex_num);

    // Binary literal support came with the C23 standard but is not widely adopted.
    // printf("Binary (2)   : %b\n", 0b11111111); // Does not work in pre-C23 compilers

    return 0;
}