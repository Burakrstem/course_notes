# 🔀 The `switch` Statement

The `switch` statement is used to perform different tasks for different values of an integer expression. The `switch` statement provides an alternative to `else if` ladders in terms of readability.

The general form of the statement is as follows:

    switch (expression) {
    case expression1 :
    case expression2 :
    case expression3 :
    .......
    case expression_n:
    default:
    }

`switch`, `case`, and `default` are keywords in the C language.

### Execution of the `switch` Statement

The numerical value of the expression inside the `switch` parenthesis is calculated. It is tested from top to bottom whether a `case` expression with a value equal to this numerical value exists. If such a `case` expression is found, the program flow is transferred to that `case` label. The program then proceeds by falling through from this point. If the numerical value of the expression inside the `switch` parenthesis is not equal to any `case` expression, the flow is transferred to the part where the **`default`** keyword is located, if it exists.

    #include <stdio.h>
    int main()
    {
        int a;
        printf("enter a number : ");
        scanf("%d", &a);
        switch (a) {
            case 1: printf("one\n");
            case 2: printf("two\n");
            case 3: printf("three\n");
            case 4: printf("four\n");
            case 5: printf("five\n");
        }
        return 0;
    }

In the example above, suppose the value 1 is read into the variable `a` from the keyboard using the `scanf` function. The program's screen output will be as follows:

    one
    two
    three
    four
    five

If it is desired that only the statement(s) corresponding to the matching `case` expression be executed, the **`break`** statement is used. With the use of the `break` statement, the `switch` statement is exited, just like loops. `break` statements are added to the previously given example:

    #include <stdio.h>
    int main()
    {
        int a;
        printf("enter a number: ");
        scanf("%d", &a);
        switch (a) {
            case 1 : printf("one\n"); break;
            case 2 : printf("two\n"); break;
            case 3 : printf("three\n"); break;
            case 4 : printf("four\n"); break;
            case 5 : printf("five\n");
        }
        return 0;
    }

In applications, a `break` statement is generally used for every `case` expression in a `switch` statement. Of course, there is no such requirement.

Any number of statements can follow the `:` token that follows the `case` expressions. There is **no need to block** these statements if more than one statement follows a `case` expression. That is, all statements following a `case` expression are treated as if they were inside a block.

There is no requirement for `case` expressions to follow a specific order.

### The `default` Case

`default` is a keyword. The `default` keyword placed in the `switch` statement body is followed by the `:` token. This constructed `case` is called the **default case**.

If an equivalent `case` expression is not found, the program flow enters the default case.

A default case is added to the previously written `switch` statement:

    #include <stdio.h>
    int main()
    {
        int a;
        printf("enter a number: ");
        scanf("%d", &a);
        switch (a) {
            case 1 : printf("one\n"); break;
            case 2 : printf("two\n"); break;
            case 3 : printf("three\n"); break;
            case 4 : printf("four\n"); break;
            case 5 : printf("five\n"); break;
            default: printf("none\n");
        }
        return 0;
    }

As explained above, all `case` expressions are tested sequentially in the compilation direction, i.e., from top to bottom, until a `case` expression equal to the numerical value of the expression inside the `switch` parenthesis is found. If there is available information about the frequency or probability of `case` expressions, writing the `case` expressions with higher probability or frequency earlier can reduce the number of unnecessary comparisons.

`case` expressions must be **constant expressions of an integral type**. As is known, constant expressions can be converted to definite numerical values by the compiler during the compilation phase:

    case 1 + 3: /* Valid */

is possible because $1 + 3$ is a constant expression, but:

    case x + 5: /* Invalid */

is not possible because it is not a constant expression. The compiler cannot calculate a numerical value during the compilation phase.

    case 'a' :

The `case` expression above is valid. 'a' is a character literal. The `case` expression is a constant expression of an integer type.

    case 3.5 :

The `case` expression above is invalid. 3.5 is a floating-point literal.

An `else if` ladder can be written instead of the `switch` control statement. That is, if there were no `switch` statement, the desired task could also be performed with an `else if` ladder. However, using the `switch` statement instead of an `else if` ladder increases readability in some situations. For example:

    if (a == 1)
        statement1;
    else if (a == 2)
        statement2;
    else if (a == 3)
        statement3;
    else if (a == 4)
        statement4;
    else
        statement5;

