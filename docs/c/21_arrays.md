# 🗂️ Arrays

## What is a Data Structure?

Arrangements for storing logically related data concerning a topic in memory are called **data structures**. Data structures allow data stored in a specific order in memory to be accessed and certain operations to be performed efficiently on this data.

## What is an Array?

A data structure consisting of contiguous objects of the same type in memory is called an **array**. The most important feature of the array data structure is that data of the same type in a logical relationship are stored **contiguously** in memory. The benefit this provides in applications is this: Any element of the array can be accessed in **constant time** with the element's position information. That is, regardless of the number of elements in the array, the time to access an element whose position is known is the same. This facilitates the efficient implementation of some applications.

## Arrays in the C Language

In the C language, an array is a tool that allows one or more objects of the same type to be stored in memory in the form of the array data structure.

By defining an array in C, multiple objects can be defined with a single statement. Instead of defining an array with 10 elements, it is certainly possible to define 10 separate objects with different names. But when 10 separate objects are defined, it is not a guaranteed feature that these objects will be placed contiguously in memory. However, in an array definition, it is a guaranteed feature that all objects that are elements of the array are placed contiguously in memory. Since an array is also a data type, arrays must also be defined before they are used.

### Defining Arrays

The general form of array definitions is:

    <type> <array name> [<number of elements>];

In the general form above, the square brackets do not indicate that the number of elements is optional, but that the number of elements information must be written inside the square brackets.

* **type**: The keyword indicating the type of the array elements.
* **array name**: Any name given in accordance with the naming rules.
* **number of elements**: Indicates how many elements the array has.

Example array declarations:

    double a[20];
    int ave[10];
    char path[80];

In the definitions above:

* `a` is an array with 20 elements, each of type `double`.
* `ave` is an array with 10 elements, each of type `int`.
* `path` is an array with 80 elements, each of type `char`.

The expression specifying the number of elements in the definition must be a **constant expression of an integral type**. In other words, the compiler must be able to obtain the value of this expression at compile time:

    int x = 100;
    int a[x]; /* Invalid */
    int b[5.]; /* Invalid */
    int c[10 * 20]; /* Valid */
    int d[sizeof(int) * 100]; /* Valid */

The definitions of arrays `a` and `b` in the statements above are invalid. In the definition of array `a`, an expression that is not a constant expression is used as the size-specifying expression. In the definition of array `b`, the size-specifying expression is of a real number type. However, there is no error in the definition of array `c`. $10 * 20$ is a constant expression. The definition of array `d` also does not cause an error because the value produced by the `sizeof` operator is obtained at compile time.

Symbolic constants are frequently used instead of an expression specifying the number of elements in array declarations:

    #define ARRAY_SIZE 100
    int a[ARRAY_SIZE];

The `ARRAY_SIZE` symbolic constant can be used in place of the array size throughout the program. Thus, if a change regarding the array size is desired later in the program, only changing the value of the symbolic constant is sufficient.

As in other variable declarations, multiple arrays can be defined with the type-specifying word used only once, separated by the comma delimiter:

    int x[100], y[50], z[10];

`x`, `y`, and `z` are arrays whose elements are of type `int`.

Arrays and other objects can be defined with a single definition statement, provided their types are the same:

    int a[10], b, c;

`a` is an array of 10 `int` elements, and `b` and `c` are `int` type objects.

Each element of an array is a separate object. Array elements can be accessed with the **square bracket operator `[]`**. This operator is a pointer operator. This operator will be discussed in detail in the section "Pointers."

The operand of the square bracket operator is the array name. This is actually an address information, because when an array name is subjected to an operation, it is automatically converted by the compiler into the address of the first element of the array before the operation. Inside the square brackets, there must be an integer expression indicating the index of the element of the array to be accessed.

The first element of an array in the C language is the element with **zero index**.

For a type $T$, let $T \ a[\text{SIZE}]$ be an array. The first element of such an array is $a[0]$, and the last element is $a[\text{SIZE} - 1]$. Examples:

