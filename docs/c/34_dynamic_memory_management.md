# 💾 Dynamic Memory Management

## What is Dynamic Memory Management?

An executable program uses a memory area. Objects are blocks within the memory area used by the program. The space that one or more objects will occupy during the program's runtime can be obtained in two different ways:

1.  The compiler allocates space in memory for the object(s) at **compile time**.
2.  Space is obtained for the object(s) during the program's **runtime**.

Methods that allow a contiguous block of memory of a certain size to be allocated by the running program during runtime, and this area to be returned to the system when desired, are called **"dynamic memory management."**

When a variable or an array is defined in the C language, the space this variable or array will occupy during the program's runtime is allocated by the compiler at compile time:

    int a[100];

A compiler encountering an array definition like the one above allocates a total of 200 bytes in memory (assuming the length of the `int` type is 2 bytes on the system used). It is **not possible** to change the length of an array during the program's execution. If this array is local, it has **automatic storage duration**. That is, it maintains its life during the execution of the code of the block in which it is defined. If the array is global, it has **static storage duration**. That is, the array retains its place in memory throughout the program's execution.

By using dynamic memory management tools, obtaining the space that one or more objects will occupy during the program's runtime can be **delayed from compile time to runtime**.

Why should obtaining the memory block be shifted from compile time to runtime? There are some important reasons for this. Most of these reasons will be addressed in the following pages.

One of the most important reasons for obtaining the memory area during the program's runtime is that the size of the required memory block is only known during the program's **runtime**.

In array definitions, the expression indicating the array size, i.e., the expression inside the square brackets, must be a **constant expression**. This expression cannot contain variables. This is because the compiler needs to know the array size at compile time to be able to allocate space for the array in memory. However, the size of the array that needs to be used in many applications is determined during the program's runtime. Suppose the names of the files in a directory need to be temporarily stored in an array for sorting from smallest to largest. What should be the size of the array to be used for this purpose? This is not known initially because the number of files in the directory is unknown. Such situations are frequently encountered, especially in database applications. In some applications, the true length of arrays can only be definitively determined during the program's execution, as a result of certain events. In this case, the programmer working with arrays is forced to define the arrays as large as possible, considering the worst-case scenario, to avoid encountering any pointer errors. This implies the **inefficient use of memory**. Furthermore, if the defined arrays are local, they are held in memory until the end of the block in which they are defined; if the defined arrays are global, they are held in memory until the end of the program's execution. However, releasing the memory region allocated for the array as soon as the operation related to the array is finished is necessary for **efficient memory usage**.

Memory control is managed by the operating system. Operating systems have system functions that make a memory area not used for another purpose available for use. These functions can certainly be called directly. However, standard C functions are mostly used in applications. Standard C functions should be preferred for the **portability** of the written source code.

The standard C functions used in dynamic memory management are examined in detail one by one below:

### The `malloc` Function

The `malloc` function is used to obtain a **dynamic block from memory** during the program's runtime. The declaration of the function in the `stdlib.h` header file is as follows:

    void *malloc(size_t nbyte);

You know that the type `size_t` is a `typedef` name for one of the `unsigned int` or `unsigned long` types.

The function takes the length of the block desired to be obtained, in bytes. The allocated area is guaranteed to be **contiguous**. The return value of the `malloc` function is the **starting address** of the obtained memory block. Since this address is of type `void *`, it can be assigned to a pointer of any type without any problem. When this address is assigned to a pointer of any type, the obtained block can now be used like an object or an array with the help of the pointer holding the starting address. Obtaining the desired block is **not guaranteed** by the `malloc` function. The `malloc` function can fail for many reasons. The lack of enough free memory space for the desired area to be obtained is a common cause of failure.

The `malloc` function returns the **NULL address** when it fails. The success of the function call must definitely be checked. An example of obtaining a block in memory with the `malloc` function is given below:

    #include <stdio.h>
    #include <stdlib.h>
    #include <time.h>
    int main()
    {
        int *pd;
        int k, n;
        srand(time(0));
        n = rand() % 100 + 10; // Random size
        
        pd = (int *) malloc(n * sizeof(int)); // Request dynamic memory
        
        if (pd == NULL) { // Check for failure
            printf("cannot allocate memory\n");
            exit(EXIT_FAILURE);
        }
        
        printf("random %d numbers\n", n);
        for (k = 0; k < n; ++k) {
            pd[k] = rand() % 100;
            printf("%d ", pd[k]);
        }
        /***/
        // Memory should be freed here (e.g., free(pd);)
        return 0; 
    }

