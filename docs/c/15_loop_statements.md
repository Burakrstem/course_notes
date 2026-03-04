# 🔁 Loop Statements

Control statements that allow a part of a program to be executed repeatedly are called **"loop statements."** There are 3 separate loop statements in the C language:

* `while` loop statement
* `do while` loop statement
* `for` loop statement

The most frequently used of these is the `for` loop statement. The `for` loop statement is the most powerful loop structure, not only in the C language but in all programming languages. Even if there were no `while` or `do while` loop statements, code written using those loops could be written using the `for` loop. However, there are situations where `while` and `do while` loops are preferred for readability.

---

## ⏳ The `while` Loop Statement

The general syntax of the `while` loop statement is as follows:

    while (expression)
        statement;

The expression inside the parenthesis following the `while` keyword is called the **control expression**. The first statement following the `while` parenthesis is called the **loop body**. The loop body can be formed by a simple statement, a null statement, a compound statement, or a control statement.

The execution of the `while` loop statement is as follows: First, the numerical value of the control expression is calculated. This expression is evaluated logically. If the expression has a value of 0, it is interpreted as false. In this case, the statement in the loop body is **not** executed, and the program flow continues with the first statement following the loop statement. If the control expression has a non-zero value, it is interpreted as true; in this case, the statement in the loop body is executed.

After the statement in the loop body is executed, the value of the control expression is calculated again. The statement in the loop body is executed as long as the control expression has a non-zero value (is true). The loop is exited when the control expression has a value of zero, meaning when the expression is interpreted as false.

The `while` loop in the C language is a loop statement that allows one or more tasks to be performed as long as a condition is true.

Examine the following example:

    #include <stdio.h>
    int main()
    {
        int i = 0;
        while (i < 100) {
            printf("%d ", i);
            ++i;
        }
        return 0;
    }

Let's examine the `while` loop in the `main` function. A compound statement forms the loop body. This compound statement is executed as long as the expression $i < 100$ is true. That is, the `printf` function is called, and then the value of the variable $i$ is incremented by 1. When the value of the variable $i$ becomes 100, the control expression will be false, and the loop is exited. Examine the following example:

    #include <stdio.h>
    int main ()
    {
        char ch = 'A';
        while (ch <= 'Z')
            putchar(ch++);
        return 0;
    }

With the `main` function above, all uppercase characters of the English alphabet are printed to the screen sequentially. You see that the variable named `ch` is first assigned the value 'A'. The loop iterates as long as the expression `ch <= 'Z'` is true. This time, a simple statement forms the loop body. You know that the postfix `++` operator produces the object's own value. However, due to the side effect of the operator, the value of the variable `ch` is incremented by 1. When the value of the variable `ch` is 'Z', the control expression is still true. But in the next iteration of the loop, the control expression is false, and the loop is exited.

In the `while` loop statement, the statement in the loop body is **not guaranteed to be executed at least once**. Since the control expression is evaluated first, if the control expression is false upon the first entry to the loop, the statement in the loop body is never executed.

### Control Expressions

Any expression can be the control expression of a `while` loop.

The control expression can contain a function call:

    while (isupper(ch)) {
        /***/
    }

The `while` loop above iterates as long as the `isupper` function returns a non-zero value, i.e., as long as `ch` is an uppercase character.

The following `while` loop iterates as long as the `isupper` function returns a value of 0, i.e., as long as `ch` is not an uppercase character.

    while (!isupper(ch)) {
        /***/
    }

The comma operator can also be used in the control expression of the `while` loop statement. Examine the following example:

    #include <stdio.h>
    #include <ctype.h>
    // #include <conio.h> (Assuming getch() is available)
    int getch_mock() { return getchar(); } // Mock function for standard C environment
    int main()
    {
        char ch;
        while (ch = getch_mock(), toupper(ch) != 'Q')
            putchar(ch);
        return 0;
    }

You know that the expression that is the left operand of the comma operator is guaranteed to be performed first. Let's look at the control expression of the `while` loop in the `main` function above:

    while (ch = getch_mock(), toupper(ch) != 'Q')

Since the expression that is the left operand of the comma operator will be performed first, the `getch` function is called (or `getch_mock` here). The code number of the character received from the keyboard is assigned to the variable `ch`. Then, with the call to the `toupper` function, it is tested whether the value of the variable `ch` is the character 'Q'. Recall that the value produced by the comma operator is the value of its right operand. In this case, the expression that determines whether the loop continues is:

    toupper(ch) != 'Q'

