#include <stdio.h>
#include <stdint.h>

// Function to check system Endianness
// Return 1 for Little-Endian, 0 for Big-Endian
int check_endianness() {
    // Union allows accessing the 32-bit integer as an array of 8-bit bytes
    union {
        uint32_t value; // 4-byte integer
        uint8_t bytes[4]; // 4 1-byte integers
    } test;

    test.value = 0x01020304; // Assign a known pattern (MSB=0x01, LSB=0x04)

    // Little-Endian: The least significant byte (0x04) is stored first (at index 0/lowest address).
    // Big-Endian: The most significant byte (0x01) is stored first (at index 0/lowest address).

    // Check the value of the first byte (lowest address)
    if (test.bytes[0] == 0x04) {
        return 1; // Little-Endian
    } else {
        return 0; // Big-Endian (or exotic system)
    }
}

// Function to swap the byte order of a 32-bit integer (Endian Swap)
uint32_t swap_endian(uint32_t val) {
    // Uses bitwise shifts and AND masks for a portable swap operation

    return ((val & 0xFF000000) >> 24) | // Move Byte 3 (MSB) to Byte 0 (LSB) position
           ((val & 0x00FF0000) >> 8) |  // Move Byte 2 to Byte 1 position
           ((val & 0x0000FF00) << 8) |  // Move Byte 1 to Byte 2 position
           ((val & 0x000000FF) << 24); // Move Byte 0 (LSB) to Byte 3 (MSB) position
}


int main() {
    uint32_t original_value = 0x1A2B3C4D; // Example value
    uint32_t swapped_value;

    printf("Original Value: 0x%X\n", original_value);

    // 1. Check Endianness
    if (check_endianness()) {
        printf("System Endianness: Little-Endian\n");
    } else {
        printf("System Endianness: Big-Endian\n");
    }

    // 2. Perform Endian Swap
    swapped_value = swap_endian(original_value);
    printf("Swapped Value : 0x%X\n", swapped_value);

    // Expected Swapped Result: 0x1A2B3C4D becomes 0x4D3C2B1A 

    return 0;
}