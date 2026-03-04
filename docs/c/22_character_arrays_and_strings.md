# 🔡 Character Arrays and Strings

**Character arrays** are arrays of type `char`. Character arrays are no different from other array types, except for some additional features. Character arrays are defined mainly to store **strings** (text) within them.

    char str[100];

In the definition above, `str` is an array of 100 elements, with each element of type `char`. Storing a string in a `char` array means sequentially assigning the sequence number of one character of the string to each element of the array. Meanwhile, it is not mandatory to store a string in a `char` array; such an array can perfectly be used to store small integers.

Suppose the string "Ali" is intended to be stored in the array defined above:

    str[0] = 'A';
    str[1] = 'l';
    str[2] = 'i';

Although the array is 100 characters long, shorter strings can also be stored in the array. So, how can the string stored in the array be accessed? The length information of the string is unknown. For example, suppose a loop statement like the one written below for integer arrays is used when the string is intended to be printed to the screen:

    for (k = 0; k < 100; ++k)
        putchar(s[k]);

With such a loop, only the string "Ali" is not printed to the screen; the images of the other 97 elements of the array, i.e., garbage values, are also printed to the screen, right?

In the C language, the concept of a **"null character"** is utilized to perform operations on characters quickly and effectively.

The null character is the zero-numbered character (`'\x0'` or `'\0'`) of the ASCII table or the character set used in the system. Therefore, its numerical value is equal to the number 0. It has no graphical representation. The null character `'\0'` should not be confused with the character `'0'`. The code number of the character `'0'` in the ASCII character set is 48. Therefore, its integer value is 48. However, the ASCII sequence number of the character `'\0'` is 0. Therefore, its integer value is 0. Compile and run the following program:

    #include <stdio.h>
    int main()
    {
        printf("%d\n", '0');
        printf("%d\n", '\0');
        return 0;
    }

When the first `printf` function is called above, the value 48 is printed to the screen, while the value 0 is printed to the screen when the second `printf` function is called.

### Initializing Character Arrays

The initialization of `char` arrays can be done in the following forms:

As in other array types, initial values separated by commas are enclosed in curly braces:

    char name[7] = {'N', 'e', 'c', 'a', 't', 'i', '\0'};

As in other arrays, giving more initial values than the array size is invalid.

    char name[5] = {'N', 'e', 'c', 'a', 't', 'i'}; /* Invalid */

Initial values can be given for as many elements as the array size or for fewer elements than the array size. If initial values are given for fewer elements, the uninitialized elements are initialized with the value 0, just like in other arrays. You know that the value 0 is the null character:

    char name[5] = {'A', 'l', 'i'}; // name[3] and name[4] are initialized to 0 ('\0')

The array size may not be specified when initializing `char` arrays. In this case, the compiler determines the array size by counting the initial values given. The compiler assumes the array is opened with this size.

    char name[ ] = {'A', 'l', 'i'};

With the definition statement above, the compiler assumes that the `name` array is opened with 3 elements.

When the array size is not specified and initial values are given with comma-separated values in the definition of a `char` array, the compiler does **not** automatically place the null character at the end of the array. In this case, the null character that should be at the end of the string must be present in the initialization list:

    char name[] = {'A', 'l', 'i', '\0'};

The same situation applies when the array size is the same as the number of initial values given:

    char isim[7] = {'N', 'e', 'c', 'a', 't', 'i', '\0'};

Since initializing this way is cumbersome, a second form has been created for initialization. Character arrays can also be initialized within **double quotes**:

    char name[] = "Ali";

The difference between this form and the other is that the compiler automatically places the null character at the end.

The compiler in the example above assumes that the `name` array is opened with 4 elements. Giving more initial values than the array size is invalid.

    char city[5] = "İstanbul"; /* Invalid */

There is one exception to this situation. If initial values are given within double quotes for the same number of elements as the array size, this situation is valid. The compiler does **not** place the null character at the end of the array in this case.

    char name[3] = "Ali"; /* Valid in C, Invalid in C++ */

