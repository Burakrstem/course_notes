# Pointer Operators

Some C language operators are used in relation to address information. Code related to pointers uses these operators. The pointer operators are:

| Operator | Name | English Name |
| :--- | :--- | :--- |
| `*` | içerik işleci | indirection operator (dereferencing operator) |
| `&` | adres işleci | address-of operator |
| `[]` | köşeli ayraç işleci | index operator (subscript operator) |
| `->` | ok işleci | arrow operator |

The arrow operator is used with addresses of structure types, so this operator will be examined in detail in the section "Structures."

---

## The Address-of Operator (`&`)

The **address-of operator (`&`)** is a **unary prefix** operator. It is located at the second precedence level of the operator precedence table. The value produced by this operator is the **address of the object** that is its operand. The operand of the address-of operator **must be an object**. This is because the address information of only objects—Lvalues—can be accessed. It is invalid for the operand of the address-of operator to be a non-object expression.

Consider the expression written after a definition like:

    int k;
    &k

The value produced by this expression is address information of type `int *`. The type of this expression is the **(int \*) type**.

The `&` operator, like other unary operators, is at the 2nd precedence level of the operator precedence table. You know that the associativity of this precedence level is **"right-to-left."**

Since a pointer variable is an object that holds address information, address information produced by the address-of operator can be assigned to a pointer variable.

    int x = 20;
    int *ptr;
    ptr = &x;

After such an assignment, the following can be said:

* The value of the `ptr` object is the address of the variable $x$. The `ptr` object holds the address of the variable $x$.

The address obtained with the address-of operator must be assigned to a pointer variable of the **same type**. For example, in the following program, an address of a different type is assigned to a pointer variable:

    char ch = 'x';
    int *p;
    p = &ch; /* Incorrect - Type mismatch */

Of course, the address information produced by this operator is also **not an Lvalue**. For example:

    int x;
    ++&x; /* Invalid */

An operation like this results in an error. The operand of the increment operator must be an object. In the expression above, the expression `&x`, which is the operand of the `++` operator, is not an object. It is only an address value.

### Printing Address Values to the Screen

You know that the values of expressions of native data types can be printed to the screen with the standard `printf` function. Recall that predetermined format specifiers (conversion specifiers) are used in the string passed as the first argument to the `printf` function to print the value of an expression. Can address information also be printed to the screen using the appropriate format specifier? Yes! The **`%p`** format specifier is used for this purpose in the standard `printf` function. If the argument matched with the `%p` format specifier is address information, the `printf` function prints only the **numerical component** of the relevant address information to the screen in **hexadecimal** format.

Compile and run the following program:

    #include <stdio.h>
    int main()
    {
        int *ptr;
        int x = 20;
        ptr = &x;
        printf("address of object x = %p\n", &x);
        printf("value of variable ptr = %p\n", ptr);
        printf("address of object ptr = %p\n", &ptr);
        return 0;
    }

Since `ptr` is an object, the `ptr` object can also be the operand of the address-of operator, right? The address that is the value of the `ptr` object is the address of the object $x$. But the address of the `ptr` object itself can also be referred to. The address that is the value of a pointer variable and the address of the pointer variable itself are different things.

The address of the `ptr` variable itself is printed to the screen with the call:

    printf("address of object ptr = %p\n", &ptr);

### Conversion of Array Names to Address Information

In the C language, when array names are subjected to an operation, they are automatically converted by the compiler into address information.

After an array definition like:

    char s[5];

the array name $s$ is converted into the **address of the first element** of this array when it is subjected to an operation.

Array names are converted by the compiler into address information that indicates the starting location of the blocks allocated in memory for the arrays. In the example above, assume the array is placed in memory as follows:

| s[0] | s[1] | s[2] | s[3] | s[4] |
| :--- | :--- | :--- | :--- | :--- |
| 1C00 | 1C01 | 1C02 | 1C03 | 1C04 |

In this case, the array name $s$ is equivalent to the `char` type address `1C00`. That is, if this address had been written as an address literal:

    (char *)0x1C00

it would be written in this form.

In this case, the expression $s$ and the expression `&s[0]` are the same address information, right?

Since a pointer variable must be assigned address information of its own type, all the following assignments are valid and correct:

    int a[100];
    long l[20];
    char s[100];
    double d[10];
    
    int *p;
    long *lp;
    char *cp;
    double *dp;
    
    p = a;
    lp = l;
    cp = s;
    dp = d;

Only the name of an array of the **same type** can be assigned to a pointer. For example:

    int *p;
    char s[] = "Necati";
    p = s; /* INCORRECT - Type mismatch */

### Array Names Do Not Denote Objects (Lvalues)

After a definition like:

    int a[100];
    int *ptr;

if an expression like $a$ is used, this expression is automatically converted to the `int *` type by the compiler. That is, the type of this expression is also the **(int \*) type**.

While the expression `ptr` is an expression denoting an object (an Lvalue), the expression $a$ is an expression that **does not denote an object**. It cannot be used as a **modifiable Lvalue**. For example:

    a++ /* Invalid */

The expression is invalid.

In the C language, the location of no variable or array during the program's runtime can be determined by the programmer. The programmer defines the variable, and the compiler can place it anywhere.

Array names cannot be used as Lvalues like pointers. For example, let $s$ be an array name:

    ++s; /* Invalid */

The statement is invalid.

---

## The Indirection Operator (`*`)

The **indirection operator (dereferencing operator, `*`)** is also a **unary prefix** operator. The operand of the indirection operator must be **address information**. When an address expression is the operand of the `*` operator, the resulting expression represents the **object located at that address in memory**. Therefore, an expression created with the `*` operator corresponds to an object and can be used as an **Lvalue**.

In a declaration like:

    int a;

the type of the object $a$ is the `int` type. This is because `int` type data is held inside the object $a$.

In the declaration:

    int *p;

the type of $p$ is an address of type `int`. That is, the type of the object $p$ is the **(int \*) type**. Data of type `(int *)` is held inside the object $p$.

From a declaration like:

    char *ptr;

two things can be understood:

1.  `ptr` is a pointer of type `char *`. It is defined to hold address information of type `char *`.
2.  The object obtained when the pointer `ptr` is used with the `*` operator is of type `char`. That is, `*ptr` is a `char` type object.

For example:

    int *p;
    p = (int *) 0x1FC2;
    *p = 100;

Here, the type of `*p` is the `int` type. Therefore, an operation like `*p = 100` affects not only the byte `0x1FC2` (under DOS) but **both** the bytes `0x1FC2` and `0x1FC3` (assuming a 2-byte `int`) by assigning the value 100 in integer format. The numerical component of the address inside the pointer contains the address of the object's low-order byte. In this case, the address of any region in memory can be assigned to a pointer variable. Then, that memory region can be accessed with the `*` operator.

