# 🚦 The `if` Statement

The most important statement for controlling program flow in the C language is the `if` statement.

In its simplest form, the general syntax of the `if` statement is as follows:

    if (expression)
        statement;

The expression inside the `if` parenthesis is called the **conditional expression**.

The statement following the `if` parenthesis is called the **true path** of the `if` statement.

The statement that forms the true path of the `if` statement can be a simple statement, a null statement, a compound statement, or another control statement.

The execution of the simple `if` statement is as follows:
First, the numerical value of the conditional expression is calculated. The calculated numerical value is interpreted as logical **TRUE** or **FALSE**. If the calculated value of the conditional expression is 0, it is interpreted as false; if it is any non-zero value, it is interpreted as true. For example, let's assume the calculated value of the conditional expression is $-5$. In this case, the control expression is evaluated as true. If the expression is interpreted as **TRUE**, the true path of the `if` statement is executed; if the expression is interpreted as **FALSE**, the true path is not executed. The simple `if` statement is based on the execution or non-execution of a statement according to the truth or falsity of an expression.

Compile and run the following program:

    int main()
    {
        int x;
        printf("enter a number : ");
        scanf("%d", &x);
        if (x > 10)
            printf("the true path of the if statement!\n");
    }
    return 0;

With the `if` statement written in the `main` function, the `printf` call is executed if the integer entered from the keyboard is greater than 10; otherwise, it is not executed.

---

## ⛔ The `if` Statement with a False Path (`if-else`)

The `if` control statement can also include the `else` keyword. Such an `if` statement is called an `if` statement with a false path. The general form of the `if` statement with a false path is as follows:

    if (expression)
        statement1;
    else
        statement2;

This time you see the `else` keyword after the statement following the true path of the `if` statement, followed by another statement. The `statement2` in the general form is called the **false path** of the `if` statement.

The conditional expression of the `if` statement is interpreted as logically **TRUE** or **FALSE**. This time, if the conditional expression is **TRUE**, `statement1` is executed; if it is interpreted as **FALSE**, `statement2` is executed. The `if` statement with a false path aims at executing one of two separate statements depending on whether a conditional expression is true or false. That is, if the expression is true, one task is performed; if false, another task is performed.

Examine the following example:

    #include <stdio.h>
    int main()
    {
        char ch;
        printf("enter a character : ");
        ch = getchar();
        if (ch >= 'a' && ch <= 'z')
            printf("%c is a lowercase letter!\n", ch);
        else
            printf("%c is not a lowercase letter!\n", ch);
    }
    return 0;

In the `main` function above, a character is retrieved from the keyboard using the standard `getchar` function. The sequence number of the retrieved character is assigned to the variable named `ch`. Information on whether the character entered from the keyboard is a lowercase letter is printed to the screen, depending on whether the conditional expression is true or false. Let's look at the conditional expression:

    ch >= 'a' && ch <= 'z'

For this expression to be true, both terms of the **"logical AND (`&&`)"** operator must be true. This is only possible if the character `ch` is a lowercase letter character.

The true and/or false path of an `if` statement can be a **compound statement** (a block). In this case, more than one simple statement can be executed depending on whether the conditional expression is true or false. Examine the following example:

    /***/
    if (x > 0) {
        y = x * 2 + 3;
        z = func(y);
        result = z + x;
    }
    else {
        y = x * 5 - 2;
        z = func(y - 2);
        result = z + x - y;
    }
    /***/

In the `if` statement above, the value of the `result` variable is calculated by different operations depending on whether the expression $x > 0$ is true or false. Both the true and false paths of the `if` statement are formed by compound statements.

An `if` statement does not have to have a false path. However, an `if` statement cannot have only an `else` part. In this case, a null statement or an empty compound statement must be placed in the true path of the `if` statement:

    if (expression)
        ;
    else
        statement1;

or

    if (expression)
    { }
    else
        statement1;

