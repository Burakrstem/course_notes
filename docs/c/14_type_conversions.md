# 🔄 Type Conversions

There are certain limitations when computers perform arithmetic operations. For computers to perform an arithmetic operation, the operands involved generally need to have the same length (i.e., the same number of bits) and be represented in the same format in memory. For example, the processor can directly add two 16-bit integers, but it cannot directly add a 16-bit integer and a 32-bit floating-point number.

The C programming language allows different types to coexist within the same expression. That is, a variable of an integer type, a literal of type `float`, or a variable of type `char` can be included together in a single expression. In this case, before subjecting them to any operation, the C compiler performs the appropriate **type conversions** to enable the computer hardware to evaluate the expression.

For instance, when a 16-bit `int` value is added to a 64-bit `double` value, the 16-bit `int` value is first represented as a 64-bit `double` value, and then the addition is performed. Similarly, when a 16-bit `int` value is multiplied by a 64-bit `double` value, the compiler first converts the `int` value to a 64-bit `double` value. This type conversion is more complex because `int` and `double` values are stored in different formats in memory.

These type conversions are performed automatically without the programmer needing to write any code. We call such conversions **implicit type conversions**. On the other hand, the C language also gives the programmer the ability to treat any expression as a different type using an operator. We call such type conversions performed by the programmer **explicit type conversions** or **type casts**.

Let's first examine implicit type conversions. Unfortunately, implicit type conversions are complex, and if not well understood, errors in programs are inevitable. You know that there are 11 different native data types in C. To avoid any errors, it is necessary to know very well how implicit type conversion will be performed for every possible binary combination of these types.

---

## 🧐 When is Type Conversion Performed?

An implicit type conversion is performed automatically in the four cases listed below:

1.  **If the operands of an arithmetic or logical expression are not of the same type:**
    We call such type conversions **conversion before operation**.
2.  **If the type of the expression on the right side of the assignment operator is not the same as the type of the object on the left side:**

        double total;
        long number1, number2;
        /***/
        total = number1 + number2;

    We call the type conversions performed in this case **assignment type conversions**.
3.  **If the type of an argument sent to a function in a function call is not the same as the type of the corresponding parameter of the function:**

        double sqrt (double val);
        void func()
        {
            int number;
            double result = sqrt(number);
            /***/
        }

    In the example above, the type of the argument `number` sent to the called `sqrt` function is different from the type of the function's parameter variable. In this case, a type conversion operation is performed.
4.  **If the type of a `return` expression is not the same as the return type of the function:**

        double func(int val)
        {
            /****/
            return val;
        }

    In the `func` function defined above, the type of the `return` expression is `int`, while the declared return type of the function is `double`. In this case, an implicit type conversion operation is performed by the compiler.

Cases 3 and 4 can also be considered assignment operations. Arguments in a function call expression are passed by being copied to the parameter variables. Thus, there is an implicit assignment operation. Similarly, `return` expressions are also copied to temporary objects that will hold the function's return value.

---

## ➕ Implicit Arithmetic Type Conversions (Before Operation)

Implicit type conversions before an operation are applied when the types of the operands in expressions containing binary operators are different. As a result of the implicit type conversion, the situation of having two different types is eliminated, and both operands are made to have the same type. For example:

    int i;
    double d, result;
    result = i + d;

The types of the variables `i` and `d` on the right side of this expression are different. One operand is `int`, and the other is `double`. In this case, the compiler generates code that expresses one of the operands in the type of the other in a temporary region. Therefore, the operation is performed in the common type.

So, should the `int` operand be expressed as `double`, or the `double` operand as `int`? The compiler tries to perform such a conversion in a way that prevents **information loss**.

In this situation, to prevent information loss, the operand with the smaller type is generally expressed in the type of the operand with the larger type.

To learn the rules in detail, let's examine the possible situations under two main groups:

### 1. If One of the Operands is a Real Number Type:

* If one of the operands is of type `long double` and the other is of a different type, the other operand is expressed in the `long double` type, and the operation is performed in the `long double` type.
* If one of the operands is of type `double` and the other is of a different type, the other operand is expressed in the `double` type, and the operation is performed in the `double` type.
* If one of the operands is of type `float` and the other is of a different type, the other operand is expressed in the `float` type, and the operation is performed in the `float` type.

### 2. If None of the Operands are Real Number Types:

If any of the operands in the expression are of type `signed char`, `unsigned char`, `signed short int`, or `unsigned short int`, these types are converted to the `int` type before the following algorithm is applied. This conversion is called **"integral promotion."**

The following rules are then applied:

* If one of the operands is of type `unsigned long` and the other is of a different type, the other operand is expressed in the `unsigned long` type, and the operation is performed in the `unsigned long` type.
* If one of the operands is of type `signed long` and the other is of a different type, the other operand is expressed in the `signed long` type, and the operation is performed in the `signed long` type.
* If one of the operands is of type `unsigned int` and the other is of a different type, the other operand is expressed in the `unsigned int` type, and the operation is performed in the `unsigned int` type.

**Exceptions:**

* If one of the operands is `signed long int` and the other is `unsigned int`, and the lengths of these types are the same on the system used (as in UNIX and Win 32 systems), both operands are converted to the `unsigned long int` type.
* If one of the operands is `signed int` and the other is `unsigned short int`, and the lengths of these types are the same on the system used (as in the DOS operating system), both operands are converted to the `unsigned int` type.

Care should be taken when converting from a signed integer type to an unsigned integer type:

    #include <stdio.h>
    int main()
    {
        int x = -2;
        unsigned int y = 1;
        if (y > x)
            printf("true!\n");
        else
            printf("false!\n");
    }
    return 0;

When the program above runs, the message "false!" is printed to the screen.

In the expression `y > x`, the left operand of the `>` operator is of type `unsigned int`, while the right operand is of type `int`. As a result of the implicit type conversion, the `int` operand is expressed as `unsigned int` before the operation. When the value $-2$ is expressed as `unsigned int`, it is no longer a negative value but a large positive number. For example, if a 2-byte `int` type is involved, this value is 65534. Therefore, the expression `y > x` is interpreted as false. The comparison is $1 > 65534$, which is false.

Function call expressions can also cause implicit type conversions if they form other expressions with operators. This is because for functions that have a return value, the function call expression corresponds to the function's return value. For example:

    int i = 5;
    ...
    pow(2, 3) + i

In the expression above, since the return value of the `pow` function is of type `double`, the variable `i`, which is of type `int`, is also expressed as `double` in a temporary region and entered into the operation so that the operation can be performed.

---

## ➡️ Assignment Type Conversions

These type conversions have a very simple rule: **Before assignment, the expression on the right side of the assignment operator is expressed in the type of the object on the left side of the assignment operator.**

There is no information loss when converting smaller types to larger types. For example:

    double leftx;
    int righty = 5;
    leftx = righty;

In the example above, the type of the `righty` variable is `int`. First, an implicit conversion to the `double` type is performed, and then the value of the `righty` variable, expressed as `double`, is assigned to the `leftx` variable.

Below are some examples for 16-bit systems:

| TYPE | decimal | hex | converted type | hex | decimal |
| :--- | :--- | :--- | :--- | :--- | :--- |
| `int` | 138 | `0x008A` | `long int` | `0x0000008A` | 138L |
| `char` | 'd' (100) | `0x64` | `int` | `0x0064` | 100 |
| `int` | -56 | `0xFFC8` | `long int` | `0xFFFFFFC8` | -56L |
| `char` | '\x95' (-107) | `0x95` | `int` | `0xFF95` | -107 |
| `unsigned int` | 45678 | `0xB26E` | `long int` | `0x0000B26E` | 45678L |
| `char` | '0' (48) | `0x30` | `long int` | `0x00000030` | 48L |

When a negative integer is converted from a smaller type to a larger type, the high-order bits of the number are filled with the **1 bit** to preserve negativity (sign extension).

In assignment type conversions performed by the compiler, information loss may occur before the assignment if a larger type is converted to a smaller type.

The following simple rules can be given:

* If both sides of the assignment operator are integer types (`char`, `short`, `int`, `long`), information loss may occur if the right side of the assignment operator is a larger type. Information loss only occurs if the value on the right side of the assignment operator is outside the boundaries of the type on the left side. Information loss appears as the loss of high-order bytes. Example:

        long m = 0x12345678;
        int y = m;
        printf ("m = %x\n", m);

    In the example above, the value of a `long` type variable is assigned to an `int` type variable $y$. We assume the code is running on a 16-bit system, for example, under DOS. Under DOS, the number limits for the `int` type are $-32768$ to $+32767$. These numbers are the largest and smallest values that can be written as signed for a two-byte area. In the hexadecimal number system, each digit corresponds to 4 bits, and every two digits correspond to 1 byte of space. Therefore, the number `0x12345678` is an 8-hex digit, or 4-byte, long number. However, the object to which the assignment will be made is of type `int`, and this type can be at most 4 hex digits (2 bytes) long. In this case, the high-order 2 bytes (4 hex digits) of the value belonging to the variable $m$ are lost. After the assignment operation, the value of the variable $y$ is printed as `5678` by the `printf` function.

