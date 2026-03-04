# 🚀 The `goto` Statement

As in other programming languages, the program flow in the C language can be directed to another point in the source code unconditionally. This is done with the **`goto`** statement in C:

The general syntax of the `goto` statement is as follows:

    goto label;
    ....
    label:
        statement;

`goto` is one of the 32 keywords in the C language. A **label** is a name given by the programmer. It must, of course, be chosen in accordance with the naming rules. The program flow is directed to the point where this label is placed. The label can be placed anywhere within the function where the `goto` keyword is used. The `:` token must be placed after the label name. The statement following the label is also part of the `goto` control statement's syntax. The absence of a statement after the label is a syntax error.

There is no requirement for the label to be placed at a source code point later than the `goto` keyword. The label can also be defined before the `goto` keyword:

    #include <stdio.h>
    int main()
    {
        /***/
        goto JUMP;
        /***/
    JUMP:
        printf("arrived here with the goto statement\n");
        return 0;
    }

In the program above, the label is placed after the `goto` keyword.

    int main()
    {
    JUMP:
        printf("point to be reached with the goto statement\n");
        /***/
        goto JUMP;
        /***/
        return 0;
    }

In the program above, the label is placed before the `goto` keyword.

`goto` labels are conventionally written in **uppercase** and aligned to the first column. This makes them stand out more in the source code.

`goto` labels can be placed anywhere before a statement within a function. That is, the label can be placed above or below the `goto` keyword, provided it is within the same function. With this feature, `goto` labels create a new scope rule. A name, no matter where it is defined within a function, is known everywhere within that function. This scope rule is called **"function scope."**

`goto` labels are not added to the namespace of the block they are in. `goto` label names are evaluated in a separate namespace. A local variable can have the same name as a `goto` label within a block:

    void func()
    {
        int x;
        goto x; // Jumps to the label named 'x'
    x: // This is the label
        x = 20; // This is the local variable 'x'
    }

The use of the `goto` statement is not recommended in structured programming technique. This is because the use of the `goto` statement gives rise to some disadvantages:

1.  The `goto` statement impairs program readability. When the person reading the code encounters a `goto` statement, they must search for and find the label within the function and continue reading the program from that point.
2.  It is more difficult to modify a program that uses `goto` statements or to try to develop the program by making additions. If a change is made at any point in the program, and if other places in the program jump to the point where the change was made using `goto` statements, changes may also be required at those points. That is, the `goto` statement increases the dependency of program segments on each other, which is generally undesirable.

Despite these drawbacks, in some situations, the use of the `goto` statement, far from impairing program readability, helps create a structure that is **more readable** than other options:

If there are multiple **nested loops**, and while in one of the inner loops, it is desired to exit **all** the loops at once, the `goto` statement should be used.

The following code snippet contains three nested loops. Inside the innermost loop, the `test_func` function is called, and its return value is checked. If the function returns the value 0, the program flow is directed outside all loops with the `goto` statement:

    #include <stdio.h>
    int test_func(int val);
    int main()
    {
        int i, j, k;
        for (i = 0; i < 100; ++i) {
            for (j = 0; j < 100; ++j) {
                for (k = 0; k < 20; ++k) {
                    /*...*/
                    if (!test_func(k))
                        goto BREAK; // Jumps out of all loops
                    /*...*/
                }
            }
        }
    BREAK:
        printf("first statement outside the loop\n");
        return 0;
    }

Three separate loop statements are located within the function above. An inner function call performs a test operation, and if the test result is negative, the program flow is directed to the point after the outermost loop statement.

Otherwise, the same goal could only be achieved by using a **flag** variable. It would be necessary to check whether the value of the variable used as a flag was changed at the exit of every loop.

    #include <stdio.h>
    #define BREAK 0
    #define NO_BREAK 1
    int test_func(int val);
    int main()
    {
        int i, j, k;
        int flag = NO_BREAK;
        for (i = 0; i < 100; ++i) {
            for (j = 0; j < 100; ++j) {
                for (k = 0; k < 20; ++k) {
                    /*...*/
                    if (!test_func(k)) {
                        flag = BREAK;
                        break; // Exits innermost loop
                    }
                    /*...*/
                }
                if (flag == BREAK)
                    break; // Exits middle loop
            }
            if (flag == BREAK)
                break; // Exits outermost loop
        }
        printf("first statement outside the loop\n");
        return 0;
    }

The use of the `goto` statement is better in terms of readability here.

In the example below, the `goto` statement is used to exit both the `switch` statement and the `for` loop that contains the `switch` statement:

    #define ADDREC 1
    #define LISTREC 2
    #define DELREC 3
    #define SORTREC 4
    #define EXITPROG 5
    
    int get_option(void);
    void add_rec(void);
    void list_rec(void);
    void del_rec(void);
    void sort_rec(void);
    
    int main()
    {
        int option;
        for (;;) { // Infinite loop
            option = get_option();
            switch (option) {
                case ADDREC : add_rec(); break;
                case LISTREC : list_rec(); break;
                case DELREC : del_rec(); break;
                case SORTREC : sort_rec(); break;
                case EXITPROG : goto EXIT; // Jumps out of switch AND for loop
            }
        }
    EXIT:
        return 0;
    }

In the `main` function above, when the value of the variable `option` is `EXITPROG`, the program flow is sent outside the infinite loop with the `goto` statement. If the `break` statement had been used instead of the `goto` statement, only the `switch` statement would have been exited.

The `goto` statement can be used to jump from one point within a function to another point also within itself. Such jumps are called **local jumps**. Jumping from inside one function to inside another function is possible with other means. Such jumps are called **non-local jumps**. In the C language, non-local jumps are performed with standard functions named `setjmp` and `longjmp`. These jumps are mostly used for **"exception handling."**

---
Would you like to move on to the next section, which would likely be about the remaining **Preprocessor Directives**, or perhaps another topic?