The `else if` ladder above is functionally equivalent to the following `switch` statement:

    switch (a) {
        case 1 : statement1; break;
        case 2 : statement2; break;
        case 3 : statement3; break;
        case 4 : statement4; break;
        default: statement5;
    }

An `else if` ladder can be written to perform the same task as every `switch` statement, but not every `else if` ladder can be replaced by a `switch` statement. The expression inside the `switch` parenthesis must be of an **integral type**. The `case` expressions must also be constant expressions of integral types. The `switch` statement is used to test the equality of an expression of an integral type to different integer values and to perform different tasks in case of equality. However, any kind of comparison can be involved in an `else if` ladder. Example:

    if (x > 20)
        m = 5;
    else if (x > 30 && x < 55)
        m = 3;
    else if (x > 70 && x < 90)
        m = 7;
    else
        m = 2;

A `switch` statement cannot be written instead of the `else if` ladder above.

The `switch` statement, in some cases, forms a much more readable structure than the `else if` ladder; that is, the use of the `switch` statement, above all, makes the code easier to read and understand.

The same operations for multiple `case` expressions can be achieved as follows:

    case 1:
    case 2:
    case 3:
        statement1;
        statement2;
        break;
    case 4:

There is no shorter way to do this. Some programmers arrange the source code layout as follows:

    case 1: case 2: case 3: case 4: case 5:
        statement1; statement2;

Examine the following program first, then compile and run it:

    void print_season(int month)
    {
        switch (month) {
            case 12:
            case 1 :
            case 2 : printf("winter"); break;
            case 3 :
            case 4 :
            case 5 : printf("spring"); break;
            case 6 :
            case 7 :
            case 8 : printf("summer"); break;
            case 9 :
            case 10:
            case 11: printf("autumn");
        }
    }

The `print_season` function takes the sequence number of a month, i.e., the information of which month of the year it is, and prints the name of the season the month is in to the screen. How could the same task be done with an `else if` ladder? The logical OR operator could be used in the conditional expression of each `if` statement:

    void print_season(int month)
    {
        if (month == 12 || month == 1 || month == 2)
            printf("winter");
        else if (month == 3 || month == 4 || month == 5)
            printf("spring");
        else if (month == 6 || month == 7 || month == 8)
            printf("summer");
        else if (month == 9 || month == 10 || month == 11)
            printf("autumn");
    }

Since symbolic constants are replaced by the preprocessor before the compilation process, they can be included in `case` expressions:

    #define TRUE 1
    #define FALSE 0
    #define UNDEFINED 2

    case TRUE :
    case FALSE :
    case UNDEFINED :

The `case` expressions above are valid.

Character literals can also be used as `case` expressions:

    #include <stdio.h>
    int main()
    {
        switch (getchar()) {
            case '0': printf("zero\n"); break;
            case '1': printf("one\n"); break;
            case '2': printf("two\n"); break;
            case '3': printf("three\n"); break;
            case '4': printf("four\n"); break;
            case '5': printf("five\n"); break;
            default : printf("invalid!\n");
        }
        return 0;
    }

The readability of the code is weakened if the statements following the `case` expressions are longer than 15-20 lines. In this case, converting the operations to function calls is a good technique.

    switch (x) {
        case ADDREC:
            addrec();
            break;
        case DELREC:
            delrec();
            break;
        case FINDREC:
            findrec();
            break;
    }

In the example above, `ADDREC`, `DELREC`, and `FINDREC` used as `case` expressions are previously defined symbolic constants. The operations performed for each `case` are wrapped inside a function.

    char ch = getch();
    switch (ch) {
        case 'E' : statement1; break;
        case 'H' : statement2; break;
        default : statement3;
    }

There cannot be more than one `case` expression with the same numerical value in a `switch` statement. This results in a compile-time error.