That is, the loop iterates as long as `ch` is not the uppercase character 'Q' (or 'q').

A variable can also form the control expression:

    while (x) {
        /***/
    }

The loop above iterates as long as the variable $x$ has a non-zero value.

A literal can also be the control expression:

    while (1) {
        /***/
    }

In the `while` statement above, the literal 1 is used as the control expression. Since 1 is a non-zero value, and the control expression does not change based on a variable, the loop cannot be exited by the condition becoming false. Such loops are called **infinite loops**. Infinite loops can occur as a result of a programmer's mistake, or they can be created consciously to achieve a specific purpose. A `while` loop where the literal value 1 is inside the `while` parenthesis is a consciously created infinite loop statement.

The use of the assignment operator within the control expression is also a common occurrence:

    while ((val = get_value()) > 0) {
        foo(val);
        /***/
    }

In the `while` loop above, the return value of the `get_value` function is assigned to the variable named `val`. You see that the expression formed by the assignment operator is enclosed in parentheses. Since the value produced by the assignment operator is the value assigned to the object, the left operand of the greater-than operator is again the return value of the `get_value` function. In this case, the loop iterates as long as the return value of the `get_value` function is greater than 0. You see that the `foo` function called inside the loop body is sent the value of `val` as an argument. The `foo` function is called with the return value of the `get_value` function.

---

## 🚪 The `break` Statement

The `break` keyword is immediately followed by the terminating token:

    break;

The statement formed in this manner is called the **"break statement."** The `break` statement can be used in the body of a loop statement or a `switch` statement. When a `break` statement is encountered during the execution of a loop statement, the loop is exited, and the program flow continues with the first statement outside the loop body. That is, the loop is exited **unconditionally**.

Examine the following program:

    #include <stdio.h>
    #include <math.h>
    int main ()
    {
        int val;
        while (1) {
            printf("enter a number : ");
            scanf("%d", &val);
            if (val < 0)
                break;
            printf("square root of %d = %lf\n", val, sqrt(val));
        }
        printf("loop exited, program terminating!\n");
        return 0;
    }

An infinite loop is consciously created in the program. In each iteration of the loop, a value is read into the variable named `val` from the keyboard. If a value less than 0 is entered from the keyboard, the loop is exited with the `break` statement.

The `break` statement can only be used in the body of a loop statement or a `switch` statement. The following code snippet is invalid:

    if (x > 100) {
        if (y < 200)
            break; // Invalid use of break outside a loop or switch
        /***/
    }

---

## ⏩ The `continue` Statement

The `continue` keyword is also immediately followed by the terminating token:

    continue;

The statement formed in this manner is called the **"continue statement."**

When the program flow reaches the `continue` statement inside a loop statement, the loop skips to the next iteration, as if the current iteration of the loop has finished.

    int getval(void);
    int isprime(void);
    while (1) {
        val = getval();
        if (val < 0)
            break;
        /* statements */
        if (isprime(val))
            continue;
        /* statements */
    }

In the `main` function above, an infinite loop is created. In each iteration of the loop, the return value of the `getval` function is stored in the `val` variable. If the value assigned to the `val` variable is 0, the loop is exited with the `break` statement. The subsequent `if` statement tests whether the `val` value is prime. If the value assigned to `val` is prime, the rest of the loop is not executed, and the program moves to the next iteration of the loop with the `continue` statement.

The `continue` statement is particularly used to increase readability, especially when there are long `if` statements inside the loop.

    while (k++ < 100) {
        ch = getch();
        if (!isspace(ch)) {
            /* statements */
        }
    }

In the `while` loop written above, the code number of a character is read into the `ch` variable from the keyboard using the `getch` function. It is desired that the statements be executed if the character received from the keyboard is not a whitespace character. The readability of the code snippet above can be increased by using the `continue` statement:

    while (k++ < 100) {
        ch = getch();
        if (isspace(ch))
            continue;
        /* statements */
    }

Some programmers also use the `continue` statement as an alternative to a null statement in the loop body:

    while (i++ < 100)
        continue;

The `continue` statement can only be used in the body of a loop statement. Using the `continue` statement anywhere outside a loop is invalid.

### Common Mistakes