* `a[20]` /* The object that is the 20th indexed, i.e., 21st, element of array a */
* `ave[0]` /* The object that is the 0th indexed, i.e., first, element of array ave */
* `total[j]` /* The object that is the j-indexed element of array total */

As seen, the terms "the $n$-th element of an array" and "the $n$-indexed element of an array" refer to different elements of the array. The $n$-indexed element of an array is the $(n + 1)$-th element of that array.

A compiler that encounters an array definition allocates space in memory for the defined array. The space to be allocated is undoubtedly:

$$\text{number of elements} \times \text{space occupied by one element in memory}$$

in bytes. For example:

    int a[5];

If it is assumed that the `int` type occupies 4 bytes in memory when working in the Windows operating system, the compiler allocates $4 \times 5 = 20$ bytes of space in memory for the array $a$.

The `++` or `--` operators are frequently used in array index expressions:

    int a[20];
    int k = 10;
    int i = 5;

    a[k++] = 100;

The statement assigns the value 100 to the 10-indexed element of the array, i.e., the 11th element of the array. The value of the variable $k$ is then incremented by 1 to 11.

    a[--i] = 200;

The statement assigns the value 200 to the 4-indexed element of the array, i.e., the 5th element of the array. The value of the variable $i$ is then decremented by 1 to 4.

With the use of the square bracket operator, any element of the array can now be used like other variables. Examine the following examples:

    a[0] = 1; // The value 1 is assigned to the first element of array a.
    printf("%d\n", b[5]); // The value of the 6th element of array b is printed to the screen.
    ++c[3]; // The value of the 4th element of array c is incremented by 1.
    d[2] = e[4]; // The 5th element of array e is assigned to the 3rd element of array d.

Loop statements are frequently used to operate on arrays. Reaching all elements of an array with the help of a loop statement is a very common situation.

Some patterns using `for` and `while` loop statements for an array named `a` with $\text{SIZE}$ elements are shown below:

The value 0 is assigned to all elements of array $a$:

    for (i = 0; i < SIZE; ++i)
        a[i] = 0;

The same task could undoubtedly be performed with a `while` loop statement:

    i = 0;
    while (i < SIZE)
        a[i++] = 0;

Values are read into the elements of array $a$ from the standard input unit using the standard `scanf` function below:

    for (i = 0; i < SIZE; i++)
        scanf("%d", &a[i]);

or

    i = 0;
    while (i < SIZE)
        scanf("%d", &a[i++]);

The sum of the elements of array $a$ is calculated below:

    for (total = 0, i = 0; i < SIZE; i++)
        total += a[i];

or

    total = 0;
    i = 0;
    while (i < SIZE)
        total += a[i++];

### Array Overrun (Out-of-Bounds Access)

A compiler that sees an array definition allocates an area in memory large enough to hold all the array's elements:

    double a[10];

If a definition like this is made, and it is assumed that the `double` type occupies 8 bytes in memory on the system being worked on, a total of 80 bytes of contiguous space is allocated in memory for the array $a$.

The last element of the array is $a[9]$. A very frequent mistake is accidentally assigning a value to a location in memory that has not been allocated by the compiler to access the last element of the array, i.e., **overrunning the array**:

    a[10] = 5.;

The statement attempts to transfer a value to an 8-byte area whose purpose is unknown in memory, i.e., an unsafe memory region. Array overruns are **not checked at compile time**. Such errors are related to the program's runtime.

### Initializing Arrays

In variable definitions, a defined variable could be initialized with a specific value using a rule called the "initialization syntax."

Defined arrays can also be initialized:

    double sample[5] = {1.3, 2.5, 3.5, 5.8, 6.0};
    char str[4] = {'d', 'i', 'z', 'i'};
    unsigned a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

When arrays are initialized as above, the given values are assigned sequentially to the array elements, starting from the first element of the array.

It is not mandatory to initialize all elements of the array. If fewer elements are initialized than the number of elements in the array, the remaining elements are assigned the value **0**. This rule applies to both local and global arrays.

