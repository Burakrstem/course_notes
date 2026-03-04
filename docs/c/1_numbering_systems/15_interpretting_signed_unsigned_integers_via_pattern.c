#include <stdio.h>
#include <stdint.h>

void analyze_conversion() {
    // 1. Small, Negative Signed Number (8-bit)
    int8_t signed_char_val = -10; // 8-bit Two's Complement: 1111 0110

    // 2. Implicit Conversion to Wider Unsigned Type
    // C rule: signed_char_val is first promoted to int (with sign extension), then converted to unsigned int.
    uint32_t unsigned_int_val = signed_char_val; 

    // 3. Illustrating Sign Extension in Conversion
    // The bit pattern of signed_char_val (which is 0xFFFFFFF6 as a 32-bit int) is interpreted as a uint32_t.
    // Result is the large positive number (4294967286)

    printf("--- Implicit Conversion of Negative Number to Wider Unsigned Type ---\n");
    printf("Original Value (int8_t): %d\n", signed_char_val);
    printf("Unsigned Value (uint32_t): %u\n", unsigned_int_val);

    // Rationale: C performed sign extension:
    // 1111 0110 (-10) -> 1111 1111 1111 1111 1111 1111 1111 0110 (32-bit int)
    // This bit pattern, when interpreted as uint32_t, becomes a large positive number.

    // 4. Interpreting Bit Pattern via Pointer Casting
    int32_t signed_int_val = -1; // 32-bit: 1111...1111

    // Pointer cast: Changes the type of the memory address, does not copy the data, only reinterprets it.
    // The bit pattern in memory remains the same.
    uint32_t *unsigned_ptr = (uint32_t *)&signed_int_val;

    printf("\n--- Interpretation via Pointer Casting ---\n");
    printf("Original Value (int32_t): %d\n", signed_int_val);
    // The bit pattern 0xFFFFFFFF, when interpreted as uint32_t, equals the maximum unsigned value.
    printf("Pointer Interpretation (uint32_t): %u\n", *unsigned_ptr); 

    // Note: Casting the pointer provides a guaranteed way to get the unsigned counterpart of a negative number's bit pattern.
}

int main() {
    analyze_conversion();
    return 0;
}