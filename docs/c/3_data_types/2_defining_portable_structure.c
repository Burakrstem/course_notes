#include <stdio.h>
#include <stdint.h> // For fixed-width integer types (e.g., int32_t, uint16_t)

// Define a type whose size is strictly guaranteed for portability
// This is crucial for Data Structures that rely on fixed sizes (like network packets or file storage).
typedef struct {
    // We use types from stdint.h to ensure fixed sizes regardless of the system architecture.
    uint16_t id;    // Guaranteed 2 bytes (short)
    int32_t count;  // Guaranteed 4 bytes (int/long)
    double price;   // Standard 8 bytes
} ProductData;


int main() {
    ProductData item;

    printf("--- Portable Type Analysis ---\n");

    // 1. Check fixed sizes guaranteed by stdint.h
    printf("Size of uint16_t (ID): %zu bytes\n", sizeof(uint16_t)); 
    printf("Size of int32_t (Count): %zu bytes\n", sizeof(int32_t));

    // 2. Check the size of the structure itself (may include padding/alignment)
    printf("Size of ProductData Structure: %zu bytes\n", sizeof(ProductData));

    // 3. Robustly calculate array size using sizeof (as taught in the previous section)
    int my_array[] = {10, 20, 30, 40, 50};
    size_t array_length = sizeof(my_array) / sizeof(my_array[0]);
    printf("Calculated Array Length (Robust): %zu\n", array_length);

    // Note: Using int32_t instead of plain int ensures the structure layout is consistent 
    // across 16-bit, 32-bit, and 64-bit systems, which is vital for DSA and I/O.

    return 0;
}