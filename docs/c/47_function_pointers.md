# ⚙️ Function Pointers

The image of an executable program on the disk is called a program. When a program is loaded into memory to be run, i.e., made executable, it is named a **process** or **task**. That is, a program refers to its state on the disk, while a process refers to a running program.

An executable program consists of three content sections:

1.  **Code (Kod)**: Contains the compiled machine code of the functions.
2.  **Data (Veri)**: Contains static duration entities (global variables, static local variables, string literals).
3.  **Stack (Yığın)**: Contains local variables and parameter variables created temporarily during execution.

For an executable file to be run by the operating system, it must first be loaded from the disk into RAM. The part of the operating system that takes the program from the disk, loads it into memory, and runs it is called the **loader**. Normally, for a program to be loaded into memory, the program's total size must be smaller than the available free space in memory. However, in systems like UNIX and Windows, programs can be run under small amounts of memory.

This feature is called **"virtual memory."** With the use of virtual memory, a small part of the program is loaded into RAM first. The operating system understands when the program's flow of execution shifts to a part that is not in RAM, in terms of code or data. It unloads the part of the program in RAM and loads the required part into RAM this time. That is, the program is executed in fragments. The DOS operating system does not use virtual memory. The memory size for running programs in the DOS system is at most 640 KB.

Just as objects have addresses, functions also have addresses. The **address of a function** is the starting address in memory of that function's machine code. Function starting addresses can be placed in special pointers called **function pointers**. A function pointer can be assigned the address of a function whose return value and parameters are of the specified types.

### Defining Function Pointer Variables

A function pointer is defined with a special syntax:

    int (*fp)(void);

The statement above defines a **function pointer variable** named $fp$. The pointer variable $fp$ can point to a function that has an `int` type return value and no parameter variables. In other words, the address of a function with an `int` type return value and no parameter variables can be assigned to the pointer variable $fp$.

You see that the `*` token and the pointer name following it are enclosed in parentheses in the definition. The type of the return value of the function that the function pointer will point to is written to the left of this parenthesis. The type of the parameter variables of the function that the function pointer will point to is written inside the parenthesis to the right of the parenthesis.

Another example:

    int (*fptr) (int, int);

The address of a function with an `int` type return value and parameters of type (`int, int`) can be assigned to the pointer variable named `fptr` defined above.

If the pointer variable name is **not** enclosed in parentheses in the definition, a function pointer is not defined. A function that returns an address type is declared:

    int *f(int, int);

The declaration above declares a function named $f$ that has a return value of type `(int *)` and parameters of type (`int, int`).

### Function Names

You know that an array name is automatically converted to the address of the first element of the array when it is subjected to an operation. Similarly, a **function name** is automatically converted to the address of the relevant function by the compiler when it is subjected to an operation. Function names can be viewed as the addresses of the functions programmatically.

A function name can also be the operand of the address-of operator. In this case, the address of the function is obtained again. That is, let `func` be a function name:

    func

and

    &func

can be considered equivalent expressions. Both expressions can be used as the address of the `func` function.

### The Function Call Operator (`()`)

The function call operator is a **unary postfix** operator. It is at the highest level of the operator precedence table. The operand of this operator is a function address. The operator redirects the program flow to that address, i.e., executes the code at that address. For example:

    func()

Here, the operand of the function call operator is the address `func`. The operator executes the code located at the address `func`, i.e., runs the `func` function. The value produced by the function call operator is the return value of the called function. For example:

    a = add(10, 20);

Here, the type of the expression `add` is a function address that has an `int` return value and parameters of type (`int, int`). That is, the expression `add` is converted to the **`int (*)(int, int)`** type. The expression formed by a function call like `add(10, 20)` is of type `int`.

### Calling Functions with Function Pointers

A function pointed to by a function pointer can be called in two separate forms. Let $pf$ be a function pointer variable. The function pointed to by this pointer can be called in the form:

    pf();

or in the form:

    (*pf)();

While the first form looks more natural, it is not very clear whether the name $pf$ is the name of a pointer variable or the name of a function.

