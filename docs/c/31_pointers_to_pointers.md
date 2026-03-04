# 🌟 Pointers to Pointers

Pointer variables are objects that hold address information within them. A declaration like:

    int *p;

creates an object named $p$ that will occupy 2 or 4 bytes in memory. This object is of type **`int *`**.

Since $p$ is an object, the address of the variable $p$ can also be referred to. The variable $p$ can be the operand of the address-of operator:

    &p

What is the type of the expression `&p`? This expression is of a type that can be the address of an object of type `int *`. This type is denoted in C as the **(int \*\*) type**. In that case, if the address of a variable like $p$ is to be stored in another object, the object that will hold $p$'s address must be of type `int **`. Examine the following code snippet:

    void func()
    {
        int x = 10;
        int *p = &x; // p is int*, holds address of x (int)
        int **ptr = &p; // ptr is int**, holds address of p (int*)
        /******/
    }

In the program above, the address of the variable $p$, which is of type `int *`, is assigned to the variable named `ptr`, which is of type `int **`. The meaning of this is: the value of the variable `ptr` is the address of the variable $p$. In other words, the pointer `ptr` points to the pointer $p$. In this case, the expression:

    *ptr

is the object pointed to by the object `ptr`. That is, the expression `*ptr` is the object $p$ itself. An assignment made to the expression `*ptr` actually changes the object $p$. Examine the following program:

    #include <stdio.h>
    int main()
    {
        int x = 10;
        int y = 20;
        int *p;
        int **pp;
        
        printf("x = %d\n", x); // Output: x = 10
        printf("y = %d\n", y); // Output: y = 20
        
        p = &x;
        *p = 100; // x = 100
        
        pp = &p;
        *pp = &y; // Changes p's value to &y. Now p points to y.
        *p = 200; // y = 200
        
        printf("x = %d\n", x); // Output: x = 100
        printf("y = %d\n", y); // Output: y = 200
        
        **pp = 2000; // Changes the object pointed to by *pp (which is p), which points to y
        
        printf("x = %d\n", x); // Output: x = 100
        printf("y = %d\n", y); // Output: y = 2000
        
        return 0;
    }

In the `main` function above, after the address of the `int` type variable $x$ is assigned to the pointer variable named $p$, the value 100 is assigned to the object pointed to by the pointer $p$, i.e., the variable $x$, with the statement:

    *p = 100;

Then, the address of the object $p$ is assigned to the pointer named $pp$ with the statement:

    pp = &p;

After this assignment, the pointer `pp` points to the pointer $p$.

With the statement:

    *pp = &y;

the address of the variable $y$ is assigned to the object pointed to by the pointer `pp`, i.e., the variable $p$. The assignment:

    *p = 200;

which will be executed after this assignment, now assigns the value 200 to the object pointed to by the pointer $p$, i.e., the variable $y$.

Now examine the following statement:

    **pp = 2000;

You know that the indirection operator is located at the second level of the operator precedence table and has **right-to-left** associativity.

In this case, the object pointed to by the pointer `pp`, i.e., the object $p$, is accessed first with the expression `*pp`. Then, with the expression `*(*pp)`, the object pointed to by the object pointed to by the pointer `pp` is accessed, i.e., the object pointed to by the object $p$, i.e., the variable $y$, is reached. With the execution of the statement, the value 2000 is assigned to the variable $y$.

The expression `**pp` corresponds to the object pointed to by the object pointed to by $pp$, i.e., the object $y$.

---

## 🔁 Functions That Change the Value of a Local Pointer Variable

A function that will change the value of a local object must be called with the address of the local object. A function that will change the value of a local pointer variable must also receive the **address** of the local pointer, not its value. Examine the following example:

    void swap_ptr(int **p1, int **p2) // Receives addresses of pointers
    {
        int *temp = *p1; // temp = value of *p1 (address of x)
        *p1 = *p2;      // *p1 = value of *p2 (address of y)
        *p2 = temp;     // *p2 = old value of *p1 (address of x)
    }