An `if` statement that only has a false path, with an empty true path, is not a good option in terms of readability. In such cases, a better technique is to take the logical inverse of the conditional expression and eliminate the false path of the `if` statement:

    if (!expression)
        statement1;

Examine the following code snippet:

    /***/
    if (x > 5)
        ;
    else {
        func1(x);
        func2(x);
    }
    /***/

In the `if` statement above, if the value of the variable $x$ is greater than 5, nothing is done; otherwise, the functions `func1` and `func2` are called with the value of the variable $x$. If the conditional expression is inverted and the `if` statement is rewritten:

    /***/
    if (x <= 5) {
        func1(x);
        func2(x);
    }
    /***/

Any expression conforming to the definition of an expression can be found inside the `if` parenthesis:

    if (10)
        statement1;
    if (-1)
        statement2;

The value of the conditional expressions above is always interpreted as true, because the expressions have a non-zero value.

The following conditional expression, however, will always be interpreted as false, so the true path of the `if` statement will never be executed:

    if (0)
        statement1;

In the following `if` statement, `statement1` and `statement2` are executed depending on whether the value of the variable $x$ is non-zero or zero:

    if (x) {
        statement1;
        statement2;
        /***/
    }

The structure above is equivalent to the following structure:

    if (x != 0) {
        statement1;
        statement2;
    }

Examine the following example:

    if (!x) {
        statement1;
        statement2;
    }

In this `if` statement, `statement1` and `statement2` are executed only if the value of the variable $x$ is 0.

Again, the structure above is equivalent to the following structure:

    if (x == 0) {
        statement1;
        statement2;
    }

---

## 📝 Using the Assignment Operator in the Conditional Expression

The assignment operator is often used in the conditional expression of the `if` statement. Thus, the value produced by the assignment operator is utilized. Examine the following code snippet:

    if ((x = getval()) > 5)
        func1(x);
    else
        func2(x);

In the conditional expression of the `if` statement, the return value of the called `getval` function is assigned to the variable $x$. Recall that the value produced by the assignment operator is the value assigned to the object. You see that the expression formed by the assignment operator is enclosed in parentheses. In this case, the return value of the `getval` function is both assigned to the variable $x$ and checked whether it is greater than 5. If parentheses had not been used, the value 0 or 1 would have been assigned to $x$ depending on whether the return value of the `getval` function was greater than 5. In that case, either the `func1` function would be called with the value 1 or the `func2` function would be called with the value 0. The statement could have been written as follows, couldn't it?

    x = getval();
    if (x > 5)
        func1(x);
    else
        func2(x);

However, the idiomatic code provides convenience in writing more complex statements. Consider how the following `if` statement will be executed. Recall that the pre-evaluation, or **"short-circuiting,"** behavior of the first part of the "logical AND" operator is guaranteed.

    if ((y = getval()) > 5 && isprime(x))
        func1(y);
    func2(y);

---

## 🧩 Nested `if` Statements

The true or false path of an `if` statement can also be another `if` statement:

    if (expression1)
        if (expression2) {
            statement1;
            statement2;
            statement3;
        }
        statement4;

In this example, the second `if` statement forms the true path of the first `if` statement. The first and second `if` statements do not have false paths.

In nested `if` statements, the `else` keyword that follows the last `if` keyword belongs to the **innermost** `if` statement:

    if (expression1)
        if (expression2)
            statement1;
        else
            statement2;

In the example above, even though the visual formatting might suggest the `else` part belongs to the first `if` statement, the `else` part belongs to the second, innermost `if` statement (**dangling else**).

If it is desired that the `else` keyword belongs to the first `if` statement, the true path of the first `if` statement must be blocked (enclosed in braces):

    if (expression1) {
        if (expression2)
            statement1;
    }
    else
        statement2;