The operand of the `*` operator must be address information. That is, the operand can be an address literal, an array name, a pointer variable, or an address expression obtained with the address-of operator.

The indirection operator can be used not only with pointer objects but also with all forms of address information (address literals, array names, etc.). This operator is used to access the object at the address that is its operand. The value obtained with the operator is the value of the object located at the address that is its operand.

An expression produced with the indirection operator denotes an object (Lvalue). The type of the object is the same as the type of the address that is the operand.

Compile and run the following program, and try to interpret the screen output:

    #include <stdio.h>
    int main()
    {
        char s[] = "Balıkesir";
        int a[] = {1, 2, 3, 4, 5};
        int x = 10;
        int *ptr;
        
        putchar(*s);
        printf("%d\n", *a);
        *&x = 20;
        printf("x = %d\n", x);
        ptr = &x;
        *ptr = 30;
        printf("x = %d\n", x);
        return 0;
    }

In the program above:

i) Since $s$ is the name of a `char` array, it is converted to a `char *` address. This address is the starting address of the $s$ array. Since the expression `*s` is the object at this address, the expression `*s` is the object that is the first element of our array, so the value of the expression `*s` is 'B', right?

ii) Since $a$ is the name of an `int` array, it is converted to an `int *` address. This address is the starting address of the $a$ array. Since the expression `*a` is the object at this address, the expression `*a` is the object that is the first element of our `int` array, so the expression `*a` is the object $a[0]$. The value of this object is 1.

iii) In the expression `*&x`, two operators are used: the address-of and indirection operators. Both of these operators are located at the second precedence level in the operator precedence table. Since the associativity for the second level of the operator precedence table is **right-to-left**, the address-of operator is evaluated first. The value produced by the address-of operator is the address of the object $x$, and this address becomes the operand of the indirection operator. Since the indirection operator accesses the object at that address, the expression `*&x` is the object at the address of the object $x$, i.e., the object $x$ itself.

iv) The address of the object $x$ is assigned to the pointer `ptr`. Since the operand of the indirection operator is the object `ptr`, the object at the address that is the value of the object `ptr` is accessed. In this case, the object `*ptr` is also the object $x$ itself, right?

You know that the indirection operator is at the second level of the precedence table. Let $s$ be an array name:

    *s + 1;

In the expression above, the indirection operator is evaluated first. The value produced by the indirection operator becomes the operand of the addition operator. However, if the expression were:

    *(s + 1)

the `+` operator would be evaluated first.

Compilers determine whether the `*` token in an expression containing the `*` token is the multiplication operator or the indirection operator by looking at its usage in the expression. The multiplication operator is binary, while the indirection operator is a unary prefix operator.

In the expression:

    *s * 2

the first `*` is the indirection operator, while the second `*` is the arithmetic multiplication operator.

---

## A Pointer Pointing to an Object

    int x = 20;
    int *ptr ;
    ptr = &x;
    *ptr = 30;

In the code snippet above, the address of the `int` type object $x$ is assigned to the pointer `ptr`. After this assignment, the value of the pointer `ptr` is the address of the object $x$. In this case, it is said that **"ptr points to the variable x."**

If `ptr` points to $x$, then `*ptr` is the object $x$ itself. More generally, if $p$ is a pointer variable, `*p` is the object the pointer points to!

Just as you can directly access a defined variable by its name, you can indirectly access it by making the pointer that points to it the operand of the indirection operator, right? The English name of the operator, **"indirection operator,"** also emphasizes this situation.

---

## Functions Whose Parameter Variable is a Pointer (Call by Reference)

Pointers are mostly used as parameter variables of a function. Since a pointer is an object, a function's parameter variable can be a pointer of any type:

    void func(int *p)
    {
        /***/
    }

Since a function's parameter variables are initialized with the argument expressions passed to them through function calls, if a function's parameter variable is a pointer, the function must be called with address information of the same type.

Such a function can change the value of a local variable whose address is copied to the parameter variable:

    #include <stdio.h>
    void func(int *ptr)
    {
        *ptr = 20; // Dereferences the address in ptr and assigns 20 to that location
    }
    int main()
    {
        int a = 10;
        func(&a); // Passes the address of 'a'
        printf("%d\n", a); // Output: 20
        return 0;
    }

In the example above, the address of the local variable $a$ defined in the `main` function is sent to the `func` function. When the `func` function is called, the created parameter variable `ptr` receives its initial value from the expression `&a`. When the function's code is entered, the pointer variable `ptr`, which is the parameter variable, now points to the object $a$ whose address was sent. In this case, the expression `*ptr` is the object $a$ itself.

The value 20 is assigned to the object $a$ with the statement:

    *ptr = 20; /* right? */

If a function wants to obtain a value and convey this value to the calling function, two methods can be used:

i. The obtained value is produced as the return value by the called function.
ii. The obtained value is placed at the address sent by the calling function. Of course, for this, the parameter variable of the called function must be a pointer.

Below is a function written that calculates the factorial of a number passed to it and copies this value to the address sent as a parameter:

    #include <stdio.h>
    void factorial(int n, long *p);
    int main()
    {
        long a;
        int k;
        for (k = 0; k < 14; ++k) {
            factorial(k, &a); // Pass address of 'a'
            printf ("%2d! = %ld\n", k, a);
        }
        return 0;
    }
    void factorial(int n, long *p)
    {
        *p = 1;
        if (n == 0 || n == 1)
            return;
        while (n > 1)
            *p *= n--; // Assigns value to the object pointed to by 'p'
    }

Let $a$ be a local variable. If a function in the C language is called in the form:

    func(a);

the called function has **no chance** of changing the variable $a$. This type of function call is called **"call by value."** As you will recall from the "Functions" section, in this case, the value of the variable $a$ is copied and passed to the parameter variable of the `func` function. That is, the parameter variable of the `func` function is not the object $x$ itself. Even if the code of the `func` function is not seen, it can be said that the value of the local variable $a$ does not change after the function call.

For the function to be able to change the variable $a$, it must be called in the form:

    func(&a);

For example, this is why the address of an object is sent as an argument to the standard `scanf` function using the `&` operator. The function call made in this manner is called **"call by reference"** in C. In such a call, the address of an object is sent to the function. The parameter variable of the function is also a pointer that will hold this address.

Suppose the values of two local integer objects are to be swapped. This task can be done within the current function as follows:

    int main()
    {
        int a = 10, b = 20, temp;
        temp = a;
        a = b;
        b = temp;
        /*....*/
        return 0;
    }

