# 📚 Standard Functions Operating on Strings

Some standard C functions take the starting address of a string as a parameter and perform several useful operations related to the string. These functions are called **string functions**. The declarations of string functions are in the **`string.h`** file.

## The `strlen` Function

This is one of the most frequently called standard C functions. The name of the function, `strlen`, comes from the words "string length." This function is used to obtain the character length of a string, i.e., the information of how many characters the string consists of.

The declaration of the function is in the form:

    size_t strlen(const char *str);

The parameter variable of the function is the starting address of the string whose length will be calculated. The function calculates the count of characters until it sees the null terminator. You can think of `size_t` written for the return value type as another name for the `unsigned int` type for now.

    #include <stdio.h>
    #include <string.h>
    int main()
    {
        char s[100];
        printf("enter a string : ");
        gets(s);
        printf("length of the string (%s) is = %zu\n", s, strlen(s));
        return 0;
    }

The standard C function `strlen` can be defined in the following forms:

    unsigned int mystrlen1(const char *str)
    {
        unsigned int length = 0;
        while (*str != '\0') {
            ++length;
            ++str;
        }
        return length;
    }

    unsigned int mystrlen2(const char *str)
    {
        unsigned int len;
        for (len = 0; str[len] != '\0'; ++len)
            ;
        return len;
    }

    unsigned int mystrlen3(const char *str)
    {
        const char *ptr = str;
        while (*str != '\0')
            str++;
        return str - ptr; // Pointer arithmetic difference
    }

## The `strchr` Function

The name of the function, `strchr`, comes from the words "string character." The `strchr` function is a standard C function used to search for a specific character within a character array.

The declaration of the function in the `string.h` file is as follows:

    char *strchr(const char *str, int ch);

This function searches for the character `ch`, which is its second parameter, starting from the address `str`, which is its first parameter, until it sees the null terminator. The character being searched for can also be the null terminator itself. The return value of the function is the address of the location where the character `ch` is found in the string, if it is found. If the character `ch` is not found in the string, the function returns the **NULL address**.

The `strchr` function can be defined as follows:

    #include <stdio.h>
    #include <string.h>
    int main()
    {
        char s[100];
        char *p, ch;
        printf("enter a string : ");
        gets(s);
        printf("enter the character you want to search for in the string : ");
        scanf("%c", &ch);
        p = strchr(s, ch);
        if (p == NULL)
            printf("searched character was not found\n");
        else
            printf("found: (%s)\n", p);
        return 0;
    }

    char *strchr(const char *str, int ch)
    {
        char c = ch;
        while (*str != '\0') {
            if (*str == c)
                return (char *)str;
            ++str;
        }
        if (ch == '\0') // Check if the null terminator itself was searched for
            return (char *)str;
        return NULL;
    }

## The `strrchr` Function

This standard function searches for a character within a string, similar to the `strchr` function. The search is performed starting from the **end** of the string. That is, when searching for the character 'n' in the string "ankara", the function returns the address of the last character. The declaration of the function in the `string.h` header file is as follows:

    char *strrchr(const char *str, int ch);

The function returns the address of the **last** occurrence of the character `ch` that can be found in the string at address `str`. If the character `ch` is not in the string, the return value of the function is the **NULL address**. The null terminator at the end of the string can also be searched for with this function.

    #include <stdio.h>
    char *mstrrchr(const char *str, int ch)
    {
        const char *p = str;
        const char *pf = NULL;
        while (*p) { // Iterate until null terminator
            if (*p == ch)
                pf = p; // Store the address of the last match found so far
            p++;
        }
        if (ch == '\0') // If searching for null terminator, return its address
            return (char *)p;
        return (char *)pf; // Return the address of the last match
    }
    int main()
    {
        char s[100];
        char *ptr;
        int ch;
        printf("enter a string : ");
        gets(s);
        printf("enter the character to be searched: ");
        ch = getchar();
        ptr = mstrrchr(s, ch);
        if (ptr == NULL)
            printf("'%c' was not found in the string \"%s\"!\n", ch, s);
        else
            printf("found: (%s)\n", ptr);
        return 0;
    }

