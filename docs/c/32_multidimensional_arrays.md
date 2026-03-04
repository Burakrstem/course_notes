# 🔳 Multi-Dimensional Arrays

Arrays with two or more dimensions can be defined in the C language:

    int a[5][10][20]; // a is a 3-dimensional array.
    int m[5][10];     // m is a 2-dimensional array.

**2-dimensional arrays** are more commonly used in applications. 2-dimensional arrays are also referred to as **matrices**.

## Matrices

A two-dimensional array in C is actually treated as an array of single-dimensional arrays of a certain size:

    int a[5][10];

The array $a$ is a 5-element array where each element is a 10-element array of type `int`. That is, the true size of the array $a$ is 5. The expression 10 inside the second square bracket is the size of the arrays that are the elements of the array $a$.

This array, like all other arrays, exists as a contiguous block in memory. That is, the compiler allocates a block of size $50 \times \text{sizeof}(\text{int})$ bytes in memory for such an array.

Confusing the elements of a multi-dimensional array with the elements of the matrix that is the equivalent of this array in the problem domain is a frequent mistake.

A $5 \times 10$ matrix has 50 elements. However, the array $a$ above has only 5 elements.

How can each of the total 50 objects of type `int` in the array above be accessed? For this, the square bracket operator `[]` can be used twice with the array name:

Examine the following program. In this program, random values between $0-100$ are given to all elements in a matrix. Then, the value of all elements in the matrix is printed to the screen:

    #include <stdio.h>
    #include <stdlib.h>
    #include <time.h>
    #define ROW 5
    #define COL 10
    int main()
    {
        int a[ROW][COL];
        int i, k;
        srand(time(0));
        // Nested loop to initialize elements
        for (i = 0; i < ROW; ++i)
            for (k = 0; k < COL; ++k)
                a[i][k] = rand() % 100;
        /********/
        // Nested loop to display elements
        for (i = 0; i < ROW; ++i) {
            for (k = 0; k < COL; ++k)
                printf("%2d ", a[i][k]);
            printf("\n");
        }
        return 0;
    }

Examine the code above. The array $a$ is an array of `int` arrays with 10 elements. That is, $a[0]$ corresponds to the first of these arrays, and $a[4]$ corresponds to the last of these arrays.

Since $a[0]$ corresponds to the first of these arrays, the 5-indexed element of the 10-element array that is the first element of array $a$ can be accessed in the form:

    a[0][5] // right?

Recall that the square bracket operator is at the first precedence level and has left-to-right associativity.

When such a two-dimensional array is viewed as a matrix, which is its equivalent in the problem domain, the first element in this matrix is the object:

    a[0][0]

This object is the object located in the 1st row and 1st column of the matrix. The last element of the matrix is the object:

    a[4][9]

This object is the object located in the 5th row and 10th column of the matrix. If the address of the first object in the matrix is assigned to an `int` pointer and this pointer is continuously incremented, the addresses of all elements in the matrix can be obtained, reaching the address of the last element. Now let's add an extension to the example above:

    int main()
    {
        int a[ROW][COL];
        int i, k;
        int *ptr; // Pointer to int
        srand(time(0));
        
        for (i = 0; i < ROW; ++i)
            for (k = 0; k < COL; ++k)
                a[i][k] = rand() % 100;
        /********/
        for (i = 0; i < ROW; ++i) {
            for (k = 0; k < COL; ++k)
                printf("%2d ", a[i][k]);
            printf("\n");
        }
        
        printf("***********************************************\n");
        
        ptr = &a[0][0]; // ptr points to the first element's address
        i = ROW * COL; // Total number of elements
        while (i--)
            printf("%2d ", *ptr++); // Dereference and increment pointer
        printf("\n");
        
        return 0;
    }

You see that an addition has been made to the previously written `main` function. With the statement:

    ptr = &a[0][0];

the address of the first `int` type object in the matrix is assigned to the object `ptr` of type `int *`. The value of the expression $\text{ROW} \times \text{COL}$, i.e., the total number of elements in the matrix, is assigned to the variable $i$.

In this case, the `while (i--)` loop iterates as many times as the number of elements in the matrix, right? With the `printf` call located in the loop body, the value of the object `*ptr` is printed in each iteration of the loop, and then the value of the pointer is incremented by 1 with the postfix `++` operator, ensuring the pointer points to the next `int` type object in memory. Thus, all values in the matrix are printed to the screen.

It should be understood from this: **The elements of a two-dimensional array are actually one-dimensional arrays placed sequentially in memory.**

### Passing Two-Dimensional Arrays to Functions