If the swap operation is desired to be done by a function, would a function like the following work?

    void swap(int x, int y)
    {
        int temp = x;
        x = y;
        y = temp;
    }
    int main()
    {
        int a = 10, b = 20;
        swap(a, b);
        printf("a = %d\nb = %d\n", a, b);
        return 0;
    }

When the program above is run, it prints:

    a = 10
    b = 20

The written `swap` function does not change the values of the variables $a$ and $b$. The values of the local variables $a$ and $b$ could only be changed by sending the **addresses** of these variables to a function. However, the `swap` function above copies the values of the variables $a$ and $b$ to the parameter variables $x$ and $y$. That is, it is the parameter variables $x$ and $y$ whose values are changed.

The function that will perform the swap operation must have **pointer parameter variables** because it will receive address values from the code snippet that calls it:

    void swap(int *p1, int *p2)
    {
        int temp = *p1;
        *p1 = *p2;
        *p2 = temp;
    }

---

## Operations with Addresses - Incrementing and Decrementing Addresses (Pointer Arithmetic)

In the C language, address information can be added to an integer, and an integer can be subtracted from address information. Such an expression is of the type of the address that is added or subtracted. For example, if the address of an `int` type object is added to the integer 1, address information of an `int` type object is obtained again.

When 1 is added to address information, the numerical component of the address increases by the **size of the type of the object the address belongs to**. In this case, for example, in the DOS operating system, when the value of a `char *` pointer is incremented by 1, the numerical component of the address increases by 1; when an `int *` pointer is incremented by 1, the numerical component of the address increases by 2; and when a `double *` pointer is incremented by 1, the numerical component of the address increases by 8.

Suppose a pointer variable points to an object in memory. If the value of this pointer variable is incremented by 1, the pointer variable now points to the **next object** after the object it was pointing to.

    #include <stdio.h>
    int main()
    {
        int k;
        int a[10];
        for (k = 0; k < 10; ++k) {
            *(a + k) = k; // *(a + k) is equivalent to a[k]
            printf("%d ", a[k]);
        }
        return 0;
    }

In the example above, the elements of the array $a$ defined in the `main` function are accessed using pointer arithmetic. `*(a + k)` means the object at a distance of $k$ from the address $a$. This is the $k$-indexed element of the array, right? If the array had been of type `double` instead of `int`, the elements of the array could still be accessed this way, right?

**Pointer arithmetic provides a type-independent abstraction.**

Adding two pieces of address information is invalid. However, two pieces of address information on the same array can be subtracted from each other. If two addresses are subtracted from each other, the result is an integer type. When two addresses are subtracted from each other, their numerical components are subtracted first, and then the resulting value is divided by the size of the type the address belongs to. For example, let $a$ be an `int` array. The value obtained from the expression `&a[2] - &a[0]` is 2.

The following program queries pointer arithmetic. Compile and run the program, and try to interpret the screen output:

    #include <stdio.h>
    int main()
    {
        char s[10];
        int a[10];
        double d[10];
        
        printf("%p\n", (char *)0x1AC0 + 1); // Address increases by 1 (size of char)
        printf("%p\n", (int *)0x1AC0 + 1); // Address increases by sizeof(int)
        printf("%p\n", (double *)0x1AC0 + 1); // Address increases by sizeof(double)
        
        printf("%d\n", &s[9] - &s[0]); // Result: 9 (distance in units of char)
        printf("%d\n", &a[9] - &a[0]); // Result: 9 (distance in units of int)
        printf("%d\n", &d[9] - &d[0]); // Result: 9 (distance in units of double)
        return 0;
    }

### Comparing Address Values

Two addresses on the same block can be compared with comparison operators:

    #include <stdio.h>
    int main()
    {
        int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int *ptr = a;
        while (ptr < a + 10) { // a + 10 is the address one past the last element
            printf("%d ", *ptr);
            ++ptr;
        }
        return 0;
    }

---

## The Square Bracket Operator (`[]`)

The square bracket operator, which we previously used to access array elements, is actually a binary pointer operator. The **square bracket operator (index / subscript operator, `[]`)** is at the **highest** precedence level of the operator precedence table. The first operand of the operator is placed before the square brackets. This operand is address information. The second operand is an integral type expression written inside the square brackets.

The expression:

    p[n]

and the expression:

    *(p + n)

are completely equivalent expressions.

That is, the square bracket operator is used to access the object $n$ steps forward from an address. The type of the object obtained with the `[]` operator is the same as the type of the address that is the operand.

Try to estimate what the following program will print to the screen first. Then compile and run the program:

    #include <stdio.h>
    int main()
    {
        int a[5] = {1, 2, 3, 4, 5};
        int *ptr = a + 2; // ptr points to a[2], which is 3
        printf("%d\n", ptr[-1]); // Equivalent to *(ptr + (-1)) -> a[1] = 2
        printf("%d\n", ptr[0]); // Equivalent to *(ptr + 0) -> a[2] = 3
        printf("%d\n", ptr[1]); // Equivalent to *(ptr + 1) -> a[3] = 4
        return 0;
    }
    /* Output: 2, 3, 4 */

The first operand of the `[]` operator does not have to be an array name. As mentioned before, when the name of an array is used in an expression, it is converted by the compiler to the address of the first element of that array, i.e., the starting address of the array.

The `[]` operator is at the highest level of the operator precedence table. For example:

    &p[n]

In the expression above, the square bracket operator is evaluated first. The value produced by the operator relates to an object (Lvalue). Since the precedence level of the address-of operator is lower than the square bracket operator, the object reached by the operator becomes the operand of the address-of operator.

The numerical value of the expression inside `[]` can undoubtedly be negative. For example:

    p[-2]

is a valid expression. Similarly, this expression has the same meaning as the expression:

    *(p - 2)

In the example below, the square bracket operator and the address-of operator are used in the same expression.

    #include <stdio.h>
    int main()
    {
        char ch = 'A';
        (&ch)[0] = 'B'; // Equivalent to *(&ch + 0) = 'B', which is *&ch = 'B'
        putchar(ch);
        return 0;
    }

---

## Using `++` and `--` Operators with Pointer Operators

In many C code patterns, pointer operators are used together with the increment or decrement operator.

### 1. Indirection operator (`*`) and `++` operator in the same expression

a) The situation `++*p`:

    #include <stdio.h>
    int main()
    {
        int a[5] = {1, 2, 3, 4, 5};
        int k;
        int *ptr = a; // ptr points to a[0]
        ++*ptr; // Increment the object pointed to by ptr (a[0] becomes 2)
        for (k = 0; k < 5; ++k)
            printf("%d ", a[k]);
        /* Output: 2 2 3 4 5 */
        return 0;
    }