In the example above, the `else` part belongs to the first `if` statement.

    if (expression1) {
        if (expression2)
            statement1;
        else {
            statement2;
            statement3;
        }
        statement4;
    }
    else
        statement5;

In the example above, since the true path of the first `if` statement consists of more than one statement—one of which is another `if` statement—blocking (braces) is used. `statement5` forms the false path of the first `if` statement.

---

## 🪜 The `else if` Ladder

Examine the following `if` statements:

If the other comparisons are not true when a comparison results in true, such comparisons are called **disjoint comparisons**. In disjoint comparisons, using separate `if` statements is poor technique:

    if (m == 1)
        printf("January\n");
    if (m == 2)
        printf("February\n");
    if (m == 3)
        printf("March\n");
    /***/
    if (m == 12)
        printf("December\n");

In the example above, suppose the value of the variable $m$ is 1. In this case, the text "January" is printed to the screen. However, the subsequent `if` statements separately test whether the variable $m$ is equal to 2, 3, ... 12 in turn. But since the variable $x$ has the value 1, it is clear that the control expressions within all other `if` statements will be evaluated as false. In this case, all `if` statements after the first `if` statement are unnecessarily executed. At the same time, the readability of the code is also impaired.

In disjoint comparisons, **`else if` ladders** should be used:

    if (expression1)
        statement1;
    else
        if (expression2)
            statement2;
        else
            if (expression3)
                statement3;
            else
                if (expression4)
                    statement4;
                else
                    statement5;

In this structure, if the conditional expression of any `if` statement is evaluated as true, the program flow never proceeds to another `if` statement. This structure is called an **else if ladder (cascaded if)**. Since writing the `else if` ladder in the form above impairs readability, especially in long `else if` ladders, the following writing style should be preferred for readability:

    if (expression1)
        statement1;
    else if (expression2)
        statement2;
    else if (expression3)
        statement3;
    else if (expression4)
        statement4;
    else
        statement5;

The false path of the `if` statement at the very end of the ladder has a special importance. In the example above, `statement5` is in the `else` part of the last `if` statement. If the conditional expression of none of the `if` statements in the ladder is true, the false path of the last `if` statement is executed, right? As a result of the execution of the ladder above, one of `statement1`, `statement2`, `statement3`, `statement4`, or `statement5` is definitely executed.

An `else if` ladder without a false path for the last `if` statement can be exited without any action being performed.

In terms of both readability and efficiency, conditions with higher probability or frequency in the `else if` ladder should be placed higher up.

---

## ⚠️ Common Mistakes

One common mistake, especially made by C beginners, is confusing the simple `if` statement with the `if` statement with a false path. That is, the false path of the `if` statement is forgotten:

    #include <stdio.h>
    int main()
    {
        int x;
        printf("enter a number: ");
        scanf("%d", &x);
        if (x % 2 == 0)
            printf("%d is an even number!\n", x);
        printf("%d is an odd number!\n", x);
    }
    return 0;

If the expression inside the `if` parenthesis is false, there is no error. But what is printed to the screen if the expression is true? Suppose the value 28 is entered from the keyboard:

    28 is an even number!
    28 is an odd number!

Perhaps the most common mistake is accidentally placing the terminating token (`;`) at the end of the `if` parenthesis. Examine the following `main` function:

    #include <stdio.h>
    int main()
    {
        int x;
        printf("enter a number: ");
        scanf("%d", &x);
        if (x % 2 == 0);
            printf("%d is an even number!\n", x);
    }
    return 0;

In the `main` function above, the `printf` function is called regardless of whether the expression $x \% 2 == 0$ is true or false. The `printf` call is outside the `if` statement. It is absolutely compliant with the syntax rules for a null statement to form the true path of the `if` statement. The written `if` statement actually means **"do nothing if x is even."** Most compilers do not issue a logical warning message for this situation, which is unlikely to be written consciously.

If the same mistake were made in the true path of an `if` statement with a false path, a syntax error would occur, right?

    if (x > 5);
        printf("true!\n");
    else
        printf("false\n");