In fact, passing a two-dimensional array to a function is not different from passing a one-dimensional array to a function. To pass an array to a function, the address of the first element of the array and the size of the array are sent to the function, right?

So, what is the first element of an array like $a$ in the example above? The first element of this array is $a[0]$. And this is an `int` array with 10 elements. Now let's consider taking the address of this element:

    &a[0]

What is the type of this expression? Beginners in the C language might think the type of such an expression should be the **(int \*\*) type**. However, the type of this expression is a type we have not encountered before:

**The address of a 10-element array of type `int`!**

This type information is expressed in the C language as follows:

    int (*)[10];

That is, the first element of array $a$ can be assigned to a pointer of this type:

    int (*ptr)[10] = &a[0];

The name of an array is automatically converted to the address of the first element of the array when it is subjected to an operation in an expression, right? In that case, the expression $a$ can also be written directly instead of the expression `&a[0]`:

    int (*ptr)[10] = a; // Correct, 'a' is implicitly converted to int (*)[10]

Yes, the type of the expression $a$ is not `int **`, but the **`int (*)[10]` type**.

This situation can also be expressed as follows: $ptr$ is a pointer that points to a 10-element array of type `int`. $ptr$ can point only to a 10-element array of type `int`, not an `int` array of any size. If the pointer `ptr` is incremented by 1 (e.g., `++` operator), it now points to the next 10-element array of type `int` located in memory. That is:

    ptr + 1

The numerical component of the address is $\text{sizeof}(\text{int}) \times 10$ larger than the numerical component of the address $ptr$.

The expression `ptr + 1` corresponds to the address of the 10-element array of type `int` that is the second element of the two-dimensional array $a$. In this case:

    *(ptr + 1)

the expression is actually the array $a[1]$.

Undoubtedly, the expression `ptr[1]` can also be used instead of the expression `*(ptr + 1)`. In this case, all elements of the two-dimensional array can be accessed with a loop using this pointer:

    for (k = 0; k < ROW; ++k)
        ptr[k]

With a loop statement like this, in each iteration of the loop, a row of the matrix is reached, i.e., the arrays of length $\text{COL}$ that are an element of the two-dimensional array.

In this case, the parameter variable of a function that will operate on a 2-dimensional array, i.e., a matrix, can be such a pointer. The other parameter of the function can receive the size of the array. Examine the following program:

    #include <stdio.h>
    #include <stdlib.h>
    #include <time.h>
    #define ROW 5
    #define COL 10
    
    void fill_matrix(int (*ptr)[COL], int size)
    {
        int i, k;
        for (i = 0; i < size; ++i)
            for (k = 0; k < COL; ++k)
                ptr[i][k] = rand() % 100;
    }
    
    void display_matrix(int (*ptr)[COL], int size)
    {
        int i, k;
        for (i = 0; i < size; ++i) {
            for (k = 0; k < COL; ++k)
                printf("%2d ", ptr[i][k]);
            printf("\n");
        }
    }
    
    int main()
    {
        int a[ROW][COL];
        srand(time(0));
        fill_matrix(a, ROW);
        display_matrix(a, ROW);
        return 0;
    }

When a pointer like `int (*ptr)[10]` is used as a function parameter, it can also be written in the form **`int ptr[][10]`**. That is, the following two declarations are equivalent:

    void fill_matrix(int (*ptr)[10], int size);
    void fill_matrix(int ptr[][10], int size);

The first square bracket can even be written with an integer if desired. However, this integer has no importance from the compiler's perspective. Some programmers write the size of the array into the first square bracket only for readability. The declaration above could also have been made as follows:

    void fill_matrix(int ptr[5][10], int size);

Another way to pass matrices to a function is to pass the address of the first element of the matrix, and the number of rows and columns of the matrix to the function. We are now changing the functions we wrote above:

    #include <stdio.h>
    #include <stdlib.h>
    #include <time.h>
    #define ROW 5
    #define COL 10
    
    void fill_matrix(int *ptr, int rowsize, int colsize)
    {
        int i, k;
        for (i = 0; i < rowsize; ++i)
            for (k = 0; k < colsize; ++k)
                // Accessing element at row i, column k using pointer arithmetic
                ptr[i * colsize + k] = rand() % 100; 
    }
    
    void display_matrix(int *ptr, int rowsize, int colsize)
    {
        int i, k;
        for (i = 0; i < rowsize; ++i) {
            for (k = 0; k < colsize; ++k)
                // Accessing element at row i, column k using pointer arithmetic
                printf("%2d ", ptr[i * colsize + k]); 
            printf("\n");
        }
    }
    
    int main()
    {
        int a[ROW][COL];
        srand(time(0));
        // Pass address of the first element of the matrix
        fill_matrix(&a[0][0], ROW, COL); 
        display_matrix(&a[0][0], ROW, COL);
        return 0;
    }

