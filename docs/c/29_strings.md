# 🧠 C Programming Basics
# ✍️ Strings (String Literals)

In the C language, characters enclosed in double quotes are called **string literals** or simply **strings**. For example:

    "Necati Ergin"
    "x = %d\n"
    "please enter a number : "

All of the expressions above are strings.

You will recall from our previous topics that strings are treated as a single token. In C, strings are actually treated by compilers as the **address of a `char` array**. When C compilers encounter a string literal during the compilation phase, they first place the characters making up this string into a safe memory region and append the **null terminator** to the end. Then, they replace the string with the **starting address** of the location where it was placed. In this case, string literal expressions are actually the starting addresses of the array where the strings are placed by the compiler. For example:

    char *p;
    p = "Necati Ergin";

During the compilation of a code snippet like this, the compiler first places the string "Necati Ergin" into a safe memory region. Then, it replaces the string literal with the starting address of the location where it was placed.

Since strings are treated as the starting address of a `char` array, assigning strings to `char` pointer variables is valid. Compile and run the following `main` function:

    #include <stdio.h>
    int main()
    {
        printf("address = %p\n", "Necati");
        printf("address = %s\n", "Necati");
        return 0;
    }

In the first `printf` call within the `main` function, the string "Necati" is matched with the `%p` format specifier. Recall that address information can be printed to the screen with the `%p` format specifier using the `printf` function. In this case, the running code prints the **starting address** of the location where the string "Necati" was placed to the screen. In the second `printf` call, the string "Necati" is matched with the `%s` format specifier. In this case, the string at the relevant address, i.e., the string "Necati," is printed to the screen.

Now look at the following call:

    putchar(*"Necati");

You see that the string "Necati" is the operand of the **indirection operator** (`*`) this time. Since the indirection operator provides access to the object at the address that is its operand, the value of this object is the code number of the character 'N'. The character 'N' is printed to the screen upon execution of the called `putchar` function.

The `get_hex_char` function defined below returns the code number in the character set used of the character that represents a hexadecimal digit value:

    #include <stdio.h>
    int get_hex_char(int val)
    {
        return "0123456789ABCDEF"[val];
    }
    int main()
    {
        int k;
        for (k = 0; k < 16; ++k)
            putchar(get_hex_char(k));
        return 0;
    }

The return value of the function is the value of the expression:

    "0123456789ABCDEF"[val]

This is the value of the object at a distance of `val` from the address where the string is placed. The value of this `char` type object is the sequence number of one of the characters in the string. In the `main` function, the characters corresponding to the values in the range $0 – 15$ are obtained with the `get_hex_char` function within a loop and sent as an argument to the `putchar` function. The screen output of the program is:

    0123456789ABCDEF

The memory space that strings will occupy is determined at **compile time**. The same address value is always printed to the screen every time the following program is run:

    #include <stdio.h>
    int main()
    {
        int k;
        for (k = 0; k < 10; ++k)
            printf("%p\n", "Necati");
        return 0;
    }

## Sending Strings as Arguments to Functions

You know that a function whose parameter variable is a `char` pointer must be called with a `char` type address. This is because a `char` type pointer variable must naturally be assigned a `char` type address.

Since compilers also treat strings as specifying a `char` type address, calling a function whose parameter variable is a `char` type pointer with a string is an extremely natural situation:

    puts("Necati Ergin");

Here, after the compiler places the string "Necati Ergin" in memory and puts the null terminator at the end, it treats this string as the starting address of the memory block where its characters are placed. A `char` type address is then copied to the parameter variable of the `puts` function. The `puts` function writes all characters to the screen until it sees the null terminator, starting from the address held in the parameter variable. In this case, the string:

    Necati Ergin

appears on the screen.

In the example below, the string "Necati Ergin" is also copied to the address `str`. It should be considered that where string literal expressions are located, there is the address of a `char` array.

    #include <stdio.h>
    #include <string.h>
    int main()
    {
        char str[20];
        strcpy(str, "Necati Ergin");
        puts(str);
        return 0;
    }

## Strings Are Read-Only Text

Strings can be stored in **read-only memory areas**. Therefore, **modifying the content of a string literal** in the source code is incorrect. Code that modifies string literals exhibits **undefined behavior**. Examine the following example:

    #include <stdio.h>
    int main()
    {
        char *ptr = "Durak";
        *ptr = 'B'; /* Incorrect! Undefined behavior */
        puts(ptr);
        return 0;
    }

The pointer variable named `ptr` defined in the `main` function points to the string "Durak." Assigning to the object pointed to by the pointer `ptr` is incorrect. The program above does not contain a compile-time error.

## Identical Strings

Even if C compilers encounter entirely **identical strings** in various places in the source code, they may allocate different locations for them. Alternatively, the compiler may store only a single copy of identical strings in memory, based on the fact that strings are read-only text. How identical strings are stored is left to the compiler's choice. Many compilers allow the programmer to choose how identical strings will be stored in memory.

## Comparing Strings