In the second form, enclosing the expression `*pf` in parentheses is mandatory. This is because the precedence level of the function call operator is higher than the precedence level of the indirection operator.

Compile and run the following program:

    #include <stdio.h>
    void func()
    {
        printf("func()\n");
    }
    int main()
    {
        void (*pf)(void) = func; // Initialization with function address
        pf(); // Direct call (preferred form)
        (*pf)(); // Dereferenced call (explicit form)
        return 0;
    }

In the `main` function, the address of the function named `func` is assigned to the function pointer variable named `pf`. The function pointed to by $pf$, i.e., the `func` function, is then called in two separate forms.

### Function Pointers and Pointer Arithmetic

A function pointer **does not** adhere to the rules of pointer arithmetic. Function addresses cannot be added to integers like other addresses. Function pointers cannot be the operand of the `++` or `--` operator.

Indeed, pointer arithmetic would have no meaning for function addresses. How would it be possible to reach the address of the next function in memory by adding an integer to a function address?

Function addresses can be the operand of the indirection operator. Only a function call can be made with such expressions. These pointers can also be the operand of comparison operators. For example, whether two function pointers point to the same function can be compared with the `==` or `!=` operators.

### Using Function Pointers as Function Parameters

A function's parameter variable can be a function pointer. Examine the following example:

    #include <stdio.h>
    void func(void (*pf)(void)) // Parameter is a function pointer
    {
        pf(); // Calls the function pointed to by pf
    }
    
    void f1()
    {
        printf("f1()\n");
    }
    
    void f2()
    {
        printf("f2()\n");
    }
    
    int main()
    {
        func(f1); // Pass address of f1
        func(f2); // Pass address of f2
        return 0;
    }

In the program above, the parameter variable of the function named `func` is a function pointer. The pointer that is the parameter variable of the `func` function can point to a function that has no return value and no parameter variables. Since the function's parameter variables receive their values from the arguments in the function calls, an address of a function that has no return value and no parameter variables should be sent as an argument to the `func` function. Inside the `func` function, the function pointed to by the pointer named $fp$, which is the function's parameter, is called.

$f1$ and $f2$ are functions that have no return value and no parameter variables. You see that the `func` function is called first with the address of the function $f1$ and then with the address of the function $f2$ in the `main` function. In this case, with the call `func(f1);`, the `func` function is called first. Inside the `func` function, the function $f1$ is also called.

### Why Are Function Pointers Used?

Function pointers allow a specific part of a function to be modified externally. That is, the function can call a function whose address it receives from the outside to perform certain operations to achieve a goal. Thus, the code snippet calling the function can ensure that a specific part of the called function's task is performed as it desires.

This way, the amount of written source code can also be reduced. Instead of writing many functions whose source code is largely the same, it may be possible to write a single function that is called with a function pointer. Functions called with function pointers are **generalized functions**. By calling the functions whose addresses they receive from the outside, their functions are made more specific.

### Type-Independent Operations Functions

Some functions, especially functions that take pointer parameters, operate based on a specific type. For example, a function that sorts an array whose elements are of type `int` cannot sort an array whose elements are of type `double`. In these kinds of situations, the same code needs to be rewritten according to different types. It may be possible to write a single function that performs type-independent operations. The pointer parameters of functions that perform type-independent operations must be of type **`void *`**. However, the parameters being of type `void *` only provides convenience in terms of calling. The programmer who will write the function must still determine the type of the address passed to the function. For this, a type parameter can be passed to the function. For example, let the declaration of a function that sorts an array of any type be as follows:

    void *gsort(void *parray, size_t size, int type);

Now, the person who will write the function can determine the type of the array whose address is received from outside by placing the parameter named `type` inside the parenthesis of a `switch` statement. Although this method works for C's native types, it does not work correctly for arrays of types created by the programmer. Such general functions can only be written using **function pointers**.

Now let's try to write a function that returns the address of the largest element of an array in a type-independent manner. The general parametric structure of functions that perform type-independent operations on arrays is generally as follows:

1.  A pointer of type `void *` to receive the starting address of the array.
2.  A parameter of type `size_t` to receive the number of elements in the array.
3.  A parameter of type `size_t` to receive the byte length, i.e., the `sizeof` value, of one element of the array.
4.  A function pointer parameter to receive the starting address of a function that will be used to compare the elements of the array.

The parametric structure of the general function that finds the address of the largest element of an array can be as follows:

    void *get_max(const void *pArray, size_t size, size_t width, 
                  int (*cmp)(const void *, const void *));

The general approach in the design of these types of functions is as follows:

The function can find the address of each array element by utilizing pointer arithmetic. However, since the type of the array elements is unknown, the function cannot perform the comparison operation of the array elements. It has the code snippet calling the function perform this comparison by using a function pointer. The programmer calling the function writes the comparison function considering that the comparison function will be called with the addresses of any two elements of the array as arguments:

The comparison function receives the addresses of the two objects to be compared. If the object whose address is received in the first parameter is greater than the object whose address is received in the second parameter, the function returns any positive value; if it is smaller, it returns any negative value; and if the two values are equal, it returns the value zero. This is the convention provided by the standard `strcmp` function.

Examine the following program:

    #include <stdio.h>
    #include <string.h>
    #define MAX_NAME_LEN 20
    
    typedef struct tag_Person {
        char name[MAX_NAME_LEN];
        int no;
    } Person;
    
    typedef unsigned char Byte;
    
    void *get_max(const void *parray, size_t size, size_t width, 
                  int (*fp)(const void *, const void *))
    {
        // Cast to Byte* (char*) for pointer arithmetic
        Byte *pb = (Byte *)parray; 
        void *pmax = (void *)parray;
        size_t k;
        
        for (k = 1; k < size; k++) {
            // Compare current element (pb + k * width) with max element found so far (pmax)
            if (fp(pb + k * width, pmax) > 0)
                pmax = pb + k * width;
        }
        return pmax;
    }
    
    // Comparison function for int
    int cmp_int(const void *vp1, const void *vp2)
    {
        return *(const int *)vp1 - *(const int *)vp2;
    }
    
    // Comparison function for Person names
    int cmp_person_name(const void *vp1, const void *vp2)
    {
        return strcmp(((const Person *)vp1)->name, ((const Person *)vp2)->name);
    }
    
    // Comparison function for Person numbers
    int cmp_person_no(const void *vp1, const void *vp2)
    {
        return ((const Person *)vp1)->no - ((const Person *)vp2)->no;
    }
    
    int main()
    {
        int a[10] = {3, 8, 4, 7, 6, 9, 12, 1, 9, 10};
        Person per[10] = { {"Ali Serce", 123}, {"Kaan Aslan", 563}, {"Ahmet Adlori", 312},
                           {"Necati Ergin", 197}, {"Guray Sonmez", 297}, {"Erdem Eker", 144}, 
                           {"Nuri Yilmaz", 765}, {"Tayfun Tan", 117}, {"Demir Kerim", 222},
                           {"Can Mercan", 12}};
        
        Person *p_person;
        int *iptr;
        
        // Find max int in array 'a'
        iptr = (int *) get_max(a, 10, sizeof(int), cmp_int);
        printf("largest element of int array: %d\n", *iptr);
        
        // Find Person with max name in array 'per'
        p_person = (Person *) get_max(per, 10, sizeof(Person), cmp_person_name);
        printf("largest element of per array (by name): %s %d\n", p_person->name, p_person->no);
        
        // Find Person with max number in array 'per'
        p_person = (Person *) get_max(per, 10, sizeof(Person), cmp_person_no);
        printf("largest element of per array (by number): %s %d\n", p_person->name, p_person->no);
        
        return 0;
    }

In the program above, the `get_max` function receives the starting address of an array, its size, the length of one element of the array, and the address of the function to be used in the comparison operation of the array elements. The array address is received into a `void *` pointer. However, this address is transferred to a `char *` pointer inside the function to utilize pointer arithmetic. Since the size of one element is known, this value can be added to the starting address of the array to find the address of the next element of the array, right?