This time, the functions receive the address of the first element of the matrix, and the number of rows and columns of the matrix. They access all elements in the matrix using pointer arithmetic, based on the information that these elements are placed contiguously in memory.

Of course, the array name can also be passed as an argument to these functions. In this case, the type cast operator must be used:

    fill_matrix((int *)a, ROW, COL);
    display_matrix((int *)a, ROW, COL);

### Address of the First Element of Arrays That Are Matrix Elements

You know that array names are automatically converted to the address of the first element of the arrays by the compiler. Similarly, when a one-dimensional array that is an element of a two-dimensional array is accessed with the square bracket operator, this expression is automatically converted to the address of the first element of this one-dimensional array. Examine the following example:

    #include <stdio.h>
    #include <stdlib.h>
    #include <time.h>
    #define ROW 5
    #define COL 10
    
    void fill_array(int *ptr, int size)
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
        int a[ROW][COL];
        int i;
        srand(time(0));
        
        // Loop over the rows (which are 1D arrays)
        for (i = 0; i < ROW; ++i)
            fill_array(a[i], COL); // a[i] is converted to the address of a[i][0]
        
        /********/
        for (i = 0; i < ROW; ++i)
            display_array(a[i], COL);
        
        return 0;
    }

Let's examine the `for` loop statement in the `main` function:

    for (i = 0; i < ROW; ++i)
        fill_array(a[i], COL);

The expression $a[i]$ corresponds to the $\text{COL}$-sized one-dimensional arrays that are elements of the array $a$ in each iteration of the loop, right? When this expression is subjected to an operation, it is automatically converted by the compiler to the address of the first element of this array.

The expression $a[0]$ is automatically converted to the expression $\&a[0][0]$. The expression $\text{COL}$ is also sent as the second argument to the `fill_array` function. This is because the expression $\text{COL}$ indicates the size of the array whose address is $a[i]$.

You know that the expressions specifying the array size during the definition of an array must be **constant expressions**. The same condition applies to multi-dimensional arrays. If the dimensions of a matrix are determined at runtime rather than compile time, dynamic memory management must be used. Examples on this topic are covered in the section "Dynamic Memory Management."

### Initializing Two-Dimensional Arrays

Two-dimensional arrays can also be initialized. The initial values given are assigned sequentially to the elements of the one-dimensional arrays that are elements of the two-dimensional array.

    #include <stdio.h>
    int main()
    {
        int a[3][5] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
        int i, k;
        for (i = 0; i < 3; ++i) {
            for (k = 0; k < 5; ++k)
                printf("%2d ", a[i][k]);
            printf("\n");
        }
        return 0;
    }

If desired, initial values can be given to a specific number of elements of the arrays that are elements by using inner blocks within the block containing the initial values. The value 0 is automatically assigned to the uninitialized elements. Compile and run the following example as well:

    #include <stdio.h>
    int main()
    {
        int a[3][5] = { {1, 2}, {3, 4, 5}, {6, 7, 8, 9}};
        int i, k;
        for (i = 0; i < 3; ++i) {
            for (k = 0; k < 5; ++k)
                printf("%2d ", a[i][k]);
            printf("\n");
        }
        return 0;
    }

### Two-Dimensional Arrays of Type `char`

Just as a string can be held within a `char` array, $n$ strings in a logical relationship can be held within a two-dimensional array:

    char words[10][50];

The array named `words` defined above has 10 elements. Each element of the array named `words` is a 50-element array of type `char`. 10 strings, whose length does not exceed 49 characters, can be held within the array `words`.

* `words[3]` : The address of the fourth of these strings.
* `words[6][2]` : The third character of the seventh of these strings.

Examine the following program:

    #include <stdio.h>
    #include <string.h>
    #define ARRAY_SIZE 10
    
    char *name_array[ARRAY_SIZE] = {"Ali", "Veli", "Hasan", "Necati", "Deniz",
                                   "Kaan", "Selami","Salah", "Nejla", "Figen"};
    int main()
    {
        char names[ARRAY_SIZE][20];
        int k;
        
        // Copy strings from name_array (array of pointers) to names (2D char array)
        for (k = 0; k < ARRAY_SIZE; ++k)
            strcpy(names[k], name_array[k]); 
        
        for (k = 0; k < ARRAY_SIZE; ++k)
            printf("(%s) ", names[k]);
        printf("\n");
        
        // Reverse each string in the 2D array
        for (k = 0; k < ARRAY_SIZE; ++k)
            strrev(names[k]); // Assuming strrev is available
            
        for (k = 0; k < ARRAY_SIZE; ++k)
            printf("(%s) ", names[k]);
        printf("\n");
        return 0;
    }

