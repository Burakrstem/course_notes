# ⌨️ Command Line Arguments

When a program is executed, some parameters that will direct or modify the program's execution may be desired to be sent to the running program. A parameter sent to the program can be a file name, for example, or an option that enables the program to run in different ways. Consider the `ls` command in the UNIX operating system. If the `ls` program is executed by typing:

    ls

the names of the files in the current directory are listed. But if the program is executed by typing:

    ls -l

this time, a more detailed list is displayed on the screen, showing not only the file names but also the size of the files in the directory, their owners, creation date and time, etc. If the `ls` program is executed again by typing:

    ls -l sample.c

only the information related to the `sample.c` file is displayed. The other parameters written next to the program name when running a program are called **command line arguments**.

Command line arguments are not valid only for operating system commands. Command line arguments can be used for all programs. Command line arguments are called **program parameters** in the C language standards.

The `main` function, where C programs begin execution, can optionally have two parameter variables. These parameter variables are conventionally named **`argc`** and **`argv`**.

    int main(int argc, char *argv[])
    {
        /***/
    }

* **`argc`** is abbreviated from the words "argument count." It indicates the **number of command line arguments**. The program name is also included in this count.
* **`argv`** is abbreviated from the words "argument vector." `argv` is a pointer that receives the address of a **`char` pointer array** that holds the command line arguments stored as strings. That is, there is an array of pointers at the location pointed to by the `argv` pointer. Each element of this pointer array holds the strings that are the command line arguments.

In this case:

* `argv[0]` holds the starting address of the string that is the **program name**.
* `argv[1]` up to `argv[argc - 1]` hold the starting addresses of the strings that are the **other command line arguments** following the program name.
* The pointer `argv[argc]` has the value of the **NULL address**.

In the example above, when the user executes the `ls` program as:

    ls -l sample.c

* `argc` receives the value **3**.
* `argv[0]` points to the program name: `argv[0] = "ls"`.
* `argv[1]` points to the first argument following the program name: `argv[1] = "-l"`.
* `argv[2]` points to the second argument following the program name: `argv[2] = "sample.c"`.
* `argv[argc]`, i.e., `argv[3]`, points to the **NULL address**.

Recall that the pointer to a pointer parameter of a function can be defined in two separate ways:

    void func(char **ptr);
    void foo(char *ptr[]);

The parameter variable of both functions is a pointer to a `char` pointer. In this case, the `argv` parameter, which is a pointer to a pointer, for a `main` function that will process command line arguments, can be defined in two different forms:

    int main(int argc, char **argv)
    {
        /***/
    }

    int main(int argc, char *argv[])
    {
        /***/
    }

Command line arguments must be separated from each other by **spaces**. In the example above, if the program were executed in the form:

    ls -lsample.c

`argc` would have the value **2**.

Command line arguments are retrieved from the command line by the operating system and sent to the `main` function with the help of the entry code produced by the compiler.

Below you see an example program that prints the command line arguments to the screen:

    #include <stdio.h>
    int main(int argc, char *argv[])
    {
        int i;
        for (i = 0; i < argc; ++i)
            printf("argv[%d] : %s\n", i, argv[i]);
        return 0;
    }

The loop statement in the `main` function could also be written in the following form:

    for (i = 0; argv[i] != NULL ; ++i)
        printf("argv[%d] : %s\n", i, argv[i]);

Programs executed from the command line generally first **interpret and check** the entered arguments. For example, suppose a program named `copy` intended to make a copy of a file is desired to be executed from the command line. Let the program require the name of the file to be copied and the name of the new file to be created from the command line:

    copy test.c newfile.c

When the program is executed from the command line as above, let it create a copy of a file named `test.c` with the name `newfile.c`. In this case, `argc` receives the value 3, right?

    #include <stdio.h>
    #include <stdlib.h>
    int main(int argc, char *argv[])
    {
        /***/
        if (argc != 3) { // Program name + 2 arguments = 3 total
            printf("usage : <copy> <source file name> <new file name>\n");
            exit(EXIT_FAILURE);
        }
        /***/
        return 0;
    }