Direct comparison of strings is an incorrect operation.

    /***/
    if ("Ankara" == "Ankara")
        printf("true!\n");
    else
        printf("false!\n");
    /***/

The output to the screen, whether "false!" or "true!," is **not guaranteed** when the code above is run. If the compiler has placed the two strings "Ankara" in separate locations in memory, the `==` comparison operator produces the value 0. However, a compiler might place the string "Ankara" in a single location and treat both string literals as the same address. In such a situation, the `==` comparison operator produces the value 1.

A similar mistake is made in the following code snippet:

    #include <stdio.h>
    int main()
    {
        char *pstr = "Blue moon"; // String literal address
        char s[20]; // Array address
        printf("enter the password : ");
        gets(s);
        if (pstr == s) // Compares two addresses, which are almost certainly different
            printf("correct password\n");
        else
            printf("wrong password\n");
        return 0;
    }

In the program above, $s$ is the name of an array. When the name $s$ is subjected to an operation, it is automatically converted by the compiler to the starting address of the array. `pstr` is a `char` pointer variable. When the string "Blue moon" is assigned to the pointer `pstr`, the compiler first places the string "Blue moon" in a safe location in memory. Then, it assigns the starting address of the location where the string was placed to the pointer `pstr`. Assume the user enters "Blue moon" as the password. In this case, inside the `if` statement, only the equality of the address $s$ and the address that is the value of the pointer `pstr` is checked. Since these addresses are not equal, "wrong password" is printed to the screen. The equality of two strings should be checked with the standard **`strcmp`** function:

    #include <stdio.h>
    #include <string.h>
    int main()
    {
        char *pstr = "Blue moon";
        char s[20];
        printf("enter the password : ");
        gets(s);
        if (!strcmp(pstr, s)) // Correct comparison: checks content, not address
            printf("correct password\n");
        else
            printf("wrong password\n");
        return 0;
    }

Of course, comparison of greater/lesser than is also incorrect, just like comparison of equality/inequality.

    if ("CAN" > "ATA") // Incorrect: compares addresses, not content
        printf("true!\n");
    else
        printf("false!\n");

In the `if` statement above, the strings "CAN" and "ATA" are **not** compared in the way the `strcmp` function does, i.e., as a string. What is actually being compared is only the numerical component of the two addresses.

## Lifespan of Strings

Strings are **static duration entities**. Strings, just like global variables, start occupying space in memory when the program is loaded and remain in memory until the end of the program. Therefore, strings increase the size of the executable code. In many systems, there is a certain limitation on the total length of static data.

Strings are written to the `.obj` module by the compiler and to the `.exe` file by the linker program. They come to life when the program is loaded.

An executable program usually consists of three main sections:

* **Code**
* **Data**
* **Stack (Yığın)**

The Code section contains the machine code of the functions. The Data section contains static duration entities. Global variables and strings are found in this section. The Stack section is the memory area where local variables are stored. The stack section is a limited area in every system. For example, in the DOS operating system, there is a stack area of size 64 KB. That is, the space occupied by local variables in memory can never exceed the value 64 KB. The default stack limit value in the WINDOWS operating system is 1 MB. However, this limit value can be increased as much as desired.

## A Function Returning a String Literal

It is a pointer error for a function that returns an address to return with the address of a local variable or a local array. Since local variables are deallocated from memory when the function ends, the address returned by the function is not a safe address. Such an error is made in the following program:

    #include <stdio.h>
    char *getname()
    {
        char s[100]; // Local array with automatic storage duration
        printf("enter name and surname : ");
        gets(s);
        return s; /* Incorrect! Returns address of a deallocated local array */
    }
    int main()
    {
        char *ptr;
        ptr = getname();
        puts(ptr);
        return 0;
    }

However, a function that returns a `char` type address can return with a **string literal**. In this case, a runtime error is **not** in question. Since strings are static duration entities, they maintain their location in memory throughout the program's execution. For example, the following function is valid and correct:

    char *getday(int day)
    {
        switch (day) {
            case 0: return "Sunday"; // Returns address of a static string literal
            case 1: return "Monday";
            case 2: return "Tuesday";
            case 3: return "Wednesday";
            case 4: return "Thursday";
            case 5: return "Friday";
            case 6: return "Saturday";
        }
        // Should also have a return statement for invalid day value
        return "Invalid day"; 
    }

## Concatenating Strings

Strings are treated as a single token. A string cannot be fragmented as follows:

    void func()
    {
        char *ptr = "Necati Ergin's C Course \n Notes are being read"; // Invalid fragmentation/line break
        /* Invalid */
        /***/
    }

However, as string length increases, it can become difficult to write strings on a single line. Lines that do not fit on a single screen line impair the readability of the source code. To allow long strings to be fragmented, C compilers combine strings with no characters other than whitespace between them and treat them as a single string. For example:

    ptr = "Necati Ergin's C Course " 
          "Notes are being read";

is a valid expression. In this case, the compiler combines the two strings and treats the code as follows:

    ptr = "Necati Ergin's C Course Notes are being read";

For the compiler to combine two strings, there must be no characters other than **whitespace characters** between the strings:

    p = "Necati" "Ergin";