Accidentally making the loop body of the `while` loop statement a null statement is a common mistake:

    #include <stdio.h>
    int main()
    {
        int i = 10;
        while (--i > 0); /* a null statement here */
        printf("%d\n", i);
        return 0;
    }

The loop iterates until the value of the expression inside the `while` parenthesis becomes 0. The `printf` call is not in the body of the loop statement. The terminating token following the `while` parenthesis is considered the statement that forms the loop body. When the loop is exited, the value 0 is printed to the screen.

If a null statement is desired in the body of the `while` loop consciously, not as a mistake, this null statement should be written on the next line, indented by one tab, rather than immediately after the `while` parenthesis, for readability.

Another typical mistake related to the `while` loop statement is forgetting to block the loop body. That is, a simple statement is accidentally used when the loop body should be a compound statement:

    #include <stdio.h>
    int main()
    {
        int i = 1;
        while (i <= 100)
            printf("%d ", i);
        i++; // This statement is outside the loop body!
        return 0;
    }

Suppose it is desired to print numbers from 1 to 100 to the screen with a space between them. In the `while` statement above, the `i++` statement, which increments the loop variable, does not belong to the loop body. In this case, since the expression $i \le 100$ will always be true, an **infinite loop** occurs, and the value 1 is continuously printed to the screen.

Similar to the `if` statement, accidentally using the assignment operator (`=`) instead of the comparison operator (`==`) inside the `while` parenthesis is also a frequent mistake:

    while (x == 5) {
        /***/
    }

A loop like the one above iterates as long as the value of the variable $x$ is 5, while the following statement creates an **infinite loop**:

    while (x = 5) {
        /***/
    }

In each iteration of the loop, the value 5 is assigned to the variable $x$. Since the value produced by the assignment operator, which is 5, is interpreted as "true," the loop iterates continuously.

### Using the Postfix `++` or `--` Operator in the Control Expression

The postfix `++` or `--` operator is often used in the control expression. In such a situation, the decision to continue the loop is made by first looking at the value of the expression, and then the side effect of the increment or decrement operator takes place. Examine the following example:

    #include <stdio.h>
    int main()
    {
        int i = 0;
        while (i++ < 100)
            ;
        printf("\n%d\n", i); // Prints 101 to the screen.
        return 0;
    }

### `while` Loop That Iterates $n$ Times

For $n$ being a positive integer, the following code templates can be used to create a `while` loop that iterates $n$ times:

    while (n-- > 0)
    
    // or
    
    while (n--)

Below is a function named `power` that calculates a specific power of an integer. Examine the function:

    int power(int base, int exp)
    {
        int result = 1;
        while (exp--)
            result *= base;
        return result;
    }

The `while` loop written in the function iterates as many times as the value of the variable `exp`, right? In this case, the `base` variable is multiplied by itself `exp` times.

### Loop Body Being a Null Statement

Sometimes the loop body is consciously made a null statement. For readability, it is recommended that the null statement be written according to the indentation rule like a normal statement in this case. Examine the following program:

    #include <stdio.h>
    #include <ctype.h>
    // #include <conio.h> (Assuming getch() is available)
    int getch_mock() { return getchar(); } // Mock function for standard C environment
    int main()
    {
        int ch;
        printf("Yes or No? [y] [n] : ");
        while ((ch = toupper(getch_mock())) != 'Y' && ch != 'N')
            ;
        if (ch == 'Y')
            printf("you said yes!\n");
        else
            printf("you said no!\n");
        return 0;
    }

The `while` loop written in the `main` function above forces the user to enter one of the characters 'y', 'Y', 'n', or 'N' from the keyboard. Examine the loop carefully. The "logical AND" operator (`&&`) is used in the loop's control expression. Recall that the left operand of the "logical AND" operator is guaranteed to be performed first. The non-standard `getch` function (or `getch_mock` here) reads a character from the keyboard. The sequence number of the received character, i.e., the return value of the `getch` function, is sent as an argument to the standard `toupper` function. Thus, if a lowercase character is entered from the keyboard, it is converted to uppercase. The return value of the `toupper` function is assigned to the `ch` variable. The value of the expression inside the parenthesis is the value assigned to the `ch` variable. The inequality of the entire right side of the "logical AND" operator to the character 'Y' is queried. If the value assigned to the `ch` variable is 'Y', the second part of the "logical AND" operator is not even checked, and the control expression is interpreted as false. The loop is thus exited. If the value assigned to the `ch` variable is 'N', the right operand of the `&&` operator is evaluated, i.e., the inequality of the value of the `ch` variable to the character 'N' is queried. If `ch` is equal to 'N', the control expression is again interpreted as false, and the loop is exited. In all other cases, since the control expression will be interpreted as true, the loop continues to iterate. In other words, exiting the loop is only possible by entering one of the characters 'y', 'Y', 'n', or 'N' from the keyboard.

