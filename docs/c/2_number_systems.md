# Number Systems in C

## 1. Introduction to Number Systems

Computers process data in the **binary system**.  
Each number system uses different symbols according to its base:

| System | Base | Symbols |
|:--------|:------|:--------|
| Binary | 2 | 0, 1 |
| Octal | 8 | 0–7 |
| Decimal | 10 | 0–9 |
| Hexadecimal | 16 | 0–9, A–F |

representing number systems
```c
#include <stdio.h>

int main() {
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
```
---

## 2. Bit, Byte, and Other Units

- **Bit (binary digit):** Smallest unit of information (0 or 1)  
- **Nibble:** 4 bits 
- **Byte:** 8 bits   
- **Word:** 16 bits  
- **Double Word (DWORD):** 32 bits  
- **Quad Word (QWORD):** 64 bits  

### Memory Capacity Units
| Unit | Equivalent | Description |
|:------|:----------|:------------|
| 1 KB | 1024 Bytes | 2¹⁰ |
| 1 MB | 1024 KB | 2²⁰ |
| 1 GB | 1024 MB | 2³⁰ |
| 1 TB | 1024 GB | 2⁴⁰ |

### Memory Capacity of Basic Data Types
Note: The `sizeof` operator in C allows us to learn how many bytes any data type or variable occupies in memory. the return type is `size_t` (unsigned int). so i use `%zu` format for print the occupied byte. This is essential for obtaining hardware-dependent information programmatically.
```c
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
```
---

## 3. Binary ↔ Decimal Conversions

### Binary → Decimal
Each bit is multiplied by **powers of 2** and summed:
1011₂ = 1×2³ + 0×2² + 1×2¹ + 1×2⁰ = 11₁₀


### Decimal → Binary
Divide the number by 2 repeatedly and write the remainders in **reverse order**:
87₁₀ → 0101 0111₂

Alternative method: Subtract the largest power of 2 and continue with the remainder.

### Binary to Decimal Conversion
This relies on checking an integer using bitwise AND (&) and bitwise Shift (>>) operators.
```c
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
```
---

## 4. MSD and LSD

- **MSD (Most Significant Digit):** Leftmost bit, **highest value**  
- **LSD (Least Significant Digit):** Rightmost bit, **lowest value**

Example:
0101 1101
MSD = 0
LSD = 1

For an 8-bit number:
- **Bit 0:** LSD (rightmost)  
- **Bit 7:** MSD (leftmost)

check the LSD
```c
#include <stdio.h>

int main() {
    unsigned char x = 0b01011101; // 93
    printf("MSD: %d\n", (x >> 7) & 1);
    printf("LSD: %d\n", x & 1);
    return 0;
}
```

To access the LSD (Bit 0) of an int variable, the bitwise AND operator is commonly used:
```c
int num = 87; // ...0101 0111
// LSD check: Is the number odd or even?
if (num & 1) { // 87 & 1 = 1 (Odd)
    // LSD is 1.
}
```

---

## 5. Unsigned and Signed Numbers

### Unsigned
Represents only positive numbers:
0000 0000 → 0
1111 1111 → 255


### Signed
The leftmost bit is the **sign bit**:
- 0 → Positive  
- 1 → Negative  

Note: Integer types in C (e.g., int) are signed by default. Declaring them as unsigned doubles the number's range because the leftmost bit (MSB/MSD) is used as a value bit instead of a sign bit.

Signed and Unsigned Undefined Behavior
```c
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
```
---

## 6. One’s Complement

The **one’s complement** of a number is obtained by inverting all its bits:

| Original | One’s Complement |
|:---------|:----------------|
| 1011 | 0100 |
| 1100 0011 | 0011 1100 |

1 → 0, 0 → 1  