In the `main` function above, the value of the variable $n$ is obtained randomly with a call to the standard `rand` function during the program's runtime. Then, a memory block large enough to hold $n$ number of `int` type objects is obtained with the standard `malloc` function.

The success of the `malloc` function is checked with an `if` statement. In case of failure, i.e., if the return value of the `malloc` function is the `NULL` address, the program is terminated by calling the standard `exit` function.

The obtained dynamic block is then used as an `int` array. Random values in the range $0 - 100$ are assigned to the elements of the dynamic array.

For the portability of the source code, the size of the memory block to be used should be obtained with the `sizeof` operator.

Undoubtedly, it is not mandatory to terminate the program if the `malloc` function fails. Checking with assignment can also be done in one go.

    if ((pd = (int *) malloc(n * sizeof(int))) == NULL) { // Check and assign
        printf("cannot allocate memory\n");
        exit(EXIT_FAILURE);
    }

The success of the `malloc` function must definitely be checked. Reading from or writing to the address that is the return value in case of the function's failure leads to the content of the `NULL` address being accessed. This is a pointer error.

Programmers are often inclined to find testing unnecessary when a large number of small blocks are allocated. However, easier methods should be tried instead of giving up the testing operation. For example, suppose a dynamic area of $n$ bytes is desired to be obtained for each of 5 separate pointer variables like $p1, p2, p3, p4, p5$. In this case, testing can be done with a single `if` statement using logical operators.

    #include <stdio.h>
    #include <stdlib.h>
    // Assuming 'n' is defined
    int main()
    {
        char *p1, *p2, *p3, *p4, *p5;
        p1 = (char *)malloc(n);
        p2 = (char *)malloc(n);
        p3 = (char *)malloc(n);
        p4 = (char *)malloc(n);
        p5 = (char *)malloc(n);
        
        if (!(p1 && p2 && p3 && p4 && p5)) { // Check if ANY is NULL
            printf("cannot allocate memory!..\n");
            exit(EXIT_FAILURE);
        }
        /*....*/
        return 0;
    }

If any of the `malloc` calls fails, the expression `!(p1 && p2 && p3 && p4 && p5)` will be interpreted as "true," and the true part of the `if` statement will be executed.

Sometimes, the `malloc` function is wrapped with another function defined by the programmer:

    #include <stdio.h>
    #include <stdlib.h>
    void *cmalloc(size_t n)
    {
        void *pd = malloc(n);
        if (!pd) {
            printf("cannot allocate memory!..\n");
            exit(EXIT_FAILURE);
        }
        return pd;
    }

You see that the parametric structure of the `cmalloc` function defined above is the same as the `malloc` function. The function, unlike the `malloc` function, terminates the program in case of failure. If the program is to be terminated with an error message when a dynamic block obtaining attempt with `malloc` fails, the `cmalloc` function can be called instead of constantly repeating the source code.

Since the return value of the `malloc` function is a `void` type address, this address can be assigned to a pointer variable of any type without any problem. However, for readability, it is recommended to convert the address that is the return value of the `malloc` function to the type of the pointer variable to be used with the help of the type cast operator. Thus, the information of what type of object or objects the block obtained with the `malloc` function will be used as is given to the person reading the code.

In the period before the standardization of the C language, i.e., the classical C period, since there were no `void` pointers, the return value of the `malloc` function was a `char` type address. In this case, type conversion was a necessity if the address that was the return value was assigned to a pointer other than the `char` type.

The `malloc` function can be called more than once to obtain more than one dynamic area. Obtaining contiguous blocks in memory with different calls to the `malloc` function is **not guaranteed**. Therefore, the address that is the return value of every function call must be stored in a pointer variable. The following code snippet is incorrect because it assumes consecutive `malloc` calls will obtain contiguous memory blocks:

    #include <stdio.h>
    #include <stdlib.h>
    int main()
    {
        int *pd;
        int i;
        pd = (int *)malloc(sizeof(int) * 10);
        if (!pd) {
            printf("cannot allocate memory!\n");
            exit(EXIT_FAILURE);
        }
        // This is a separate allocation; its location is not guaranteed to be next to 'pd'
        if (malloc(sizeof(int) * 10) == NULL) { 
            printf("cannot allocate memory!\n");
            exit(EXIT_FAILURE);
        }
        /* New block is not obliged to be right after the old block */
        for (i = 0; i < 20; ++i) // Accessing outside the first 10-int block
            pd[i] = i;           /* Pointer Error */ 
        /*...*/
        return 0;
    }