A two-dimensional array named `names` is defined in the `main` function:

    char names[ARRAY_SIZE][20];

This array can hold $\text{ARRAY\_SIZE}$ number of names whose length is at most 19 characters, right?

The strings pointed to by the elements of the pointer array named `name_array` are copied to the `char` arrays that are elements of the two-dimensional array `names` using the standard `strcpy` function with the loop statement:

    for (k = 0; k < ARRAY_SIZE; ++k)
        strcpy(names[k], name_array[k]);

Each name is printed to the screen with the following loop statement:

    for (k = 0; k < ARRAY_SIZE; ++k)
        printf("(%s) ", names[k]);

All names held in the two-dimensional array are reversed with calls to the non-standard `strrev` function using the following loop statement:

    for (k = 0; k < ARRAY_SIZE; ++k)
        strrev(names[k]);

### Initializing Two-Dimensional Arrays of Type `char`

Since a `char` array can be initialized with characters enclosed in double quotes, the elements of the one-dimensional `char` array that are the elements of a two-dimensional array can be similarly initialized:

    char names[5][10] = {"Ali", "Veli", "Hasan", "Tuncay", "Deniz"};

In the example above, the 10-element `char` arrays that are the elements of the two-dimensional array named `names` are initialized with strings enclosed in double quotes.

Now let's define some functions that operate on a two-dimensional `char` array:

    #include <stdio.h>
    #include <string.h>
    #define ARRAY_SIZE 20
    
    // Function to swap two strings (by swapping their content)
    void swap_str(char *p1, char *p2)
    {
        char temp[20]; // Buffer for swapping (size must be sufficient)
        strcpy(temp, p1);
        strcpy(p1, p2);
        strcpy(p2, temp);
    }
    
    void sort_names(char ptr[][20], int size)
    {
        int i, k;
        for (i = 0; i < size - 1; ++i)
            for (k = 0; k < size - 1 - i; ++k)
                if (strcmp(ptr[k], ptr[k + 1]) > 0)
                    swap_str(ptr[k], ptr[k + 1]); // Pass addresses of the strings
    }
    
    void display_names(const char ptr[][20], int size)
    {
        int i;
        for (i = 0; i < size; ++i)
            printf("(%s) ", ptr[i]); // ptr[i] is converted to the address of the string
        printf("\n");
    }
    
    int main()
    {
        char names[ARRAY_SIZE][20] = {"Ali", "Veli", "Hasan", "Necati",
                                      "Deniz", "Kaan", "Selami","Salah", "Nejla", 
                                      "Huseyin", "Derya", "Funda", "Kemal", "Burak", 
                                      "Burcu", "Ozlem", "Nuri", "Metin", "Guray", "Anil"};
        
        display_names(names, ARRAY_SIZE);
        sort_names(names, ARRAY_SIZE);
        printf("***********************************\n");
        display_names(names, ARRAY_SIZE);
        return 0;
    }

Of the functions defined above, the `swap_str` function swaps the two strings whose addresses it receives. The `display_names` function prints the names in the two-dimensional array, whose starting address and size it receives, to the screen. The `sort_names` function sorts the names held in the two-dimensional array, whose starting address and size it receives, from smallest to largest.

### Differences Between `char *` Array and Two-Dimensional `char` Array

$n$ strings in a logical relationship can be held either with a pointer array or within a two-dimensional array:

    char *pnames[10] = {"Ali", "Veli", "Hasan", "Deniz", "Ferda", "Murat",
                        "Ayca", "Erdem", "Kaan", "Gurbuz"};
    char names[10][20] = {"Ali", "Veli", "Hasan", "Deniz", "Ferda", "Murat",
                         "Ayca", "Erdem", "Kaan", "Gurbuz"};

The elements of a pointer array whose elements point to strings hold the starting addresses of strings that can only be used for reading. You must recall that string literals are strings that can only be used for reading.

In the example above, modifying the strings pointed to by the pointers that are the elements of the `pnames` array is incorrect. However, the names contained within the `names` array can be changed if desired. Examine the following `main` function:

    #include <string.h>
    // Assuming strrev is available
    int main()
    {
        // pnames points to static string literals (read-only)
        // names stores strings in its own modifiable memory
        
        for (k = 0; k < 10; ++k) {
            strrev(pnames[k]); // Incorrect! (Modifies read-only memory)
            strrev(names[k]);  // Not incorrect (Modifies modifiable array content)
        }
        return 0;
    }