### Examples Using the `while` Loop Statement

Below is the definition of a function named `num_digit` that returns the number of digits of an integer. Compile and run the program:

    #include <stdio.h>
    int num_digit(int val)
    {
        int digit_counter = 0;
        if (val == 0)
            return 1;
        while (val != 0) {
            digit_counter++;
            val /= 10;
        }
        return digit_counter;
    }
    int main()
    {
        int x;
        printf("enter an integer :");
        scanf("%d", &x);
        printf("the number %d has %d digits!\n", x, num_digit(x));
        return 0;
    }

A very simple algorithm is used to calculate the number of digits. The number is continuously divided by 10 until zero is obtained. In the `num_digit` function, it is first tested whether the value of the parameter variable `val` is 0. If `val` is equal to 0, the value 1 is returned. The number 0 also has 1 digit, right? The subsequent `while` loop iterates with the condition $val \neq 0$. That is, the loop is exited when the value of the variable `val` becomes 0. In each iteration of the loop, the value of the `digit_counter` variable is incremented by 1 inside the body. Then, with the statement `val /= 10;`, the `val` variable is made equal to one-tenth of its value.

Below is a function named `sum_digit` that returns the sum of the digit values of an integer passed to it:

    #include <stdio.h>
    int sum_digit(int val)
    {
        int digit_sum = 0;
        while (val) {
            digit_sum += val % 10;
            val /= 10;
        }
        return digit_sum;
    }
    int main()
    {
        int val;
        printf("enter an integer :");
        scanf("%d", &val);
        printf("the sum of the digits of the number %d is = %d\n", val, sum_digit(val));
        return 0;
    }

In the `sum_digit` function, the parameter variable `val` is again continuously divided by 10 in a loop, and the statements in the loop body are executed until `val` becomes 0. Inside the loop body, with the statement:

    digit_sum += val % 10;

the units digit of the `val` variable is added to the `digit_sum` variable. Thus, after exiting the loop, the `digit_sum` variable holds the sum of the digit values of the number passed from outside.

Below is a function named `get_rev_num` that returns the reverse of an integer passed to it:

    #include <stdio.h>
    int get_rev_num(int val)
    {
        int rev_number = 0;
        while (val) {
            rev_number = rev_number * 10 + val % 10;
            val /= 10;
        }
        return rev_number;
    }
    int main()
    {
        int val;
        printf("enter an integer :");
        scanf("%d", &val);
        printf("the reverse of the number %d is = %d\n", val, get_rev_num(val));
        return 0;
    }

The variable `rev_number` defined in the `get_rev_num` function is initialized to 0. The `while` loop in the function is made to iterate until the value of the parameter variable `val` becomes 0. In each iteration of the loop, the value of the expression:

    rev_number = rev_number * 10 + val % 10

is assigned to the `rev_number` variable.

Suppose the value passed to the function is 1357:

| `rev_number` | `val` |
| :--- | :--- |
| 0 | 1357 |
| 7 | 135 |
| 75 | 13 |
| 753 | 1 |
| 7531 | 0 |

Upon exiting the loop, the value of the `rev_number` variable is 7531.

The following program defines a function named `display_factors` that factorizes an integer and prints the factors to the screen from smallest to largest:

    #include <stdio.h>
    void display_factors(int number)
    {
        int k = 2;
        printf("(%d) -> ", number);
        while (number != 1) {
            while (number % k == 0) {
                printf("%d ", k);
                number /= k;
            }
            ++k;
        }
        printf("\n");
    }

The following program prints the 3-digit numbers that satisfy the equality $abc = a^3 + b^3 + c^3$ to the screen:

    #include <stdio.h>
    int main()
    {
        int k = 100;
        while (k < 1000) {
            int y = k / 100;
            int o = k % 100 / 10;
            int b = k % 10;
            if (y * y * y + o * o * o + b * b * b == k)
                printf("%d\n", k);
            ++k;
        }
        return 0;
    }

