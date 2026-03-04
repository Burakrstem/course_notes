#include <stdio.h>
#include <stdint.h> // For uint32_t

// Union is used to define different types sharing the same memory location
typedef union {
    float f;
    uint32_t u; // IEEE 754 single precision = 32 bits (4 bytes)
} FloatConverter;

void display_ieee754(float number) {
    FloatConverter converter;
    converter.f = number;

    uint32_t bits = converter.u;

    printf("Input Number (Float): %.6f\n", number);

    // 1. Sign Bit - Bit 31
    uint32_t sign = (bits >> 31) & 1;
    printf("1. Sign Bit (S): %u\n", sign);

    // 2. Exponent - Bits 30 to 23 (8 bits)
    uint32_t exponent = (bits >> 23) & 0xFF;
    printf("2. Exponent (E): %u (Hex: 0x%X)\n", exponent, exponent);

    // 3. Fraction (Mantissa) - Bits 22 to 0 (23 bits)
    uint32_t fraction = bits & 0x7FFFFF;
    printf("3. Fraction (F): 0x%X\n", fraction);

    // Note: This operation is critical for understanding data representation at the hardware level in the C language.
}

int main() {
    // The value 6.5f (S=0, E=10000001, F=101000...)
    display_ieee754(6.5f); 

    return 0;
}