Two operators are used in the expression `++*ptr`: the indirection operator and the increment operator. Both operators are located at the second precedence level of the operator precedence table. Since the associativity for the second level is **right-to-left**, the indirection operator on the right is evaluated first. The indirection operator accesses the object pointed to by the pointer `ptr`, and this object thus becomes the operand of the increment operator. In this case, the value of the object pointed to by the pointer `ptr` is incremented by 1. In short, the statement `++*ptr;` means **"increment the value of the object pointed to by ptr by 1."**

b) The situation `*++p`:

The object at the address that is $p$'s value plus 1 is accessed. That is, the value of the expression is the value of the object immediately following the object pointed to by the pointer $p$. Of course, after the evaluation of the expression, the value of the pointer $p$ is incremented by 1 due to the side effect of the `++` operator. That is, `ptr` points to the next object. Carefully examine the following example:

    #include <stdio.h>
    int main()
    {
        int a[5] = {1, 2, 3, 4, 5};
        int k;
        int *ptr = a;
        *++ptr = 10; // ptr becomes a+1, then 10 is assigned to a[1]
        *ptr = 20; // 20 is assigned to a[1] (ptr still points to a+1)
        for (k = 0; k < 5; ++k)
            printf("%d ", a[k]);
        /* Output: 1 20 3 4 5 */
        return 0;
    }

The statement `x = *++p;` assigns the value at the incremented address to the variable $x$.

c) The situation `*p++`:

The `++` operator and the `*` operator are both at the second precedence level. The associativity for this precedence level is **right-to-left**. The `++` operator is evaluated first, and it produces the unincremented value of the pointer $p$ for the rest of the expression. The object at this address is accessed, and then the value of the pointer $p$ is incremented by 1. The value of the expression `*p++` is the value of the object pointed to by the pointer $p$. Due to the side effect of the `++` operator, the value of the pointer $p$ is incremented by 1 after the evaluation of the expression. That is, $p$ points to the next object. Examine the following example:

    #include <stdio.h>
    int main()
    {
        int a[5] = {1, 2, 3, 4, 5};
        int k;
        int *ptr = a;
        *ptr++ = 10; // 10 is assigned to a[0] (value of *ptr), then ptr becomes a+1
        *ptr = 20; // 20 is assigned to a[1] (ptr points to a[1])
        for (k = 0; k < 5; ++k)
            printf("%d ", a[k]);
        /* Output: 10 20 3 4 5 */
        return 0;
    }

### 2. Address-of operator (`&`) and `++` operator in the same expression

    &x++ /* Invalid */

The value produced by the expression $x++$ becomes the operand of the address-of operator. The value produced by the expression $x++$ is not an Lvalue. The operand of the address-of operator must be an Lvalue. This causes a compile-time error.

    &++x /* Invalid in C */

The value produced by the expression $++x$ becomes the operand of the address-of operator. The value produced by the expression $++x$ is not an Lvalue in C, and the operand of the address-of operator must be an Lvalue. The expression is invalid in C.

> \[Since the prefix `++` operator produces an Lvalue in the C++ language, this expression is valid in C++.]

    ++&x /* Invalid */

The value produced by the address-of operator becomes the operand of the prefix increment operator. The operand of the `++` operator must be an expression denoting an object (Lvalue). The expression `&x` is not an expression denoting an object. The expression is invalid.

Any combination of the address-of operator (`&`) and the increment (`++`) or decrement (`--`) operators results in a compile-time error.

### 3. Square bracket operator (`[]`) and `++` operator in the same expression

a) The situation `++p[i]`:

The square bracket operator is at the first precedence level, and the `++` operator is at the second precedence level. In this case, the square bracket operator is evaluated first by the compiler. The expression $p[i]$ denotes an object. Therefore, there is no problem with it being the operand of the `++` operator. The expression in question means:

    p[i] = p[i] + 1;

That is, the value of the object $p[i]$ is incremented by 1.

b) The situation `p[i]++`:

    x = p[i]++;

The unincremented value of the object $p[i]$ is produced first, and the unincremented value of the object $p[i]$ is used in the rest of the expression. That is, in the example above, the unincremented value of the object $p[i]$ is assigned to the variable $x$, and then the object $p[i]$ is incremented by 1.

c) The situation `p[++i]`:

    x = p[++i];

First, the value of the expression $++i$ is obtained. The value of this expression is $i$'s value plus 1. Then, the object at a distance of $(i + 1)$ from the address $p$ is accessed. As a side effect of the `++` operator, the value of the variable $i$ is incremented by 1.

d) The situation `p[i++]`:

    x = p[i++];

First, the value of the expression $i++$ is obtained. The value of this expression is $i$'s own value. Then, the object at a distance of $i$ from the address $p$ is accessed. As a side effect of the `++` operator, the value of the variable $i$ is incremented by 1.

---

## Initializing Pointer Variables

As with variables of other types, pointer variables can be initialized during their definition. The initialization of pointers must be done with address information of the pointer's type.

Examples:

    char s[100];
    double x;
    
    int *ptr = (int *) 0x1A00;
    char * str = (char *) 0x1FC0;
    char *p = s; // Assigns the address of array s to p
    double *dbptr = &x; // Assigns the address of variable x to dbptr
    int i, *ptr = &i; // Initializes i and assigns the address of i to ptr

In the last statement, the variable named $i$ is of type `int`, and the variable named `ptr` is of type `int *`. The address of the variable $i$, defined in the same statement, is assigned to the variable `ptr`.

---

## Passing Arrays to Functions via Pointers

If the starting address and size of an array are sent to a function, the function can operate on the array. The parameter of the function that will receive the starting address of the array must be a pointer variable of the same type. The other parameter of the function can be an `int` type variable to hold the size of the array.

A function that receives the starting address of an array as a parameter can access the array elements using the square bracket operator or the indirection operator. However, the function cannot know how many array elements there are. Therefore, the array length is sent to the function as a second argument. Example:

    #include <stdio.h>
    void display_array (const int *p, int size) // p is a pointer, size is the length
    {
        int i;
        for (i = 0; i < size; ++i)
            printf("%d ", p[i]); // Accessing elements using array notation
    }
    int main()
    {
        int a[5] = {3, 8, 7, 6, 10};
        display_array(a, 5); // Array name 'a' decays to a pointer (address of a[0])
        return 0;
    }

The `display_array` function defined above takes the starting address and size of an `int` array and prints the values of all elements of the array to the screen. The `const` keyword in the declaration of the parameter pointer $p$ will be discussed later.

Below, the same function performs its task using the indirection operator this time:

    void display_array (const int *p, int size)
    {
        while (size--) // Loop size times
            printf("%d ", *p++); // Dereference and then increment the pointer
    }

### Defining Pointer Parameter Variables

When a function's parameter variable is a pointer, this pointer can be defined in two different ways:

    void func(int *ptr);
    void func(int ptr[]); // Looks like an array, but is treated as a pointer