The comparison function receives the addresses of the two objects to perform the comparison operation. Thus, inside the `get_max` function, the comparison function can be called with the correct arguments using the function pointer parameter.

You then see that three separate comparison functions are defined. The parameter variables of all comparison functions are `(const void *, const void *)`. This way, a type incompatibility problem does not arise when the `get_max` function sends two addresses to these comparison functions.

In the `main` function, an `int` array and a `Person` array are defined. You see that these arrays are initialized. Then, the addresses of the largest elements of the arrays are found by calling the `get_max` function. The `cmp_person_name` function compares two `Person` objects by their names, while the `cmp_person_no` function compares two `Person` objects by their numbers.

### Type-Independent Sorting

Comparison and value swapping are involved in every sorting algorithm. Even if the type of an array is unknown, two elements of the array can be swapped. If the address of the function that will perform the comparison operation is received from the calling code snippet, type-independent sorting can be performed. Examine the following example:

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #define SIZE 10
    
    typedef unsigned char BYTE;
    
    // General swap function for any type/size
    void gswap(void *vp1, void *vp2, size_t nbytes)
    {
        // Cast to byte pointers for byte-by-byte swap
        unsigned char *p1 = (unsigned char *)vp1;
        unsigned char *p2 = (unsigned char *)vp2;
        unsigned char temp;
        while (nbytes--) {
            temp = *p1;
            *p1++ = *p2;
            *p2++ = temp;
        }
    }
    
    // General bubble sort function
    void bsort(void *vparray, size_t nelem, size_t width, 
               int (*compare)(const void *, const void *))
    {
        size_t i, j;
        // Cast to byte pointer to perform element jumping arithmetic
        BYTE *base = (BYTE *)vparray; 
        
        for (i = 0; i < nelem - 1; i++)
            for (j = 0; j < nelem - 1 - i; j++) {
                // Get address of current element: base + j * width
                // Get address of next element: base + (j + 1) * width
                if (compare(base + j * width, base + (j + 1) * width) > 0)
                    gswap(base + j * width, base + (j + 1) * width, width);
            }
    }
    
    // Comparison function for int
    int cmp_int(const void *vp1, const void *vp2)
    {
        return *(const int *)vp1 - *(const int *)vp2;
    }
    
    // Comparison function for double
    int cmp_double(const void *vp1, const void *vp2)
    {
        const double *dp1 = (const double *) vp1;
        const double *dp2 = (const double *) vp2;
        if (*dp1 < *dp2)
            return -1;
        return *dp1 > *dp2;
    }
    
    int main()
    {
        int k;
        double ad[SIZE] = {4.3, 7.4, 2.7, 8.88, 66.99, 4.8, 90.67, 23.87, 7.89, 10.87};
        int ai[SIZE] = {12, 4, 56, 45, 23, 60, 17, 56, 29, 1};
        
        bsort(ad, SIZE, sizeof(double), cmp_double); // Sort doubles
        bsort(ai, SIZE, sizeof(int), cmp_int);       // Sort ints
        
        for (k = 0; k < SIZE; ++k)
            printf("%.2lf ", ad[k]);
        printf("\n");
        
        for (k = 0; k < SIZE; ++k)
            printf("%d ", ai[k]);
        return 0;
    }

The function named `g_swap` swaps the contents of two memory blocks of a specific length whose starting addresses it receives. This function is called by the `bsort` function, which performs type-independent sorting. You see that the parametric structure of the `bsort` function is similar to the `get_max` function written earlier. The first parameter of the function is the starting address of the array to be sorted, the second parameter is the number of elements in the array, the third parameter is the length of one element of the array, and the fourth parameter is the address of the function that will perform the comparison operation of the array elements.

The bubble sort algorithm is used inside the `bsort` function. The greater-than/lesser-than relationship of two consecutive elements of the array is obtained by calling the function whose address is received from outside with the pointer parameter. If these two elements of the array are not in the correct place, they are swapped by calling the `gswap` function defined earlier.

An array of any type can be sorted with such a function. The `bsort` function only requires the address of an appropriate function that will perform the comparison operation. This is because the function cannot know the type of the elements of the array whose address is received from outside.