The one’s complement of a number’s one’s complement is the number itself.
```c
#include <stdio.h>

void onesComplement(unsigned char x) {
    unsigned char result = ~x;
    printf("Original: 0x%X, One's Complement: 0x%X\n", x, result);
}

int main() {
    onesComplement(0b10101100);
    return 0;
}
```

---

## 7. Two’s Complement

**Definition:** Add 1 to the one’s complement of a number.

| Number | One’s Complement | +1 | Two’s Complement |
|:-------|:----------------|:--|:----------------|
| 0101 1000 | 1010 0111 | +1 | 1010 1000 |

Alternative shortcut:
- Go from right to left,
- Copy bits until the first 1 is encountered,
- Invert the remaining bits.

Example:
1110 0100 → 0001 1100


The two’s complement of a number’s two’s complement is the number itself.

### Calculating One's and Two's Complement
Note: The Bitwise NOT (~) operator in C easily calculates the One's Complement of a number. To obtain the Two's Complement, simply add 1 to the result.
```c
#include <stdio.h>

void twosComplement(unsigned char x) {
    unsigned char ones = ~x;
    unsigned char twos = ones + 1;
    printf("Original: 0x%X, Two's Complement: 0x%X\n", x, twos);
}

int main() {
    twosComplement(0b01011000);
    return 0;
}

```
---

## 8. Representation of Negative Numbers

Negative numbers are represented using **two’s complement**.

Example: Represent `-27` in 8-bit signed binary:

1. Binary of 27 → `0001 1011`  
2. One’s complement → `1110 0100`  
3. Add 1 → `1110 0101`

Result:
-27 → 1110 0101


### Examples

| Decimal | Binary (8-bit) | Description |
|:-------|:----------------|:-----------|
| 127 | 0111 1111 | Maximum positive |
| -128 | 1000 0000 | Minimum negative |
| -1 | 1111 1111 | All bits are 1 |

```c
#include <stdio.h>

int main() {
    signed char pos = 27;
    signed char neg = -27;

    printf("27 binary: %d\n", pos);
    printf("-27 binary (two's complement): %d\n", neg);
    printf("Raw bytes: 0x%X and 0x%X\n", (unsigned char)pos, (unsigned char)neg);
    return 0;
}
```
## 9. Number Overflow

In signed systems, adding 1 to the maximum positive number wraps into the negative range:

0111 1111 (127)
+1
1000 0000 (-128)


Similarly, subtracting 1 from -128 wraps to 127.

### Undefined Behavior (Signed Overflow)
Note: In C, operations that exceed the range of an integer type (e.g., a value greater than 2^31 - 1 for signed int) can lead to undefined behavior. However, the value typically wraps into the type's negative range. For unsigned integers, overflow is guaranteed and wraps back from the lowest value using modulus arithmetic.

```c
#include <stdio.h>
#include <limits.h>

int main() {
    int max_val = INT_MAX; 
    
    // The compiler is not required to follow a specific rule in the case of signed int overflow.
    // On most systems, it wraps to the value -2147483648 (INT_MIN).
    int result = max_val + 1; 
    
    printf("INT_MAX + 1 = %d\n", result); 
    
    return 0;
}
```


## 10. Hexadecimal System

Each hex digit represents **4 bits**:

| Hex | Binary | Decimal |
|:----|:-------|:--------|
| 0 | 0000 | 0 |
| 1 | 0001 | 1 |
| 2 | 0010 | 2 |
| ... | ... | ... |
| A | 1010 | 10 |
| F | 1111 | 15 |

Example:
2ADF₁₆ = 0010 1010 1101 1111₂


To check if a number is negative, look at the **leftmost hex digit**:  
If it is in [8–F], the number is negative.
```c
#include <stdio.h>

int main() {
    int x = 0x2ADF;  // hexadecimal literal
    printf("Hex: 0x%X, Decimal: %d, Binary: ", x, x);

    for (int i = 15; i >= 0; i--)
        printf("%d", (x >> i) & 1);
    return 0;
}

```
---