From the compiler's perspective, there is no difference between the two forms. However, some programmers prefer the second form if the function expects the starting address of an array from outside:

    void sort_array(int ptr[], int size);

This form is only relevant for pointers that are function parameters. Global or local pointers cannot be defined in this form:

    void foo(void)
    {
        int ptr[]; /* Invalid for local definition */
    }

Below, functions that perform some useful operations on `int` arrays are designed. Carefully examine the definitions of the functions. You will see that the `const` keyword is used in the declaration of the pointers that are the parameters of some of the functions. Ignore the `const` keyword for now. This keyword will be discussed in detail later.

### Examples of Functions Operating on Arrays

Below, a function is defined to place random values into the elements of an array:

    void set_random_array(int *ptr, int size, int max_val)
    {
        int k;
        for (k = 0; k < size; ++k)
            ptr[k] = rand() % (max_val + 1);
    }

This function fills the elements of the array, whose starting address and size it receives, with random values in the range $0$ to `max_val`.

    int sum_array(const int *ptr, int size)
    {
        int sum = 0;
        int k;
        for (k = 0; k < size; ++k)
            sum += ptr[k];
        return sum;
    }

The `sum_array` function returns the sum of the array's elements. The value of all array elements is added to the local object named `sum`. The function returns the value of the `sum` object.

    int max_array(const int *ptr, int size)
    {
        int max = *ptr;
        int k;
        for (k = 1; k < size; ++k)
            if (ptr[k] > max)
                max = ptr[k];
        return max;
    }

    int min_array(const int *ptr, int size)
    {
        int min = *ptr;
        int k;
        for (k = 1; k < size; ++k)
            if (ptr[k] < min)
                min = ptr[k];
        return min;
    }

The `max_array` function returns the value of the largest element of the array whose address and size it receives. The `min_array` function similarly returns the value of the smallest element.

    void sort_array(int *ptr, int size)
    {
        int i, k, temp;
        for (i = 0; i < size - 1; ++i)
            for (k = 0; k < size - 1 - i; ++k)
                if (ptr[k] > ptr[k + 1]) {
                    temp = ptr[k];
                    ptr[k] = ptr[k + 1];
                    ptr[k + 1] = temp;
                }
    }

The `sort_array` function sorts the array, whose address and size it receives, from smallest to largest using the "bubble sort" algorithm.

Below you see a `main` function that tests the written functions. Compile and run the program together with the definitions of all functions (assuming `ARRAY_SIZE` is defined and `set_random_array`, `display_array`, `sum_array`, `max_array`, `min_array`, `sort_array` are implemented).

    #include <stdio.h>
    #include <stdlib.h>
    #include <time.h>
    #define SIZE 100
    #define ARRAY_SIZE SIZE // Use consistent name
    // Function prototypes would be here
    
    int main()
    {
        int a[ARRAY_SIZE];
        srand(time(0));
        // Assuming set_random_array, display_array, etc. are defined elsewhere
        set_random_array(a, SIZE, 1000); 
        printf("array filled with random numbers in the range 0 - 1000!\n");
        printf("array is being printed!\n");
        display_array(a, SIZE);
        printf("sum of the array = %d\n", sum_array(a, ARRAY_SIZE));
        printf("largest element of the array = %d\n", max_array(a, SIZE));
        printf("smallest element of the array = %d\n", min_array(a, SIZE));
        sort_array(a, SIZE);
        printf("array is being printed after sorting!\n");
        display_array(a, SIZE);
        return 0;
    }

### Functions Passing Their Received Address Information to Other Functions

Functions can call other functions and send the information passed to their own parameter variables as arguments to the functions they call. This situation is undoubtedly also valid for functions whose parameters are pointers.

Let's define a function named `mean_array` to calculate the arithmetic mean of an `int` array. To find the arithmetic mean of the array, one must first find its sum, right?

    double mean_array(const int *ptr, int size)
    {
        return (double)sum_array(ptr, size) / size;
    }

The `mean_array` function passes the array address and array size it received to the `sum_array` function as arguments to calculate the sum of the array.

In the `sort_array` function, if two consecutive elements of the array are not in the correct order, these elements are swapped. Let's first write a function that swaps the values of two integer objects. Let's call this function inside the `sort_array` function:

    void swap(int *p1, int *p2)
    {
        int temp = *p1;
        *p1 = *p2;
        *p2 = temp;
    }
    
    void sort_array(int *ptr, int size)
    {
        int i, k;
        for (i = 0; i < size - 1; ++i)
            for (k = 0; k < size - 1 - i; ++k)
                if (ptr[k] > ptr[k + 1])
                    swap(ptr + k, ptr + k + 1); // Pass addresses to swap function
    }

In the `sort_array` function, pay attention to the statement:

    if (ptr[k] > ptr[k + 1])
        swap(ptr + k, ptr + k + 1);

With this statement, if the $k$-indexed element of the array whose address was received from outside is greater than the $(k + 1)$-indexed element, the values of the objects that are the $k$ and $(k + 1)$-indexed elements of the array are swapped by calling the `swap` function. The address of both objects is passed as arguments to the `swap` function. The `swap` function could also have been called as follows, right?

    swap(&ptr[k], &ptr[k + 1]);

Below, a function named `reverse_array` that reverses an array is defined:

    void reverse_array(int *ptr, int size)
    {
        int *pend = ptr + size - 1; // Address of the last element
        int n = size / 2;
        while (n--)
            swap(ptr++, pend--); // Swaps elements pointed to, then increments ptr and decrements pend
    }

The address of the last element of the array is assigned to the pointer variable `pend`. The `while` loop iterates half the number of elements in the array. In each iteration of the loop, the $n$-th element from the beginning of the array is swapped with the $n$-th element from the end. The pointer variables `ptr` and `pend` are the operands of the postfix `++` and `--` operators. Due to the side effect of the operators, `ptr` points to the next object, while `pend` points to the previous object in each iteration of the loop.

---

## Functions Whose Return Value is of Address Type

Just as a function's parameter variable can be of an address type, a function's return value can also be of an address type. In the definition of such a function, an address type is written where the function's return type is written.

For example, a function named `func` that returns the address of an `int` type object can be defined as follows:

    int *func(void)
    {
        /***/
    }

You see that `int *` is written in place of the return type of the `func` function. If the `*` token were removed from the function definition above, it would be understood that the function returns an `int` type value.

What does a function that returns an address mean? The function conveys the address of an `int` type object to the location where it is called. The function call expression is equivalent to the function's return value, which is address information. If the function's return value is desired to be stored in an object, it must be assigned to a pointer variable of the same type:

    int *ptr;
    ptr = func();