The `'\0'` character is used to speed up operations performed on character strings. For example, when an `int` array is used, the array length must be known when performing operations on array elements using loops. But when `char` arrays are in question, it is no longer necessary to know the array length, because the `'\0'` character will be at the end of the string, and by testing this situation with control expressions, it can be understood whether the end of the string has been reached. However, a drawback of using the `'\0'` character as the last element of strings in character arrays is the necessity of adding an extra character, the `'\0'` character, to the array. For this reason, a string of maximum $\text{SIZE} – 1$ length can be stored in an array of $\text{SIZE}$ elements.

## Standard String I/O Functions

The C language contains standard functions that read a string from the keyboard or print a string to the screen.

### The `gets` Function

The previously covered `getchar`, `getch`, and `getche` functions read a single character from the keyboard. **`gets`** is a standard C function used to read a character string from the keyboard. The user must press the **Enter** key after entering the characters from the keyboard. The function takes the name of the array where the characters to be entered from the keyboard will be placed as a parameter. As mentioned before, array names actually specify address information. The parameter of the `gets` function is actually a `char` type address. However, since the basic concepts related to pointers have not yet been explained, for now, you will only learn enough about the `gets` function to be useful to you. For example:

    char s[20];
    gets(s);

All characters entered from the keyboard until the Enter key is pressed are placed sequentially into the `name` array (using `s` here). Suppose the string "Necati" is entered from the keyboard:

The `gets` function places the characters entered from the keyboard into the array and then places the **null character** at the end of the array.

The `gets` function **does not** check for array overrun in any way. If more characters are entered than the number of array elements with the `gets` function, unexpected results may be encountered because the array will overrun. We will examine these kinds of situations in detail in the section "Pointers" under the heading "pointer errors."

Since the `gets` function adds the `'\0'` character to the end of the array, the maximum number of characters that can be read with the `gets` function for an array of size $\text{SIZE}$ must be at most $\text{SIZE} – 1$. This is because the null character also occupies memory space, just like other characters. Example:

    char isim[6];
    gets(isim);

Suppose the name "Necati" is entered from the keyboard:

The compiler allocates 6 bytes of space in memory for this array with the definition of the `isim` array (`isim[0] ... isim[5]`).

The `gets` function in this situation writes the `'\0'` character to a memory cell that the compiler has not allocated for the array. Such situations are called **"off-by-one errors" (array overrun errors)**. Errors that arise regarding the overrun situation are related to **run time**, not compile time.

Examine the following program:

    #include<stdio.h>
    #define SIZE 100
    int main()
    {
        char str[SIZE];
        int ch;
        int index = 0;
        printf("enter a string: ");
        printf("\n\n");
        while ((ch = getchar()) != '\n')
            str[index++] = ch;
        str[index] = '\0'; // Manually adding the null terminator
        return 0;
    }

In the `main` function above, a string entered from the keyboard is stored in the `str` array. All characters entered until the `'\n'` character is received from the keyboard are sequentially assigned to the elements of the `str` array. When the `'\n'` character is received from the keyboard, the `'\0'` character is written after the last character written to the array to mark the end of the string in the array.

A string read from the keyboard can also be placed into a `char` array with the standard **`scanf`** function. The `%s` format specifier is used for this purpose. However, in this case, not all characters entered from the keyboard are placed into the array. The placement operation into the array ends with the first space character received from the keyboard. Examine the following program:

    #include <stdio.h>
    int main()
    {
        char name[20];
        char fname[30];
        int no;
        printf("enter name surname and number : ");
        scanf("%s%s%d", name, fname, &no);
        /***/
        return 0;
    }

Suppose the following input is made when the `scanf` function is called during the program's runtime (the `_` character indicates a space character):

    __Necati___Ergin___564

In this case, the string "Necati" is placed in the `name` array, the string "Ergin" is placed in the `fname` array, and the integer value 564 is placed in the variable named `no`.

### The `puts` Function

**`puts`** is a standard C function. This function is used to print the string held in a character array to the screen. It takes the name of the character array holding the string (the array name is automatically converted to the starting address of the array by the compiler) as a parameter. The `puts` function moves the cursor to the beginning of the next line after printing the character array to the screen:

    #include <stdio.h>
    int main()
    {
        char name[20];
        printf("enter a name : ");
        gets(name);
        puts(name);
        return 0;
    }