The block obtained with the `malloc` function contains **garbage values**. Test this situation with the following code snippet:

    #include <stdio.h>
    #include <stdlib.h>
    int main()
    {
        int *pd;
        int i;
        pd = (int *) malloc(10 * sizeof(int));
        if (!pd) {
            printf("insufficient memory!..\n");
            exit(EXIT_FAILURE);
        }
        for (i = 0; i < 10; ++i)
            printf("pd[%d] = %d\n", i, pd[i]); // Output will be garbage
        return 0;
    }

The memory region made available for use by dynamic memory functions is called the **heap** in English. This area is called the free store in the C++ language. The size of the heap area can vary from system to system, but when an executable program is in question, a heap area of a specific size is reserved for the program's use when the program is loaded into memory.

Since the parameter variable of the `malloc` function is of type `unsigned int` ($\text{size\_t}$) in most systems, a block of at most 65535 bytes (64 KB) in size can be obtained with the `malloc` function under DOS. However, in 32-bit systems like UNIX and WINDOWS, since the `unsigned int` type is 4 bytes long, theoretically, a contiguous block of $4,294,967,295$ bytes (4 GB) in length can be obtained with the `malloc` function in these systems. Of course, this does not mean that the dynamic allocation operation is guaranteed.

The heap area is also limited. If the `malloc` function is continuously called, the functions will return the `NULL` address after a certain point due to failure.

Below, the size of the heap area used is attempted to be obtained with a code:

    #include <stdio.h>
    #include <stdlib.h>
    #define BLOCK_SIZE 2048
    int main()
    {
        long total = 0L;
        void *pd;
        for (;;) {
            pd = malloc(BLOCK_SIZE);
            if (!pd) // Exit if malloc fails
                break;
            total += BLOCK_SIZE;
        }
        printf("total heap area = %ld byte\n", total);
        system("pause"); // Non-standard, but pauses execution
        return 0;
    }

Run the program above for the DOS operating system first by compiling it with the symbolic constant $\text{BLOCK\_SIZE}$ having the value 2048. Then, recompile and run the program by changing the value of the $\text{BLOCK\_SIZE}$ constant to 1. You will see that the total value is much smaller.

The `malloc` function performs the dynamic block obtaining operation during the program's runtime. A table is maintained in the heap area with an appropriate data structure so that the blocks obtained with dynamic memory functions can be controlled. This table contains the starting address and size of each obtained dynamic block. This table itself is also in the heap area. When a program is run, the heap area is consumed in two different ways:

i) By making the blocks obtained by the `malloc`/`calloc`/`realloc` functions available for use.
ii) By adding information to the relevant table for each allocation operation.

### Returning the Obtained Dynamic Block

A block obtained from a call to dynamic memory functions can be returned to the system with a call to the standard function **`free`**. The declaration of the `free` function is also in the `stdlib.h` header file:

    void free(void *block);

The starting address of a memory block previously obtained with the `malloc`, `calloc`, or `realloc` functions must be passed to the `free` function. With a call to the `free` function, this block is returned to the heap area. The block returned to the heap area enters the potential for being obtained again by the `malloc`, `calloc`, or `realloc` functions.

As seen, the `free` function only takes the starting address of the memory block to be returned; it does not request the size of the previously allocated memory block. At runtime, the size value of the already obtained memory blocks is maintained in the tables held in the heap area.

Passing an address other than the starting address of a memory block previously obtained with dynamic memory functions as an argument to the `free` function is **undefined behavior** and should not be done.

    #include <stdlib.h>
    int main()
    {
        char *p1, *ptr;
        char s[100]; // Static array
        ptr = (char *)malloc(20); // Dynamic block
        free(ptr); // Correct and valid
        // free(p1); /* Incorrect: p1 uninitialized (local) or NULL (global) - Undefined/No-op */
        // free(s); /* Incorrect: s is a static array, not dynamic */
        return 0;
    }

In the example above, the call `free(p1)` causes a runtime error (or undefined behavior) because there is no area obtained with dynamic memory functions at address $p1$. The call `free(s)` also causes a runtime error (or undefined behavior) because space for array $s$ was not allocated from the dynamic memory area.

