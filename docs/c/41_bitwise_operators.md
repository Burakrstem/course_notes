# ⚡ Bitwise Operators

**Bitwise operators** perform operations on the bits of an integer. They are used more often in system programs or low-level code. The common feature of bitwise operators is that they process the integers they operate on **bit by bit**, not as a whole. The operands of these operators must be of integer types. It is invalid for their operands to be of real number types.

There are a total of 11 bitwise operators in the C language. The table below lists the bitwise operators in order of their precedence:

| Precedence Level | Symbol | Operator | English Name |
| :---: | :---: | :--- | :--- |
| 2 | `~` | Bitsel değil | Bitwise NOT |
| 5 | `<<` | Bitsel sola kaydırma | Bitwise left shift |
| 5 | `>>` | Bitsel sağa kaydırma | Bitwise right shift |
| 8 | `&` | Bitsel ve | Bitwise AND |
| 9 | `^` | Bitsel özel veya | Bitwise EXCLUSIVE OR (XOR) |
| 10 | `|` | Bitsel veya | Bitwise OR |
| 14 | `<<=`, `>>=`, `&=`, `^=`, `|=` | Bitsel işlemli atama işleçleri | Bitwise compound assignment operators |

Among the operators above, only the **Bitwise NOT (`~`)** operator is a **unary prefix** operator. The others are **binary infix** operators.

---

## ➖ The Bitwise NOT Operator (`~`)

The **bitwise NOT operator (`~`)**, like all other unary operators, is at the second precedence level of the operator precedence table.

This operator obtains a value by performing the **one's complement** operation on the bits of the integer that is its operand. That is, it produces a value by making the bits that are 1 in the integer value of its operand 0, and the bits that are 0, 1. The operator has **no side effect**. If its operand is an object, the value of this object is not changed.

Examine the program below:

    #include <stdio.h>
    int main()
    {
        unsigned int x = 0x1AC3;
        unsigned int y;
        y = ~x;
        printf("y = %X\n", y);
        return 0;
    }

Assume the program above is compiled on a system where the `int` type is 4 bytes long. The value $0\text{x}1\text{AC3}$ assigned to the variable $x$ is expressed in the binary number system in the following form:

$$\text{0000 0000 0000 0000 0001 1010 1100 0011}$$

In this case, the value assigned to the variable $y$ is:

$$\text{1111 1111 1111 1111 1110 0101 0011 1100}$$

The `printf` function prints:

    y = FFFFE53C

to the screen. Now compile and run the following program:

    #include <stdio.h>
    int main()
    {
        int x = 0;
        int y = ~x;
        printf("y = %d\n", y); // Output: -1 (for signed int)
        return 0;
    }

In the signed binary number system, the one's complement of 0 is the value $-1$, right?

---

## ➡️ The Bitwise Shift Operators (`<<`, `>>`)

There are two **bitwise shift operators**:

* **Bitwise right shift operator `>>`**
* **Bitwise left shift operator `<<`**

Both operators are located at the 5th precedence level of the precedence table. Thus, the precedence of these operators is lower than all arithmetic operators but higher than comparison operators. Bitwise shift operators are **binary infix** operators.

The **bitwise left shift operator** produces the value obtained by shifting the integer that is its left operand to the left by the integer that is its right operand. The bits that exit the boundary are filled with the **0 bit** from the right side of the number. Example:

    #include <stdio.h>
    int main()
    {
        unsigned int x = 52;
        unsigned int y = 2;
        unsigned int z;
        z = x << y; // 52 shifted left by 2 (equivalent to 52 * 4 = 208)
        printf("z = %u\n", z);
        return 0;
    }
    /* x = 0000 0000 0011 0100 (binary) */
    /* z = 0000 0000 1101 0000 (binary) */
    /* z = 208 */

Shifting an integer to the left by 1 bitwise obtains the value of that integer multiplied by two.

The **bitwise right shift operator** produces the value obtained by shifting the integer that is its left operand to the right by the integer that is its right operand. If the left operand is of an unsigned integer type, or of a signed integer type but has a positive value, the bits that exit the boundary are replaced by the **0 bit** from the left side of the number. If the expression to be shifted right is of a signed integer type and has a negative value, the padding from the left side for the bits that exit the boundary is **implementation specified** (either 0 or 1). That is, compilers can generate code that pads with the 1 bit to preserve the sign of the number, or they can generate code that pads with the 0 bit without considering preserving the sign of the number. Bitwise right shifting a signed negative integer is **not a portable feature**.

