# ❓ The Conditional Operator (Ternary Operator)

The conditional operator (ternary operator) is the only ternary operator in the C language. Any expression can be one of the operands of the conditional operator. The general syntax of the conditional operator is as follows:

    expression1 ? expression2 : expression3

The conditional operator, as seen from the syntax above, consists of two separate tokens. The `?` and `:` tokens separate the operator's three operands.

The compiler recognizes a conditional operator from the `?` token. The numerical value of the expression to the left of the `?` token (**expression1**) is calculated. This expression is interpreted logically. If the value of `expression1` is non-zero (true), then **only** the numerical value of **expression2** is calculated. If the value of `expression1` is 0 (false), then **only** the numerical value of **expression3** is calculated.

Like other operators, the conditional operator also produces a value. The value produced by the conditional operator is the value of `expression2` if `expression1` is true (non-zero), and the value of `expression3` if `expression1` is false. Example:

    m = x > 3 ? y + 5 : y – 5;

Here, the numerical value of the expression $x > 3$ is calculated first. If the value of this expression is non-zero (true), the conditional operator produces the value $y + 5$. If the value of the expression $x > 3$ is 0 (false), the conditional operator produces the value $y – 5$. In this case, the value $y + 5$ or $y – 5$ is assigned to the variable $m$, depending on whether the expression $x > 3$ is true or false.

The same operation can also be done with an `if` statement:

    if (x > 3)
        m = y + 5;
    else
        m = y – 5;

The conditional operator is at the **13th precedence level** of the operator precedence table. This level is immediately above the assignment operator. Let's consider the following expression:

    x > 3 ? y + 5 : y – 5 = m

Since the precedence of the conditional operator is higher than the assignment operator, the conditional operator is evaluated first. Assume that the expression $x > 3$ is true and the operator produces the value $y + 5$.

    y + 5 = m

Since the value produced by the conditional operator is not an Lvalue (an object), the expression above is **invalid**.

It is usually not necessary to enclose the first operand of the conditional operator in parentheses. However, it is generally preferred to enclose this operand in parentheses for readability:

    (x >= y + 3) ? a * a : b

Care must be taken with the third operand of the conditional operator. For example:

    m = a > b ? 20 : 50 + 5

Depending on whether the expression $a > b$ is true or false, the conditional operator produces the value 20 or 55, and finally, the value produced by the conditional operator is assigned to the variable $m$. However, if it is desired that $m$ be assigned the value produced by the expression $a > b ? 20 : 50$ plus 5, the expression must be structured as follows:

    m = (a > b ? 20 : 50) + 5;

All three operands of the conditional operator can be function call expressions, but the called functions must be functions that produce a return value. A function call expression for a function whose return value is `void` as one of the three operands can create an invalid situation.

Examine the following code snippet:

    #include <stdio.h>
    int func1(void);
    int func2(void);
    int func3(void);
    int main()
    {
        int m;
        m = func1() ? func2() : func3();
        return 0;
    }

In the expression using the conditional operator above, the return value of the `func2` function is assigned to the variable $m$ if the return value of the `func1` function is a non-zero value; otherwise, the return value of the `func3` function is assigned.

What the conditional operator produces is a **value**, not an object. Since the value produced by the conditional operator does not denote an object, an assignment cannot be made to this value. Examine the following `if` statement:

    if (x > y)
        a = 5;
    else
        b = 5;

In the `if` statement above, the value 5 is assigned to the variable $a$ if the expression $x > y$ is true, and to the variable $b$ if it is false. If the same task is performed using the conditional operator:

    (x > y) ? a : b = 5; /* Invalid! */

This leads to a compile-time error. This is because what the conditional operator produces is the **value** of the variables $a$ or $b$, not the object itself. Such an assignment creates an error at compile time because the left side is not an Lvalue (an expression denoting an object).

For the same reason, the following expression is also invalid:

    (x > 5 ? y : z)++; /* Invalid! */

What is obtained when the expression inside the parenthesis is evaluated is the **values** of the objects $y$ or $z$, not the objects themselves. That is, the operand of the postfix `++` operator is not an Lvalue.

> \[In C++, if the 2nd or 3rd operand of the conditional operator is an Lvalue, the value produced by the operator is an Lvalue. Thus, the statements above, which are invalid in C, are valid in C++.]

---

## 🎯 Situations Where the Conditional Operator is Used

It is not always correct to use the conditional operator instead of the `if` statement. There are typical situations where the use of the conditional operator is recommended. In these situations, the general idea is to utilize the value produced by the conditional operator within the same expression and transfer this value somewhere:

1.  **The value produced by the conditional operator can be assigned to an object:**

    * `p = (x == 5) ? 10 : 20;`
    * `m = (a >= b + 5) ? a + b : a – b;`

    `if` statements that would perform the job of the statements above could also be written:

    * `if (x == 5) p = 10; else p = 20;`
    * `if (a >= b + 5) m = a + b; else m = a - b;`

2.  **A function can return with the value produced by the conditional operator:**

        return x > y ? 10 : 20;

    In this example, the function returns the value 10 or 20 depending on whether the expression $x > y$ is true or false. The following `if` statement could also be used instead of the expression above:

        if (x > y)
            return 10;
        return 20;

3.  **A function can be called with the value produced by the conditional operator:**

        func(a == b ? x : y);

    In the statement above, the `func` function is called with the value $x$ if $a$ is equal to $b$, and with the value $y$ if $a$ is not equal to $b$. An `if` statement performing the same task could also be written:

        if (a == b)
            func(x);
        else
            func(y);

4.  **The value produced by the conditional operator can also be used as part of the control expression of a control statement:**

        if (y == (x > 5 ? 10 : 20))
            func();

    In the statement above, the equality of the variable $y$ to 10 or 20 is checked inside the `if` parenthesis, depending on whether the expression $x > 5$ is true or false.

In the situations above, preferring the conditional operator over the `if` statement is good technique. In these cases, the conditional operator creates a more readable structure.

The conditional operator should not be used carelessly. If the value produced by the conditional operator will not be utilized directly, the `if` control statement should be preferred over the conditional operator. For example:

    x > y ? a++ : b++;

The value produced by the conditional operator is not utilized in the statement. Here, the following `if` statement should be preferred:

    if (x > y)
        a++;
    else
        b++;

Another example:

    x == y ? printf("equal\n") : printf("not equal\n");

In this example, the conditional operator is used by utilizing the fact that the `printf` function produces a return value. The conditional operator produces the return value of one of the `printf` function calls, which are the second or third operands, depending on whether the expression $x == y$ is true or false. This is actually the number of characters written to the screen. But the value produced by the conditional operator is not used in the expression. Here too, the `if` statement should be preferred:

    if (x == y)
        printf("equal\n");
    else
        printf("not equal\n");

If the types of the second and third operands of the conditional operator are different, type conversion rules come into play, just as with other operators:

    int i;
    double d;
    m = (x == y) ? i : d;

In this example, the variable $i$ is of type `int`, and the variable $d$ is of type `double`. If the comparison expression $x == y$ is true, the type of the value produced by the conditional operator is `double`.

In some cases, neither the `if` statement nor the conditional operator needs to be used:

    if (x > 5)
        m = 1;
    else
        m = 0;

The following statement could have been written instead of the `if` statement above:

    m = (x > 5) ? 1 : 0;

In situations where the values produced by the conditional operator can only be 1 or 0, using the comparison operator directly should be considered better technique:

    m = x > 5;

Another example:

    return x == y ? 1 : 0;

could have been written instead of:

    return x == y;

The associativity of the conditional operator is **right-to-left**. If there is more than one conditional operator in an expression, the rightmost one is evaluated first. Examine the following code snippet:

    #include <stdio.h>
    int main()
    {
        int x = 1, y = 1, m;
        m = x < 5 ? y == 0 ? 4 : 6 : 8;
        printf("m = %d\n", m);
        return 0;
    }

In the `main` function above, the value 6 is printed to the screen as the value of the variable $m$ by the `printf` function call. The expression is evaluated as follows:

    m = x < 5 ? (y == 0 ? 4 : 6) : 8;

---

## 💻 Examples of Conditional Operator Usage

Below is the function `max2` defined, which returns the larger of two numbers:

    int max2(int a, int b)
    {
        return a > b ? a : b;
    }

The series $1 - \frac{1}{3} + \frac{1}{5} - \frac{1}{7} + \frac{1}{9} + \dots$ converges to $\frac{\pi}{4}$. Below, the number $\pi$ is calculated using a loop. Examine the use of the conditional operator in the loop body:

    #include <stdio.h>
    int main()
    {
        double sum = 0.;
        int k;
        for (k = 0; k < 10000; ++k)
            sum += (k % 2 ? -1. : 1.) / (2 * k + 1);
        printf("pi = %lf\n", 4. * sum);
        return 0;
    }