A block previously obtained dynamically is returned to the heap area with the `free` function, but the pointer holding the starting address of this block is not changed in any way. The pointer that holds the starting address of the block and is sent as an argument to the `free` function now points to an **unsafe address** after the call to the `free` function. Accessing a returned memory block is a frequent pointer error. Compile and run the following code:

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #define ARRAY_SIZE 100
    int main()
    {
        char name_entry[ARRAY_SIZE];
        char *pd;
        printf("enter a name: ");
        gets(name_entry);
        pd = (char *)malloc(strlen(name_entry) + 1); // Allocation size: length + 1 for '\0'
        if (pd == NULL) {
            printf("cannot obtain a dynamic block!\n");
            exit(EXIT_FAILURE);
        }
        strcpy(pd, name_entry);
        printf("string = %s\n", pd);
        free(pd); // Block is returned to heap
        printf("string = %s\n", pd); /* Incorrect! Accessing freed memory */
        return 0;
    }

In the `main` function above, a name entered from the keyboard is first placed into the local array named `name_entry`. Then, a memory block 1 byte larger than the length of the name entered from the keyboard is obtained with the called `malloc` function. The name in the local array is copied to the obtained memory block. Then, the name in the dynamic block is printed to the screen. The dynamic block is returned to the heap area with the call `free(pd)`. However, the returned block is accessed with the `printf` call made after the return operation. This is a pointer error.

Dynamic memory functions perform dynamic allocation and deallocation operations during the program's runtime.

A typical mistake related to the `free` function is trying to shrink a previously obtained dynamic block with the `free` function. Examine the following code:

    #include <stdlib.h>
    int main()
    {
        char *pd;
        pd = (char *)malloc(1000);
        /****/
        free(pd + 500); /* Incorrect */ // Not the start of the block
        /****/
        free(pd);
        return 0;
    }

In the `main` function above, first, a 1000-byte block is obtained with the `malloc` function, and the starting address of the block is assigned to the pointer variable $pd$. You then see that the address $pd + 500$ is sent as an argument to the called `free` function. With such a call, the `free` function does not return 500 bytes of the previously allocated 1000-byte area. The address $pd + 500$ is not the starting address of a dynamic area. Therefore, the function call exhibits **undefined behavior**. A dynamic area obtained with a `malloc` call cannot be shrunk with a call to the `free` function.

Passing an address other than the starting address of a dynamic block to the `free` function is undefined behavior. The only exception to this situation is passing the **`NULL` address** to the `free` function. Passing the `NULL` address to the function does not cause undefined behavior; it is simply a **no operation** call:

    if (ptr)
        free(ptr);

In the `if` statement above, where $ptr$ is a pointer variable, the `free` function is called if the value of the variable $ptr$ is not the `NULL` address. Even if the `free` function is called directly, the meaning of the code would not change much.

### Using a Dynamic Array

A memory block obtained with the `malloc` function can be used as an array whose size is obtained at the program's runtime. Compile and run the following program:

    #include <stdio.h>
    #include <stdlib.h>
    #include <time.h>
    
    void set_array(int *ptr, int size)
    {
        int k;
        for (k = 0; k < size; ++k)
            ptr[k] = rand() % 100;
    }
    
    void display_array(const int *ptr, int size)
    {
        int k;
        for (k = 0; k < size; ++k)
            printf("%2d ", ptr[k]);
        printf("\n");
    }
    
    int main()
    {
        int n;
        int *pd;
        printf("how many integers : ");
        scanf("%d", &n);
        
        pd = (int *)malloc(sizeof(int) * n);
        if (pd == NULL) {
            printf("cannot allocate memory!\n");
            exit(EXIT_FAILURE);
        }
        
        srand(time(0));
        set_array(pd, n);
        display_array(pd, n);
        free(pd);
        return 0;
    }

In the program above, the information of how many objects are desired at the program's runtime is received into the variable $n$ from the user with the standard `scanf` function. Then, a dynamic memory block large enough to hold $n$ number of `int` type objects is obtained with the `malloc` function. You see that the starting address of the obtained dynamic memory block is assigned to the pointer named $pd$. Now, there is an array whose starting address is $pd$ and size is $n$, right? The `set_array` and `display_array` functions are called with the starting address and size of this array.

### The `calloc` Function

The `calloc` function is very similar to the `malloc` function. Its declaration in the `stdlib.h` header file is as follows:

    void *calloc(size_t nblock, size_t block_size);

The `calloc` function is used to obtain a memory block of size equal to the product of its first parameter and its second parameter from the heap area. The return value of the function is the starting address of the obtained memory block if the allocation operation is successful. If the allocation operation is unsuccessful, the `calloc` function also returns the **`NULL` address**, just like the `malloc` function.