Shifting an integer to the right by 1 bitwise obtains the value of that number divided by two:

    #include <stdio.h>
    int main()
    {
        unsigned int x = 52;
        unsigned int y = 2;
        unsigned int z = x >> y; // 52 shifted right by 2 (equivalent to 52 / 4 = 13)
        printf("z = %u\n", z);
        return 0;
    }
    /* x = 0000 0000 0011 0100 (binary) */
    /* z = 0000 0000 0000 1101 (binary) */
    /* z = 13 */

Bitwise shift operators have **no side effects**. That is, if their left operand is an object, the value of this object in memory is not changed. If the value of the object that is the left operand is desired to be changed by the shifting operation, the compound assignment forms of these operators must be used.

The right operand of the shift operators must be smaller than the total number of bits of the type the left operand belongs to. If this condition is not met, the resulting situation is **undefined behavior**. For example, shifting an `int` type value by 32 or more to the left or right is undefined in Windows systems. This situation should be avoided.

The associativity of the bitwise shift operators is **left-to-right**:

    x << 4 >> 8

Let $x$ be an unsigned 2-byte integer variable. The expression above is treated by the compiler in the form:

    (x << 4) >> 8

This expression obtains the middle 8 bits of the variable $x$.

---

## 🤝 The Bitwise AND Operator (`&`)

The **bitwise AND operator (`&`)** is at the 8th precedence level of the operator precedence table. The associativity of this level is **left-to-right**. The operator has **no side effect**. If its operands are expressions denoting objects, the value of these operands in memory is not changed. To produce a value, it performs the "AND" operation on the corresponding bits of the integers that are its operands. The operation table for the "AND" operation is given again below:

| Bit 1 | Bit 2 | Result (Bit 1 AND Bit 2) |
| :---: | :---: | :---: |
| 0 | 0 | 0 |
| 0 | 1 | 0 |
| 1 | 0 | 0 |
| 1 | 1 | 1 |

The value produced by the "bitwise AND" operator is the value obtained by performing the "AND" operation on the corresponding bits of its operands:

    #include <stdio.h>
    int main()
    {
        unsigned int x = 0x1BC5;
        unsigned int y = 0X3A0D;
        unsigned int z = x & y;
        printf("z = %X\n", z);
        return 0;
    }
    /* x = 0001 1011 1100 0101 */
    /* y = 0011 1010 0000 1101 */
    /* z = 0001 1010 0000 0101 */
    /* z = 0x1A05 */

The **1 bit is the identity element** in the "bitwise AND" operation. The **0 bit is the absorbing element** in the "bitwise AND" operation.

Mistakenly using the "bitwise AND" operator instead of the "logical AND" operator is a frequent mistake. Carefully examine the following code:

    #include <stdio.h>
    int main()
    {
        int x = 85;
        int y = 170;
        if (x && y) // Logical AND
            printf("true!\n");
        else
            printf("false!\n");
        if (x & y) // Bitwise AND
            printf("true!\n");
        else
            printf("false!\n");
        return 0;
    }

In the program above, the "bitwise AND" operator (`&`) is mistakenly used instead of the "logical AND" operator (`&&`). Both "logical AND" and "bitwise AND" are binary infix operators. Compilers do not generate an error or warning message for the code above. In the example above, the expression, which would be interpreted as logically "true" if the "logical AND" operator were used, produces the value 0 when the bitwise AND operator is used, and is interpreted as logically "false."

---

## ⊕ The Bitwise EXCLUSIVE OR Operator (`^`)

The **bitwise EXCLUSIVE OR operator (`^`)** is at the 9th precedence level of the operator precedence table. The associativity is **left-to-right**. It has **no side effect**; the value of the objects that are its operands in memory is not changed. To produce a value, it performs the "exclusive OR" operation on the corresponding bits of the integers that are its operands. The operation table for the bitwise "exclusive OR" operation is given below:

| Bit 1 | Bit 2 | Result (Bit 1 XOR Bit 2) |
| :---: | :---: | :---: |
| 0 | 0 | 0 |
| 0 | 1 | 1 |
| 1 | 0 | 1 |
| 1 | 1 | 0 |