You know that the `else` keyword must be used in conjunction with an `if` statement. The `if` statement in the code snippet above is an `if` statement whose true path means "do nothing." Therefore, the `else` keyword is not attached to any `if` statement. This is a syntax error, because there cannot be an `else` that is not attached to an `if` statement.

Of course, a null statement can form the true or false path of an `if` statement. In this case, for readability, writing this null statement indented one tab gives a strong impression that the null statement was placed consciously.

    if ((val = getval()) != 0)
        ;

Another frequent mistake is using the **assignment operator (`=`)** instead of the **comparison operator (`==`)** inside the `if` parenthesis.

    /***/
    if (x == 5)
        printf("equal\n");
    /***/

In the `if` statement above, the `printf` function is called if the value of the variable $x$ is equal to 5. The comparison operator has no side effect. That is, the value of the variable $x$ is only compared with the constant 5 inside the `if` parenthesis above; it is not changed. However, if the assignment operator is accidentally used instead of the comparison operator:

    /***/
    if (x = 5)
        printf("equal\n");
    /***/

The assignment operator produces the value of the expression on its right side. The value of the expression inside the `if` parenthesis is calculated as 5. Since 5 is a non-zero value, the `printf` function is called regardless of the value of the variable $x$. Since the assignment operator has a side effect, the value 5 is also assigned to the variable $x$ upon execution of the `if` statement.

Most C compilers view the situation with suspicion and issue a logical warning message if the expression inside the `if` parenthesis is a simple assignment expression. For example, a typical warning message in Borland compilers is:

    warning : possibly incorrect assignment!

However, the assignment operator can also be used consciously inside the `if` parenthesis:

    if (x = func())
        m = 20;

In conscious use, the expression can be structured as follows to suppress the compiler's logical warning message:

    if ((x = func()) != 0)
        m = 20;

As in the example above, if the value produced by the assignment operator is explicitly made a term in a comparison operation, compilers do not issue a "logical warning" message in this case.

Another common mistake is forgetting to block the true or false path of the `if` statement. That is, a simple statement is accidentally written instead of a compound statement.

    if (x == 10)
        m = 12;
    k = 15;

In the `if` statement above, only the statement:

    m = 12;

forms the true path of the `if` statement.

    k = 15;

is outside the `if` statement. This situation usually occurs because the programmer first creates the true or false path of the `if` statement with a simple statement, and then forgets to block when adding a second simple statement to the true or false path.

It is also clear from the writing style of the code that the true path of the `if` statement was accidentally not blocked. The correct way should have been:

    if (x == 10) {
        m = 12;
        k = 15;
    }

The following `if` statement is invalid because it again uses an `else` keyword that is not matched with an `if` keyword:

    if ( x == 10)
        m = 12;
    k = 15;
    else /* Invalid */
        y = 20;

Because you know that an `else` must be attached to an `if` statement.

To avoid such mistakes, some programmers write the simple statement as a compound statement, even if the true or false path of the `if` statement consists of a simple statement:

    if (x > 10) {
        y = 12;
    }
    else {
        k = 5;
    }

In the example above, no syntax error or mistake occurs if another simple statement is added to the true or false path of the `if` statement. However, avoiding unnecessary blocking is better for readability.

Consider the case where it is desired to test if a value is within a certain range inside the `if` parenthesis:

    if (10 < x < 20)
        func();

In the `if` statement above, it is intended to call the `func` function if the variable $x$ is between the values 10 and 20. However, the expression inside the `if` parenthesis is always true. That is, the `func` function call is always executed. Since the less-than operator (`<`) has left-to-right associativity, the leftmost less-than operator is evaluated first. You know that the value produced by the operator is 1 or 0. The produced value of 1 or 0 becomes the operand of the rightmost less-than operator. Since the value 20 is greater than 1 or 0, the expression is always true.

