# 🐞 Pointer Errors

A region in RAM can be accessed using pointers. During the execution of a program, there may be other programs running in memory. If data is transferred to the memory area of a currently running program using pointers, the code of that program will be corrupted, leading to various malfunctions in the program's operation. This malfunction can negatively affect the entire system.

Memory regions whose users are unknown are called **unsafe regions**. Accessing unsafe regions is called a **"pointer error."**

When pointer errors are made, the system may lock up, or programs may run incorrectly. The negative consequences resulting from pointer errors may not emerge immediately.

Pointer errors occur not when unsafe regions are accessed, but when data is transferred **to** them.

Pointer errors **cannot be detected by the compiler during compilation**. These types of errors lead to negative consequences during the program's **runtime**. Memory regions obtained through the definition method are called **safe regions**. When an object is defined, the space allocated in memory by the compiler for that object is an area reserved for the programmer and is **safe**.

## Typical Situations That Cause Pointer Errors

### i) Errors Caused by Uninitialized Pointers:

As stated before, pointers are also objects. Their difference from other objects is that they hold address information. Since pointers are objects, they can be local or global, like other objects. While globally defined pointers are initialized with the value 0, local pointers are initialized with **garbage values**:

If a local pointer is defined and a value assignment is not made to this pointer in any way, the pointer will contain a random value. Consequently, when this pointer is used with the `*` operator or the `[]` operator, an object located at a random place in memory is accessed. Therefore, when an assignment is made to the obtained object, data is written to a random, unknown location in memory. This is a typical pointer error.

Examples:

    int main()
    {
        int *p; // Local pointer, contains garbage address
        *p = 25; /* INCORRECT */ // Writing to a random, unsafe location
        return 0;
    }

In the example above, the defined pointer $p$ contains a garbage value. With the statement `*p = 25;`, data is transferred to a random location, i.e., an unsafe location. The location where the data is transferred might contain the code of the operating system, the compiler, or another memory-resident program. In some systems, the program's own code may also be located in the region where the data is transferred.

Uninitialized global pointers (or static local pointers) contain the value zero. The number zero (**NULL address**) is used for testing in pointers. If data is transferred to this address, this error is optionally checked at runtime in most compilers. Example:

    char *p; // Global pointer, initialized to NULL (0)
    int main()
    {
        *p = 'm'; /* NULL pointer assignment */ // Writing to address 0
        return 0;
    }

When the code above is run, a runtime error such as "NULL pointer assignment" may be encountered. This check is performed thanks to the "checking code" placed inside the executable program by the compiler.

Errors caused by uninitialized pointers can also emerge through function calls:

    int main()
    {
        char *ptr; // Local pointer, contains garbage address
        gets(ptr); /* ????? */ // Writing to a random address
        return 0;
    }

In the code snippet above, the characters read from the keyboard with the standard `gets` function are written to a random location in memory. Since the standard `gets` function places the characters read from the keyboard starting from the address sent to it as an argument, the error given in the previous example applies to all characters entered from the keyboard.

### ii) Pointer Errors Caused by Unsafe Initial Values

Initializing a pointer **does not** mean that the pointer points to a safe region. For example:

    char *ptr;
    /***/
    ptr = (char *) 0x1FC5; // Assigning an arbitrary address
    *ptr = 'M';

In the example above, there is no information about whether the address `(char *) 0x1FC5` assigned to the pointer `ptr` is safe. It is unknown whether the region related to the address is in use. Although there are safe regions used for certain purposes within the memory area, `1FC5` does not point to such a region.

### iii) Pointer Errors Arising from Array Overruns

As is known, when the compiler sees an array definition, it allocates space in memory equal to the total array length during compilation. C compilers **do not check at compile time** whether an array is overrun.

    int main()
    {
        int a[10], k; // a has indices 0 to 9
        for (k = 0; k <= 10; ++k) // Loop runs for k=10
            a[k] = 0; // Accesses a[10] when k=10
        /***/
        return 0;
    }

When the example above is compiled and run on many systems, the loop continues even for the value $k = 10$. However, space has not been allocated for the element $a[10]$. The last element of the array is $a[9]$. The compiler allocates a total of 10 objects' worth of space, i.e., 40 bytes, in memory for the elements $a[0]$ through $a[9]$ of array $a$. However, there is no information about who is using the unallocated region $a[10]$ and for what purpose.

Although there is no guarantee in this regard, most compilers place consecutively defined elements contiguously in memory. But this is not a guaranteed feature. That is, writing code assuming this is guaranteed leads to problems. In the example above, the region $a[10]$ is allocated to the variable $k$, which is defined immediately after the array $a$ and used as the loop variable, in most compilers. Therefore, assigning the value 0 to the element $a[10]$ might actually assign the value 0 to the variable $k$, which could lead to the loop turning into an **infinite loop**.

The square bracket operator is also a pointer operator; assignments outside the allocated area for the array can be made using this operator. C language compilers do not check the source code for this purpose. Furthermore, expressions like $a[-1]$, $a[-2]$, etc., are also syntactically valid for array $a$, and assignments made here also lead to pointer errors.

Sometimes functions can implicitly cause array overruns. For example:

    void func()
    {
        char str[6]; // Space for 6 characters
        printf("enter name : ");
        gets(str); // Reads input until newline or EOF
        /***/
    }

A total of 6 characters' worth of space is allocated for the array `str` defined in the `func` function. The standard `gets` function places the characters received from the keyboard into memory starting from the address sent to it, and then writes the null terminator to the array. Therefore, in the example above, entering 6 or more characters during the program's runtime leads to a pointer error. Since the null terminator (`'\0'`) also occupies space in memory, it must be located within a memory area reserved for the program. For example, suppose the entered name is:

    necati

The `gets` function places these characters as follows:

    | n | e | c | a | t | i | \0 | ... |
    |---|---|---|---|---|---|----|---|
    | str[0] | ... | ... | ... | ... | str[5] | str[6] | ... |
    
The null terminator is placed outside the region allocated for the array. If the entered name had been longer in this example, more characters would have been written to an unallocated region for the program. To avoid such errors, the array should be sufficiently long, or a function that does not allow more elements than the array size to be placed should be used instead of the standard C function `gets`. The function **`fgets`** can be called for this purpose. You will see the standard `fgets` function in the section on files.

Incorrect use of standard C functions that operate on strings, such as `strcpy`, `strcat`, `strncpy`, and `strncat`, can also create similar errors.