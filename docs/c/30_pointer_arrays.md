# 🗃️ Array of Pointers

Since pointers are also objects, arrays of pointers can also be defined. Arrays whose elements consist of pointer variables are called **"pointer arrays."** Examples:

    char *pstr[10];
    int *ap[50];
    float *kilo[10];

The declarations of pointer arrays are made with the `*` token, unlike normal array declarations. For example:

In the declaration:

    char str[100];

`str` is an array of 100 elements of type `char`, while in the declaration:

    char *pstr[100];

`pstr` is a **pointer array** of 100 elements of type `char *`. That is, each element of the array is an object of type `char *`. Each element of the array is a pointer variable.

When the compiler encounters a pointer array definition, it allocates a contiguous block of memory large enough to hold the specified number of pointer objects, just as it does for other arrays. For example:

    char *p[10];

With the declaration, the compiler understands that the array $p$ has 10 elements, and each element is a pointer of type `char *`. If the length of pointers is assumed to be 4 bytes on the system used, the compiler allocates a 40-byte memory block for this array. In this case:

    p[0], p[1], p[2], ...p[9]

each of the array elements is of type `char *`. Each object element of this array can be used independently of the others.

### Initializing Pointer Arrays

Pointer arrays can also be initialized. For example:

    int *p[] = {
        (int *) 0x1FC0,
        (int *) 0x1FC2,
        (int *) 0x1FC4,
        (int *) 0x1FC6,
        (int *) 0x1FC8
    };

Undoubtedly, for the addresses assigned to the elements of the pointer array to be used for a purpose, they must point to safe regions. For this reason, initializing pointer arrays other than `char` pointer arrays is not frequently encountered in applications. Generally, `char` pointer arrays are initialized with **string literals**.

## `char` Pointer Arrays

The most frequently seen in applications are `char` pointer arrays. You know that string literals are automatically converted to `char` array addresses by the C compiler. In this case, the elements of a `char` pointer array can be initialized with strings:

    char *aylar[] = {"January", "February", "March", "April", "May", "June",
                     "July", "August", "September", "October", "November", "December"};

Each element of the `aylar` array is a `char` pointer. This pointer array is initialized with string literals. In other words, each element of the `aylar` array, which is a `char` pointer array, points to the strings that are the names of the months of the year.

### Themes for Using `char` Pointer Arrays

`char` pointer arrays are frequently used in programs that deal with strings. Storing frequently used strings in the program in the elements of a pointer array instead of writing them as a string literal each time in the source code is a common theme. In the example below, the string messages related to errors are stored in each element of the `error_messages` array.

    char *error_messages[] = {"Insufficient Memory!", "Invalid Password", "File not found", 
                              "Specified file already exists", "Driver not ready", 
                              "File to be read cannot be opened", "File to be written cannot be opened..", 
                              "Undetermined error!"};

Now, when one of the strings is to be printed anywhere in the program, the starting address of the relevant string is obtained by accessing any element of the pointer array.

    /*...*/
    if (fp == NULL) {
        printf("%s\n", error_messages[5]); // Prints "File to be read cannot be opened"
        return 5;
    }

Now examine the following program:

    #include <stdio.h>
    // Assumed prototypes:
    int day_of_week(int day, int month, int year); 
    
    char *months[] = {"January", "February", "March", "April", "May", "June",
                      "July", "August", "September", "October", "November", "December"};
    char *days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday",
                    "Friday", "Saturday" };
    
    void display_date(int day, int mon, int year)
    {
        printf("%02d ", day);
        // Corrected index for months array (mon is 1-based)
        puts(months[mon - 1]); 
        printf(" %d ", year);
        // Assuming day_of_week returns 0-6
        printf("%s", days[day_of_week(day, mon, year)]); // Corrected function call
    }

In the program above, `char` pointer arrays named `months` and `days` are defined. Each element of the `months` array holds the starting address of the string containing a month name, and each element of the `days` array holds the starting address of the string containing a day name. The elements of the pointer array are initialized with string literals. You see that the `display_date` function receives the day, month, and year values related to a date, and utilizes the pointer arrays while printing the relevant date to the screen.

`char` pointer arrays are also frequently used for the purpose of testing whether a string is present within a specific group of strings. The equality of a string to a specific string can be tested with the standard `strcmp` function. So, how can it be determined whether a string is present within a group of strings?

The `get_month` function defined below tests whether a string whose starting address is sent to it is one of the English month names. If the string it tests is a valid month name, the function returns the information of which month it is ($1 - 12$). If the string sent to it does not correspond to a month name, the function returns the value 0.

    #include <stdio.h>
    #include <string.h>
    #define SIZE 20
    
    int get_month(const char *str)
    {
        // Changed month names to English for consistency with common usage/locale
        char *months[] = {"January", "February", "March", "April", "May", "June",
                          "July", "August", "September", "October", "November", "December"};
        int k;
        
        for (k = 0; k < 12; ++k)
            if (!stricmp(months[k], str)) // Assuming stricmp is available (case-insensitive)
                return k + 1; // Return 1-based month number
        return 0; // Not found
    }
    int main()
    {
        char s[SIZE];
        int result;
        printf("enter a month name: ");
        gets(s);
        result = get_month(s);
        if (result)
            printf("%s is the %dth month of the year\n", s, result);
        else
            printf("%s is not a valid month name\n", s);
        return 0;
    }

Recall that the non-standard `stricmp` function has no difference from the `strcmp` function, except that it performs the comparison of two strings without case sensitivity.