Another dangerous mistake is forgetting the function call operator (parentheses) when the expression inside the `if` parenthesis is a function call expression:

Instead of:

    if (func())
        m = 12;

Suppose:

    if (func)
        m = 12;

is written. This does not result in a syntax error. In this case, the true path of the `if` statement is always executed. In the C language, a function name is treated as an address information equivalent to the function's code location in memory. Since this address information is always a non-zero value, the conditional expression is always evaluated as true.

---

## ✅ Testing Functions (Predicate Functions)

Since the `bool` data type is not one of C's native data types (historically), testing functions, i.e., functions that answer a question, written in the C language often return the `int` type.

> \[The `bool` type was also added as a native data type with C99 standards. According to C99 standards, the `_Bool` keyword was added to the C language.]

For example, let's assume a function is written to test whether an integer is a prime number. The function's signature would be:

    int isprime(int val);

The widely used convention for the return values of testing functions is as follows: If the function answers the question posed as true or positive, it returns any non-zero value. If the result of the question or test is negative or false, the function returns the value 0. This simplifies the job of the code snippet calling the testing function, allowing idiomatic code to be written like this:

If a task is to be performed when the test result is positive:

    if (isprime(val))
        statement;

If a task is to be performed when the test result is negative:

    if (!isprime(val))
        statement;

can be written.

Examine the following program:

    #include <stdio.h>
    #include <ctype.h>
    int main()
    {
        int ch;
        printf("enter a character : ");
        ch = getchar();
        if (isupper(ch))
            printf("%c is an uppercase letter!\n", ch);
        else
            printf("%c is not an uppercase letter!\n", ch);
    }
    return 0;

`isupper` is a standard function that tests whether the character whose code number is passed to it is an uppercase letter character. If the character whose code number is passed is an uppercase letter, the function returns a non-zero value. If it is not an uppercase letter, the function's return value is 0. In this case, the conditional expression of the `if` statement in the `main` function means "if ch is an uppercase letter," right? If the conditional expression were written as:

    if (!isupper(ch))

this would mean "if ch is not an uppercase letter."

Below, a function named `isleap` is defined, which tests whether a year is a leap year. Years that are exactly divisible by 4, but not by 100, or that are exactly divisible by 400, are leap years:

    #include <stdio.h>
    int isleap(int y)
    {
        return y % 4 == 0 && (y % 100 != 0 || y % 400 == 0);
    }
    int main()
    {
        int year;
        printf("enter a year: ");
        scanf("%d", &year);
        if (isleap(year))
            printf("%d is a leap year!\n", year);
        else
            printf("%d is not a leap year!\n", year);
        return 0;
    }

---

## 🔡 Standard Character Testing Functions

Character testing functions are functions that allow information about characters to be obtained. In most compilers, these functions are also defined as macros within the `ctype.h` header file. Therefore, the `ctype.h` file must be included in the source code before character testing functions are called. Character testing functions are valid for the first half of the ASCII character set. That is, their return values are not reliable when used for Turkish characters. Correctly running character testing functions for Turkish-specific characters (`ç`, `ğ`, `ı`, `ö`, `ş`, `ü`, `Ç`, `Ğ`, `I`, `Ö`, `Ş`, `Ü`) is a matter of **localization**. This topic will be addressed in later sections.

Below is a table listing the standard character testing functions:

| Function | Return Value |
| :--- | :--- |
| `isalpha` | True if an alphabetic character, false otherwise. |
| `isupper` | True if an uppercase letter, false otherwise. |
| `islower` | True if a lowercase letter, false otherwise. |
| `isdigit` | True if a digit character, false otherwise. |
| `isxdigit` | True if a character representing one of the hexadecimal digits (0123456789ABCDEFabcdef), false otherwise. |
| `isalnum` | True if an alphabetic or digit character, false otherwise. |
| `isspace` | True if one of the whitespace characters (space, carriage return, new line, vertical tab, form feed), false otherwise. |
| `ispunct` | True if one of the punctuation characters, i.e., a character outside of control characters, alphanumeric characters, and whitespace characters, false otherwise. |
| `isprint` | True if a printable character (including the space character), false otherwise. |
| `isgraph` | True if a visible character (excluding the space character), false otherwise. |
| `iscntrl` | True if a control character or delete character (first 32 characters of ASCII set or character number 127), false otherwise. |

