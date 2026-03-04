# 👻 `void` Pointers

Some functions perform generalized operations on memory blocks. These functions are not concerned with what is in the memory blocks they operate on. Consider copying the content of a memory block to another location in memory. The function can achieve this goal by copying byte by byte from the source address to the destination address. What type should the parameter variables of such a function be?

**`void` pointers** are pointers that are not of any specific type. The `void` keyword is used in the definitions of variables of this type:

    void *ptr;

`void` pointers do not have type information. Only the **numerical component** of the addresses is stored in `void` pointers. Therefore, assignments made between `void` pointers and pointers of other types (addresses) are valid. An address of any type can be assigned to a `void` pointer without any problem. Similarly, a `void` pointer can be assigned to a pointer variable of a specific type without any problem.

    char *ptr;
    void *vp;
    /***/
    ptr = vp; /* Valid */
    vp = ptr; /* Valid */

Since `void` pointers do not belong to a specific type, some operations applied to pointers that have type information **cannot be applied to `void` pointers**:

i) It is invalid for `void` pointers to be the operand of the **`*` or `[]` operators**. These operators require type information to access an object.

    void func()
    {
        double a[50];
        void *vptr;
        vptr = a;      /* Valid: Array address assigned to void pointer */
        *vptr = 3.7;   /* Invalid! Needs type info for dereference */
        vptr[2] = 5.6; /* Invalid! Needs type info for subscripting */
        /****/
    }

The expressions `*vptr` and `vptr[2]` in the code snippet above are invalid.

ii) Adding an integer to a `void` address or subtracting an integer from a `void` address is **invalid**. This is because, according to pointer arithmetic, when a pointer's value is incremented by $n$, the numerical component of the address inside the pointer increases by $n$ multiplied by the size of the type of the object the pointer points to. Since `void` pointers do not have types, it is unknown how much the numerical component should increase in this case.

`void` pointers cannot be the operand of the `++` and `--` operators.

The expression `++ptr;` is equivalent to the expression `ptr = ptr + 1;`.

    void func()
    {
        int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        void *vptr = a;
        void *p;
        p = vptr + 2; /* Invalid */
        ++vptr;       /* Invalid */
        --vptr;       /* Invalid */
        vptr += 2;    /* Invalid */
        vptr -= 3;    /* Invalid */
    }

iii) Similarly, two `void` addresses **cannot be subtracted** from each other. For addresses of other types, subtracting two addresses related to two objects within the same block is completely valid. Recall that the value of such an expression is an integer equivalent to the number of objects between the two addresses.

    void func()
    {
        void *p1, *p2;
        int k;
        /***/
        k = p1 - p2; /* Invalid */
    }

`void` pointer variables are used only to store the numerical components of addresses. Since they do not cause warnings or errors in assignment operations between pointers of other types, they can also be found as **parameter variables** in functions where type-independent address operations are performed. For example:

    void func(void *p);

Since the parameter variable of the function named `func` is a `void` pointer, address information of any type can be sent as an argument to this function. That is, the `func` function can be called with the address of any object. In this case, no error occurs during compilation, nor is a warning message received from the compiler.

The `func` function does not perform an operation dependent on the type of the object at the received address.

In the C language, functions can also return `void` type addresses. Assigning `void` type addresses to pointer variables of any type is valid:

    void *func(void);
    int main()
    {
        int *p;
        char *str;
        p = func();   /* Valid */
        /***/
        str = func(); /* Valid */
        return 0;
    }

## Standard C Functions Whose Parameter is a `void` Pointer

In the standard library, there is a group of functions starting with the letters **`mem`**. These functions perform general, type-independent operations related to memory blocks.

The best example explaining the use of `void` pointers is the **`memcpy`** function declared in the standard `string.h` header file.

    void *memcpy(void *pdest, const void *psource, size_t nbytes);

The `memcpy` function copies $nbytes$ of bytes, starting from the address specified by its second parameter (`psource`), starting to the address specified by its first parameter (`pdest`).

The function has no relation to the null terminator or strings; it performs an unconditional copy. That is, a **block copy** is in question. The function copies a specific number of bytes from the source address to the destination address, regardless of what is in the memory block it copies or what type of data it is. It is a standard function widely used, especially in system programs.

