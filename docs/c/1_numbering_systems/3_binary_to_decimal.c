#include <stdio.h>

int main() {
    unsigned char binary_num = 0b10110011; // 179
    int decimal_val = 0;
    int power = 1;

    // Convert to decimal by checking each bit
    for (int i = 0; i < 8; i++) {
        // Check the rightmost bit (LSD) with Bitwise AND
        if (binary_num & 1) { 
            decimal_val += power;
        }

        // Shift the number one bit to the right (makes the next bit the LSB)
        binary_num >>= 1; 

        // Increase the power of 2
        power *= 2; 
    }

    printf("1011 0011 (Binary) = %d (Decimal)\n", decimal_val); // Output: 179

    return 0;
}