Let's try to write some of these functions ourselves:

### `islower` Function

`islower` is a standard function that tests whether the character whose code number is passed to it is a lowercase letter character. If the character is a lowercase letter, the function returns a non-zero value, i.e., a logical "true" value. If it is not a lowercase letter, the function's return value is zero. This function can be written as follows:

    #include <stdio.h>
    int islower (int ch)
    {
        return ch >= 'a' && ch <= 'z';
    }
    int main()
    {
        char ch;
        printf("enter a character: ");
        ch = getchar();
        if (islower(ch))
            printf("lowercase letter\n");
        else
            printf("not a lowercase letter\n");
        return 0;
    }

In the `islower` function written above, it is first tested whether the parameter variable is a lowercase letter:

    ch >= 'a' && ch <= 'z';

In a character code where lowercase letters are placed consecutively, the value of the expression above is true only if the value of the variable `ch` is the sequence number of a lowercase letter.

### `isalpha` Function

`isalpha` is also a standard function. If the character whose code number is passed to its parameter is an alphabetic character, i.e., an uppercase or lowercase letter, the function returns a non-zero value; if it is not an alphabetic character, it returns a zero value.

    int isalpha (int ch)
    {
        return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
    }

### `isdigit` Function

`isdigit` is a standard function. If the character whose code number is passed to its parameter is a digit character, the function returns a non-zero value; if it is not a digit character, it returns a zero value:

    int isdigit (int ch)
    {
        return (ch >= '0' && ch <= '9');
    }

### `isalnum` Function

`isalnum` is also a standard function. If the character whose code number is passed to its parameter is an alphabetic character or a digit character, it returns a non-zero value; otherwise, it returns a zero value. This function is written in two separate forms below:

    #include <ctype.h>
    int isalnum1(int ch)
    {
        return ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z'
            || ch >= '0' && ch <= '9';
    }
    int isalnum2(int ch)
    {
        return isalpha(ch) || isdigit(ch);
    }

### `isxdigit` Function

`isxdigit` is a standard function that tests whether a character is a symbol for a digit in the hexadecimal number system. If the character is one of `0123456789ABCDEFabcdef`, the function returns a non-zero value; if it is not one of these characters, it returns a zero value.

    int isxdigit (int ch)
    {
        return ch >= '0' && ch <= '9' || ch >= 'A' && ch <= 'F'
            || ch >= 'a' && ch <= 'f';
    }

---

## 🔀 Standard Character Conversion Functions

Converting from lowercase to uppercase or from uppercase to lowercase is a frequently needed operation. The standard `toupper` and `tolower` functions are used for this purpose.

### `tolower` Function

`tolower` is a standard C function. If the character whose code number is passed to its parameter is an uppercase letter, it returns the code number of its lowercase counterpart. If the code number of a non-uppercase character is passed to the `tolower` function, the function returns the same value. This function is defined below:

    #include <stdio.h>
    int tolower (int ch)
    {
        if (ch >= 'A' && ch <= 'Z')
            return ch - 'A' + 'a';
        return ch;
    }
    int main()
    {
        char ch;
        printf("enter a character :");
        ch = getchar();
        printf("%c\n", tolower(ch));
    }
    return 0;

### `toupper` Function