* If the right operand of the assignment operator is a real number type (`float`, `double`, `long double`) and the left operand is an integer type, the decimal part of the real number value is first lost. If the integer part obtained from the real number cannot be expressed in the integer type to which the assignment is made, this behavior is **undefined behavior**. Code where this situation occurs must be strictly avoided. However, almost all compilers perform type conversion in the following way in this situation:
    If the real number that is the right operand of the assignment operator contains a decimal part, the decimal part is first lost. If the remaining integer value after the decimal part is lost stays within the limits of the left operand's type, there is no further information loss, but if the limits of the left side's type are exceeded, there is an additional information loss, and this time the high-order bytes are lost. Example:

        #include <stdio.h>
        int main()
        {
            double y = 234.12;
            int x;
            x = y;
            printf("x = %d\n", x); /* x is assigned the value 234 */
            y = 7689523345.347;
            x = y; /* Error: Undefined behavior/Information loss */
            printf("x = %d\n", x);
            return 0;
        }

Now, compile and run the following program:

    #include <stdio.h>
    int main()
    {
        char ch;
        ch = 135;
        if (ch == 135)
            printf("true!\n");
        else
            printf("false!\n");
        return 0;
    }

Why is "false!" printed to the screen when the program runs?

The value 135 is assigned to the variable `ch`:

    ch = 135;

In this case, since the high-order byte will be lost, the value assigned to the variable `ch` becomes:

    1000 0111

In the comparison operation `ch == 135`, the variable `ch`, which is of type `char`, is promoted to the `signed int` type before the comparison operation. As a result of integral promotion before the operation, the high-order bytes are filled with **1 bits** because `ch` has a negative value. Before the comparison operation, the value of `ch` becomes:

    1111 1111 1000 0111

However, the value 135, which is the right operand of the comparison operator, is an `int` type literal. That is, the values actually being compared are as follows:

    1111 1111 1000 0111
    0000 0000 1000 0111

The comparison results in false.

---

## ⬆️ Integral Promotion

As explained earlier, **integral promotion** means that the types `char`, `unsigned char`, `short`, and `unsigned short` found in an expression are automatically converted to the `int` type before the expression is evaluated by the compiler.

So, is the conversion made to `signed int` or `unsigned int`?

The general rule is this: If the value of the operand undergoing type conversion can be expressed in the `int` type, the conversion is made to `int`; if it cannot be expressed, the conversion is made to `unsigned int`.

For example, in the DOS operating system, where `unsigned short` and `int` types have the same length, the `unsigned short` type is converted to the `unsigned int` type during integral promotion.

If the value to be promoted is of type `signed char`, `unsigned char`, or `signed short`, the conversion is made to the `signed int` type.

We must not overlook the following point regarding information loss. In some cases, information loss occurs not because type conversion is performed, but because it is **not** performed. Boundary value overflows can be a good example of this situation.

Example: (Assume we are working under DOS)

    long x = 1000 * 2000;