Dynamic allocation for a 100-element array of type `int` can be done with the `calloc` function as follows:

    void func()
    {
        int *pd;
        /***/
        pd = (int*) calloc(100, sizeof(int));
        if (pd == NULL) {
            printf("cannot allocate memory\n");
            exit(EXIT_FAILURE);
        }
        /***/
    }

Undoubtedly, the `calloc` function could also be called as follows in the code snippet above:

    pd = (int*) calloc(sizeof(int), 100);

Another difference between the `calloc` function and the `malloc` function is that it **zeros out** the memory block it obtains. All bytes of the block obtained by the `calloc` function contain zero values. The `malloc` function is used much more frequently than the `calloc` function. If the allocated block is to be zeroed out, the `calloc` function can be preferred instead of the `malloc` function.

Suppose the elements of an $n$-element array of type `int` obtained from the heap area are desired to be zeroed out. If this operation is done with the `malloc` function, the elements of the array must be zeroed out with a separate loop statement:

    int main()
    {
        int *pd;
        int i;
        int n = rand() % 100 + 10;
        pd = (int *) malloc(sizeof(int) * n);
        /***/
        for (i = 0; i < n; ++i) // Must be done manually after malloc
            pd[i] = 0;
        /***/
        return 0;
    }

However, the `calloc` function performs the zeroing operation within itself:

    pd = calloc(sizeof(int) , n);

In most compilers, the `calloc` function calls the `malloc` function within itself to perform the memory allocation operation.

### Memory Leak

A block obtained from the heap area with dynamic memory functions is held until a call to the `free` function. If the starting address of the dynamic block is lost, there is no longer a chance to use this block until the end of the program, and the block cannot be returned to the heap area. This situation is called a **memory leak**. Suppose a dynamic block is obtained within a function, but this block is not returned to the heap area within the function:

    void process()
    {
        char *pd = (char *)malloc(1000);
        if (pd == NULL) {
            printf("cannot obtain a dynamic block!\n");
            exit(EXIT_FAILURE);
        }
        /***/
        // No free(pd) call here!
    }

Every time the `process` function is called, a 1000-byte area is obtained. However, the dynamic area obtained within the function is not returned to the heap area. In this case, a 1000-byte area is blocked from the heap area with every call made to the `process` function. If the `process` function is a function called very frequently within the main program, the heap area can be entirely consumed after a certain number of calls. That is, after a certain time, the `malloc` function will no longer be able to obtain a new block.

### The `realloc` Function

The `realloc` function is called to **enlarge or shrink** a memory block previously obtained with the `malloc` or `calloc` functions. The declaration of the function is in the `stdlib.h` header file.

    void *realloc(void *block, size_t newsize);

The first argument sent to the `realloc` function is the starting address of a previously obtained memory block, and the second argument is the total length of the new block.

When a dynamic block is desired to be enlarged with the `realloc` function, the function is **not obliged** to enlarge the block towards a higher numerical address. If the `realloc` function cannot find a block of the desired length immediately after the end of the previously obtained block, or if it does not prefer to enlarge the dynamic area in this direction, it searches for another unused location in memory for the entire block. If a contiguous block of the desired total length is found, it allocates this block, moves the values in the old memory block to the new location, and returns the old memory block to the system. If a contiguous area of the requested length cannot be found, the function returns the **`NULL` address**.

Examine the dynamic memory operations performed in the following program:

    #include <stdio.h>
    #include <stdlib.h>
    int main()
    {
        int *pd;
        int k;
        int n, nplus;
        printf("how many integers : ");
        scanf("%d", &n);
        
        pd = (int *) malloc(sizeof(int) * n);
        if (!pd) {
            printf("insufficient memory!..\n");
            exit(EXIT_FAILURE);
        }
        
        for (k = 0; k < n; ++k)
            pd[k] = k;
            
        printf("how many integers to add: ");
        scanf("%d", &nplus);
        
        pd = (int *) realloc(pd, sizeof(int) * (n + nplus)); // Resize block
        if (pd == NULL) {
            printf("insufficient memory!..\n");
            exit(EXIT_FAILURE);
        }
        
        for (; k < n + nplus; ++k)
            pd[k] = k;
            
        for (k = 0; k < n + nplus; ++k)
            printf("%d ", pd[k]);
        printf("\n");
        
        free(pd);
        return 0;
    }