Pointer arrays, just like other arrays, can be local or global. If the array is global, each element of the array contains the value 0 when the array comes to life. Local pointer arrays contain random values. Since each element of the array holds address information, each element of uninitialized global pointer arrays contains the address 0 (NULL address). The elements of uninitialized local pointer arrays contain random address values.

To avoid a pointer error, safe addresses must first be placed in the elements of the pointer array. Since string literals are static duration entities, giving values to the elements of a pointer array with strings does not cause a pointer error. This is because string literals, as mentioned before, are first placed in a safe memory region by the compiler and then treated as the starting address of the block where they were placed.

In some cases, the **NULL address** is deliberately assigned to the last element of a pointer array. Such a pointer array can be processed without specifying the array size. Examine the following example:

    #include <stdio.h>
    int main()
    {
        int k;
        // NULL address at the end acts as a sentinel
        char *names[] = {"Ali", "Hasan", "Mehmet", "Sebahat", "Fatma",
                         "Tuncay", "Deniz", "Kerim", "Necati", NULL}; 
        
        for (k = 0; names[k] != NULL; ++k) // Loop until NULL is found
            puts(names[k]);
        return 0;
    }

In the example below, the elements of a `char` pointer array are sorted according to the magnitude (lexicographical order) of the strings they point to:

    #include <stdio.h>
    #include <string.h>
    #define SIZE 10
    int main()
    {
        // Array of pointers to string literals
        char *names[SIZE] = {"Ali", "Hasan", "Mehmet", "Sebahat", "Fatma",
                             "Tuncay", "Kaan", "Taylan", "Aleyna", "Deniz"};
        int i, k;
        char *temp; // Must be char * to hold a pointer
        
        printf("array is being printed!\n");
        for (k = 0; k < SIZE; ++k)
            puts(names[k]);
            
        // Bubble Sort algorithm
        for (k = 0; k < SIZE - 1; ++k)
            for (i = 0; i < SIZE - 1 - k; ++i)
                if (strcmp(names[i], names[i + 1]) > 0) { // Compares strings
                    // Swap pointers (swaps which string the array element points to)
                    temp = names[i];
                    names[i] = names[i + 1];
                    names[i + 1] = temp;
                }
        
        printf("sorted array is being printed!\n");
        for (k = 0; k < SIZE; ++k)
            puts(names[k]);
        return 0;
    }

The "bubble sort" algorithm is used again for sorting. The values of two consecutive elements of the pointer array are swapped if the condition:

    strcmp(names[i], names[i + 1]) > 0

is true. This means, "if the string pointed to by the $i$-indexed element of the array is lexicographically greater than the string pointed to by the $(i + 1)$-indexed element," right? What would happen if the swap operation was performed with the condition used when sorting other array types previously:

    if (names[i] > names[i + 1]) // Incorrect: compares addresses, not strings
        /* swap */;

Now examine the following code snippet:

    #include <stdio.h>
    int main()
    {
        // Missing comma between "Fatma" and "Tunc"
        char *names[6] = {"Ali", "Hasan", "Mehmet", "Sebahat", "Fatma" "Tunc"}; 
        int k;
        for (k = 0; k < 6; ++k)
            puts(names[k]);
        return 0;
    }

Could you see the bug?

You know that strings that have no characters other than whitespace between them are automatically combined by the compiler and treated as a single string. In the code snippet above, the comma token is missing between the string literal "Fatma" and the string literal "Tunc" used when initializing the elements of the array named `names`. In this case, the compiler combines these two strings and treats them as a single string, i.e., in the form "FatmaTunc". This string is assigned to the second-to-last element of the pointer array. In this case, the last element of the array is assigned the **NULL address**, right? The `for` loop in the `main` function also accesses the **NULL address**. This is undoubtedly a pointer error.

Below, a function named `syaz` (number-to-text) is defined that converts an integer to a string of text. Examine the use of pointer arrays in the function definitions:

    #include <stdio.h>
    
    // Helper function for 1-999 part of the number
    void yuzyaz(unsigned int val) 
    {
        static const char *birler[] = {"", "one", "two", "three", "four", "five",
                                      "six", "seven", "eight", "nine"};
        static const char *onlar[] = {"", "ten", "twenty", "thirty", "forty",
                                      "fifty", "sixty", "seventy", "eighty", "ninety"};
        int y = val / 100; // hundreds
        int o = val % 100 / 10; // tens
        int b = val % 10; // ones
        
        if (y > 1)
            printf("%s ", birler[y]); // e.g., "two hundred"
        if (y > 0)
            printf("hundred ");
        
        if (o > 0)
            printf("%s ", onlar[o]); // e.g., "forty"
        
        if (b > 0)
            printf("%s ", birler[b]); // e.g., "five"
    }
    
    void syaz(unsigned int val) // Main function for number-to-text
    {
        int billion, million, thousand, hundred;
        
        if (val >= 1000000000) {
            billion = val / 1000000000;
            yuzyaz(billion);
            printf("billion ");
        }
        
        if (val >= 1000000) {
            million = val % 1000000000 / 1000000;
            yuzyaz(million);
            if (million)
                printf("million ");
        }
        
        if (val >= 1000) {
            thousand = val % 1000000 / 1000;
            if (thousand >= 1) {
                yuzyaz(thousand);
                printf("thousand ");
            }
        }
        
        hundred = val % 1000;
        yuzyaz(hundred);
        printf("\n");
    }
    
    int main()
    {
        unsigned int val;
        printf("enter an integer:");
        scanf("%u", &val);
        syaz(val);
        return 0;
    }