Try to find what value the following function calculates:

    int func(int val)
    {
        int sum = 0;
        while (val) {
            sum += val % 10;
            if (sum > 10)
                sum = 1 + sum % 10;
            val /= 10;
        }
        return sum;
    }

---

## 🔁 The `do while` Loop Statement

The general syntax of the `do while` loop statement is as follows:

    do
        statement;
    while (expression);

In the `do while` loop, the control expression is at the end. The terminating token (semicolon) must be found after the `while` parenthesis. That is, the semicolon here is part of the loop statement's syntax. The execution of the `do while` loop is as follows:

The statement following the `do` keyword is executed once upon entering the loop; then, the control expression inside the `while` parenthesis is checked. The statement forming the loop body is executed as long as the control expression is true. What is the difference between the `do while` loop and the `while` loop? In the `while` loop, the statement in the loop body is not guaranteed to be executed at least once. However, in the `do while` loop, since the check is performed at the end, the statement in the body is executed **at least once**.

Compile and run the following program:

    #include <stdio.h>
    int main()
    {
        int val;
        do {
            printf("enter a value between 0 - 100 : ");
            scanf("%d", &val);
        } while (val < 0 || val > 100);
        printf("val = %d\n", val);
        return 0;
    }

In the `main` function, the `do while` loop forces the user to enter a value in the range 0-100. If the entered value is less than 0 or greater than 100, a new value is requested from the user.

The `num_digit` function, previously written using a `while` loop, is now written with a `do while` loop:

    int num_digit(int val)
    {
        int digit_counter = 0;
        do {
            digit_counter++;
            val /= 10;
        } while(val != 0);
        return digit_counter;
    }

The `print_ulam` function defined below prints the Collatz sequence for an integer to the screen:

    #include <stdio.h>
    void print_ulam(int val)
    {
        printf("Collatz sequence for %d\n", val);
        do {
            printf("%d ", val);
            if (val % 2 == 0)
                val /= 2;
            else
                val = val * 3 + 1;
        } while(val > 1);
        printf("%d\n", val);
    }
    int main()
    {
        int x;
        printf("enter a number: ");
        scanf("%d", &x);
        print_ulam(x);
        return 0;
    }

---

## 🔂 The `for` Loop Statement

The general syntax of the `for` loop statement is as follows:

    for (expression1; expression2; expression3)
        statement;

The compiler expects an opening parenthesis after the `for` keyword and two semicolon tokens inside the parenthesis. These two semicolons divide the `for` parenthesis into three parts. Expressions conforming to the definition of an expression can be placed in all three parts.

**Two semicolons must be present inside the `for` parenthesis.** Leaving the `for` parenthesis empty, or having one, three, or more semicolons inside the `for` parenthesis is invalid.

The first statement that follows the closing of the `for` parenthesis forms the **loop body**. The loop body can consist of a simple statement, a compound statement (i.e., multiple statements enclosed in a block), a null statement, or a control statement.

Each of the three expressions inside the `for` parenthesis has a separate function.

The expression forming the second part of the `for` parenthesis is called the **control expression**. Like the expression inside the `while` parenthesis, this expression determines whether the loop continues. If the value of this expression is non-zero, i.e., interpreted as "true," the loop continues. The statement in the loop body is executed. If the value of the control expression is 0, i.e., the expression is interpreted as false, the program flow continues with the execution of the first statement following the `for` loop statement.

When the program flow reaches the `for` statement, the expression in the **first part** of the `for` parenthesis is evaluated. The expression in the first part is typically used to **initialize** the loop variable. However, there is no such requirement.

The expression in the **third part** of the `for` parenthesis is evaluated after the statement(s) in the loop body have been executed and before the control expression is checked again. This part is mostly used for **incrementing or decrementing** a loop variable.

Examine the following program:

    #include <stdio.h>
    int main()
    {
        int i;
        for (i = 0; i < 2; ++i)
            printf("%d ", i);
        printf("\nlast value = %d\n", i);
        return 0;
    }

When the program flow reaches the `for` loop statement, the first expression inside the `for` parenthesis is evaluated first. That is, the value 0 is assigned to the variable `i`.

Now the program flow moves to the second part of the `for` parenthesis, the control expression, and the condition $i < 2$ is checked. Since the value of the control expression is non-zero, the expression is accepted as logically true. The program flow thus moves to the loop body. You see that the loop body is formed by a simple statement. This statement is executed. That is, the value of the variable `i` is printed to the screen, and the cursor moves to the next line.