In the example above, the string read from the keyboard with the `gets` function is printed to the screen with the `puts` function.

The standard **`printf`** function can also be used to print the strings held in character arrays to the screen. In this case, `%s` is used as the format specifier and is matched with the array name (the starting address of the array).

    printf("%s\n", name);

performs the same task as:

    puts(name);

However, the `printf` function does not move the cursor to the next line after printing the string held in the array to the screen (unless `\n` is explicitly used).

Instead of the statement `puts(name);`, the following code snippet could also have been written:

    for (i = 0; name[i] != '\0'; ++i)
        putchar(name[i]);
    putchar('\n');

The `puts` function and the `printf` function when used with the `%s` format specifier write all characters until they encounter the null character. In this case, if the null character at the end of the string is somehow overwritten, both functions continue writing until they encounter the first null character. Examine the following program:

    #include <stdio.h>
    int main()
    {
        char city[] = "Ankara";
        city[6] = '!'; // Overwrites the null terminator ('\0') at city[6]
        puts(city);
        return 0;
    }

With the assignment `city[6] = '!'`, the null character at the end of the string "Ankara" is overwritten, and the character `!` is written over it. The subsequently called `puts` function prints the string:

    Ankara!

to the screen and continues writing until it encounters the first null character. You will see that this situation constitutes a pointer error in the section on pointers. The `puts` and `printf` functions only consider the null character when writing character arrays. These functions are not concerned with the length of the character arrays.

### Some Small Applications Related to Character Arrays

The following program finds the length of the string held in a character array:

    #include <stdio.h>
    #define SIZE 100
    int main()
    {
        char str[SIZE];
        int k;
        int len = 0;
        printf ("enter a string : ");
        gets(str);
        printf("string = (%s)\n", str);
        for (k = 0; str[k] != '\0'; ++k)
            len++;
        printf("length of the string (%s) is = %d\n", str, len);
        return 0;
    }

After the execution of the loop statement:

    for (k = 0; str[k] != '\0'; ++k)
        len++;

in the program, the value of the loop variable $k$ is also the length of the string, right?

The following program prints the string received into a `char` array to the screen in reverse:

    #include <stdio.h>
    #define SIZE 100
    int main()
    {
        char s[SIZE];
        int k;
        printf("enter a string :");
        gets(s);
        for (k = 0; s[k] != '\0'; ++k)
            ; // Finds the position of the null terminator
        for (--k; k >= 0; --k)
            putchar(s[k]);
        return 0;
    }

The following program first receives a string into a character array from the keyboard. Then, the lowercase characters of the string are converted to uppercase, and the uppercase characters are converted to lowercase:

    #include <stdio.h>
    #include <ctype.h>
    #define SIZE 100
    int main()
    {
        char str[SIZE];
        int k;
        printf ("enter a string : ");
        gets(str);
        printf("string = (%s)\n", str);
        for (k = 0; str[k] != '\0'; ++k)
            str[k] = isupper(str[k]) ? tolower(str[k]) : toupper(str[k]);
        printf("converted string = (%s)\n", str);
        return 0;
    }

The following program reverses the string received into a character array from the keyboard:

    #include <stdio.h>
    #define SIZE 100
    int main()
    {
        char str[SIZE];
        int k, temp, len;
        printf ("enter a string : ");
        gets(str);
        for (len = 0; str[len] != '\0'; ++len)
            ; // Find length (len holds the index of '\0')
        for (k = 0; k < len / 2; ++k) {
            temp = str[k];
            str[k] = str[len - 1 - k];
            str[len - 1 - k] = temp;
        }
        printf("reversed string = (%s)\n", str);
        return 0;
    }

Examine the algorithm used in the code above. The length of the string is found with the first `for` loop. Then, a `for` loop statement that iterates half the length of the string is created. In each iteration of the loop, the $n$-th character from the beginning of the string is swapped with the $n$-th character from the end. If the string length is an odd number, the character in the middle of the string remains in place. Since the null character is $str[\text{len}]$, the last character of the string is $str[\text{len} – 1]$, right?

