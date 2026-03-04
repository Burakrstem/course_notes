#include <stdio.h>
#include <limits.h> // For INT_MAX

int main() {
    // Assuming a 4-byte (32-bit) system

    int signed_max = INT_MAX; 
    unsigned int unsigned_num = signed_max;

    // Signed int has reached its positive maximum value: 0111...111
    printf("Signed Max: %d\n", signed_max);

    // Adding 1 to Signed Max causes an overflow (Section 9: Overflow)
    int overflow_num = signed_max + 1;
    printf("Signed Overflow: %d\n", overflow_num); // Output: -2147483648 (Minimum negative number)

    // For Unsigned int (no sign bit), this is just a value increase: 1000...000
    printf("Unsigned Max + 1: %u\n", unsigned_num + 1); 

    return 0;
}