In this case, the shortest way to initialize all elements of an array to 0 is as follows:

    int a[20] = {0};

Only the first element of the array is given the initial value 0. In this case, the compiler generates code that automatically places the value 0 in the remaining elements of the array.

The expressions used to initialize array elements must be **constant expressions**.

    int a[10] = {b, b + 1, b + 2}; /* Invalid */

An initialization operation like this is invalid.

> \[The definition above is compliant with the rules of the C++ language. In C++, it is not mandatory to initialize array elements with constant expressions.]

Giving more initial values than the array size in an array initialization operation is invalid:

    int b[5] = {1, 2, 3, 4, 5, 6}; /* Invalid */

In the example above, although array $b$ has 5 elements, 6 values are used in the initialization statement. This results in a compile-time error.

The array size may not be specified in the initialization operation. In this case, the compiler calculates the array length itself by counting the initial values given. It assumes that the array is opened with that size. For example:

    int a[] = {1, 2, 3, 4, 5};

When the compiler sees the statement above, it assumes that array $a$ has 5 elements. In this case, a declaration like the one above is equivalent to a declaration like the one below:

    int a[5] = {1, 2, 3, 4, 5};

Other examples:

    char name[] = {'B', 'E', 'R', 'N', 'A', '\0'};
    unsigned short count[ ] = {1, 4, 5, 7, 8, 9, 12, 15, 13, 21};

The compiler assumes the size of the array `name` is 6 and the size of the array `count` is 10.

The initialization list for the array can be terminated with a comma token:

    int a[] = { 1, 4, 5, 7, 8, 9, 12, 15, 13,
                2, 8, 9, 8, 9, 4, 15, 18, 25,
              };

### Local and Global Arrays

An array, like other objects, can be local or global. Local arrays are arrays defined inside blocks. Global arrays are defined in the global namespace, i.e., outside all blocks. All elements of a global array have the characteristics of global objects. That is, if the array is global, the objects that are array elements have **file scope** and **static storage duration**. If a global array is in question and initial values are not given to the array elements, the array elements are initialized with the value **0**. However, when local arrays are in question, the objects that are array elements have **block scope** and **automatic storage class** in terms of lifetime. The array elements that have not been assigned a value contain **garbage values**.

Write and compile the following program:

    #include <stdio.h>
    #define SIZE 10
    int g[SIZE]; // Global array
    int main()
    {
        int y[SIZE]; // Local array
        int i;
        for (i = 0; i < SIZE; ++i)
            printf("g[%d] = %d\n", i, g [i]); // g elements will be 0
        for (i = 0; i < SIZE; ++i)
            printf("y[%d] = %d\n", i, y [i]); // y elements will be garbage values
        return 0;
    }

### Assigning Arrays to Each Other

Array elements are objects. However, the entirety of an array cannot be treated as a single object:

    int a[SIZE], b[SIZE];

After a definition like this, writing a statement like the following to copy the elements of array $b$ to the elements of array $a$ is a **syntax error**:

    a = b; /* Invalid */

An assignment like the one above causes a compile-time error. This is because the array names $a$ and $b$ do not denote Lvalues (objects). The total memory space occupied by the array cannot be directly treated as a single object. That is, the elements of the array are objects, but the array itself is not an object. In C, array names are address values, of the same type as the array's type, indicating the start of the memory block where the arrays are placed. Therefore, they are not **modifiable Lvalues**.

Two arrays can only be copied to each other using a loop statement:

    for (i = 0; i < SIZE; ++i)
        a[i] = b[i];

The loop statement above assigns the value of each element of array $b$ to the corresponding indexed element of array $a$. Another method for copying arrays is to use the standard C function **`memcpy`**. This function will be discussed in the section "Pointers."

### Examples Related to Array Usage