Similarly:

You know that functions create their return values with the help of a temporary object. The return type of a function is the type of the temporary object that will hold the return value. In this case, the temporary object that will hold the return value of a function that returns an address type is also a pointer.

Functions that return address information are frequently encountered in C programs. Some standard C functions also return a value of an address type.

Examine the following code snippet:

    #include <stdio.h>
    int g = 10; // Global variable
    
    int *foo() // Returns the address of an int
    {
        return &g; // Returns the address of global variable g
    }
    
    int main()
    {
        int *ptr;
        printf("g = %d\n", g); // Output: 10
        ptr = foo();
        *ptr = 20; // Changes the value of g through the pointer
        printf("g = %d\n", g); // Output: 20
        return 0;
    }

When the `foo` function is called, it returns the address of the global variable $g$. The function produces its return value with the statement:

    return &g;

The expression `&g` is of the **(int \*) type**. The value of this expression is assigned to the temporary object, which is also of the **(int \*) type**. The address returned by the `foo` function called in the `main` function is assigned to the pointer variable `ptr`.

The `getmax` function, which finds the largest element of an array and returns the value of this element, was written previously. Below, the same function is written this time to return the address of the largest array element:

    #include <stdio.h>
    #include <stdlib.h>
    #include <time.h>
    #define SIZE 20
    
    int *getmax(const int *p, int size) // Returns int *
    {
        int *pmax, i;
        // The address of the first element is assigned to pmax
        // Type cast needed since p is 'const int *'
        pmax = (int *)p; 
        for (i = 1; i < size; ++i)
            if (p[i] > *pmax)
                // Assign the address of the currently largest element to pmax
                pmax = (int *)(p + i); 
        return pmax;
    }
    
    int main()
    {
        int a[SIZE];
        int k;
        srand(time(0));
        for (k = 0; k < SIZE; ++k) {
            a[k] = rand() % 1000;
            printf("%d ", a[k]);
        }
        printf("\n");
        // Dereference the returned address to get the value
        printf("max = %d\n", *getmax(a, SIZE)); 
        return 0;
    }

Examine the function's code. The local pointer variable `pmax` is defined to hold the address of the array's largest element. Since the first element of the array is initially accepted as the largest, the address of the first element of the array is assigned to the pointer `pmax` first:

    pmax = (int *)p

You see that the starting address of the array received from outside is assigned to the pointer named `pmax` with the assignment. Then, a `for` loop is created to check whether the other elements of the array are larger than the object pointed to by the pointer `pmax`. When an array element larger than the object pointed to by `pmax` is found, the address of this element is assigned to the pointer `pmax`.

In the assignment `pmax = (int *)(p + i)`, you know that the expression `p + i` is equivalent to the expression `&p[i]`.

Upon loop exit, the pointer variable `pmax` holds the address of the largest element of the array, right?

In the `main` function, an array of length $\text{SIZE}$ is first filled with random values. Then, the values of the array elements are printed to the screen.

The value of the object at the address returned by the `getmax` function is printed to the screen with the function call below.

    printf("max = %d\n", *getmax(a, SIZE));

This is the value of the largest element of the array, right?

A function returning address information can have other benefits too. Instead of conveying the value to be calculated to the outside, the address of the object that will hold this calculated value can be conveyed to the outside. After all, if we have the address of an object, we can also access the value of that object, right?

Let the word `Type` specify a type. The declaration of a function that returns a value of type `Type` is as follows:

    Type foo(void);

To store the return value of such a function, the function call expression must be assigned to an object of type `Type`:

    Type val = foo();

Let an object of type `Type` occupy 100 bytes in memory. In this case, when the `return` statement is reached during the execution of the called `foo` function, a 100-byte temporary object is created. The assignment made from the `return` expression to this temporary object causes a 100-byte block to be copied. The transfer of the temporary object to the variable named `val` also causes a 100-byte memory block to be copied.

Now let's look at the following declaration:

    Type *foo(void);

This time, the function returns the address of a `Type` type object that holds the calculated value. In this case, the temporary object that will hold the return value of the function that returns an address type will only be 2 bytes or 4 bytes, right? That is, instead of copying a 100-byte block, only a 2- or 4-byte copy is involved.

To store the return value of such a function, the function call expression must be assigned to an object of type `Type *`:

    Type *ptr;
    ptr = foo();

The address of the `Type` type object that holds the value calculated by the `foo` function is assigned to a pointer variable of type `Type *`. Regardless of the `sizeof` value of the `Type` type, this operation causes only a block the size of the `sizeof` of a pointer to be copied, right?

A function conveying the address of the object that holds the value to the outside instead of the value itself reduces the cost in terms of memory and time usage.

Let's also mention another benefit. If the value of an object is received from a function, the object carrying this value cannot be changed. However, if the address of an object is received from a function, the object whose address is received can be changed.

The `getmax` function written above returned the address of the largest element of the array, right? Examine the following `main` function:

    #include <stdio.h>
    #include <stdlib.h>
    #include <time.h>
    #define SIZE 100
    // Function prototypes would be here
    
    int *getmax(const int *p, int size);
    void set_random_array(int *ptr, int size, int max_val);
    void display_array(const int *ptr, int size);
    
    int main()
    {
        int a[SIZE];
        srand(time(0));
        set_random_array(a, SIZE, 1000);
        display_array(a, SIZE);
        
        *getmax(a, SIZE) = -1; // Changes the largest element to -1
        display_array(a, SIZE);
        
        *getmax(a, SIZE) = -1; // Changes the new largest element (which was the second largest before the first call) to -1
        display_array(a, SIZE);
        return 0;
    }

Let's look at the statement below:

    *getmax(a, SIZE) = -1;

You see that the address returned by the function is the operand of the indirection operator. The object at the address returned by the function is reached with this expression, and the value $-1$ is assigned to this object. That is, the value of the largest element of the array is made $-1$. This task could not have been done with a function that returns the value of the largest element of the array.

Now carefully examine the following program and try to understand what is done in the written `select_sort` function:

    #include <stdio.h>
    #include <stdlib.h>
    #include <time.h>
    #define SIZE 100
    // Function prototypes would be here
    
    int *getmax(const int *p, int size); // Assumed to return max element's address
    void swap(int *p1, int *p2);
    void display_array (const int *p, int size);
    void set_random_array(int *ptr, int size, int max_val);
    
    void select_sort(int *ptr, int size)
    {
        int k;
        for (k = 0; k < size - 1; ++k)
            // Swaps the max element in the unsorted part (ptr+k to ptr+size-1) with the current element (ptr+k)
            swap (getmax(ptr + k, size - k), ptr + k); 
    }
    
    int main()
    {
        int a[SIZE];
        srand(time(0));
        set_random_array(a, SIZE, 1000);
        printf("before sorting\n");
        display_array(a, SIZE);
        select_sort(a, SIZE);
        printf("after sorting\n");
        display_array(a, SIZE);
        return 0;
    }

