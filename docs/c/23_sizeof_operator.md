# 📏 The `sizeof` Operator

**`sizeof`** is an operator that produces the value of how many bytes the type of an expression occupies in memory. `sizeof` is a **unary prefix operator**.

The operand of the `sizeof` operator can be one of the following:

1.  **Type-specifying keywords can be used as the operand.** In this case, the operand must be enclosed in parentheses. Examples:

        sizeof(int)
        sizeof(double)
        sizeof(long)

    In this case, the operator produces the value of how many bytes the type information that is its operand occupies on the system being used. For example, on Windows or UNIX systems, the value of an expression like `sizeof(int)` is 4.

2.  **An expression can be used as the operand.** In this case, enclosing the operand in parentheses is **not** mandatory. However, most programmers prefer to enclose the operand in parentheses for readability:

        double x;
        sizeof (x)
        sizeof(17.8)
        sizeof(func())

    In this case, the operator produces the value of how many bytes the type belonging to the operand expression occupies on the system being used. For example, on Windows or UNIX systems, the value of an expression like `sizeof(x)` is 8. Such an expression can naturally also be used to determine how many bytes the object $x$ occupies in memory on the relevant system. The `sizeof` operator is most commonly used in this form. That is, the operand of the operator is chosen as an expression denoting an object to find out how many bytes the operand object occupies in memory.

3.  **When the `sizeof` operator takes an array name as an operand, it produces the total length of that array in bytes as its value:**

        double a[10];
        sizeof(a)

    The expression produces the value 80.

    On the other hand, the value produced by the `sizeof` operator when it takes an element of the array as an operand is the length in bytes of the type of that array on the system being used. That is, in the example above:

        sizeof(a[0])

    The expression produces the value 8.

    In this case, the expression:

    $$\text{sizeof}(a) / \text{sizeof}(a[0])$$

    gives the array size. Example:

    $$\text{for } (i = 0; i < \text{sizeof}(a) / \text{sizeof}(a[0]); ++i) \ a[i] = 0;$$

    The loop above, where $a$ is an array name, iterates as many times as the number of elements in array $a$.

    Instead of explicitly writing the array size in the loop above, writing it in the form $\text{sizeof}(a) / \text{sizeof}(a[0])$ might seem surprising to you. Can such a writing style have a benefit?

    You know that in array definitions, there is no need to specify the size of arrays that are initialized, and the compiler deduces the array size from the number of initial values given. Examine the following code:

    ```c
    #include <stdio.h>
    int main()
    {
        int a[] = {2, 5, 7, 8, 9, 23, 67};
        int k;
        for (k = 0; k < sizeof(a) / sizeof(a[0]); ++k)
            printf("%d ", a[k]);
        printf("\n");
        return 0;
    }
    ```

    An `int` array named $a$ is defined in the `main` function above. The defined array is initialized. The compiler counts the given initial values, determines the array size as 7, and generates code accordingly. The `for` loop statement in the `main` function iterates as many times as the number of elements in the array, i.e., 7 times.

    Now assume that a change is made in the source code, and a few more elements are added to array $a$:

    `int a[] = {2, 5, 7, 8, 9, 23, 67, 34, 58, 45, 92};`

    In this case, there is no need to make a change in the `for` loop statement. This is because the compiler calculates the array size as 11 this time. The expression $\text{sizeof}(a) / \text{sizeof}(a[0])$ used in the `for` loop statement also produces the value 11 this time.

---

## ⏫ Precedence of the `sizeof` Operator

You know that all unary operators are located at the second level of the operator precedence table. `sizeof` is also an operator located at the second level.

### `sizeof` is Not a Function

Since the operand of the `sizeof` operator is often written inside parentheses, the usage of the operator resembles a function call:

    sizeof(y)

However, `sizeof` is an **operator**, not a function. `sizeof` is one of the 32 keywords in the C language.

### Type of the Value Produced by the `sizeof` Operator

The value produced by the `sizeof` operator is of type **`unsigned int`**. Accepting the type of the value produced by the operator as `signed int` is an error. When the value produced by the operator is subjected to an operation with a negative number of type `signed int`, type conversion is performed towards the unsigned direction:

    -2 * sizeof(int)

$-2$ is a literal of type `signed int`. The value produced by the expression `sizeof(int)` is the value 4 of type `unsigned int`. With the implicit type conversion to be performed before the operation, the value $-2$ is converted to the `unsigned int` type. The operation is performed in the `unsigned int` type. That is, the result of the operation is not $-8$.

> \[Actually, the value produced by the `sizeof` operator is of the standard `typedef` type called **`size_t`**. Standard `typedef` types are covered in the section "Type Name Declarations and the `typedef` Specifier."]

### Side Effect of the Expression That is the Operand of the `sizeof` Operator

The expression that is the operand of the `sizeof` operator **does not exhibit a side effect**. Examine the following example:

    #include <stdio.h>
    int func()
    {
        printf("func()\n");
        return 1;
    }
    int main()
    {
        unsigned int x = sizeof(func()); // func() is NOT called
        printf("x = %u\n", x); // x will be the size of int (e.g., 4)
        return 0;
    }

The `func` function is **not** called in the `main` function. The `sizeof` operator only looks at its operand expression as a type information. The type of the expression `func()` in the example code is the `int` type.

### What is the `sizeof` Operator Used For?

The number of bytes a specific type of object occupies in memory can vary from system to system. The only native type whose length is guaranteed is the `char` type. An object of type `char` occupies 1 byte on all systems. The fact that type lengths can differ from system to system can lead to portability problems in some applications. It can generally be said that the `sizeof` operator is used to eliminate such portability problems.