## The `strstr` Function

The name of the function comes from the words "string string." This function is used to search for one string within another string. The declaration of the function is as follows:

    char *strstr(const char *p1, const char *p2);

If the string at address $p2$ is present within the string at address $p1$, the function returns the address of the location where the string is found. If it is not present, the return value of the function is the **NULL address**. Compile and run the following program:

    #include <stdio.h>
    #include <string.h>
    #define SIZE 100
    int main()
    {
        char s1[SIZE];
        char s2[SIZE];
        char *ptr;
        printf("enter the string to be searched within: ");
        gets(s1);
        printf("enter the string to be searched: ");
        gets(s2);
        ptr = strstr(s1, s2);
        if (!ptr)
            printf("string (%s) is not in string (%s)!\n", s2, s1);
        else
            printf("found! (%s)\n", ptr);
        return 0;
    }

## The `strcspn` Function

This function finds the index of the first character in a string that is also present in another string. The declaration of the function in `string.h` is as follows:

    size_t strcspn(const char *p1, const char *p2);

The return value can also be defined as follows: The function returns the length of the string segment starting from the beginning of string $p1$ that does **not** contain any characters from string $p2$.

    #include <stdio.h>
    #include <string.h>
    #define SIZE 100
    int main()
    {
        char s1[SIZE];
        char s2[SIZE];
        size_t index;
        printf("enter the string to be searched within: ");
        gets(s1);
        printf("characters: ");
        gets(s2);
        index = strcspn(s1, s2);
        printf("first match found at index %zu: (%s)\n", index, s1 + index);
        s1[index] = '\0'; // Truncate the string at the first match
        printf("truncated string: (%s)\n", s1);
        return 0;
    }

## The `strpbrk` Function

The standard `strpbrk` function searches for any character from one string within another string:

    char *mstrpbrk(const char *s1, const char *s2)

If any of the characters of the string at address $s2$ are present within the string at address $s1$, the function returns the address of this character. If none of the characters of string $s2$ are present in string $s1$, the function returns the **NULL address**.

Below is an example definition of the `strpbrk` function and a test code:

    #include <string.h>
    #include <stdio.h>
    #define SIZE 100
    char *mstrpbrk(const char *s1, const char *s2)
    {
        const char *p1, *p2;
        for (p1 = s1; *p1 != '\0'; ++p1) // Iterate through s1
            for (p2 = s2; *p2 != '\0'; ++p2) // Iterate through s2 for each char in s1
                if (*p1 == *p2)
                    return (char *)p1; // Return address of the first match in s1
        return NULL;
    }
    int main()
    {
        char str1[SIZE];
        char str2[SIZE];
        char *ptr;
        printf("enter the first string : ");
        gets(str1);
        printf("enter the second string : ");
        gets(str2);
        ptr = strpbrk(str1, str2);
        if (ptr == NULL)
            printf("none of the characters in (%s) are in the string \"%s\"!\n", str2, str1);
        else
            printf("found : (%s)\n", ptr);
        return 0;
    }

## The `strcpy` Function

This is a standard C function. The name of the function, `strcpy`, comes from the words "string" and "copy." The function sequentially writes all characters, including the null terminator, starting from the address held in its second parameter, until it sees the null terminator, starting from the address held in its first parameter. The declaration of the function in the `string.h` header file is as follows:

    char *strcpy(char *dest, const char *source);

The return value of the function is the address where the copy operation began, i.e., the **dest** address.

The `strcpy` function can be defined as follows:

    #include <stdio.h>
    #include <string.h>
    int main()
    {
        char dest[100] = "We are learning C!";
        char source[100];
        printf("enter the string to be copied : ");
        gets(source);
        printf("string before copying :(%s)\n", dest);
        strcpy(dest, source);
        printf("string after copying :(%s)\n", dest);
        return 0;
    }

    char *mystrcpy(char *dest, const char *source)
    {
        int i;
        for (i = 0; (dest[i] = source[i]) != '\0'; ++i) // Assigns and checks for null terminator
            ;
        return dest;
    }