The table above can be summarized as follows: If both of its operands have the same value, the produced value is 0; if one of the operands is different from the other, the produced value is 1.

    #include <stdio.h>
    int main()
    {
        unsigned int x = 0x1BC5;
        unsigned int y = 0X3A0D;
        unsigned int z = x ^ y;
        printf("z = %X\n", z);
        return 0;
    }
    /* x = 0001 1011 1100 0101 */
    /* y = 0011 1010 0000 1101 */
    /* z = 0010 0001 1100 1000 */
    /* z = 0x21C8 */

If an integer is subjected to the bitwise exclusive OR operation with the same value consecutively, the integer's own value is obtained:

    #include <stdio.h>
    int main()
    {
        unsigned int a = 0X1BC5;
        unsigned int b = 0X3A0D;
        /* a = 0001 1011 1100 0101 */
        /* b = 0011 1010 0000 1101 */
        a ^= b; // a now holds a ^ b
        a ^= b; // a now holds (a ^ b) ^ b = a
        printf("a = %X\n", a);
        /* a = 0x1BC5 */
        return 0;
    }

The value of the variable $a$ is obtained again. This property of the "exclusive OR" operation is utilized in some encryption algorithms.

---

## ∨ The Bitwise OR Operator (`|`)

The **bitwise OR operator (`|`)** is at the 10th precedence level of the operator precedence table. The associativity is **left-to-right**. It has **no side effect**; if its operands are expressions denoting objects, it does not change their values in memory. To produce a value, it performs the "OR" operation on the corresponding bits of the integers that are its operands. The operation table for the bitwise OR operation is given below:

| Bit 1 | Bit 2 | Result (Bit 1 OR Bit 2) |
| :---: | :---: | :---: |
| 0 | 0 | 0 |
| 0 | 1 | 1 |
| 1 | 0 | 1 |
| 1 | 1 | 1 |

The value produced by the bitwise OR operator is the value obtained by performing the "OR" operation on the corresponding bits of its operands:

    #include <stdio.h>
    int main()
    {
        unsigned int x = 0x1BC5;
        unsigned int y = 0X3A0D;
        unsigned int z = x | y;
        printf("z = %X\n", z);
        return 0;
    }
    /* x = 0001 1011 1100 0101 */
    /* y = 0011 1010 0000 1101 */
    /* z = 0011 1011 1100 1101 */
    /* z = 0x3BCD */

The **0 bit is the identity element** in the bitwise OR operation. The **1 bit is the absorbing element** in the bitwise OR operation.

The program below prints the values produced by the bitwise AND, exclusive OR, and OR operators in the binary number system. Compile and run the program:

    #include <stdio.h>
    #include <stdlib.h>
    
    // Assumed standard or helper function for binary output (itoa is non-standard)
    void bit_print(int val)
    {
        // Placeholder for binary printing logic
        // Assumes a 32-bit int for demonstration clarity
        int i;
        printf("%10d ", val);
        for(i = sizeof(int) * 8 - 1; i >= 0; --i) {
            putchar((val & (1 << i)) ? '1' : '0');
        }
        putchar('\n');
    }
    
    int main()
    {
        int x, y;
        printf("enter two numbers: ");
        scanf("%d%d", &x, &y);
        
        bit_print(x);
        bit_print(y);
        
        printf("bitwise AND operation\n");
        bit_print(x & y);
        printf("*********************************************************\n");
        
        printf("bitwise EXCLUSIVE OR operation\n");
        bit_print(x ^ y);
        printf("*********************************************************\n");
        
        printf("bitwise OR operation\n");
        bit_print(x | y);
        return 0;
    }

### Bitwise Operators Do Not Exhibit Short-Circuit Behavior

Bitwise operators **do not** have short-circuit behavior. That is, both operands of these operators are necessarily processed.

---

## 🧮 Bitwise Compound Assignment Operators

Except for the bitwise NOT operator, there are compound assignment operators for all bitwise operators. As mentioned before, bitwise operators have **no side effects**. Bitwise operators do not change the values of the objects that are their operands in memory. If the values of the objects that are their operands are desired to be changed, the compound assignment operators can be used:

| Long Form | Short Form |
| :---: | :---: |
| `x = x << y` | `x <<= y` |
| `x = x >> y` | `x >>= y` |
| `x = x & y` | `x &= y` |
| `x = x ^ y` | `x ^= y` |
| `x = x | y` | `x |= y` |

The bitwise exclusive OR compound assignment operator can also be used in the **swap** of the values of two integer variables without a temporary variable:

    #include <stdio.h>
    int main()
    {
        int x, y;
        printf("enter two numbers: ");
        scanf("%d%d", &x, &y);
        printf("x = %d\ny = %d\n", x, y);
        
        x ^= y ^= x ^= y; // Swap operation
        
        printf("x = %d\ny = %d\n", x, y);
        return 0;
    }