A dynamic area large enough to hold $n$ number of `int` type objects is obtained with the `malloc` function. If the `malloc` function fails, the program is terminated with the standard `exit` function. $n$ number of objects in the obtained dynamic area are assigned values with the help of a loop. Then, the obtained dynamic area is expanded with the called `realloc` function to be able to hold `nplus` more objects. If the `realloc` function fails, the program is terminated. The array with $n + \text{nplus}$ objects at the address that is the return value of the `realloc` function is then printed with a loop statement.

If the `realloc` function is successful, two possibilities exist:

1.  The `realloc` function provided the additional memory area immediately after the previously obtained dynamic area, i.e., at a higher numerical address, thus enlarging the initial block. This is rarely encountered in most systems. In this case, the address that is the return value of the `realloc` function is the address sent as the first parameter of the function.
2.  The `realloc` function could not find free space below the previously allocated block or did not prefer to perform an enlargement operation in this direction. And it allocated another free block of total size $\text{(n + nplus)} \times \text{sizeof}(\text{int})$ bytes in the heap area. In this case, the `realloc` function copied the values in the previously obtained area to this new area and returned the old block to the system.

Due to this behavior of the `realloc` function, the return value must definitely be assigned to a pointer variable. A common typical mistake is seen below:

    #include <stdio.h>
    #include <stdlib.h>
    int main()
    {
        char *p;
        p = malloc(10);
        if (p == NULL) {
            printf("can not allocate memory!..\n");
            exit(EXIT_FAILURE);
        }
        /***/
        // The return value of realloc is NOT assigned to p!
        if (realloc (p, 20) == NULL) { 
            printf("can not allocate memory!..\n");
            exit(EXIT_FAILURE);
        }
        gets(p); // If realloc moved the block, 'p' is now a dangling pointer
        return 0;
    }

The successful execution of the `realloc` function does not mean that an additional block was provided immediately below the previously obtained block, i.e., at a greater numerical address. The `realloc` function might have moved the previously obtained dynamic area to another location and returned with the starting address of the new block. In this case, the old block is freed, and this address is no longer reliable.

In the example above, it is assumed that the `realloc` function enlarged the previously obtained block in place. If the `realloc` function moved and enlarged the memory block to another location, a pointer error is made in the code above because the address pointed to by the pointer $p$ is no longer a reliable address.

Therefore, in applications, the return value of the `realloc` function is generally assigned to the pointer to which the value was sent in the `realloc` function:

    ptr = realloc(ptr, 100);

However, this is not mandatory. If the program is not to be terminated in case the allocation operation with the `realloc` function is unsuccessful and the values in the previously obtained region are to be written to a file, using a temporary pointer is appropriate because the pointer $ptr$ would be assigned the `NULL` address if the `realloc` function fails, thus severing the relationship of the pointer $ptr$ with the previously obtained block.

In such a case, using a temporary pointer is appropriate:

    temp = realloc(ptr, 100);
    if (temp == NULL)
        printf("cannot allocate memory!..\n"); // ptr still holds the old address

In this case, the pointer $ptr$ still points to the starting address of the previously obtained block.

The C standards have introduced the following rules regarding the `realloc` function:

i) In the case of enlarging a previously obtained memory block, the `realloc` function does not assign any value to the part added to the block. That is, the new block added to the old block contains **garbage values**. If the `realloc` function cannot enlarge the previously obtained memory block, it returns the **`NULL` address**, but the values in the previously obtained and unenlargeable memory block are preserved.

ii) If the first argument sent to the `realloc` function is the **`NULL` address**, the `realloc` function behaves entirely like the `malloc` function. That is:

    realloc(NULL, 100);

and

    malloc(100);

the calls have exactly the same meaning. Both attempt to obtain a dynamic area of 100 bytes.

Why is this necessary? That is, why might a call like `realloc(NULL, 100)` be preferred instead of a call like `malloc(100)`?