### Declaring Function Pointers

Leaving the parameter parenthesis empty when defining function pointers and writing `void` inside the parameter parenthesis have different meanings. If the parameter parenthesis is left empty, the address of a function that has an appropriate return value and any parameter structure can be placed in the function pointer variable defined in this way. However, writing `void` means that the addresses of functions with no parameters can be placed.

By leaving the parameter parenthesis empty, the parametric structure of the functions to be called can be arranged as desired externally.

> \[In the C++ language, leaving the parameter parenthesis empty conveys the information that the function pointer variable will point to a function that has no parameters. There is no difference in meaning between leaving the parenthesis empty and writing `void` inside the parenthesis in C++.]

### The Standard `qsort` Function

The standard **`qsort`** function has the same parametric structure as the `bsort` function defined above. The `bsort` function we wrote used the bubble sort algorithm. The standard `qsort` function uses the **"quick sort"** algorithm.

The declaration of the `qsort` function in the `stdlib.h` header file is as follows:

    void qsort(void *vp, size_t size, size_t width, int (*cmp)(const void *, const void *));

The first parameter of the function is the starting address of the array to be sorted, the second parameter is the number of elements in the array, the third parameter is the length of one element of the array, and the last parameter is the address of the comparison function. If the comparison function is written to return any positive value if the value of the element whose address is sent to its first parameter is greater than the element whose address is sent to its second parameter, any negative value if it is smaller, and zero if the two values are equal, sorting from smallest to largest occurs; if it is written in reverse, sorting from largest to smallest occurs.

In C compilers before the standards, the parenthesis of the pointer that would receive the address of the comparison function was left empty in the declaration of the `qsort` function. This makes writing the comparison function easier. If desired, to obtain such convenience in the `qsort` function, the parenthesis of the function pointer can be left empty in the declaration found in the `stdlib.h` header file:

    void qsort(void *parray, size_t size, size_t width, void(*fp)());

Attention must be paid to sorting an array of pointers with the `qsort` function. Examine the following program and try to understand why the sorting operation could not be performed:

    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #define SIZE 20
    
    int cmp(const void *vp1, const void *vp2)
    {
        const char *p1 = (const char *)vp1; // Incorrect cast: vp1 points to a char*
        const char *p2 = (const char *)vp2; // Incorrect cast: vp2 points to a char*
        return strcmp(p1, p2); // Compares addresses as if they were strings
    }
    
    int main()
    {
        char *names[SIZE] = {"Ali", "Veli", "Hasan", "Necati", "Burcu", "Kaan",
                             "Selami", "Salah", "Nejla", "Huseyin", "Derya", "Funda", 
                             "Kemal", "Burak", "Ozlem", "Deniz", "Nuri","Metin", 
                             "Guray", "Anil"};
        int k;
        
        qsort(names, SIZE, sizeof(char *), cmp); // names is an array of char*
        
        for (k = 0; k < SIZE; ++k)
            printf("%s ", names[k]);
        return 0;
    }

Could you see the error? The comparison function named `cmp` is written incorrectly. Since the addresses of two objects of type `char *` are sent to this function, the target type in the type conversion operation performed inside the function should have been **`char **`** (or `const char **`), not `const char *`. Address information of type `(char *)` is of type `(char **)` when its address is taken.

The function should have been written as follows:

    int cmp(const void *vp1, const void *vp2)
    {
        // vp1 and vp2 point to elements of the names array, i.e., to char* pointers.
        // Cast to const char * const * to dereference the pointer and get the string address.
        const char * const *p1 = (const char * const *)vp1; 
        const char * const *p2 = (const char * const *)vp2; 
        return strcmp(*p1, *p2); // Compare the strings pointed to by *p1 and *p2
    }

### Array of Function Pointers

Arrays whose elements are function pointers can also be defined:

    void (*fparray[10])(void);

The definition above defines `fparray` as a 10-element array where each element points to a function that has no return value and no parameter variables.

The expression `fparray[2]` accesses the third element of this array. The type of this expression is:

    void(*)(void)