`toupper` is a standard C function. If the character whose sequence number is passed to its parameter is a lowercase letter, it returns the sequence number of its uppercase counterpart. If the sequence number of a non-lowercase character is passed to the `toupper` function, the function returns the same value. The function is defined below:

    int toupper(int ch)
    {
        if (ch >= 'a' && ch <= 'z')
            return ch - 'a' + 'A';
        return ch;
    }

---

## 💻 Example Programs Using the `if` Statement

Below are the functions `get_max2`, which returns the larger of two numbers, and `get_max3`, which returns the largest of three numbers:

    int get_max2(int a, int b)
    {
        if (a > b)
            return a;
        return b;
    }
    int get_max3(int a, int b, int c)
    {
        int max = a;
        if (b > max)
            max = b;
        if (c > max)
            max = c;
        return max;
    }
    #include <stdio.h>
    int main()
    {
        int x, y, z;
        printf("enter two numbers : ");
        scanf("%d%d", &x, &y);
        printf("the larger of %d and %d is = %d\n", x, y, get_max2(x, y));
        printf("enter three numbers : ");
        scanf("%d%d%d", &x, &y, &z);
        printf("the largest of %d %d and %d is = %d\n",x, y, z,
            get_max3(x, y, z));
        return 0;
    }

The following program defines a function named `get_hex_char`. The function returns the sequence number of the character symbol in the hexadecimal number system for an integer between 0 and 15 passed to it.

    #include <stdio.h>
    int get_hex_char(int number)
    {
        if (number >= 0 && number <= 9)
            return ('0' + number);
        if (number >= 10 && number <= 15)
            return ('A' + number - 10);
        return -1;
    }
    int main()
    {
        int number;
        printf("enter a number between 0 and 15 : ");
        scanf("%d", &number);
        printf("%d = %c\n", number, get_hex_char(number));
        return 0;
    }

The following program defines a function named `get_hex_val`. The function returns the value in the decimal number system of a hexadecimal digit symbol whose code number is passed to it. If the character passed to the function is not a hexadecimal character, the value -1 is returned.

    #include <stdio.h>
    #include <ctype.h>
    int get_hex_val(int ch)
    {
        ch = toupper(ch);
        if (isdigit(ch))
            return ch - '0';
        if (ch >= 'A' && ch <= 'F')
            return ch - 'A' + 10;
        return -1;
    }
    int main()
    {
        char hex;
        printf("enter a character showing a hex digit: ");
        hex = getchar();
        printf("%c = %d\n", hex, get_hex_val(hex));
        return 0;
    }

The following program defines a function named `change_case`. If the character passed to the `change_case` function is a lowercase letter, it converts this character to an uppercase letter; if it is an uppercase letter, it converts the character to a lowercase letter. If it is not an alphabetic character, the function returns the character's own value.

    #include <stdio.h>
    #include <ctype.h>
    int change_case(int ch)
    {
        if (isupper(ch))
            return tolower(ch);
        return toupper(ch);
    }
    int main()
    {
        int c;
        printf("enter a character : ");
        c = getchar();
        c = change_case(c);
        putchar(c);
        return 0;
    }

The following C program solves a quadratic equation whose coefficients are obtained from the keyboard:

    #include <stdio.h>
    #include <math.h>
    int main()
    {
        double a, b, c;
        double delta;
        printf("enter the coefficients of the equation\n");
        printf("a = ");
        scanf("%lf", &a);
        printf("b = ");
        scanf("%lf", &b);
        printf("c = ");
        scanf("%lf", &c);
        delta = b * b - 4 * a * c;
        if (delta < 0)
            printf("your equation has no real root\n");
        else if (delta == 0) {
            printf("your equation has one real root\n");
            printf("root = %lf\n", -b / (2 * a));
        }
        else {
            double kokdelta = sqrt(delta);
            printf("your equation has 2 real roots\n");
            printf("root 1 = %lf\n", (-b + kokdelta) / (2 * a));
            printf("root 2 = %lf\n", (-b - kokdelta) / (2 * a));
        }
        return 0;
    }

---