In the second part of the `for` loop used in the function, assignment is performed first, and then the value of the assignment expression, i.e., the value on the right side of the assignment operator, is compared with the null terminator. Thus, the loop is exited after the null terminator is also copied to the relevant address.

The function could also be written as follows:

    /***/
    for (i = 0; source[i] != '\0'; ++i)
        dest[i] = source[i];
    dest[i] = '\0';
    /***/

Since the square bracket operator is used in the `for` loop statement, the value of the `dest` pointer variable, which is the first parameter variable, is not changed. The function returns with the `dest` address at the end. A `while` loop could have been used to continuously increment the address in the `dest` variable. In this case, to enable the function to return with the initial value of the `dest` pointer, it would be necessary to store the value in another pointer variable before changing the `dest` pointer:

    char *mystrcpy(char *dest, const char *source)
    {
        char *temp = dest;
        while ((*dest++ = *source++) != '\0') // Dereference, assign, then increment both pointers
            ;
        return temp;
    }

## The `strcat` Function

This is a standard C function. The name of the function comes from the words "string" and "concatenate." The `strcat` function is used to append one string to the end of another string. The declaration of the function in the `string.h` file is as follows:

    char *strcat(char *s1, const char *s2);

The `strcat` function appends the string whose starting address is held in the second parameter variable to the end of the first string (including the null terminator), overwriting the null terminator at the end of the string whose starting address is held in the first parameter variable, $s1$. That is, after the operation, the length of the string at address $s1$ increases by the length of the string at address $s2$.

The return value of the function is the starting address of the string to which the appending was performed, i.e., the **$s1$ address**.

    #include <stdio.h>
    #include <string.h>
    int main()
    {
        char s1[100], s2[100];
        printf("enter the string to be appended to: ");
        gets(s1);
        printf("length of the string you entered = %zu\n", strlen(s1));
        printf("enter the string you want to append : ");
        gets(s2);
        printf("length of the string to be appended = %zu\n", strlen(s2));
        strcat(s1, s2);
        printf("1st string after appending : ");
        puts(s1);
        printf("length of the string after appending : %zu\n", strlen(s1));
        return 0;
    }

The `strcat` function can be defined as follows:

    char *mystrcat(char *s1, const char *s2)
    {
        char *temp = s1;
        while (*s1 != '\0') // Find the null terminator of s1
            ++s1;
        while ((*s1++ = *s2++) != '\0') // Copy s2 starting from where s1's null terminator was, including the new null terminator
            ;
        return temp;
    }

Appending one string to the end of another string means copying the string to be appended to the location of the null terminator at the end of the other string, right? Therefore, the `strcat` function can also be defined in the following forms.

    char *mystrcat(char *s1, const char *s2)
    {
        strcpy(s1 + strlen(s1), s2); // s1 + strlen(s1) points to the null terminator
        return s1;
    }

    char *mystrcat(char *s1, const char *s2)
    {
        strcpy(strchr(s1, '\0'), s2); // strchr(s1, '\0') also finds the null terminator
        return s1;
    }

## The `strcmp` Function

This is a standard C function. The name of the function comes from the words "string compare." The function is used to compare two character strings. The comparison is the query of the precedence or equality status of the strings within the two character arrays, considering the character set table used. For example:

* The string "Adana" is considered smaller than the string "Ankara." This is because the character 'n', which breaks the equality, comes after the character 'd' in the ASCII character table.
* The string "ankara" is considered greater than the string "ANKARA." This is because lowercase letters come after uppercase letters in the ASCII table.
* The lowercase "masa" is greater than the uppercase "MASA."
* The string "kalem" is greater than the string "kale."

The declaration of the `strcmp` function in the `string.h` header file is as follows:

    int strcmp(const char *s1, const char *s2);

The function compares the string whose starting address is held in the first parameter variable ($s1$) with the string whose starting address is held in the second parameter variable ($s2$).

The return value of the function is:

* a **positive value** if the first string is greater than the second string,
* a **negative value** if the first string is smaller than the second string,
* the **value 0** if the first string and the second string are equal to each other.

    #include <stdio.h>
    #include <string.h>
    int main()
    {
        char s[20];
        char password[ ] = "Blue moon"; // Changed to English equivalent
        printf("enter the password : ");
        gets(s);
        if (!strcmp(s, password)) // If strcmp returns 0 (equal), !strcmp returns 1 (true)
            printf("Password correct!..\n");
        else
            printf("Password incorrect!..\n");
        return 0;
    }

The `strcmp` function can be defined as follows:

    int mystrcmp(const char *s1, const char *s2)
    {
        while (*s1 == *s2) { // Loop while characters are equal
            if (*s1 == '\0') // If they are equal and reached the end of string
                return 0;
            ++s1;
            ++s2;
        }
        // Comparison is done byte by byte (unsigned char to avoid sign extension issues)
        return *(unsigned char *)s1 > *(unsigned char *)s2 ? 1 : -1;
    }

## The `strncpy` Function

This is a standard C function. The name of the function comes from the words "string number copy." The function is used to copy the first **$n$** characters of a string (character array) to another location. The declaration of the function in `string.h` is as follows:

    char *strncpy(char *dest, const char *source, size_t n);

The function copies the number of characters held in its third parameter from the string whose address is held in the second parameter variable to the string whose starting address is held in the first parameter variable.

The return value of the function is the address where the copying will be performed, i.e., the **dest** address.

If the third parameter, $n$, is less than or equal to the length of the string to be copied, the function **does not add the null terminator** to the end of the first array after copying. That is, if $n \le \text{strlen}(\text{source})$, the null terminator is not added.

If the third parameter, $n$, is greater than the length of the string to be copied, the function appends null characters to the end of the first array after copying, up to $n$ characters in total.

The `strncpy` function is defined below:

    #include <string.h>
    #include <stdio.h>
    #define SIZE 100
    char *mstrncpy(char *s1, const char *s2, unsigned int n)
    {
        char *s = s1;
        // Copy characters while n > 0 AND s2 has characters
        while (n > 0 && *s2) {
            *s++ = *s2++;
            n--;
        }
        // Fill the rest with null terminators if n is still positive
        while (n--)
            *s++ = '\0';
        
        return s1;
    }
    int main()
    {
        char str1[SIZE];
        char str2[SIZE];
        int n;
        printf("enter the first string : ");
        gets(str1);
        printf("enter the second string : ");
        gets(str2);
        printf("how many characters to copy from the second string? ");
        scanf("%d", &n);
        strncpy(str1, str2, n);
        printf("(%s)\n", str1);
        return 0;
    }

Why do you think the null terminator is not added to the copied location if the value passed to the third parameter is less than or equal to the length of the copied string?

This function was intended to be able to perform replacement operations within strings:

    #include <string.h>
    #include <stdio.h>
    #define SIZE 100
    int main()
    {
        char str1[SIZE] = "Necati Ergin";
        char str2[SIZE] = "Mehmet Aktunc";
        strncpy(str1, str2, 6); // Replaces "Necati" with "Mehmet" (but without null terminator at end of "Mehmet")
        printf("(%s)\n", str1); // Output: (Mehmet Ergin)
        return 0;
    }

## The `strncat` Function

This is a standard C function. The name of the function comes from the English words "string number concatenate." It is used to copy a specific number of characters from one string to the end of another string. Its declaration in the `string.h` header file is as follows:

    char *strncat(char *s1, const char *s2, size_t n);

The function appends the number of characters held in its third parameter from the character array whose starting address is held in its second parameter to the end of the string whose starting address is held in its first parameter variable.

The return value of the function is the starting address of the string to which the appending was performed.