In the program above, the values of the variables $x$ and $y$ are swapped using the bitwise exclusive OR operator.

---

## 🛠️ Some Themes Regarding the Use of Bitwise Operators

The use of bitwise operators is encountered more often in system programs. In system programs, it is frequently necessary to perform some operations on the bits of an integer. The following describes frequently performed operations at the bitwise level:

### Setting a Specific Bit of an Integer (To 1)

This can also be called "setting" a specific bit of an integer. To set a specific bit of an integer to 1, the integer in question must be subjected to the **"bitwise OR"** operation with a mask number that has the relevant bit as 1 and the other bits as 0. This is because the 1 bit is the absorbing element and the 0 bit is the identity element in the bitwise OR operation.

In the example below, the 5th bit of a number is set to 1:

    #include <stdio.h>
    int main()
    {
        int ch = 0x0041; // 'A' (0100 0001)
        int mask = 0x0020; // (0010 0000) (5th bit is 1)
        ch |= mask; // OR with mask
        printf("ch = %d\n", ch); // Output: 97 ('a')
        return 0;
    }

Let $x$ be an integer and $k$ be any bit number of this number. An expression that sets the $k$-th bit of an integer to 1 can be written in the form:

    x |= 1 << k;

Expressions like `1 << k` used to perform such operations are called a **"bitmask"** or simply **"mask."**

### Clearing a Specific Bit of an Integer (To 0)

To clear a specific bit of an integer (to 0), the integer in question must be subjected to the **"bitwise AND"** operation with a mask that has the relevant bit as 0 and the other bits as 1. This is because the 0 bit is the absorbing element and the 1 bit is the identity element in the "bitwise AND" operation.

In the example below, the 5th bit of an integer is cleared:

    #include <stdio.h>
    int main()
    {
        int ch = 0x0061; // 'a' (0110 0001)
        int mask = ~0x0020; // ~(0010 0000) (5th bit is 0, others 1)
        ch &= mask; // AND with mask
        printf("ch = %d\n", ch); // Output: 65 ('A')
        return 0;
    }

Let $x$ be an integer and $k$ be any bit number of this number. An expression that clears the $k$-th bit of a number can be generalized as follows:

    x &= ~(1 << k);

### Obtaining the Value of a Specific Bit of an Integer (Is it 0 or 1?)

To learn whether a specific bit of an integer is 0 or 1, the integer in question must be subjected to the **"bitwise AND"** operation with a mask that has the relevant bit as 1 and the other bits as 0, and then interpreted logically. This is because the 0 bit is the absorbing element and the 1 bit is the identity element in the "bitwise AND" operation. If the expression is interpreted as logically "true," the relevant bit is 1; if it is interpreted as logically "false," the relevant bit is 0.

Let $x$ be an integer and $k$ be any bit number of this number. A statement that checks whether the $k$-th bit of a number is 1 or 0 can be written in the following form:

    if (x & 1 << k)
        /* k-th bit is 1 */
    else
        /* k-th bit is 0 */

Whether a positive integer is an odd number can be checked with the "bitwise AND" operator. If an integer is an odd number, the 0th bit of the number is 1.

    #include <stdio.h>
    int main()
    {
        int x;
        printf("enter a number: ");
        scanf("%d", &x);
        if (x & 1) // Check the 0th bit
            printf("%d is an odd number\n", x);
        else
            printf("%d is an even number\n", x);
        return 0;
    }

### Toggling a Specific Bit of an Integer

In some applications, the value of a specific bit of an integer needs to be **toggled** (flip). That is, if the bit in question is 1, it should be made 0; if it is 0, it should be made 1. The **"bitwise EXCLUSIVE OR"** operator is used for this purpose. The 0 bit is the identity element in the bitwise exclusive OR operation. To change the value of the $k$-th bit of a number, the number is subjected to the "bitwise exclusive OR" operation with a mask that has the $k$-th bit as 1 and the other bits as 0.

Let $x$ be an integer and $k$ be any bit number of this number. An expression that toggles the $k$-th bit of a number can be written as follows:

    x ^= 1 << k;

### Operating on Multiple Bits