Examine the following program:

    #include <stdio.h>
    #include <ctype.h>
    #include <stdlib.h>
    // Assuming getch() and necessary functions are defined elsewhere
    
    // Function prototypes would be here
    
    int main()
    {
        int *ptr = NULL;
        int ch, grade;
        int counter = 0;
        
        for (;;) {
            printf("do you want to enter a grade? [y] [n]\n");
            // Assuming toupper(getch()) is available and returns 'Y' or 'N'
            while ((ch = toupper(getch())) != 'Y' && ch != 'N')
                ; 
            
            if (ch == 'N')
                break;
                
            printf("enter the grade : ");
            scanf("%d", &grade);
            
            counter++;
            // ptr is NULL on the first run, making realloc act like malloc
            ptr = (int *) realloc(ptr, sizeof(int) * counter); 
            
            if (ptr == NULL) {
                printf("cannot allocate memory!..\n");
                exit(EXIT_FAILURE);
            }
            
            ptr[counter - 1] = grade;
        }
        
        if (counter == 0) {
            printf("you did not enter any grades!..\n");
            return 0;
        }
        
        // Output results
        printf("you entered a total of %d grades\n", counter);
        printf("the grades you entered are listed below :\n");
        // display_array(ptr, counter); // Assuming display_array is defined
        
        // Calculations
        // printf("\nlargest grade : %d\n", get_max(ptr, counter));
        // printf("smallest grade : %d\n", get_min(ptr, counter));
        // printf("average of grades : %lf\n", get_ave(ptr, counter));
        // printf("standard deviation of grades . %lf\n", get_stddev(ptr, counter));
        
        free(ptr); // Free the memory block
        return 0;
    }

In the program above:

In the statement `ptr = (int *) realloc(ptr, sizeof(int) * counter);`, since the value of the pointer $ptr$ is `NULL` in the first iteration of the loop, the `realloc` function will behave like `malloc` and allocate space for 1 object of type `int`. However, since the address sent to the `realloc` function in subsequent iterations of the loop will not be the `NULL` address, the previously obtained block is continuously enlarged within the loop.

If the second argument sent to the `realloc` function is $0$, the `realloc` function behaves entirely like the `free` function:

    realloc(ptr, 0);

and

    free(ptr);

have exactly the same meaning. Why is this necessary? That is, why should a call like `realloc(ptr, 0)` be preferred instead of a call like `free(ptr)`?

### Functions Returning the Starting Address of Dynamically Obtained Area

Since a dynamically allocated block can be used safely until it is released with the `free` function and returned to the system, a function can return the starting address of such a block.

Examine the following function:

    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    
    char *getname()
    {
        char s[30]; // Local array
        char *ptr;
        printf("enter name : ");
        gets(s);
        
        // Allocate space for the string + null terminator
        ptr = (char *) malloc(strlen(s) + 1); 
        
        if (ptr == NULL) {
            printf("cannot allocate memory!..\n");
            exit(EXIT_FAILURE);
        }
        // Copy name from local array 's' to dynamic block 'ptr'
        return strcpy(ptr, s); 
    }

In the `getname` function, a name is first received from the keyboard into a local array. Then, the length of the name received into the local array is found using the `strlen` function. An area large enough to contain this name and the null terminator at the end is dynamically obtained with the `malloc` function. Then, the name is copied to the dynamically obtained area using the `strcpy` function, and the starting address of this block is returned.

The responsibility for freeing the block allocated as a result of a function call that performs a dynamic allocation operation lies with the calling code:

    int main()
    {
        char *p = getname();
        /*****/
        free(p);
        /*****/
        return 0;
    }

Allocating a dynamic memory block within a function and then returning the starting address of this block is a very common technique in the C language.

The `strcon` function, whose source code is given below, copies the string whose starting address is held in the second parameter to the end of the string whose starting address is held in the first parameter; however, it returns the address that is the starting address of the concatenated string **without modifying either of the strings** at the two addresses:

    #include <string.h>
    #include <stdlib.h>
    
    char *strcon(const char *s1, const char*s2)
    {
        // Allocate space for s1 + s2 + null terminator
        char *ptr = malloc (strlen(s1) + strlen(s2) + 1); 
        
        /* Check for success (omitted here for brevity, but needed) */
        // Assuming success:
        strcpy(ptr, s1);
        strcat(ptr, s2);
        return ptr;
    }

Our function copies the strings whose addresses were sent to a dynamic area and returns the starting address of the dynamic area. Since the `strcpy` and `strcat` functions return the value of their first parameter, the statements:

    strcpy(ptr, s1);
    strcat(ptr, s2);
    return ptr;

could have been written as a single statement, right?

    return strcat(strcpy(ptr, s1), s2);

### Controlling Multiple Dynamic Areas with a Pointer Array