With the `memcpy` function, for example, any two arrays of the same type can be copied to each other:

    #include <stdio.h>
    #include <string.h>
    #define SIZE 10
    int main()
    {
        int a[SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int b[SIZE];
        int i;
        memcpy(b, a, sizeof(int) * SIZE); // Copy all elements (40 bytes)
        for (i = 0; i < SIZE; ++i)
            printf("%d ", b[i]);
        return 0;
    }

The following function calls are also equivalent:

    char s[50] = "Ali";
    char d[50];
    
    strcpy(d, s);
    memcpy(d, s, strlen(s) + 1); // Copies string including the null terminator

The pointer parameters of the `memcpy` function are of type `void *`. This is because no warning message is received from the compilers, regardless of what type of address is passed. This function can be defined as follows:

    void *mymemcpy(void *vp1, const void *vp2, unsigned int n)
    {
        char *p1 = vp1;       // Convert to char* for byte arithmetic
        const char *p2 = vp2; // Convert to char* for byte arithmetic
        unsigned int k;
        for (k = 0; k < n; ++k)
            p1[k] = p2[k];
        return vp1;
    }

The function could also be defined in this form:

    #include <stdio.h>
    void *mymemcpy(void *vp1, const void *vp2, size_t n)
    {
        char *p1 = vp1;
        const char *p2 = vp2;
        while (n--)
            *p1++ = *p2++; // Copy byte and advance pointers
        return vp1;
    }
    
    int main()
    {
        int a[5] = {1, 2, 3, 4, 5};
        int b[5], i;
        mymemcpy(b, a, sizeof(int) * 5); // Copy 20 bytes (5 ints)
        for (i = 0; i < 5; ++i)
            printf("%d ", b[i]);
        return 0;
    }

However, the behavior of the `memcpy` function in copying **overlapping blocks is not guaranteed**.

### The `memmove` Function

`memmove` also copies a block from one location to another. The declaration of the function is exactly the same as that of the `memcpy` function.

    void *memmove(void *dest, const void *source, size_t nbytes);

The only difference between the two functions is that the behavior of the `memmove` function is **guaranteed in copying overlapping blocks**.

Should the `memmove` function be preferred in copying non-overlapping blocks? No, this would not be good advice, because:

1.  The `memmove` function has an added overhead to provide this guarantee.
2.  The person reading the code gains a strong impression that the block being copied and the block to which the copying is being performed somehow overlap if the `memmove` function is used.

In this case, the `memmove` function should be preferred in cases where the source block and the destination block overlap or there is a risk of overlap. Otherwise, i.e., if it is definitively known that the blocks in question do not overlap, the `memcpy` function should be preferred.

Below is an example code written for the `memmove` function:

    void *mymemmove(void *vp1, const void *vp2, unsigned int n)
    {
        char *p1 = vp1;
        const char *p2 = vp2;
        // Check for overlap and if source is before dest (p1 > p2)
        if (p1 > p2 && p2 + n > p1) {
            // Copy backwards (to avoid overwriting source data that hasn't been copied yet)
            p1 += n;
            p2 += n;
            while (n--)
                *--p1 = *--p2;
        }
        else
            // Copy forwards (safe for non-overlapping or when dest is before source)
            while (n--)
                *p1++ = *p2++;
        return vp1;
    }

### The `memset` Function

This is a standard C function. It is used to fill a memory block at a given address with a specific character, i.e., a byte value. The declaration of the function is:

    void *memset(void *block, int c, size_t nbytes);

This function fills the block of size $nbytes$, starting from the address $block$, with the byte value specified by its second parameter.

The function can be used, for example, to zero out an array of any type:

    double d[100];
    memset(d, 0, sizeof(d));

The function can be defined as follows:

    #include <stdio.h>
    void *mymemset(void *block, int c, size_t n); // Note: Correct prototype uses size_t
    int main()
    {
        int a[10];
        int i;
        mymemset(a, 0, sizeof(a));
        for (i = 0; i < 10; ++i)
            printf("%d ", a[i]);
        return 0;
    }
    
    void *mymemset(void *block, int c, size_t n)
    {
        char *p=(char *)block;
        while (n--)
            *p++ = c;
        return block;
    }

### The `memchr` Function

This is a standard C function. It is used to search for a specific byte value in a memory block at a given address. The declaration of the function in the `string.h` header file is as follows:

    void *memchr(const void *block, int c, size_t nbytes);

The function searches for a byte with the value $c$ within $nbytes$ starting from the address $block$. The function returns the address of the first byte it finds with the value $c$. The return value of the function is a **`void` type address**. If the searched byte is not found, the function returns the **NULL address**.

The success of the function must definitely be checked. The function can be defined as follows:

    void *mymemchr(const void *p_block, int c, unsigned int nbytes)
    {
        const char *p = p_block;
        while (nbytes--) {
            if (*p == c)
                return (void *)p;
            p++;
        }
        return NULL;
    }

### The `memcmp` Function

This is a standard C function. It is used to compare two memory blocks at given addresses. The declaration of the function in the `string.h` header file is as follows:

    int memcmp(const void *pblock1, const void *pblock2, size_t nbytes); // Note: Corrected second param name

The function compares two blocks of size $nbytes$ starting from the addresses $pblock1$ and $pblock2$. The return value of the function is of type `int`. The interpretation of the return value is similar to the standard `strcmp` function:

* If the two memory blocks are exactly the same, i.e., all bytes in the two blocks are equal, the function returns the **value 0**.
* If the first memory block is greater than the second memory block, the function returns a **positive value**.
* If the first memory block is smaller than the second memory block, the function returns a **negative value**.

The comparison is done as follows: The blocks are compared byte by byte as **unsigned integers**, starting from the lowest numerical addresses. When the first differing byte is encountered, the block with the greater integer value is greater.

The function can be defined as follows:

    int mymemcmp(const void *vp1, const void *vp2, size_t nbytes)
    {
        const unsigned char *p1 = vp1;
        const unsigned char *p2 = vp2;
        unsigned int k;
        for (k = 0; k < nbytes; ++k)
            if (p1[k] != p2[k])
                // Compare as unsigned char to follow standard
                return p1[k] < p2[k] ? -1 : 1; 
        return 0;
    }

A `main` function to test the written function is provided below:

    int main()
    {
        unsigned char s1[100] = {0};
        unsigned char s2[100] = {0};
        
        if (!mymemcmp(s1, s2, 100))
            printf("blocks are equal!\n");
        
        s1[90] = 1;
        
        if (mymemcmp(s1, s2, 100) > 0)
            printf("first block is greater!\n");
        return 0;
    }