If objects of the same type are defined under an array, codes that process all array elements can be easily written with the help of a loop statement. Carefully examine the following example:

    #include <stdio.h>
    #include <stdlib.h>
    #include <time.h>
    #define SIZE 10
    int main()
    {
        int a[SIZE];
        int sum = 0;
        int k;
        srand(time(0));
        for (k = 0; k < SIZE; ++k) {
            a[k] = rand() % 100;
            printf("%d ", a[k]);
        }
        for (k = 0; k < SIZE; ++k)
            sum += a[k];
        printf("\nsum of a elements = %d\n", sum);
        return 0;
    }

The first `for` loop statement in the `main` function assigns random values between 0 and 99 to the elements of array $a$ with calls to the standard `rand` function. The value of each element of the array is also printed to the screen within the same loop. The subsequent second `for` statement sequentially adds the value of each element of array $a$ to the variable named `sum`.

The following program finds the value of the smallest element in an integer array:

    #include <stdio.h>
    #include <stdlib.h>
    #include <time.h>
    #define SIZE 10
    int main()
    {
        int a[SIZE];
        int sum = 0;
        int k, min;
        srand(time(0));
        for (k = 0; k < SIZE; ++k) {
            a[k] = rand() % 100;
            printf("%d ", a[k]);
        }
        min = a[0];
        for (k = 1; k < SIZE; ++k)
            if (min > a[k])
                min = a[k];
        printf("\nsmallest element = %d\n", min);
        return 0;
    }

You know the algorithm. The variable named `min` is defined to hold the value of the smallest element of the array. It is first assumed that the first element of the array is the smallest element of the array. Then, a `for` loop statement is used to check whether the values of the other elements of the array, starting from the 1-indexed element, are smaller than the value of the `min` variable. If the value of any element of the array is smaller than the value of the `min` variable, the value of the `min` variable is changed, and the value of the newly found element is assigned to the `min` variable. Upon loop exit, the `min` variable holds the value of the smallest element of the array, right?

The following program calculates the arithmetic averages of the odd and even elements of an integer array separately:

    #include <stdio.h>
    #define SIZE 10
    int main()
    {
        int a[SIZE] = {2, 3, 1, 7, 9, 12, 4, 8, 19, 10};
        int sum_of_odds = 0;
        int sum_of_even = 0;
        int no_of_odds = 0;
        int k;
        for (k = 0; k < SIZE; ++k)
            if (a[k] % 2) {
                sum_of_odds += a[k];
                no_of_odds++;
            }
            else
                sum_of_even += a[k];
        if (no_of_odds)
            printf("Average of odds = %lf\n",(double)sum_of_odds / no_of_odds);
        else
            printf("No odd numbers in the array!\n");
        if (SIZE - no_of_odds)
            printf("Average of evens = %lf\n",(double)sum_of_even /(SIZE - no_of_odds));
        else
            printf("No even numbers in the array!\n");
        return 0;
    }

The following program searches within an array:

    #include <stdio.h>
    #define SIZE 10
    int main()
    {
        int a[SIZE] = {2, 3, 1, 7, 9, 12, 4, 8, 19, 10};
        int k;
        int searched_val;
        printf("enter the value to be searched : ");
        scanf("%d", &searched_val);
        for (k = 0; k < SIZE; ++k)
            if (a[k] == searched_val)
                break;
        if (k < SIZE)
            printf("a[%d] = %d\n", k, a[k]);
        else
            printf("searched value not found in the array!\n");
        return 0;
    }

The variable named `searched_val` is defined to hold the value to be searched in the array. The value of this variable is read from the keyboard using the standard `scanf` function. Then, a `for` loop is created, and the equality of each element of the array to the searched value is tested with an `if` statement located in the loop body. If any element of the array is equal to the searched value, the loop is exited with the `break` statement. If the loop variable $k$ is less than the $\text{SIZE}$ value upon loop exit, the searched value has been found, i.e., the loop was exited with the `break` statement. If the loop was not exited with the `break` statement, the value of the variable $k$ becomes equal to the $\text{SIZE}$ value, right?

If the elements of the array are unsorted, all elements of the array must be checked to conclude that a value is not in the array.