The program flow then moves to the third part of the `for` parenthesis, and the expression here is evaluated. That is, the value of the variable $i$ is incremented by 1, and the value of the variable $i$ becomes 1.

The second expression is evaluated again, and since the expression $i < 2$ is true, the statement in the loop body is executed one more time.

The program flow again moves to the third part of the `for` parenthesis, and the expression here is evaluated. That is, the value of the variable $i$ is incremented by 1. The value of the variable $i$ becomes 2.

The program flow again moves to the second part of the `for` parenthesis. The control expression is checked again. Since the expression $i < 2$ is false this time, the program flow does not enter the loop body but continues with the first statement following the loop body. That is, the following is printed to the screen:

    last value = 2

### Loop Variables

There is no requirement to use a loop variable in the `for` loop. For example, the following loop fully conforms to the rules:

    for (func1(); func2(); func3())
        func4();

With the `for` loop statement above, the `func1` function is called upon entering the loop. The statement in the loop body is executed, meaning the `func4` function is called, as long as the `func2` function returns a non-zero value. After the `func4` function is called, and before the control expression is checked again, the `func3` function is called this time.

The following `for` loop statement prints the character received from the keyboard as long as the character 'x' is not entered:

    #include <stdio.h>
    // #include <conio.h> (Assuming getch() is available)
    int getch_mock() { return getchar(); } // Mock function for standard C environment
    int main()
    {
        char ch;
        for (ch = getch_mock(); ch != 'x' ; ch = getch_mock())
            putchar(ch);
        return 0;
    }

There is no requirement for the loop variable to be one of the integer types. The loop variable can also be one of the real number types:

    #include <stdio.h>
    int main()
    {
        double i;
        for (i = 0.1; i < 6.28; i += 0.01)
            printf("%lf ", i);
        return 0;
    }

In the loop above, a `double` type loop variable is chosen. In the first part of the `for` parenthesis, the value 0.1 is assigned to the loop variable. In the third part of the parenthesis, the loop variable is incremented by 0.01. The loop iterates under the condition that the value of the variable $i$ is less than 6.28.

### Omission of Expressions inside the `for` Parenthesis

The first part of the `for` loop statement parenthesis may not contain an expression. This is fully compliant with the rules. Suppose it is desired to print numbers from 1 to 100. The initialization of the loop variable can be moved outside the `for` loop, from the first part of the `for` parenthesis:

    #include <stdio.h>
    int main()
    {
        int i = 0;
        for (; i < 100; ++i)
            printf("%d ", i);
        return 0;
    }

The third part of the `for` loop parenthesis may also not contain an expression. The increment or decrement of the loop variable can be performed in the loop body instead of inside the `for` parenthesis:

    #include <stdio.h>
    int main()
    {
        int i = 0;
        for (; i < 100;) {
            printf("%d ", i);
            i++;
        }
        return 0;
    }

`for` loops without the first and third expressions are completely equivalent to `while` loops. Any code that can be written with a `while` loop can also be written with a `for` loop. The `while` loop is a better option for `for` loops without the first and third parts in terms of readability.

The second expression of the `for` parenthesis may also be completely absent. In this case, since there will be no control expression, the loop iterates continuously, independent of a condition. That is, an **infinite loop** is created. However, the two semicolons must still be present inside the parenthesis. The same task is now performed using a conscious infinite loop:

Most C programmers prefer the pattern **`for (;;)`** when they want to consciously create an infinite loop. This pattern is equivalent to the pattern **`while (1)`**. Both indicate an infinite loop. The `for (;;)` form is preferred over the `while (1)` form for creating an infinite loop.

    #include <stdio.h>
    int main()
    {
        int i = 0;
        for (;;) {
            if (i == 100)
                break;
            printf("%d ", i);
            i++;
        }
        return 0;
    }

Now, try to estimate what will be printed to the screen by the execution of the following loop statement:

    #include <stdio.h>
    int main()
    {
        double d;
        for (d = 1.5; d < 3,0; d += 0.1)
            printf("%lf ", d);
        return 0;
    }

Nothing is printed to the screen! You see that the loop's control expression is `d < 3,0`. A comma character was accidentally used instead of a period when writing the floating-point literal. In this case, the value produced by the comma operator is the value of the second operand, which is 0. The control expression is interpreted as false, so the statement in the loop body is never executed.

### `for` Loops That Iterate $n$ Times