The following program counts all English letters found in a string entered from the keyboard and prints how many of them there are:

    #include <stdio.h>
    #include <ctype.h>
    #define SIZE 500
    int main()
    {
        char str[SIZE];
        int letter_counter[26] = {0};
        int k;
        printf("enter a string : ");
        gets(str);
        for (k = 0; str[k] != '\0'; ++k)
            if (isalpha(str[k]))
                letter_counter[toupper(str[k]) - 'A']++;
        for (k = 0; k < 26; ++k)
            if (letter_counter[k])
                printf("%3d of %c\n", letter_counter[k], 'A' + k);
        return 0;
    }

The array named `letter_counter` used in the `main` function is used as a counter array. The 1st element of the array acts as the counter for the characters 'A', 'a', the 2nd element acts as the counter for the characters 'B', 'b', and the last element acts as the counter for the characters 'Z', 'z'. This local array is zeroed out with the initialization statement. The first `for` loop statement iterates through all characters of the string, and if any character of the string is an alphabetic character, it is converted to uppercase, and the value 'A' is subtracted from this character. You see that the resulting value is used as the index for the `letter_counter` array, and the value of this indexed element of the `letter_counter` array is incremented by 1.

The second `for` loop statement then prints the values of the elements of the counter array that are not 0 to the screen.

In the following program, digit characters are deleted from a string received into an array. Examine the code:

    #include <stdio.h>
    #include <ctype.h>
    #define SIZE 500
    int main()
    {
        char str[SIZE];
        int k;
        int index = 0;
        printf("enter a string : ");
        gets(str);
        printf("string = (%s)\n", str);
        for (k = 0; str[k] != '\0'; ++k)
            if (!isdigit(str[k])) // Corrected from !isdigit[k] to !isdigit(str[k])
                str[index++] = str[k];
        str[index] = '\0';
        printf("string = (%s)\n", str);
        return 0;
    }

To delete digit characters from the string, the string is copied back to its location. However, digit characters are not copied during the copying process. The variable named `index` indicates where in the array the character will be written. If a character is not a digit character, this character is assigned to the `index`-indexed element of the array, and then the value of the `index` variable is incremented by 1. However, after exiting the `for` loop that traverses the entire string, the null character is added to the end of the string formed after the deletion operation.

The following program finds the total number of words in a string:

    #include <stdio.h>
    #define SIZE 200
    #define OUTWORD 0
    #define INWORD 1
    
    int is_sep(int ch)
    {
        char seps[] = " \t.,;:?!";
        int k;
        for (k = 0; seps[k] != '\0'; ++k)
            if (ch == seps[k])
                return 1;
        return 0;
    }
    
    int main()
    {
        char str[SIZE];
        int word_counter = 0;
        int k;
        int word_flag = OUTWORD;
        printf("enter a string : ");
        gets(str);
        for (k = 0; str[k] != '\0'; ++k)
            if (is_sep(str[k]))
                word_flag = OUTWORD;
            else if (word_flag == OUTWORD) {
                word_flag = INWORD;
                word_counter++;
            }
        printf("total %d words!\n", word_counter);
        return 0;
    }

The `is_sep` function tests whether a character whose sequence number is passed to it is one of the separator characters that separate words.

The flag variable named `word_flag` defined in the `main` function indicates whether one is inside or outside a word. You see that this variable is initialized with the value OUTSIDE\_WORD (`OUTWORD`).

A `for` loop statement is used to test whether each character of the string is a separator character. If it is a separator character, the value `OUTWORD` is assigned to the `word_flag` variable. If the character is not a separator character and the flag's value is also `OUTWORD`, the value `INWORD` is assigned to the flag, and the value of the counter that holds the word count is incremented by 1.

The following program reduces the number of consecutive identical characters in a string taken into an array to one:

    #include <stdio.h>
    #define SIZE 100
    int main()
    {
        char str[SIZE];
        int index = 0;
        int k;
        printf("enter a string : ");
        gets(str);
        // Corrected logic: start with str[0] already in place
        for (k = 1; str[k] != '\0'; ++k)
            if (str[k] != str[index]) // Compare current char to the last unique char written
                str[++index] = str[k];
        
        // Ensure the string is terminated correctly
        str[++index] = '\0';
        
        printf("string = (%s)\n", str);
        return 0;
    }