However, if the array is sorted, the use of an algorithm called **binary search** allows the search operation to be performed much more efficiently:

    #include <stdio.h>
    #include <stdlib.h>
    #include <time.h>
    #define SIZE 100
    int main()
    {
        int a[SIZE];
        int k, mid, searched_val;
        int val = 1;
        int low = 0;
        int high = SIZE - 1; // Correct initialization for high
        srand(time(0));
        for (k = 0; k < SIZE; ++k) {
            a[k] = val;
            val += rand() % 10;
            printf("%d ", a[k]);
        }
        printf("\nenter the value to be searched : ");
        scanf("%d", &searched_val);
        
        while (low <= high) {
            mid = (low + high) / 2;
            if (a[mid] == searched_val)
                break;
            if (a[mid] > searched_val)
                high = mid - 1;
            else
                low = mid + 1;
        }
        if (low > high)
            printf("%d value was not found in the array!\n", searched_val);
        else
            printf("a[%d] = %d\n", mid, searched_val);
        return 0;
    }

The binary search algorithm is used in the `main` function above to search within a sorted array. Since the array is sorted, looking at the middle element of the array means half of the elements in the array are now excluded from the query, right?

The variable `low` holds the lowest index of the array segment to be searched, and the variable `high` holds the highest index. You then see that a `while` loop is created that iterates as long as the value of `low` is less than or equal to the value of `high`. The variable `mid` holds the index of the middle element of the array segment to be searched. It is checked whether the `mid`-indexed element of the array is the searched value. If the searched value is not found, there are two possibilities: If the `mid`-indexed array element is greater than the searched value, the value of the `high` variable is made `mid - 1`. Thus, the size of the array to be searched is halved. If the `mid`-indexed array element is smaller than the searched value, the value of the `low` variable is made `mid + 1`. Thus, the size of the array to be searched is again halved.

Upon exiting the `while` loop, if the value of `low` is greater than the value of `high`, it means the searched value was not found. Otherwise, the `mid`-indexed element of the array is the searched value.

### Sorting Arrays

Different algorithms can be used to sort the elements of an array from smallest to largest or from largest to smallest. Below, an array is sorted with the algorithm called **"bubble sort,"** which does not have very high perceptual complexity:

    #include <stdio.h>
    #define SIZE 10
    int main()
    {
        int a[SIZE] = {2, 3, 1, 7, 9, 12, 4, 8, 19, 10};
        int i, k, temp;
        for (i = 0; i < SIZE - 1; ++i)
            for (k = 0; k < SIZE - 1 - i; ++k)
                if (a[k] > a[k + 1]) {
                    temp = a[k];
                    a[k] = a[k + 1];
                    a[k + 1] = temp;
                }
        for (k = 0; k < SIZE; ++k)
            printf("%d ", a[k]);
        return 0;
    }

The same algorithm could also be coded using a `do while` loop:

    #include <stdio.h>
    #define SIZE 10
    #define UNSORTED 0
    #define SORTED 1
    int main()
    {
        int a[SIZE] = {12, 25, -34, 45, -23, 29, 12, 90, 1, 20};
        int i, k, temp, flag;
        do {
            flag = SORTED;
            for (k = 0; k < SIZE - 1; ++k)
                if (a[k] > a[k + 1]) {
                    temp = a[k];
                    a[k] = a[k + 1];
                    a[k + 1] = temp;
                    flag = UNSORTED;
                }
        } while (flag == UNSORTED);
        for (i = 0; i < SIZE; ++i)
            printf("a[%d] = %d\n", i, a[i]);
        return 0;
    }

The following program sorts the elements of an array from smallest to largest using the **"insertion sort"** algorithm:

    #include <stdio.h>
    #define SIZE 10
    int main()
    {
        int a[SIZE] = {2, 3, 1, 7, 9, 12, 4, 8, 19, 10};
        int i, k, temp;
        for (i = 1; i < SIZE; ++i) {
            temp = a[i];
            for (k = i; k > 0 && a[k - 1] > temp; --k)
                a[k] = a[k - 1];
            a[k] = temp;
        }
        for (i = 0; i < SIZE; ++i)
            printf("%d ", a[i]);
        return 0;
    }