For $n$ being a positive integer, all of the following loops iterate $n$ times:

    for (i = 0; i < n; ++i)
    for (i = 1; i <= n; ++i)
    for (i = n - 1; i >= 0; --i)
    for (i = n; i > 0; --i)

### Use of the `continue` Statement in `for` Loops

With the use of the `continue` statement inside the body of a loop, the remaining statements in the body are skipped, and the loop moves to the next iteration. When a `continue` statement is encountered inside the body of a `for` loop, the program flow moves to the third expression of the `for` parenthesis, and this expression is evaluated.

### Using the Loop Variable as a Flag

In some applications, the loop variable of the `for` loop also acts as a flag. Suppose it is necessary to exit a `for` loop when a certain condition occurs:

    for (i = 0; i < 100; ++i)
        if (is_valid(i))
            break;

As a result of running the loop statement above, two different situations are possible. If the `break` statement is executed in the loop body, i.e., if the `is_valid` function returns a non-zero value for any value of $i$, the value of the variable $i$ upon loop exit will be less than 100. If the loop completes all its iterations without the `break` statement being executed, the value of the variable $i$ upon loop exit will be 100.

By checking whether the value of $i$ is 100 upon loop exit, it can be understood how the loop was exited.

### Examples of `for` Loop Statement Usage

The following program defines functions named `okek` (LCM) and `obeb` (GCD) that calculate the greatest common divisor and the least common multiple of two numbers:

    #include <stdio.h>
    int obeb(int number1, int number2)
    {
        int i;
        int min = (number1 < number2) ? number1 : number2;
        for (i = min; i >= 1; --i)
            if (number1 % i == 0 && number2 % i == 0)
                return i;
        return 1;
    }
    int okek(int number1, int number2)
    {
        int i;
        int max = (number1 > number2) ? number1 : number2;
        for (i = max; i <= number1 * number2; i += max)
            if (i % number1 == 0 && i % number2 == 0)
                return i;
        return number1 * number2;
    }
    int main()
    {
        int x, y;
        int n = 5;
        while (n--) {
            printf("enter two integers : ");
            scanf("%d%d", &x, &y);
            printf("gcd = %d\n", obeb(x, y));
            printf("lcm = %d\n", okek(x, y));
        }
        return 0;
    }