### Returning with Addresses of Local Objects

A function that returns an address should **never** return with the address of a local object with automatic storage duration. Returning with the addresses of local objects with automatic storage duration is a typical programming error.

Suppose it is desired to write a function that returns the starting address of a name entered from the keyboard:

    char *getname()
    {
        char name_entry[40]; // Local array with automatic storage duration
        printf("enter a name: ");
        gets(name_entry);
        return name_entry; /* Incorrect! */
    }
    
    #include <stdio.h>
    int main()
    {
        char *ptr = get_name();
        printf("received name = %s\n", ptr);
        return 0;
    }

A local array is defined inside the `get_name` function. The name entered by the user is placed into the local array, and then the address of the local array is returned.

You know that local variables have automatic storage duration, meaning they are deallocated from memory when the execution of the block they belong to ends. The return value of the `get_name` function, i.e., the starting address of the local `name_entry` array, is assigned to the pointer `ptr` in the `main` function. However, since the local array has already been deallocated from memory, the address assigned to the pointer variable `ptr` has no reliability. Reading from or writing to the location pointed to by the pointer `ptr` is a **pointer error**.

A function that returns an address should not return with the address of a local variable or the starting address of a local array. Calling the `getname` function written above causes a runtime error. Most C compilers flag this situation with a logical warning message.

---

## The NULL Address Literal (Null Pointer)

A pointer variable is an object that holds address information, right?

    int x = 10;
    int *ptr = &x;

We can express the statements above with the following sentences:

* The pointer `ptr` holds the address of the object $x$.
* The pointer `ptr` points to the object $x$.
* The object `*ptr` is the object pointed to by `ptr`.
* `*ptr` is the object $x$ itself.

Let there be a pointer that points to **no object**. The value of a pointer that points nowhere must be an address that is guaranteed not to be used for any other purpose. A standard symbolic constant is defined in some header files for the purpose of being used as an address that points nowhere. This symbolic constant is known as the **NULL symbolic constant**.

**NULL** is a symbolic constant. This symbolic constant is defined in standard header files such as `stdio.h`, `string.h`, and `stddef.h`.

The `NULL` address can be assigned to a pointer of any type. Such an assignment is entirely compliant with the syntactic rules, and no situation requires a warning.

    int *iptr = NULL;
    char *cptr = NULL;
    double *dptr = NULL;

The `NULL` address is the value of a pointer that points nowhere. A pointer either points to an object (in which case the value of the pointer is the address of the object it points to) or points to **no object** (in which case the value of the pointer is the `NULL` address).

When it is in question whether address information is interpreted as true or false, the address information is interpreted as **"false"** if it is the `NULL` address. All address information other than the `NULL` address is interpreted as **"true."**

Suppose a function is desired to be called if the value of a pointer named `ptr` is not the `NULL` address, i.e., if the pointer `ptr` points to an object. The conditional expression of such an `if` statement can be written in two separate forms:

    if (ptr != NULL)
        foo();
    
    // or
    
    if (ptr)
        foo();

Now suppose a function is desired to be called if the value of the pointer variable named `ptr` is the `NULL` address, i.e., if the pointer `ptr` points to no object. The conditional expression of the `if` statement can again be written in two separate forms:

    if (ptr == NULL)
        foo();
    
    // or
    
    if (!ptr)
        foo();

When the value $0$ of any type is assigned to a pointer variable, the value $0$ is automatically converted to the **`NULL` address** before the assignment:

    int *ptr = 0;

With the statement above, the `NULL` address is assigned to the pointer variable `ptr`.

So, what is the `NULL` address used for?

If a function that returns an address fails, the function can report the failure state by returning the **`NULL` address**.

Let's write a function that returns the address of the first prime number found in an `int` array:

    int *get_first_prime(const int *ptr, int size);

Let the first parameter of the function be the starting address of the array, and the second parameter be the size of the array. Imagine we wrote the function in the following form:

    int is_prime(int val);
    int *get_first_prime(const int *ptr, int size)
    {
        int k;
        for (k = 0; k < size; ++k)
            if (isprime (ptr[k]))
                return ptr + k;
        /* ??????? */ // What to return if no prime is found?
    }

In the function above, every element of our array, whose starting address is received from outside, is tested to see if it is prime, and when the first prime number is seen, the function returns with the address of this element. But what if there are no prime numbers in the array? The function returns a garbage value when the `for` loop statement is exited, right? So, what return value can the function produce in this case?

Since the `NULL` address is an address that points nowhere, a function that returns an address can report failure by returning the `NULL` address, right?

    #include <stdio.h>
    int is_prime(int val);
    int *get_first_prime(const int *ptr, int size)
    {
        int k;
        for (k = 0; k < size; ++k)
            if (isprime (ptr[k]))
                return ptr + k;
        return NULL; // Returns NULL address on failure
    }

The convention of a function that returns an address returning the `NULL` address upon failure is a very frequently used convention in the C language.

A function whose parameter variable is a pointer can use the `NULL` address passed to it as a flag value. Suppose we designed a function like the following:

    void func(char *ptr)
    {
        if (ptr == NULL) {
            /***/ // Perform task A if no address is provided
        }
        else {
            /***/ // Perform task B if an address is provided
        }
    }

The function performs different tasks depending on whether the address passed to it is the `NULL` address. Of course, this situation must be known by the code snippet that calls the function. The standard C function `time` is like this. When the `NULL` address is passed to the pointer parameter of the `time` function, the function does not assign a value to any object. It conveys the calculated value only as a return value to the outside. However, when an address other than the `NULL` address is sent to the function, the function writes the calculated value to the object at the given address.

Many programmers give a pointer variable the value of the **`NULL` address** before assigning a reliable address to the pointer. In this way, the information that the relevant pointer does not yet point to an object is strongly conveyed within the code, and the readability of the code is increased.

The lifespan of a pointer may end before the lifespan of the object it points to ends. In this case, the address that is the value of the pointer is not a reliable address. The `NULL` address can be assigned to the pointer to emphasize this situation in the code.

---

## Warnings and Possible Pointer Errors Related to Pointers

### Assigning an Address of a Different Type to a Pointer:

When an address of a different type is assigned to a pointer, most C compilers view the situation with suspicion and issue a logical warning message. However, the compiler still assigns the numerical component of the address of the different type to the target pointer. Borland compilers give the following warning message in this situation:

    warning : suspicious pointer conversion in function ......