Storing the starting addresses of different blocks obtained with dynamic memory functions in the elements of a pointer array is a frequently encountered theme. Examine the following program:

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    char *get_name()
    {
        char name_entry[40];
        char *pd;
        printf("enter name : ");
        gets(name_entry);
        
        pd = (char *) malloc(strlen(name_entry) + 1);
        if (pd == NULL) {
            printf("insufficient memory!..\n");
            exit(EXIT_FAILURE);
        }
        return strcpy(pd, name_entry); // Copy to dynamic block and return its address
    }
    
    int main()
    {
        char *p[10]; // Array of 10 char pointers
        int k;
        int len_sum = 0;
        
        for (k = 0; k < 10; ++k)
            p[k] = get_name(); // Each pointer stores the address of a dynamically allocated string
            
        printf("names : \n");
        for (k = 0; k < 10; ++k) {
            printf("(%s) ", p[k]);
            len_sum += strlen(p[k]);
        }
        printf("\n");
        printf("average length of entered names = %lf\n", (double)len_sum / 10);
        
        for (k = 0; k < 10; ++k)
            free(p[k]); // Free each dynamically allocated string
            
        return 0;
    }

In some cases, the pointer array itself is also created dynamically. In the following program, random values between $0 - 100$ are first given to the elements of a matrix whose number of rows and columns are entered from the keyboard, and then the matrix is printed to the screen:

    #include <stdio.h>
    #include <stdlib.h>
    #include <time.h>
    int main()
    {
        int no_of_rows, no_of_cols;
        int **prows; // Pointer to a pointer to int (prows will be an array of pointers)
        int i, k;
        srand(time(0));
        
        printf("number of rows : ");
        scanf("%d", &no_of_rows);
        printf("number of columns : ");
        scanf("%d", &no_of_cols);
        
        // 1. Allocate memory for the array of row pointers (nrows * sizeof(int*))
        prows = (int **)malloc(sizeof(int *) * no_of_rows);
        if (prows == NULL) {
            printf("cannot obtain dynamic memory!\n");
            exit(EXIT_FAILURE);
        }
        
        // 2. Allocate memory for each row (ncols * sizeof(int))
        for (k = 0; k < no_of_rows; ++k) {
            prows[k] = (int *) malloc(sizeof(int) * no_of_cols);
            if (prows[k] == NULL) {
                printf("cannot obtain dynamic memory!\n");
                exit(EXIT_FAILURE);
            }
        }
        
        /****/ // Initialization
        for (i = 0; i < no_of_rows; ++i)
            for (k = 0; k < no_of_cols; ++k)
                prows[i][k] = rand() % 100;
        
        /****/ // Display
        for (i = 0; i < no_of_rows; ++i) {
            for (k = 0; k < no_of_cols; ++k)
                printf("%2d ", prows[i][k]);
            printf("\n");
        }
        
        /****/ // Deallocation (must be in reverse order of allocation)
        for (i = 0; i < no_of_rows; ++i)
            free(prows[i]); // Free each row's array
        free(prows); // Free the array of pointers
        
        return 0;
    }

Now examine the program. The number of rows and columns of the matrix is entered by the user from the keyboard. The number of rows of the matrix is `no_of_rows`, and the number of columns is `no_of_cols`. The matrix consists of `no_of_rows` number of dynamic arrays of type `int` of length `no_of_cols`. That is, each row of the matrix is a dynamic array. The starting addresses of these dynamic arrays are held in a dynamic pointer array. You first see that a dynamic area is allocated for `no_of_rows` number of objects of type `int *`:

    prows = (int **)malloc(sizeof(int *) * no_of_rows);

The following loop ensures that each element of this dynamic array holds the starting address of a dynamic array of type `int` of length `no_of_cols`.

    for (k = 0; k < no_of_rows; ++k) {
        prows[k] = (int *) malloc(sizeof(int) * no_of_cols);

After the allocation operations are completed, the element at index $i$ and $k$ of the matrix can be accessed with the expression:

    prows[i][k]

because `prows[i]` is an object of type `int *`. The value of this object is the starting address of a dynamic array of type `int`. Recall that the square bracket operator is at the first level of the operator precedence table and has left-to-right associativity. In this case, the leftmost square bracket operator produces a value first. The value of type `int *` produced by the left square bracket operator then becomes the operand of the second square bracket operator. This operator then accesses an element of the dynamic array of type `int` that forms one of the rows. In this case, the `int` type object reached is the $[i][k]$ indexed element of the matrix.

Care must be taken in returning the allocated dynamic areas. The dynamic arrays that form the rows of the matrix must be returned to the heap area first, and then the return operation of the pointer array that holds the starting addresses of the dynamic arrays must be performed:

    for (i = 0; i < no_of_rows; ++i)
        free(prows[i]); // Free the dynamic row array
    free(prows); // Free the dynamic array of pointers