The function defined below finds the greatest common divisor using the Euclidean algorithm:

    int obeb(int a, int b)
    {
        int temp;
        while (b) {
            temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

The following program writes a function named `fact` that calculates the factorial value for an integer. The program should be compiled on a system where the `int` type is 4 bytes:

    #include <stdio.h>
    int fact(int number)
    {
        int i;
        int result = 1;
        if (number == 0 || number == 1)
            return 1;
        for (i = 2; i <= number; ++i)
            result *= i;
        return result;
    }
    int main()
    {
        int k;
        for (k = 0; k < 14; ++k)
            printf("%2d! = %-10d\n", k, fact(k));
        return 0;
    }

The number $e$ is found below using a series summation with the `fact` function:

    #include <stdio.h>
    int fact(int);
    int main()
    {
        int k;
        double e = 0.;
        for (k = 0; k < 14; ++k)
            e += 1. / fact(k);
        printf("e = %lf\n", e);
        return 0;
    }

The following program writes a function named `isprime` that tests whether an integer passed to it is prime. The function returns a non-zero value if the number passed to it is prime, and 0 if it is not prime. In the `main` function written for testing purposes, the `isprime` function is called, and prime numbers less than 1000 are printed to the screen:

    #include <stdio.h>
    int isprime(int number)
    {
        int k;
        if (number == 0 || number == 1)
            return 0;
        if (number % 2 == 0)
            return number == 2;
        if (number % 3 == 0)
            return number == 3;
        if (number % 5 == 0)
            return number == 5;
        for (k = 7; k * k <= number; k += 2)
            if (number % k == 0)
                return 0;
        return 1;
    }
    int main()
    {
        int k;
        int prime_counter = 0;
        for (k = 0; k < 1000; ++k)
            if (isprime(k)) {
                if (prime_counter % 10 == 0 && prime_counter)
                    putchar('\n');
                prime_counter++;
                printf("%3d ", k);
            }
        return 0;
    }

An integer that is equal to the sum of its divisors is called a **perfect integer**. For example, 6 and 28 are perfect integers.
$1 + 2 + 3 = 6$
$1 + 2 + 4 + 7 + 14 = 28$
The following program searches for perfect numbers less than 10000. The found numbers are printed to the screen:

    #include <stdio.h>
    int is_perfect(int number);
    int main()
    {
        int k;
        for (k = 2; k < 10000; ++k)
            if (is_perfect(k))
                printf("%d perfect\n", k);
        return 0;
    }
    int is_perfect(int number)
    {
        int i;
        int total = 1;
        for (i = 2; i <= number / 2; ++i)
            if (number % i == 0)
                total += i;
        return number == total;
    }

The following program ensures that characters are continuously read from the keyboard, and the read characters are displayed on the screen. The program terminates when the characters "xyz" are entered consecutively:

    #include <stdio.h>
    // #include <conio.h> (Assuming getch() is available)
    int getch_mock() { return getchar(); } // Mock function for standard C environment
    int main()
    {
        char ch;
        int total = 0;
        while (total < 3) {
            ch = getch_mock();
            putchar(ch);
            if (ch == 'x' && total == 0)
                total++;
            else if (ch == 'y' && total == 1)
                total++;
            else if (ch == 'z' && total == 2)
                total++;
            else total = 0;
        }
        return 0;
    }

### 🔄 Nested Loops

A loop statement can form the body of another loop. Loops created in this manner are called **nested loops**. Compile and run the following program:

    #include <stdio.h>
    int main()
    {
        int i, k;
        for (i = 0; i < 5; ++i)
            for (k = 0; k < 10; ++k)
                printf("(%d %d) ", i, k);
        printf("\n\n(%d %d) ", i, k);
        return 0;
    }

The statement in the body of the outer `for` loop is another `for` loop. The inner `for` loop statement is executed as long as the expression $i < 5$ is true. What values does the last `printf` call print to the screen? Since the outer loop iterates with the condition $i < 5$, the value of the variable $i$ after exiting the outer loop is 5. After the inner `for` loop statement is executed for the last time, the value of the variable $k$ also becomes 10. In this case, the very last `printf` call prints **(5 10)** to the screen.

Now, try to find out what the `put_stars` function, whose code is given below, does:

    #include <stdio.h>
    void put_stars(int n)
    {
        int i, k;
        for (i = 1; i <= n; ++i) {
            for (k = 1; k <= i; ++k)
                putchar('*');
            putchar('\n');
        }
    }
    int main()
    {
        int val;
        printf("enter a value : ");
        scanf("%d", &val);
        put_stars(val);
        return 0;
    }

The following program prints the 3-digit numbers that satisfy the equality $abc = a^3 + b^3 + c^3$ to the screen.

    #include <stdio.h>
    int main()
    {
        int i, j, k;
        int number = 100;
        for (i = 1; i <= 9; ++i)
            for (j = 0; j <= 9; ++j)
                for (k = 0; k <= 9; ++k) {
                    if (i * i * i + j * j * j + k * k * k == number)
                        printf("%d\n", number);
                    number++;
                }
        return 0;
    }

### Use of the `break` Statement in Nested Loops

Care must be taken when using the `break` statement in nested loops. Using the `break` statement in the body of an inner loop only exits the **innermost** loop: Examine the following example:

    while (1) {
        while (1) {
            if (expression)
                break;
            /***/
        }
        /* flow comes to this point when inner loop is exited with break */
    }

If it is desired to exit all nested loops, not just the innermost one, the **`goto`** control statement should be used. You will see this topic in the section on the `goto` control statement.

Since the second `while` loop here will be treated as a single control statement, blocking (braces) is not necessary.

### Ways to Exit Loops

How can a loop be exited? One of the following ways can be used to exit a loop.

1.  **By the control expression being false:**
    You know that loop statements iterate as long as their control expressions are true.
2.  **With the `return` statement:**
    Since the `return` statement inside a function terminates the function, the loop is exited when a `return` statement is encountered inside a loop statement.
3.  **With the `break` statement:**
    With the use of the `break` statement, the program flow continues with the first statement following the loop statement.
4.  **With the `goto` statement:**
    The `goto` statement can redirect the program flow within the same function to another point outside the loop. Thus, the loop can be exited.
5.  **With a function call that terminates the program:**
    The program itself can be terminated with the standard `exit` or `abort` functions.

Assigning a value to the loop variable in an unnatural way to make the control expression false for the purpose of exiting a loop impairs program readability. Such code should be avoided.