The function pointed to by this pointer can be called in the form:

    fparray[2]();

or in the form:

    (*fparray[2])();

The elements of such an array can also be initialized:

    void (*fparray[5])(void) = {f1, f2, f3, f4, f5};

Thus, each element of the array can be made to point to a function.

Now, the functions pointed to by the elements of the pointer array can be called by accessing the elements of the array with the help of a loop statement. Compile and run the following code:

    #include <stdio.h>
    void f1() {printf("f1()\n");}
    void f2() {printf("f2()\n");}
    void f3() {printf("f3()\n");}
    void f4() {printf("f4()\n");}
    void f5() {printf("f5()\n");}
    int main()
    {
        void (*fparray[5])(void) = {f1, f2, f3, f4, f5};
        int k;
        for (k = 0; k < 5; ++k)
            fparray[k](); // Calls the function pointed to by fparray[k]
        return 0;
    }

### A Function Returning a Function Address

The return value of a function can also be a function address. Examine the following example:

    #include <stdio.h>
    void foo()
    {
        printf("foo()\n");
    }
    
    // Function that returns a pointer to a function (with no parameters and void return type)
    void (*func(void))(void) 
    {
        void (*fp)(void) = foo;
        return fp;
    }
    
    int main()
    {
        func()(); // Call func(), which returns a pointer, then call the function pointed to
        return 0;
    }

The function named `func` defined in the program above has no parameter variables. The return value of the `func` function is the address of a function (with no return value and no parameter variables). That is, the `func` function conveys the address of such a function to the code snippet that calls it. The local pointer variable $fp$ defined inside the `func` function points to the function named `foo`. In the statement:

    func()();

in the `main` function, the `func` function is called first. The return value obtained from this call is the address of the `foo` function. The second function call operator then calls the `foo` function.

### `typedef` Declarations for Functions

A `typedef` declaration can be made for a function type:

    typedef double FuncDouble(int);

After the declaration above, `FuncDouble` is a function type that has a `double` return value and a single parameter of type `int`.

    FuncDouble *fptr, *fpa[10];

The definition above defines $fptr$ as a pointer variable that points to a function with a `double` return value and a parameter of type `int`. $fpa$ is a 10-element array consisting of pointers like $fptr$. Each element of the $fpa$ array is a function pointer.

A variable whose elements are of type `FuncDouble` cannot be defined in C:

    FuncDouble func; /* Invalid */

However, there is no problem in the declaration of a function of this type:

    extern FuncDouble func;

With the statement above, a function is declared that has a `double` return value and an `int` parameter variable.

In applications, a `typedef` declaration is made more often for a function address type:

    typedef int (*CmpFunc)(const void *, const void *);

After the declaration above, `CmpFunc` is a function address type that has an `int` return value and two parameters of type `const void *`:

    CmpFunc fcmp1, fcmp2, fcmpa[10];

The definition above defines $fcmp1$ and $fcmp2$ as variables that will point to a function with an `int` return value and two parameters of type `const void *`. $fcmp1$ and $fcmp2$ are function pointer variables. $fcmpa$ is a 10-element array where each element is of the same type as the variable $fcmp1$.

The parameter type of a function or the return type of a function being a function address type makes the declarations quite confusing. For ease of reading and writing, new names are given to types related to function addresses with `typedef` declarations. Examine the following example:

    #include <stdio.h>
    #include <string.h>
    // FPTR is a type for a function pointer: char *(*)(const char *, int)
    typedef char *(*FPTR)(const char *, int); 
    
    // func is a function that returns an FPTR type (i.e., a function pointer)
    FPTR func(FPTR ptr)
    {
        return ptr;
    }
    
    int main()
    {
        char str[] = "Necati Ergin";
        // func(strchr) returns the address of strchr, then (*func(strchr))(str, 'E') is called
        // The parentheses around strchr are implicitly added by the compiler to turn the function name into an address.
        puts(func(strchr)(str, 'E')); 
        return 0;
    }

When the program above is run, the string "Ergin" is printed to the screen.