In the `main` function above, if the program was not executed by providing 3 command line arguments, i.e., if it was executed with insufficient or excessive arguments, the program is terminated with an error message.

A program does not have to be terminated when arguments are not entered correctly from the command line. The incorrectly entered arguments can be requested to be entered by the user of the program during the program's execution this time.

Examine the following example:

    #include <stdio.h>
    #include <string.h>
    #define NAME_LEN 80
    int main(int argc, char *argv[])
    {
        char source_name[NAME_LEN];
        char dest_name[NAME_LEN];
        
        if (argc != 3) {
            printf("enter the source file name : ");
            gets(source_name);
            printf("enter the copy file name : ");
            gets(dest_name);
        }
        else {
            strcpy(source_name, argv[1]);
            strcpy(dest_name, argv[2]);
        }
        /***/
        return 0;
    }

In some systems, such as the DOS operating system, the `main` function can take a third parameter. The third parameter is a pointer to a pointer of type `char *` related to the system's environment variables.

    int main(int argc, char *argv[], char *env[])
    {
        /***/
    }

In the program below, the words entered from the command line are printed in **reverse order** and **reversed**:

    #include <stdio.h>
    int main(int argc, char **argv)
    {
        int k, i;
        
        // Loop for words (from last argument to first argument after program name)
        for (k = argc - 1; k > 0; --k) { 
            // Loop to find end of string
            for (i = 0; argv[k][i] != '\0'; ++i)
                ;
            
            // Loop backwards to print characters
            for (i--; i >= 0; --i) 
                putchar(argv[k][i]);
            
            putchar('\n');
        }
        return 0;
    }

Below is the code for a simple calculator program to be run from the command line:

    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>
    int main(int argc, char *argv[])
    {
        char ch;
        int op1, op2;
        
        if (argc != 4) { // Expects program_name Op1 Operator Op2
            printf("usage : calc Op1 Operator Op2\n");
            exit(EXIT_FAILURE);
        }
        
        // Convert string arguments to integers
        op1 = atoi(argv[1]);
        op2 = atoi(argv[3]);
        ch = argv[2][0]; // Operator is the first char of the second argument
        
        printf(" = ");
        
        switch (ch) {
            case '+' : printf("%d\n", op1 + op2); return 0;
            case '-' : printf("%d\n", op1 - op2); return 0;
            case '/' : printf("%lf\n", (double)op1 / op2); return 0; // Division returns float
            case '*' : printf("%d\n", op1 * op2); return 0;
            case '%' : printf("%lf\n", (double)op1 * op2 / 100); return 0; // Assuming '%' means percentage here
            case 'k' : printf("%lf\n", pow(op1, op2)); return 0; // Assuming 'k' means power (kuvvet)
            default : printf("invalid operator\n");
        }
        return 0;
    }

The following program prints the day of the week for a date entered from the command line (day, month, and year values) to the screen:

    #include <stdio.h>
    #include <stdlib.h>
    // Assuming days array is defined globally or externally
    char *days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday",
                    "Friday", "Saturday"};
    
    // Zeller's Congruence variant - returns 0 for Sunday to 6 for Saturday
    int day_of_week(int d, int m, int y)
    {
        static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4,6, 2, 4}; // Offset for months
        y -= m < 3; // Adjustment for January and February
        return (y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;
    }
    
    int main(int argc, char **argv)
    {
        int day, mon, year;
        
        if (argc != 4) { // If arguments are not provided, ask the user
            printf("enter day month and year values : ");
            scanf("%d%d%d", &day, &mon, &year);
        }
        else { // Use command line arguments
            day = atoi(argv[1]); // Convert string to integer
            mon = atoi(argv[2]);
            year = atoi(argv[3]);
        }
        
        // Output the day of the week (day_of_week returns 0-6 index)
        printf("%s\n", days[day_of_week(day, mon, year)]); 
        return 0;
    }