What can be done to clear specific bits of an integer? For example, let's say we want to clear the 7th, 8th, and 9th bits of an `int` type integer without changing the values of the other bits. To achieve this, the integer can be subjected to the bitwise AND operation with a mask that has the 7th, 8th, and 9th bits as 0 and the other bits as 1. For example, on a system where the `int` type is 16 bits, this number would have the following bit pattern:

$$\text{1111 1100 0111 1111}$$

The hexadecimal representation of this value is $0\text{x}\text{FC7F}$, right?

    x &= 0xFC7F;

How about having functions perform the operations done on specific bits of integers?

    void clearbits(int *ptr, size_t startbit, size_t nbits);

The `clearbits` function clears $nbits$ starting from the bit numbered `startbit` of the expression whose address is sent. For example, to clear the 7th, 8th, and 9th bits of an `unsigned int` type variable named $x$, the function is called in the following form:

    clearbits(&x, 7, 3);

    void clearbits(unsigned int *ptr, size_t startbit, size_t nbits)
    {
        size_t k;
        // The mask is created by shifting 1 left by (startbit + k), then NOTing.
        for (k = 0; k < nbits; ++k)
            *ptr &= ~(1 << (startbit + k)); // Corrected logic from original text
    }

Similarly, the `setbits` function can also be written. To set the 7th, 8th, and 9th bits of an `unsigned int` type variable named $x$ to 1, the function is called in the following form:

    setbits(&x, 7, 3);

    void setbits(unsigned int *ptr, size_t startbit, size_t nbits)
    {
        size_t k;
        for (k = 0; k < nbits; ++k)
            *ptr |= (1 << (startbit + k)); // Corrected logic from original text
    }

So, can a 32-bit area be used to hold more than one value? Assuming negative numbers are not used, values in the range $0 – 15$ can be held in a 4-bit area. Suppose the value of a variable changes in the range $0 – 15$. In some cases, storing a value that can be expressed with 4 bits in an integer type that occupies 2 or 4 bytes may be undesirable. A 32-bit area can actually hold 4 different values, right?

What can be done to store an integer value in a specific bit field of a number? First, the relevant bits of the number are cleared. A function like `clearbits` written above can be called for this purpose. Then, the number can be subjected to the bitwise OR operation with an appropriate value. Examine the following function definition:

    void putvalue(unsigned int*ptr, size_t startbit, size_t nbits, int value)
    {
        // First clear the bits (assumed clearbits is available and correct)
        // clearbits(ptr, startbit, nbits); 
        
        // Then set the new value (value & mask to ensure value doesn't exceed nbits)
        *ptr |= (value & ((1 << nbits) - 1)) << startbit; // Corrected logic
    }

The `putvalue` function places the `value` into the $nbits$ field starting from the `startbit` of the object whose address is sent. The function can be called as follows:

    putvalue(&x, 4, 3, 7); // Places the value 7 into the 3-bit field starting at bit 4 of x

How can the value stored in a specific bit field of an integer variable be obtained? This task can also be done by a function:

    unsigned getvalue(unsigned int x, size_t startbit, size_t nbits);

The `getvalue` function returns the value stored in the $nbits$ field starting from the bit numbered `startbit` of the integer value passed as its first parameter:

    unsigned int getvalue(unsigned int number, size_t startbit, size_t nbits)
    {
        // 1. Shift out the MSBs before the field starts
        number <<= sizeof(int) * 8 - startbit - nbits;
        
        // 2. Shift the field to the rightmost position (LSBs)
        return number >>= sizeof(int) * 8 - nbits;
    }

### Some Example Applications Regarding the Use of Bitwise Operators

Below, a function named `showbits` is defined that prints an `int` type value to the screen in the binary number system:

    #include <stdio.h>
    void showbits(int x)
    {
        int i = sizeof(int) * 8 - 1; // Start from MSB
        for (; i >= 0; --i)
            // AND with 1 shifted to the current bit position to check the bit
            putchar((x >> i) & 1 ? '1' : '0'); 
    }
    int main()
    {
        int val;
        printf("enter a number : ");
        scanf("%d", &val);
        showbits(val);
        return 0;
    }

Below is the definition of a function named `showbits2` that performs the same task in a different way:

    void showbits2(int x)
    {
        // Creates a mask with only the MSB set (1000...)
        unsigned int i = (~((unsigned)~0 >> 1)); 
        
        while (i) {
            // Check the current bit with the mask
            putchar(x & i ? '1' : '0'); 
            i >>= 1; // Shift the mask right
        }
    }