is equivalent to the expression:

    p = "NecatiErgin";

In addition to combination, a line break can be achieved by terminating with a backslash character (`\`). For example:

    ptr = "Necati Ergin's C Course \
           Notes are being read";

is equivalent to the statement:

    ptr = "Necati Ergin's C Course Notes are being read";

The string must continue from the beginning of the next line after the backslash character. If the string in question is written as follows:

    ptr = "Necati Ergin's C Course \
    Notes are being read";

The space characters at the beginning of the line are also included in the string. The result is equivalent to the following expression:

    ptr = "Necati Ergin's C Course Notes are being read";

## Using Backslash Character Literals in Strings

Backslash character literals (**escape sequences**) can also be used inside strings. When compilers see a backslash character inside strings, they treat it and the character next to it as a single character. For example:

    char *p;
    p = "Necati\tErgin";

In the expression above, `\t` is a single character (the tab character, which is ASCII character number 9). That is, the statement:

    printf("number of characters in the string = %zu\n", strlen(p));

prints:

    number of characters in the string = 12

to the screen.

Double quote characters or backslash characters cannot be used directly in string expressions. These characters have special functions. To express the double quote character literal itself, a backslash character is used before the double quote character. For example:

    #include <stdio.h>
    int main()
    {
        puts("\"Necati Ergin\"");
        return 0;
    }

The call `puts(ptr);` in the `main` function prints:

    "Necati Ergin"

to the screen.

The backslash character literal inside a string can also be expressed in the hexadecimal number system. Compile and run the following program:

    #include <stdio.h>
    int main()
    {
        puts("\x41\x43\x41\x42\x41"); // Hex codes for A C A B A
        return 0;
    }

## The Null String (Empty String)

A string can be empty (**null string**), meaning it contains no characters. This is created by writing no characters between two double quote characters.

    char *ptr = "";

The null string is assigned to the pointer `ptr` with the statement above. Null strings also specify an address in memory. When the compiler sees a null string, it places only the **null terminator** in a safe memory location.

An empty string is a string with a length of 0. Compile and run the following program:

    #include <stdio.h>
    #include <string.h>
    int main()
    {
        char *ptr = "";
        printf("length = %zu\n", strlen(ptr)); // Output: length = 0
        return 0;
    }

## Initializing Pointer Variables with Strings

`char` type pointer variables can be initialized with strings. For example:

    char *p = "Istanbul";
    char *err = "Insufficient memory";
    char *s = "Press a key to continue";

Since strings are treated as a `char` array address by the compilers, initializing `char` type pointer variables with strings is a natural situation.

Attention must be paid to the difference between initializing arrays with double quotes and initializing pointer variables with strings:

    char *p = "Test";
    char s[10] = "Test";

The statements are completely different.

When pointer variables are initialized, the compiler treats it as a string literal expression. That is, after the string is placed in memory, its starting address is assigned to the pointer. In arrays, however, space is first allocated for the array, and then the characters are placed into the array elements one by one. The double quote expressions used when initializing arrays are **not converted to address information**. This initialization rule was introduced to make the programmer's job easier, as initializing array elements with single `char` literals one by one is cumbersome.

The statement:

    char s[10] = "Test";

is actually synonymous with:

    char s[10] = {'T', 'e', 's', 't', '\0'};

## Comparing `char` Arrays Holding Strings and `char` Pointers Pointing to Strings

In the C language, string information can be stored in at least two separate ways:

1.  **A string can be stored in a `char` array:**

    ```c
    #include <stdio.h>
    #include <string.h>
    void foo()
    {
        char s1[100] = "Necati Ergin";
        char s2[100];
        char s3[100];
        printf("enter a string: ");
        gets(s2);
        strcpy(s3, s2);
        /***/
    }
    ```

    In the `foo` function above, the string "Necati Ergin" is placed into the $s1$ array as an initial value. A string is read into the $s2$ array from the keyboard with a call to the standard `gets` function. The string in the $s2$ array is copied to the $s3$ array with a call to the standard `strcpy` function.

2.  **The string can be stored as a string literal, and a `char` pointer variable is made to point to this string:**

    `char *ptr = "Necati Ergin";`

The two methods are not entirely equivalent. The following points should be noted:

* Since strings are **static duration entities**, they occupy memory until the program terminates. If a pointer variable, while pointing to one string literal, is then made to point to another string literal, this does **not** mean that the previous string literal is deallocated from memory:

    `char *p = "This string will remain in memory until the end of the program.";`
    `p = "now there will be no connection to the string above...";`

* It is possible to change a string when it is held in a `char` array. The string can be changed as desired by reassigning to array elements. But modifying string literals exhibits undefined behavior and is **incorrect**:

    ```c
    #include <stdio.h>
    #include <string.h>
    void foo()
    {
        char *ps = "Text";
        char *pstr = "Ankara";
        ps[1] = 'C'; /* Incorrect! Modifies read-only memory */
        strcpy(pstr, "Bolu"); /* Incorrect! Modifies read-only memory */
        /***/
    }
    ```