The code above seems normal at first glance. This is because the result of the multiplication, 2000000, is within the signed `long` type number limits under DOS. However, information loss occurs **before** the assignment operation. `1000` and `2000` are `int` type literals, and when they are entered into the operation, the value produced by the multiplication operator is also of type `int`. In this case, since the `int` type, which is 2 bytes long, cannot hold the value 2000000, the high-order byte is lost. 2000000 can be represented as `0x1E8480` in the hexadecimal number system. When the high-order byte is lost, the operation result becomes `0x8480`. `0x8480` is a negative number because its sign bit is 1. If we take its two's complement:

    0x8480
    1000 0100 1000 0000 (binary)
    0111 1011 0111 1111 (one's complement)
    0111 1011 1000 0000 (two's complement = 0x7B80 = 31616)

As seen, the value produced by the operation is $-31616$. In this case, even if the type of the variable $x$ is `long`, the assigned value will be $-31616$.

---

## ⚙️ Type Conversion in Function Calls

As stated before, if there is a type difference between the arguments sent to a function and the parameters of the function that will hold these arguments, an implicit type conversion occurs, and the type of the arguments is converted to the type of the parameter variables. However, for this type conversion to occur, the compiler must have information about the types of the function's parameter variables before reaching the function call expression. The compiler can obtain this information in two separate ways:

1.  **If the called function is defined before the calling function:** the compiler determines the type of the parameter variables from the function's definition.
2.  **If the function declaration (prototype) is made:** the compiler has prior knowledge about the type of the parameter variables.

Examine the following example:

    #include <stdio.h>
    double func(double x, double y)
    {
        /***/
    }
    int main()
    {
        int a, b;
        /***/
        func(a, b);
        return 0;
    }

In the example above, the values of the variables $a$ and $b$, which are of type `int`, are sent as arguments to the `func` function called within the `main` function. Since the function definition is before the call expression, the values of the variables $a$ and $b$, which are of type `int`, are converted to the `double` type and passed to the variables $x$ and $y$, which are the parameters of the `func` function. If the `func` function is defined after the `main` function, information about the types of the parameter variables must be given to the compiler with a **function declaration** so that the implicit type conversion can be performed.

    #include <stdio.h>
    double func(double x, double y); // Function declaration (prototype)
    int main()
    {
        int a, b;
        /***/
        func(a, b);
        return 0;
    }
    double func(double x, double y)
    {
        /***/
    }

So, if the called function is defined after the calling function and no function declaration is made—*in which case the function must have an `int` return type to avoid a compile-time error*—will type conversion occur?

In this case, since the compiler will not have information about the types of the function's parameters, it applies an operation called **default argument conversion** to the arguments sent to the function. Default argument conversion is as follows:

* Arguments of type `char` or `short` are **promoted to integer** (`integral promotion`).
* Arguments of type `float` are **converted to double**.
* No type conversion is performed for arguments of other types.

---

## 🎯 Type Cast Operator

With the **type cast operator**, an expression can be expressed in another type before it is subjected to an operation. The type cast operator is a unary operator in the prefix position.

The operator consists of parentheses and a type information written inside the parentheses:

    (double)x

The value produced by the operator is the value of its operand expression expressed in the type inside the parentheses. The type cast operator, like all other unary operators, is at the second precedence level of the operator precedence table.

Compile and run the following program:

    #include <stdio.h>
    int main()
    {
        int x = 10;
        int y = 4;
        double z;
        z = (double)x / y;
        printf("z = %lf\n", z);
        return 0;
    }

In the expression `z = (double)x / y` in the program above, the type cast operator produces a value first. The value produced by the type cast operator is the value of the object $x$ expressed as `double`. In this case, when it is the turn of the division operator, the operand of the division operator is the value 10 of type `double`. This time, with an implicit type conversion, the right operand of the division operator is converted to `double`, and the division is performed in the `double` type. In this case, the division operator produces the value $2.5$.

Undoubtedly, if the expression had been written as follows, there would still be no information loss:

    z = x / (double)y

However, if the expression had been written as follows:

    z = (double) (x / y)

in this case, the operand of the type cast operator would be the expression `(x / y)`. This would **not prevent information loss**. The result of integer division $10 / 4$ is $2$. The type cast then converts $2$ to $2.0$.

In cases where information loss is desired, an explicit conversion with the type cast operator should be made instead of an implicit type conversion for readability.

    int i;
    double d;
    /***/
    i = d;

Assigning the value of the `double` variable $d$ to the `int` variable $i$ does not exhibit reliable behavior. At best, only the integer part of the value of $d$ is assigned to the variable $i$. Readers of such code get the impression that this assignment was made accidentally. Most compilers also report the possible information loss with a warning message. If this assignment is made consciously, the type cast operator should be used:

    int i;
    double d;
    /***/
    i = (int)d;

In the following program, a floating-point number entered from the keyboard is rounded to the nearest integer. If the decimal part of the entered value is greater than or equal to `.5`, the number is rounded up; if it is less than `.5`, the number is rounded down:

    #include <stdio.h>
    int main()
    {
        double d;
        int x;
        printf("enter a real number : ");
        scanf("%lf", &d);
        if (d >= 0) // Note: Simplified condition for rounding based on sign.
            x = d + .5;
        else
            x = d - .5;
        printf("x = %d\n", x);
        return 0;
    }