Below, a function named `reverse_bits` is defined that reverses the bits of an `int` type value:

    #include <stdio.h>
    int reverse_bits(int number)
    {
        int k;
        int no_of_bits = sizeof(int) * 8;
        int rev_num = 0;
        for (k = 0; k < no_of_bits; ++k)
            // If k-th bit of 'number' is 1
            if (number & (1 << k)) 
                // Set the corresponding bit at the reverse position
                rev_num |= (1 << (no_of_bits - 1 - k)); 
        return rev_num;
    }

Below, a function named `reverse` is defined that reverses the bits of an `unsigned char` type value:

    #include <stdio.h>
    unsigned char reverse(unsigned char byte)
    {
        unsigned char dest;
        // Swap 4-bit nibbles
        dest = (byte << 4) | (byte >> 4); 
        // Swap 2-bit groups within each nibble
        dest = ((dest << 2) & 0xCC) | ((dest >> 2) & 0x33); 
        // Swap 1-bit groups within each 2-bit group
        return ((dest << 1) & 0xAA) | ((dest >> 1) & 0x55); 
    }

Below, a function named `no_of_setbits` is defined that returns the number of bits of an `int` type value sent to it that are 1:

    #include <stdio.h>
    int no_of_setbits(unsigned int value)
    {
        int counter = 0;
        int k;
        for (k = 0; k < sizeof(int) * 8; ++k)
            if (value & (1 << k))
                counter++;
        return counter;
    }
    int main()
    {
        int number;
        printf("enter a number : ");
        scanf("%d", &number);
        printf("your number has %d bits set to 1\n", no_of_setbits(number));
        return 0;
    }

Now let's design a function that will run much faster:

    int no_of_setbits(unsigned int value)
    {
        // Static array stores the number of set bits for each 4-bit number (0-15)
        static int bitcounts[] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4}; 
        int counter = 0;
        for (; value != 0; value >>= 4)
            // AND with 0x0F (1111) to get the LSB nibble, use as index
            counter += bitcounts[value & 0x0F]; 
        return counter;
    }

In the function defined above, in each iteration of the loop, the number of set bits in the low-order 4 bits of the variable `value` is obtained by using the numerical value of the 4 bits as the index for the `bitcounts` array. For example, let the value of the integer expressed in the 4-bit area be 11: $11 = 1011$. The total number of bits set to 1 in this number is 3. The value of the 11-indexed element of the `bitcounts` array is 3. Before proceeding to the next iteration of the loop, the variable `value` is shifted 4 times to the right, and this time the bits in the next 4-bit area of `value` are checked.

Below is a function that further increases the processing speed:

    // Array stores the number of set bits for each 8-bit number (0-255)
    const static char bit_array[] = {
        // ... (256 values from 0 to 8)
        0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
        4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8
    };
    
    int count1bits(unsigned long x)
    {
        // Breaks the 32-bit number into 4 8-bit bytes and sums their set bit counts
        return bit_array[x & 0xff] + 
               bit_array[(x >> 8) & 0xff] +
               bit_array[(x >> 16) & 0xff] + 
               bit_array[(x >> 24) & 0xff];
    }

The `count1bits` function counts the bits of a 32-bit integer whose value is 1. The function performs this task by finding the number of bits that are 1 in an 8-bit group using the `bit_array`.

Below, the **greatest common divisor (GCD)** of two integers is calculated with the function named `gcd_b`. Note that the remainder operator is **not** used in the function's definition; bitwise operators are used:

    unsigned int gcd_b(unsigned int x, unsigned int y)
    {
        unsigned int temp;
        unsigned int cpof = 0; // Common powers of 2 factor
        
        if (x == 0)
            return y;
        if (y == 0)
            return x;
            
        // 1. Remove common factors of 2 (i.e., shift right until one number is odd)
        while (((x | y) & 1) == 0) { // While both are even (LSB is 0)
            x >>= 1;
            y >>= 1;
            ++cpof; // Count the common factors
        }
        
        // 2. Remove factors of 2 from x (x must be odd now)
        while ((x & 1) == 0) 
            x >>= 1;
        
        // 3. Main Euclidean algorithm using subtraction and shifts
        while (y) {
            // y must be odd
            while (!(y & 1))
                y >>= 1;
                
            temp = y; // Store y before next step
            if (x > y)
                y = x - y;
            else
                y -= x;
            x = temp;
        }
        
        // 4. Restore the common factors of 2
        return x << cpof;
    }