To change the sorting direction from smallest to largest to largest to smallest, it would be enough to change the inner loop as follows:

    for (k = i; k > 0 && array[k - 1] < temp; --k)

The following program uses the **"selection sort"** algorithm to sort the array from smallest to largest:

    #include <stdio.h>
    #define SIZE 10
    int main()
    {
        int a[SIZE] = {2, 3, 1, 7, 9, 12, 4, 8, 19, 10};
        int i, k, min, index;
        for (k = 0; k < SIZE; ++k) {
            min = a[k];
            index = k;
            for (i = k + 1; i < SIZE; ++i)
                if (a[i] < min) {
                    min = a[i];
                    index = i;
                }
            a[index] = a[k];
            a[k] = min;
        }
        for (k = 0; k < SIZE; ++k)
            printf("%d ", a[k]);
        return 0;
    }

The following program places the odd-valued elements of the array at the beginning of the array in ascending order, and the even-valued elements at the end of the array in ascending order:

    #include <stdio.h>
    #define SIZE 10
    int main()
    {
        int a[SIZE] = {2, 3, 1, 7, 9, 12, 4, 8, 19, 10};
        int i, k, temp;
        for (i = 0; i < SIZE - 1; ++i)
            for (k = 0; k < SIZE - 1 - i; ++k)
                if (a[k] % 2 == a[k + 1] % 2 && a[k] > a[k + 1] ||
                    a[k] % 2 == 0 && a[k + 1] % 2 != 0) {
                    temp = a[k];
                    a[k] = a[k + 1];
                    a[k + 1] = temp;
                }
        for (k = 0; k < SIZE; ++k)
            printf("%d ", a[k]);
        return 0;
    }

Did you notice that the "bubble sort" algorithm is used again to achieve the goal, but the condition expression tested for swapping has been changed?

The following program reverses an array:

    #include <stdio.h>
    #define SIZE 10
    int main()
    {
        int a[SIZE] = {2, 3, 1, 7, 9, 12, 4, 8, 19, 10};
        int k;
        for (k = 0; k < SIZE / 2; ++k) {
            int temp = a[k];
            a[k] = a[SIZE - 1 - k];
            a[SIZE - 1 - k] = temp;
        }
        for (k = 0; k < SIZE; ++k)
            printf("%d ", a[k]);
        return 0;
    }

To reverse the array, the $n$-th element from the beginning is swapped with the $n$-th element from the end within a loop that iterates half the size of the array.

The function named `urand` defined below generates a different random number between $0$ and $\text{MAX}$ each time it is called. When the function is called after generating $\text{MAX}$ integers, it returns the value $-1$ to report an error state:

    #include <stdio.h>
    #include <stdlib.h>
    #include <time.h>
    #define MAX 100
    int flags[MAX] = {0};
    int urand(void)
    {
        int k, val;
        for (k = 0; k < MAX; ++k)
            if (flags[k] == 0)
                break;
        if (k == MAX)
            return -1;
        while (flags[val = rand() % MAX])
            ;
        ++flags[val];
        return val;
    }
    int main()
    {
        int k;
        srand(time(0));
        for (k = 0; k < MAX; ++k)
            printf("%d ", urand());
        printf("\n\n%d\n", urand());
        return 0;
    }

The function uses a global flag array named `flags` to understand whether an integer has been generated before. If the value of an element of the `flags` array is 0, it is understood that the value corresponding to that index has not yet been generated by the function. If the value of the array element is 1, it is understood that that value was generated before.

The `while (flags[val = rand() % MAX]);` loop is exited when the value of a randomly indexed element of the `flags` array assigned to the `val` variable is zero, right?

