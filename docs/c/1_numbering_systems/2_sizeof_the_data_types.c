#include <stdio.h>
#include <limits.h> // For CHAR_BIT

int main() {
    // CHAR_BIT gives the number of bits in a byte (usually 8).
    printf("1 Byte = %d Bit\n", CHAR_BIT); 

    // Prints memory capacity in bytes
    printf("Size of char: %zu Bytes\n", sizeof(char));
    printf("Size of int: %zu Bytes\n", sizeof(int));
    printf("Size of long long: %zu Bytes\n", sizeof(long long));

    // Assuming a 32-bit system: int = 4 Bytes = Double Word (DWORD)
    printf("Size of 4 Byte (DWORD) int: %zu Bytes\n", sizeof(int));

    return 0;
}