## 11. Octal System

Each octal digit is represented by **3 bits**:

| Octal | Binary |
|:-----|:-------|
| 0 | 000 |
| 1 | 001 |
| 2 | 010 |
| 3 | 011 |
| 4 | 100 |
| 5 | 101 |
| 6 | 110 |
| 7 | 111 |

Example:
765₈ = 111 110 101₂

ex: output formatting
Note: In the printf function, we can output hexadecimal values using %x or %X, and octal values using %o.
```c
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
```
---

## 12. Representation of Real Numbers in Memory (IEEE 754)

Real numbers are stored in memory according to the **IEEE 754 standard**.

### Single Precision (32-bit)

S EEEEEEEE FFFFFFFFFFFFFFFFFFFFFFF


| Field | Bits | Description |
|:-----|:----|:-----------|
| S | 1 | Sign bit |
| E | 8 | Exponent |
| F | 23 | Fraction (mantissa) |

Formula:
V = (-1)^S × 2^(E - 127) × (1.F)
Example:
0 10000001 10100000000000000000000 → +6.5
### Double Precision (64-bit)
S EEEEEEEEEEE FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
Formula:
V = (-1)^S × 2^(E - 1023) × (1.F)

---

## 13. IEEE 754 Special Cases

| Case | E | F | Result |
|:----|:--|:--|:------|
| 255/2047 | ≠0 | ≠0 | NaN (Not a Number) |
| 255/2047 | =0, S=1 | -∞ |
| 255/2047 | =0, S=0 | +∞ |
| 0 | =0 | +0 / -0 |
| 0 | ≠0 | Denormalized number |

```c
#include <stdio.h>

void printFloatBits(float f) {
    unsigned int bits = *(unsigned int *)&f;
    printf("Float: %.2f\nBits : ", f);
    for (int i = 31; i >= 0; i--) {
        printf("%d", (bits >> i) & 1);
        if (i == 31 || i == 23) printf(" ");
    }
    printf("\n");
}

int main() {
    float x = 6.5f;
    float y = -6.5f;
    printFloatBits(x);
    printFloatBits(y);
    return 0;
}
```

---

## Additional examples:
### 1. IEEE 754 Inspection
The following code uses Pointer and Union structures to inspect how a float number is represented in memory according to the IEEE 754 standard (bit-by-bit). This is one of examples of C's low-level access power.
```c
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
```

### 2. binary to decimal
```c
#include <stdio.h>
#include <math.h>

int binary_to_decimal(const char *binary) {
    int len = strlen(binary);
    int decimal = 0;
    for (int i = 0; i < len; i++) {
        if (binary[len - 1 - i] == '1') {
            decimal += pow(2, i);
        }
    }
    return decimal;
}

int main(){
    char binary[] = "1101"; // Example binary number
    printf("Binary %s = Decimal %d\n", binary,binary_to_decimal(binary) );
    return 0;
}
```

### 3. decimal to binary
```c
#include <stdio.h>

void decimalToBinary(int decimal){
    int bits[32];
    int index = 0;
    while (decimal > 0){
        bits[index++] = decimal % 2;
        decimal /= 2;
    }
    for (int i = index - 1; i >= 0; i--){
        printf("%d", bits[i]);
    }
}


int main() {
    int n = 87;
    printf("%d in binary: ", n);
    decimalToBinary(n);
    return 0;
}
```

### 4. Endianness Control and Byte Order Swapping
This code demonstrates how to check a system's Endianness (byte order) using a Union and provides a portable function to swap the byte order of a 32-bit integer using Bitwise Operators.
```c
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
```

### 5. Interpreting Signed/Unsigned Integers via Bit Pattern
This example illustrates the difference between implicit type conversion (which may cause sign extension) and pointer casting (which reinterprets the bits in memory) for signed and unsigned integers, demonstrating how the same bit pattern can represent vastly different values.
```c
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
```