#include <stdio.h>

void twosComplement(unsigned char x) {
    unsigned char ones = ~x;
    unsigned char twos = ones + 1;
    printf("Original: 0x%X, One's Complement: 0x%X\n, Two's Complement: 0x%X\n", x, ones, twos);
}

int main() {
    twosComplement(0b01011000);
    return 0;
}