A `switch` statement can form the body of another `switch` statement or a loop statement:

    #include <stdio.h>
    // #include <conio.h> (Assuming getch() is available)
    #include <stdlib.h> // for rand() and srand()
    #include <time.h> // for time()
    #define ESC 0x1B
    int getch_mock() { return getchar(); } // Mock function for standard C environment
    int main()
    {
        int ch;
        srand(time(NULL)); // Seed the random number generator
        while ((ch = getch_mock()) != ESC)
            switch (rand() % 7 + 1) {
                case 1: printf("Monday\n"); break;
                case 2: printf("Tuesday\n"); break;
                case 3: printf("Wednesday\n"); break;
                case 4: printf("Thursday\n"); break;
                case 5: printf("Friday\n"); break;
                case 6: printf("Saturday\n"); break;
                case 7: printf("Sunday\n");
            }
        return 0;
    }

In the `main` function above, the `switch` statement forms the body of the outer `while` loop. Since the `switch` statement is the only statement in the loop body, there is no need to block the outer `while` loop. However, blocking the `while` loop would not cause an error. But the `break` statement inside the `case` expressions only exits the `switch` statement. The `goto` statement can be used inside the `case` expression to exit the `while` loop as well.

Now, examine the following program. A function named `display_date` is defined in the program. The function prints a date information received as day, month, and year values in the following English format to the screen:

    5th Jan 1998

    #include <stdio.h>
    void display_date(int day, int month, int year)
    {
        printf("%d", day);
        switch (day) {
            case 1 :
            case 21 :
            case 31 : printf("st "); break;
            case 2 :
            case 22 : printf("nd "); break;
            case 3 :
            case 23 : printf("rd "); break;
            default : printf("th ");
        }
        switch (month) {
            case 1 : printf("Jan "); break;
            case 2 : printf("Feb "); break;
            case 3 : printf("Mar "); break;
            case 4 : printf("Apr "); break;
            case 5 : printf("May "); break;
            case 6 : printf("Jun "); break;
            case 7 : printf("Jul "); break;
            case 8 : printf("Aug "); break;
            case 9 : printf("Sep "); break;
            case 10: printf("Oct "); break;
            case 11: printf("Nov "); break;
            case 12: printf("Dec ");
        }
        printf("%d", year);
    }
    int main()
    {
        int day, month, year;
        int n = 20;
        while (n-- > 0) {
            printf("enter date as day month year : ");
            scanf("%d%d%d", &day, &month, &year);
            display_date(day, month, year);
            putchar('\n');
        }
        return 0;
    }

Two separate `switch` statements are used in the function's definition. The first `switch` statement prints the suffixes (th, st, nd, rd) following the day value, while the second `switch` statement prints the month abbreviations (Jan, Feb, Mar.).

One of the statements following the `case` expressions does not have to be a `break` statement. In some cases, the `break` statement is deliberately omitted, and it is specifically desired that the statements inside the following cases also be executed when an appropriate `case` expression is found. Compile and run the following program:

    #include <stdio.h>
    int isleap(int y)
    {
        return y % 4 == 0 && (y % 100 != 0 || y % 400 == 0);
    }
    int day_of_year(int day, int month, int year)
    {
        int sum = day;
        switch (month - 1) {
            case 11: sum += 30;
            case 10: sum += 31;
            case 9 : sum += 30;
            case 8 : sum += 31;
            case 7 : sum += 31;
            case 6 : sum += 30;
            case 5 : sum += 31;
            case 4 : sum += 30;
            case 3 : sum += 31;
            case 2 : sum += 28 + isleap(year);
            case 1 : sum += 31;
        }
        return sum;
    }
    int main()
    {
        int day, month, year;
        int n = 5;
        while (n-- > 0) {
            printf("enter date as day month year : ");
            scanf("%d%d%d", &day, &month, &year);
            printf("it is the %d. day of the year %d!\n", day_of_year(day, month,
                year), year);
        }
        return 0;
    }

The `day_of_year` function calculates which day of the relevant year the date information received as day, month, and year values corresponds to and returns this value. Examine the `switch` statement used in the function carefully. The value one less than the month value received from outside is used inside the `switch` parenthesis. **No `break` statement is used inside any case.** When an appropriate `case` expression is found, all the statements inside the cases located below it are also executed. Thus, the information of how many days each month lower than the month value received from outside has is added to the `sum` variable, which holds the total number of days.