The function's definition and a test `main` function are given as an example below:

    char *mstrncat(char *s1, const char *s2, unsigned int n)
    {
        char *ptr;
        for (ptr = s1; *ptr != '\0'; ++ptr)
            ; // ptr points to the null terminator of s1
        while (n-- && *s2 != '\0') // Copy up to n characters or until end of s2
            *ptr++ = *s2++;
        *ptr = '\0'; // Add the new null terminator
        return s1;
    }
    #include <string.h>
    #include <stdio.h>
    #define SIZE 100
    int main()
    {
        char dest[SIZE];
        char source[SIZE];
        int n;
        printf("enter the first string : ");
        gets(dest);
        printf("enter the second string : ");
        gets(source);
        printf("how many characters to copy to the end of the 1st string : ");
        scanf("%d", &n);
        mstrncat(dest, source, n);
        printf("1st string after appending = (%s)\n", dest);
        return 0;
    }

## The `strncmp` Function

This is a standard C function. The name of the function comes from the words "string number compare." It is similar to the `strcmp` function, but this function is used to compare a specific number of characters of two strings, not the entire strings.

The function compares the number of characters held in its third parameter of the string whose starting address is held in the first parameter variable with the string whose starting address is held in the second parameter variable.

The function returns:

* a **positive value** if the first $n$ characters of the first string are greater than the first $n$ characters of the second string,
* a **negative value** if the first $n$ characters of the first string are smaller than the first $n$ characters of the second string,
* the **value 0** if the first $n$ characters of the first string and the second string are equal to each other.

Below is the definition of the function and a test `main` function:

    int strncmp(const char *s1, const char *s2, unsigned int n)
    {
        while (n--) {
            if (*s1 != *s2)
                return *(unsigned char *)s1 < *(unsigned char *)s2 ? -1 : 1;
            if (*s1 == '\0') // If the strings are equal up to the null terminator
                return 0;
            s1++;
            s2++;
        }
        return 0; // If n characters were compared and were all equal
    }
    #include <stdio.h>
    #define SIZE 100
    int main()
    {
        char str1[SIZE];
        char str2[SIZE];
        int n, result;
        printf("enter the first string : ");
        gets(str1);
        printf("enter the second string : ");
        gets(str2);
        printf("how many characters of the two strings will be compared? ");
        scanf("%d", &n);
        result = strncmp(str1, str2, n);
        if (result == 0)
            printf("(%s) == (%s)\n", str1, str2);
        else if (result > 0)
            printf("(%s) > (%s)\n", str1, str2);
        else
            printf("(%s) < (%s)\n", str1, str2);
        return 0;
    }

## The `strset` Function

This non-standard function is found in most compilers. The name of the function comes from the words "string" and "set." It is used to fill a character array with a specific character. The declaration of the function in the `string.h` header file is as follows:

    char *strset(char *str, int ch);

The function fills the string, whose starting address is in the first parameter variable, with the character held in the second parameter variable until it sees the null terminator. It does not touch the null terminator at the end of the string.

The return value of the function is again the starting address of the filled string.

    #include <stdio.h>
    #include <string.h>
    int main()
    {
        char s[100];
        int ch;
        printf("enter a string : ");
        gets(s);
        printf("what character do you want to fill the string with : ");
        ch = getchar();
        printf("\nstring filled with character %c: (%s)\n", ch, strset(s, ch));
        return 0;
    }

The `strset` function can be defined as follows:

    #include <stdio.h>
    char *mystrset(char *str, int ch)
    {
        int i;
        for (i = 0; str[i] != '\0'; ++i)
            str[i] = ch;
        return str;
    }

## The `strrev` Function

This non-standard function is also found in most compilers. The name of the function comes from the words "string reverse." The function is used to reverse a string. Its declaration in the `string.h` header file is as follows:

    char *strrev(char *str);

The function reverses the string whose starting address is held in the parameter variable. The return value of the function is the starting address of the reversed string.

The `strrev` function can be defined as follows:

    char *mystrrev(char *str)
    {
        int i, temp;
        int length = strlen(str);
        for (i = 0; i < length / 2; ++i) { // Loop only half the length
            temp = str[i];
            str[i] = str[length - i - 1];
            str[length - i - 1] = temp;
        }
        return str;
    }

## The `strupr` and `strlwr` Functions