The following program prints a randomly generated numerical lottery coupon to the screen:

    #include <stdio.h>
    #include <stdlib.h>
    #include <time.h>
    #define KOLON_SAYISI 8
    void kolon_yaz() // print\_column
    {
        int numaralar[50] = {0}; // numbers
        int k, no;
        for (k = 0; k < 6; ++k) {
            while (numaralar[no = rand() % 49 + 1])
                ;
            numaralar[no]++;
        }
        for (k = 1; k < 50; ++k)
            if (numaralar[k])
                printf("%2d ", k);
    }
    int main()
    {
        int k;
        srand(time(0));
        for (k = 0; k < KOLON_SAYISI; ++k) {
            printf("column %2d : ", k + 1);
            kolon_yaz();
            printf("\n");
        }
        return 0;
    }

The `kolon_yaz` function prints a single column to the screen. You see that the local array named `numaralar` in the function is used again as a flag array. If the value of any indexed element of the array is 0, it indicates that the index value is a number that has not been generated before. The `while` loop inside the `for` loop iterates until a number that has not been generated before is found. Thus, 6 different numbers are generated by the `for` loop, which iterates 6 times.

The following program finds the value of the second largest element in an array:

    #include <stdio.h>
    #define SIZE 10
    int main()
    {
        int a[SIZE] = {12, 34, 3, 56, 2, 23, 7, 18, 91, 4};
        int k;
        int max1 = a[0];
        int max2 = a[1];
        if (a[1] > a[0]) {
            max1 = a[1];
            max2 = a[0];
        }
        for (k = 2; k < SIZE; ++k)
            if (a[k] > max1) {
                max2 = max1;
                max1 = a[k];
            }
            else if (a[k] > max2)
                max2 = a[k];
        printf("second largest value = %d\n", max2);
        return 0;
    }

The following program prints only the values of the unique elements in an array to the screen:

    #include <stdio.h>
    #include <stdlib.h>
    #include <time.h>
    #define SIZE 100
    int main()
    {
        int a[SIZE];
        int i, k;
        int counter;
        srand(time(0));
        for (k = 0; k < SIZE; ++k) {
            a[k] = rand() % 30;
            printf("%d ", a[k]);
        }
        printf("\n*******************************************************\n");
        for (i = 0; i < SIZE; ++i) {
            counter = 0;
            for (k = 0; k < SIZE; ++k)
                if (a[k] == a[i])
                    if (++counter == 2)
                        break;
            if (counter == 1)
                printf("%d ", a[i]);
        }
        printf("\n");
        return 0;
    }

The following program places different random values between $0$ and $\text{MAX}$ into all elements of an array of $\text{SIZE}$ elements:

    #include <stdio.h>
    #include <stdlib.h>
    #include <time.h>
    #define SIZE 50
    #define MAX 100
    int main()
    {
        int a[SIZE];
        int k;
        srand(time(0));
        for (k = 0; k < SIZE; ++k) {
            int val;
            while (1) {
                int i;
                val = rand() % MAX;
                for (i = 0; i < k; ++i)
                    if (val == a[i])
                        break;
                if (i == k)
                    break;
            }
            a[k] = val;
        }
        /* array is printed */
        for (k = 0; k < SIZE; ++k)
            printf("%d ", a[k]);
        printf("\n");
        return 0;
    }

The following program merges two sorted arrays into one sorted array:

    #include <stdio.h>
    #define SIZE 10
    int main()
    {
        int a[SIZE] = {2, 3, 6, 7, 8, 9, 13, 45, 78, 79};
        int b[SIZE] = {1, 2, 4, 5, 7, 9, 10, 18, 33, 47};
        int c[SIZE + SIZE];
        int k;
        int index1 = 0, index2 = 0;
        for (k = 0; k < SIZE + SIZE; ++k)
            if (index1 == SIZE)
                c[k] = b[index2++];
            else if (index2 == SIZE)
                c[k] = a[index1++];
            else {
                if (a[index1] < b[index2])
                    c[k] = a[index1++];
                else
                    c[k] = b[index2++];
            }
        for (k = 0; k < SIZE + SIZE; ++k)
            printf("%d ", c[k]);
        return 0;
    }