Examine the following code:

    #include <stdio.h>
    int main()
    {
        double d = 1874567812.987;
        int *ptr;
        ptr = &d; // Assigns a double* address to an int* pointer (Warning)
        *ptr = 0; // Writes 0 to the first sizeof(int) bytes of 'd'
        printf("d = %lf\n", d);
        return 0;
    }

In the code above, the address of the `double` type variable $d$ is assigned to the `ptr` variable, which is supposed to point to an `int` type object. After such an assignment, `ptr` points not to the `double` type variable $d$, but to an object of type `int`.

With the assignment `*ptr = 0;`, the value $0$ in integer format is assigned to the first 4 bytes (assuming 4-byte `int`) of the variable $d$. After such an assignment, the value of the variable $d$ is changed in an undesirable way, right?

If an address of a different type is assigned to the pointer consciously, the **type cast operator** must be used:

    #include <stdio.h>
    int main()
    {
        double d;
        unsigned int k;
        unsigned char *ptr;
        printf("enter a real number :");
        scanf("%lf", &d);
        ptr = (unsigned char *)&d; // Conscious type cast
        for (k = 0; k < sizeof(double); ++k)
            printf("%u\n", ptr[k]);
        return 0;
    }

In the `main` function above, the address of the `double` type variable $d$ is assigned to a pointer of type `unsigned char *`. The `ptr` pointer variable is incremented byte by byte, and the value of each byte of the variable $d$ is interpreted as an integer and printed to the screen.

In the statement `ptr = (unsigned char *)&d;`, the address of the variable $d$ is first converted to address information of type `unsigned char *` to show that the assignment is made consciously, and then the assignment is performed.

### Assigning a Non-Address Value to a Pointer Variable

This is also an operation that is very unlikely to be done consciously. C compilers inform the programmer about this suspicious situation with a logical warning message. For example, this warning message in Borland compilers is as follows:

    "non-portable pointer conversion"

So, what happens if a non-address value is assigned to a pointer? In C, this is not directly a syntax error. Implicit type conversion is involved again. The type of the expression on the right side of the assignment operator is converted to the type of the expression denoting the object on the left side of the assignment operator, and the assignment is performed. Therefore, the assigned value is converted to address information of the pointer variable's type and assigned to the pointer. For example:

    void func()
    {
        int x = 1356;
        int *ptr;
        ptr = x; // Assigns the value 1356 to the pointer ptr (Warning/Error)
        /***/
    }

In the example above, the value of the object $x$, $1356$, is assigned to the pointer `ptr` with the assignment statement `ptr = x;`. The value $1356$, which is the value of the variable $x$, is converted to address information through type conversion before the assignment and assigned to the pointer `ptr`. Now, `ptr` no longer points to the variable $x$; it points to the object at address 1356.

Accessing the object `*ptr` is now a **pointer error**.

### Memory Layout of Objects

The way variables larger than one byte are laid out in memory can vary depending on the microprocessor used. Therefore, the appearance of variables in memory is not portable information. Microprocessors can use two types of layout:

i) **Little-endian**: The low-order byte values are located at the low-numbered address in memory. This type of layout is called little-endian. Intel processors use this layout. In systems using these processors, for example, let an `int` type variable $x = 0x1234$ be placed starting from address `1A00`:

| Address | Byte Value | Meaning |
| :--- | :--- | :--- |
| 1A00 | 0x34 | Low-order byte |
| 1A01 | 0x12 | High-order byte |

As seen from the figure, the low-order byte value of the variable $x$ (`34H`) is placed at the low-numbered address (`1A00H`).

ii) **Big-endian**: The low-order byte is placed at the high-numbered address. This type of layout is called big-endian. Motorola processors use this layout. In systems using these processors, for example, let an `int` type variable $x = 0x1234$ be placed starting from address `1A00`:

| Address | Byte Value | Meaning |
| :--- | :--- | :--- |
| 1A00 | 0x12 | High-order byte |
| 1A01 | 0x34 | Low-order byte |

The following code checks whether the system used is little-endian or big-endian:

    #include <stdio.h>
    int main()
    {
        int x = 1; // On a 4-byte system: 0x00000001
        if (*(char *)&x) // Accesses the first byte
            printf("little endian\n");
        else
            printf("big endian\n");
        return 0;
    }

In the written code, the address of the variable $x$ is obtained first with the address-of operator. The value produced by the address-of operator is of type `int *`. Then, the obtained address information is converted to the `char *` type with the type cast operator. You see that the `char *` type address is also the operand of the indirection operator. In this case, the indirection operator accesses the `char` type object at the lowest numerical address of the object $x$, right? If the value of this object is 1, the system is **"little-endian."**

### Passing Strings to Functions

Strings are contained within character arrays. For a function to be able to operate on a string, it is sufficient for it to receive the **starting address** of the string. That is, the function is called with the starting address of the string (character array). There is no need to pass the size information of the `char` array containing the string to the function. This is because there is a **null character** at the end of strings. Code that operates on character arrays determines the end of the array with the help of the null character.

A function that operates on strings receives the starting address of the string it will operate on with a `char` pointer variable. The function can access all characters of the string with a loop until it sees the null character at the end of the string.

Let $str$ be a `char` pointer. Loops that can operate on the string until the null character is seen can be constructed as follows:

    while (*str != '\0') {
        /***/
        ++str;
    }
    
    for (i = 0; str[i] != '\0'; ++i) {
        /***/
    }

### The `puts` and `gets` Functions

The parameter variable of the standard `puts` function declared in `stdio.h` is a `char` pointer:

    int puts(const char *str);

The function writes the string at the address $str$ to the standard output device. After the function completes the writing operation, it also writes a `\n` character to the screen. If the writing operation is successful, the return value of the function is a non-negative value. The function returns a negative value in case of failure. Below, a function named `myputs` that performs a similar task is defined:

    #include <stdio.h>
    void myputs(const char *str)
    {
        while (*str != '\0')
            putchar(*str++); // Prints character, then increments pointer
        putchar('\n');
    }
    int main()
    {
        char s[] = "NecatiErgin";
        int k;
        for (k = 0; k < 11; ++k)
            myputs(s + k); // Passes address of s[k]
        return 0;
    }

The standard `gets` function declared in `stdio.h` is also essentially a function with a pointer parameter:

    char *gets(char *ptr);

The function places the string it receives from the standard input unit into the address passed to its parameter. If the input operation is successful, the function returns the address $ptr$. In case of failure, the return value of the function is the **`NULL` address**. Below, a function named `mygets` that performs a similar task is defined:

    #include <stdio.h>
    char *mygets(char *ptr)
    {
        int ch;
        int index = 0;
        while ((ch = getchar()) != '\n')
            ptr[index++] = ch;
        ptr[index] = '\0';
        return ptr;
    }