These functions are not standard but are found in almost every compiler. Their names come from the words "string upper" and "string lower." These functions perform uppercase/lowercase conversion for all characters of a string. The return values of the functions are the addresses passed to their parameters. Their return values are generally not needed. Both functions perform conversion for letters in the basic Latin alphabet. If conversion is required for non-Latin characters, a custom function must be defined for this purpose.

    #include <stdio.h>
    #include <string.h>
    // Assuming strupr and strlwr are available
    int main()
    {
        char s[] = "One must work hard to become a C programmer!";
        strupr(s);
        puts(s); // Output: ONE MUST WORK HARD TO BECOME A C PROGRAMMER!
        strlwr(s);
        puts(s); // Output: one must work hard to become a c programmer!
        return 0;
    }

The `strupr` function can be defined as follows:

    #include <stdio.h>
    #include <ctype.h>
    char *mystrupr(char *str)
    {
        char *temp = str;
        while (*str != '\0') {
            if (islower(*str))
                *str = toupper(*str);
            ++str;
        }
        return temp;
    }

## Advancing a Pointer Holding a String's Starting Address to the End of the String

In many programs, it is necessary to find the end of a string whose starting address is held. To make a pointer variable holding the starting address of a string point to the null terminator at the end of the string, three separate patterns can be used:

Let $p$ be a pointer holding the starting address of a string. All the following statements advance the pointer variable $p$ to the location of the null terminator at the end of the string.

    p += strlen(p); // Uses string length (most efficient)
    
    p = strchr(p, '\0'); // Uses strchr function
    
    while (*p != '\0') // Classic loop
        ++p;

After exiting the following loop, the pointer $p$ points to the address **after** the null terminator. Why?

    while (*p++ != '\0')
        ;

The postfix `++` increments the pointer *after* the dereferenced value is checked against `'\0'`.

## The Null String

A **null string** is a string of length 0. Let $str$ be a `char` array. If $str[0]$ is the null terminator, a null string is held in the `str` array. A null string is a valid string.

Functions that operate on strings must also work correctly if the strings whose addresses they receive are a **null string** (`""`). Examine the following loop:

    while (*++p != '\0')
        ;

Let $p$ be a pointer variable holding the starting address of a string. When the loop above is exited, $p$ points to the null terminator at the end of the string. However, if the string pointed to by $p$ is a null string, the loop above begins operating on the memory area that does not belong to the string. This is undoubtedly a programming error.

Now, examine the following `if` statement:

    int strfunc(const char *ptr)
    {
        if (!ptr || !*ptr) // Checks for NULL pointer OR empty string
            return 0;
        /***/
    }

The expression:

    !ptr || !*ptr

in the `if` statement located in the `strfunc` function is true if the value of the pointer variable `ptr` is the **NULL address** OR if the string pointed to by `ptr` is an **empty string** (`*ptr` is `'\0'`). This expression means, "if $ptr$ does not point to a string or the string pointed to by $ptr$ is empty."

The logical inverse of this expression:

    ptr && *ptr

means, "if $ptr$ points to a string AND the string pointed to by $ptr$ is not empty," right?

Both expressions utilize the **short-circuit evaluation** feature of the logical operators. If the logical `&&` or `||` operators did not have short-circuit behavior, the object pointed to by `ptr` would be attempted to be accessed when the value of `ptr` is the `NULL` address.

## Examples

Below, some functions that operate on strings are defined. Examine the use of pointer variables in the functions.

Below, a function named `is_valid_id` is defined, which tests whether a string is a valid identifier according to C rules. The function returns a non-zero value if the string is a valid identifier, and zero otherwise:

    #include <ctype.h>
    int is_id(const char *ptr)
    {
        int ch;
        // Not a valid identifier if it is an empty string
        if ((ch = *ptr++) == '\0')
            return 0;
        // The first character must be a letter or an underscore
        if (!(isalpha(ch) || ch == '_'))
            return 0;
        // The remaining characters must be a letter, digit, or underscore
        while ((ch = *ptr++) != '\0')
            if (!(isalnum(ch) || ch == '_'))
                return 0;
        return 1;
    }