In the program above, a function named `swap_ptr` is defined to swap the values of two objects of type `int *`. You see that the function has two parameters of type `int **`. This function must undoubtedly be called with the addresses of the objects whose values it will swap:

    #include <stdio.h>
    int main()
    {
        int x = 10;
        int y = 20;
        int *p = &x; // p points to x
        int *q = &y; // q points to y
        
        printf("*p = %d\n", *p); // Output: *p = 10
        printf("*q = %d\n", *q); // Output: *q = 20
        
        swap_ptr(&p, &q); // Swaps the values of p and q themselves
        
        printf("*p = %d\n", *p); // Output: *p = 20 (p now points to y)
        printf("*q = %d\n", *q); // Output: *q = 10 (q now points to x)
        
        return 0;
    }

In the `main` function, variables named $x$ and $y$ of type `int` are defined. Then, the defined pointer variable $p$ points to the object $x$, and the pointer variable $q$ points to the variable $y$.

The function `swap_ptr` is then called with the addresses of the pointers $p$ and $q$ sent as arguments. After the function call, the pointer $p$ points to the variable $y$, and the pointer $q$ points to the variable $x$.

Now examine the following function:

    void ppswap(int **p1, int **p2)
    {
        int temp = **p1; // temp = value of x (10)
        **p1 = **p2;     // x = 20
        **p2 = temp;     // y = 10
    }

What objects' values does the `ppswap` function swap? It swaps the values of the objects that the pointers pointed to by $p1$ and $p2$ ultimately point to (i.e., $x$ and $y$, assuming $p1 = \&p$ and $p2 = \&q$).

---

## 🗄️ Functions Operating on an Array of Pointers

You know that a function operating on an array must receive the starting address of the array and the size of the array.

The declaration of a function operating on an array of type `int` can be as follows:

    void process_array(int *p, int size);

Such a function is called with the address of the first element of the array and the size of the array, right? When an array like:

    int a[10];

is in question, the array name $a$, when subjected to an operation, is automatically converted to the address of the first element of this array. That is, from the compiler's perspective, the expression $a$ is equivalent to the expression `&a[0]`. This function can be called in the form:

    process_array(a, 10);

Now, let an array whose elements are of type `char *` be defined:

    char *a[100];

Again, the expression $a$, when subjected to an operation, is converted to the address of the object that is the first element of this array, i.e., the starting address of the array. Since the object that is the first element of this array is of type `char *`, the address of this object is of type **`char **`**. A function that will operate on such an array must be declared as follows, since it will receive the starting address of this array and the size of the array:

    void process_array(char **parray, int size);

This function can be called in the form:

    process_array(a, 10);

Now examine the following program:

    #include <stdio.h>
    #include <string.h>
    
    void swap_ptr(char **p1, char **p2)
    {
        char *temp = *p1;
        *p1 = *p2;
        *p2 = temp;
    }
    
    void display_str_array(char **p, int size)
    {
        int k;
        for (k = 0; k < size; ++k)
            printf("%s ", p[k]);
        printf("\n");
    }
    
    void sort_str_array(char **p, int size)
    {
        int i, k;
        for (k = 0; k < size - 1; ++k)
            for (i = 0; i < size - 1 - k; ++i)
                if (strcmp(p[i], p[i + 1]) > 0) // Compare the strings pointed to
                    swap_ptr(p + i, p + i + 1); // Pass the addresses of the pointers
    }
    
    int main()
    {
        char *names[10] = {"Eda", "Abdurrahman", "Berk", "Zarife", "Yusuf",
                           "Levent", "Sezgi", "Sukufe", "Ufuk", "Cansu"};
        
        display_str_array(names, 10);
        sort_str_array(names, 10);
        
        getchar(); // Pause to see output before final display
        
        display_str_array(names, 10);
        return 0;
    }