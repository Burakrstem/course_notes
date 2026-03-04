# 🏗️ Structures

## What is a Structure?

**Structures** are tools that allow the programmer to create multiple objects. By using structures, multiple objects that are placed consecutively in memory can be created. You know that objects placed contiguously in memory can also be created with array definitions. However, structures have some differences from arrays: While arrays can hold objects of the same type, structures can hold objects of **different types**. This is the main reason for using structures. Often, a set of objects of different types can logically form a whole. Information such as name, age, gender, department, salary, and education status can be stored in objects of different types. All of this might be information belonging to a person working in a workplace. Logically related data of different types can be stored within structures.

Suppose an `int` array with 10 elements is defined:

    int a[10];

Assuming the `int` type occupies 4 bytes on the system used, a 40-byte block is allocated in memory for this array, right? The programmer can perform direct operations on the element objects by accessing the elements of this array with the square bracket operator. However, the array as a whole cannot be used as a single object. That is, the C language does not view the entirety of an array as a single object. Recall that array names are converted to the addresses of the object that is the first element of the array in C. The situation is slightly different with structures. With the use of structures, a sequential block is also allocated for multiple objects. However, this time, the **entire block can also be used as a single object**. Just as we can perform operations on the objects that are elements of the structure, we can also perform some operations directly on the entire block formed by these objects.

## A Structure as a Programmer-Defined Type

By using structures, the programmer can create a **new type**. In addition to C's existing native data types, new types that abstract a logical meaning can be created. For example, a type whose value is date information or a type whose value is a complex number can be created. This way, the problem domain we want to solve with programming can be modeled better. A good understanding of structures helps in a good understanding of object-based and object-oriented programming techniques later on.

### Structure Declaration

Structures allow the programmer to create a new type. The first step that needs to be taken for structures to be used is to introduce this new type to the compiler. The introduction process is done with a **structure declaration**. The compiler, seeing the structure declaration, gains information about this new type. The following information is given to the compiler with this declaration:

* The name of the type
* How much space the type occupies in memory
* The names of the elements

After the compiler sees a structure declaration, it learns how much space to allocate in memory for an object of this type when such an object is defined, and it can perform some checks related to the expressions for the use of this object by the programmer at compile time.

A structure declaration has a specific syntax.

### General Form of Structure Declaration

    struct [structure tag] {
        <type> <member name>;
        <type> <member name>;
        <type> <member name>;
        ...
    };

`struct` is a keyword. It must be included in the declaration. The `struct` keyword can be followed by a **structure tag**. The structure tag is a name chosen in accordance with the C language's naming rules. A block follows the structure tag. This block specifies a declaration region. Declarations of the structure members are made within this block.

Examples:

    struct Date {
        int day, month, year;
    };
    
    struct Point {
        int x, y;
    };
    
    struct Complex {
        double real;
        double imag;
    };

Structure tags must comply with the naming rules. However, most programmers choose to capitalize the first letter of structure tags and use lowercase for the other letters.

Making a structure declaration **does not** cause the compiler to allocate space in memory. That is, a definition is not in question. With this declaration, information about the new data type created by the programmer is given to the compiler. The compiler uses this information as a template for objects to be created from this type.

The names of the types created with the declarations above are, respectively, **`struct Date`**, **`struct Point`**, and **`struct Complex`**. That is, the type name is obtained by combining the `struct` keyword and the structure tag. The structure tag alone does not specify type information. However, let us state that we will see tools that allow creating a type name without the `struct` keyword later.

### Location of Structure Declarations

Like all declarations, structure declarations can be made at the local or global level. Like all declarations, structure declarations also have scope. If the declaration is made within a block, the declared structure is known only within the block where the declaration was made.

Structure declarations are made within a block only in very special situations. For all functions in the source file to be able to use the newly created type, the declaration is almost always made at the **global level**. Since other source files that call the defined functions often have to use the same structure, structure declarations are generally placed in the **header files** of the modules. Thus, the same declaration is made in a source file that includes the relevant header file.

### Defining Variables of Structure Type

Just as objects of native types are defined, a variable of a structure type is defined with the same syntax. That is, first the type-specifying keywords are written, and then the name of the structure variable:

    struct Date bdate;
    struct Point p1, p2;

It is assumed that the definitions above are made at a point where the relevant structure declarations are visible. Defining a structure variable at a source code point where the structure declaration is not visible is invalid.

With the definition:

    struct Date mydate;

a variable named `mydate` whose type is `struct Date` is defined.

With the definition:

    struct Point p1, p2, p3;

three separate variables named `p1`, `p2`, and `p3` whose types are `struct Point` are defined.

The fundamental properties of objects are not dependent on the type of the objects. Undoubtedly, the scope, storage duration, and linkage properties of structure objects can also be referred to. These properties carry the same meaning for structure objects as they do for native data types.

A structure object defined in the global namespace:

i) Belongs to the **file scope**. All functions located after the object's definition can access this structure object.
ii) Has **static storage duration**. It occupies space in memory from the beginning of the program's runtime until the program terminates.
iii) Since it has static storage duration, if no initial value assignment is made, all bytes it occupies in memory are filled with 0 bits. The practical meaning of this is that the value of all elements of the structure is 0.

A structure object defined in the local area:

i) Belongs to the **block scope**. This object can only be accessed within the block where its definition was made.
ii) Has **automatic storage duration**. The object is created when the program flow enters the block where the object is defined. The object is deallocated from memory when the program flow leaves the block where the object is defined.
iii) Since it has automatic storage duration, if no initial value assignment is made, there are **garbage values** in the area it occupies in memory. The practical meaning of this is that all elements of the structure are initialized with garbage values.

Specifiers can be used in the declarations and definitions of structure objects. For example, a local or global structure object can be defined with the `static` or `const` specifier. The meanings that these specifiers add to declarations or definitions do not differ for structure objects.

Structure variables are **composite objects**. That is, they consist of parts, or sub-objects. Indeed, one operation performed with a structure declaration is to give the compiler information about the names and types of these parts. For a structure variable (object), space is allocated in memory equal to the total length (in bytes) of the members specified in the structure declaration. Examine the following example:

    #include <stdio.h>
    struct Sample {
        int i;
        long l;
        double d;
    };
    int main()
    {
        struct Sample sam;
        printf("%zu\n", sizeof(sam));
        return 0;
    }

When the program above runs on UNIX, it prints the value 16 (assuming common sizes and alignment). This is because the space occupied in memory by the object `sam`, which is of type `struct Sample`, is the sum of the length occupied by its three members. This can also be expressed as follows (ignoring potential padding/alignment for now):

$$\text{sizeof}(\text{sam}) \approx \text{sizeof}(\text{int}) + \text{sizeof}(\text{long}) + \text{sizeof}(\text{double})$$

This point will be revisited regarding **alignment**.

### Combining Structure Declaration and Variable Definition

If a list of variables is written immediately after the closing curly brace of a structure declaration, before the declaration is terminated with a semicolon, the structure declaration and variable definition are performed together.

    struct Date {
        int day, month, year;
    } bdate, edate;

With the statement above, while the `struct Date` type is declared, the variables `bdate` and `edate` of this structure type are also defined. In this case, the scope of the structure variables is determined based on the location where the structure declaration is placed. That is, the structure variables in question can be local or global.

There is no obligation to use the structure name when structure objects are defined immediately after the structure declaration. For example, the declaration above can also be made as follows.

    struct {
        int day, month, year;
    } bdate, edate;

Here, `bdate` and `edate` are variables of the un-named structure type declared above. The disadvantage of this method is that it is no longer possible to define another structure variable of the same type. For example, suppose we wanted to define another structure object of the same structure type after the code snippet above. Even if this definition were made in the form:

    struct {
        int day, month, year;
    } cdate;

the compiler treats these two structure types, whose declarations are equivalent, as **separate** structure types. Therefore, an assignment like:

    cdate = bdate;

is invalid because the structure types are different.

Another disadvantage of such a definition is that a function cannot be written related to this structure type. This is because the structure type has no name. A function's parameter variable cannot be defined without type information.

### Structures and Namespaces

Structure names (tags) and structure member names are evaluated in **separate namespaces**:

The following code is valid:

    void func()
    {
        struct x {int x;} x; // The structure tag is 'x' and the variable name is 'x'
    }

### Accessing Structure Members

An important difference of structures from arrays is in accessing members. While array members are accessed via the array name and the square bracket operator `[]` (index operator - subscript operator), the **dot operator (`.`)** is used to access structure members.

The token for the dot operator is `.`. The dot operator is a **binary infix** operator. The left operand of this operator must be a **structure type object**. The right operand of the operator must be one of the members of the relevant structure type to which the object belongs. The dot operator is located at the **highest precedence level** of the operator precedence table.

When a structure object is defined and the members of this structure object are accessed with the dot operator, each of these members is now treated as a separate object. These objects are no different from objects defined outside the structure. Compile and run the following code:

    #include <stdio.h>
    struct Sample{
        int i;
        long l;
        double d;
    };
    int main()
    {
        struct Sample sam;
        sam.i = 10;
        sam.l = 200000L;
        sam.d = 1.25;
        printf("sam.i = %d\nsam.l = %ld\nsam.d = %lf\n", sam.i, sam.l, sam.d);
        return 0;
    }

As seen in the example above, the structure members `sam.i`, `sam.l`, and `sam.d` exhibit separate object characteristics. They can be accessed individually, and individual assignments can be made to them. These objects can be the operand of the `++` and `--` operators or the address-of operator.

### Memory Layout of Structure Members

Structure members are placed contiguously in memory, with the first-declared member being at the lowest numerical address. Compile and run the following program:

    struct Sample{
        int i;
        long l;
        double d;
    };
    #include <stdio.h>
    int main()
    {
        struct Sample sam;
        printf("address of sam.i = %p\n", &sam.i);
        printf("address of sam.l = %p\n", &sam.l);
        printf("address of sam.d = %p\n", &sam.d);
        return 0;
    }

### Operations That Can Be Performed on Structure Objects

When the structure objects themselves are in question, i.e., when a structure object is treated as a whole, it can only be the operand of four operators: the **dot operator**, the **`sizeof` operator**, the **address-of operator**, and the **assignment operator**. It is invalid for a structure object to be the operand of an operator other than these.

#### The `sizeof` Operator and Structures

A structure object can be the operand of the `sizeof` operator. In this case, the value produced by the `sizeof` operator is the number of bytes the object's type occupies in memory. You know that the operand of the `sizeof` operator can also be a type name. Examine the following example:

    struct Point {
        int x, y;
    };
    int main()
    {
        struct Point p;
        printf("sizeof(struct Point) = %zu\n", sizeof(struct Point));
        printf("sizeof(p) = %zu\n ", sizeof(p));
        return 0;
    }

In the `printf` call inside the `main` function above, the operand of the `sizeof` operator is a type name (`struct Point`), while in the second `printf` call, the operand of the `sizeof` operator is the object $p$ of type `struct Point`.

#### The Address-of Operator and Structure Objects

A structure object can be the operand of the address-of operator. In this case, the value produced by the address-of operator is address information of the relevant structure type:

Suppose a structure named `struct Date` is defined as follows, and an object is defined after it:

    struct Date {
        int d, m, y;
    };
    struct Date mydate = {4, 3, 1964};

The expression `&mydate` is a valid expression. This expression is of the **(struct Date \*) type**.

Are `&mydate` and `&mydate.day` the same addresses? While the numerical components of these addresses are the same, their type components are different. The two expressions are two different address information of different types with the same numerical components.

The type of the expression `&mydate` is `(struct Date *)`, while the type of the expression `&mydate.day` is `(int *)`.

#### The Assignment Operator and Structure Objects

A structure object can be the left or right operand of the assignment operator. A structure object can only be assigned another structure object of the **same type** with the assignment operator. It is invalid for the types on the right and left sides of the assignment operator to be different structure types. In the assignment of two structure objects of the same type to each other, the structure members are assigned to each other correspondingly. That is, a **block copy** is in question. The two structure variables must definitely be of the **same type** for the assignment operation. If the two structure variables are not of the same type, this situation is invalid. For two structures to be of the same type, they must be defined with the same structure name. The following two structures specify two different types, even though the types and names of their members are the same, and objects from these types cannot be assigned to each other.

    struct POINT_1 {
        int x, y;
    };
    struct POINT_2 {
        int x, y;
    };
    void func()
    {
        struct POINT_1 a;
        struct POINT_2 b;
        b.x = 10;
        b.y = 20;
        a = b; /* Invalid: POINT_1 and POINT_2 are different types */
    }

Assigning two structure objects to each other results in all members of the objects being assigned to each other correspondingly. That is, a block copy is in question. It should be kept in mind that the cost of assigning structure objects to each other with the assignment operator is high, especially when large structures are in question. A memory block the size of $\text{sizeof}(\text{struct Data})$ is copied, much like a `memcpy` function.

Compile and run the following program:

    #include <stdio.h>
    #include <string.h>
    struct Data{
        int i;
        long l;
        double d;
    };
    int main()
    {
        struct Data d1, d2, d3, d4;
        d1.i = 10;
        d1.l = 200000L;
        d1.d = 1.25;
        d2 = d1; // Assignment copies the block
        d3.i = d2.i;
        d3.l = d2.l;
        d3.d = d2.d;
        memcpy(&d4, &d3, sizeof(struct Data)); // memcpy also copies the block
        
        printf("d1.i = %d\nd1.l = %ld\nd1.d = %lf\n\n", d1.i, d1.l, d1.d);
        printf("d2.i = %d\nd2.l = %ld\nd2.d = %lf\n\n", d2.i, d2.l, d2.d);
        printf("d3.i = %d\nd3.l = %ld\nd3.d = %lf\n\n", d3.i, d3.l, d3.d);
        printf("d4.i = %d\nd4.l = %ld\nsam4.d = %lf\n\n", d4.i, d4.l, d4.d);
        return 0;
    }

In the `main` function above, you see that 4 variables named `d1`, `d2`, `d3`, and `d4` of type `struct Data` are defined. The value of the variable `d1` is assigned to the variable `d2` using the assignment operator. Copying is also performed from the object `d3` to the object `d4` using the standard `memcpy` function.

#### The Type Cast Operator and Structure Objects

A structure object cannot be the operand of the type cast operator. That is, code like the following is also invalid:

    struct S1 {
        int a, b;
    };
    struct S2 {
        int a, b;
    };
    void func()
    {
        struct S1 s1;
        struct S2 s2;
        s1.a = 10;
        s1.b = 20;
        s2 = (struct S2)s1; /* Invalid! Cannot cast between structures */
    }

#### Memory Layout of Structure Members Revisited

Structure members are placed contiguously in memory, with the first-declared member being at the lowest address. Compile and run the following program:

    #include <stdio.h>
    struct Date {
        int day, mon, year;
    };
    int main()
    {
        struct Date date;
        printf("address of date.day = %p\n", &date.day);
        printf("address of date.mon = %p\n", &date.mon);
        printf("address of date.year = %p\n", &date.year);
        return 0;
    }

### Using Arrays as Structure Members

An element of a structure can be an array of any type. In this case, the name of the array member of the structure does not denote an object, but is **address information**. First, examine the following example:

    #include <stdio.h>
    #define NAME_LEN 20
    struct Person {
        char name[NAME_LEN];
        int no;
    };
    int main()
    {
        struct Person per;
        gets(per.name); // Passes the address of the array per.name
        puts(per.name);
        putchar(per.name[3]);
        // per.name++; /* Invalid. Array name is not an Lvalue. */
        return 0;
    }

One member of the declared `struct Person` structure is a 20-element `char` array. In this case, if our source code is compiled on the Unix operating system, $\text{sizeof}(\text{struct Person})$ will be 24 (likely $20 + 4$). Each object of type `struct Person` defined contains a 20-element `char` array.

The expression `per.name` used in the `main` function is the starting address of the `char` array located inside the `per` structure object. When this expression is subjected to an operation, it is automatically converted to a `char *` type by the compiler.

With the call `gets(per.name);`, the starting address of the `char` array `name` inside the `per` object is passed to the `gets` function. Thus, the string read from the keyboard is placed into the array inside the object.

Similarly, the string inside this array is printed to the screen with the call `puts(per.name);`.

However, if desired, any element of the array inside the object can be accessed with the square bracket operator or the indirection operator:

    per.name[3]
    *(per.name + 3)

The type of the expressions above is `char`. These expressions correspond to the `char` type object that is the 3-indexed element of the `name` array inside the `per` object.

The $\text{sizeof}$ value of the `struct Person` type does not change, regardless of the length of the string held in the array member of the structure. In some cases, arrays located inside structure objects are not preferred because they unnecessarily increase the size of the structure object.

Why would an element of a structure be an array? This way, a specific number of values of the same type can be held within a structure object. Suppose the information related to a student is modeled with a structure type. An `int` array that will hold the student's grades can be located inside such a structure. However, the most commonly seen situation in applications is the storage of string information within `char` arrays located inside the structure.

Another way to hold a specific number of values of the same type associated with a structure object is for one of the structure's members to be a **pointer**.

### Using Pointer Variables as Structure Members

An element of a structure can be a pointer of any type. Examine the following example:

    #include <stdio.h>
    struct Person {
        char *name_ptr;
        int no;
    };
    int main()
    {
        struct Person per;
        per.name_ptr = "Necati Ergin"; // Assigns string literal address
        per.no = 125;
        printf("%s %d\n", per.name_ptr, per.no);
        return 0;
    }

In the code snippet above, one member of the `struct Person` type is chosen as a `char` pointer this time. Since a pointer occupies 2 or 4 bytes on the system used, the $\text{sizeof}$ value of the `struct Person` structure above would be 8 bytes under UNIX (4 bytes for the pointer + 4 bytes for the integer).

With the expression:

    per.name_ptr = "Necati Ergin";

the string literal "Necati Ergin" is assigned to the member named `name_ptr` of the `per` object. You know that string literals are address information, evaluated by the compiler as `char *` type expressions.

The expression `per.name_ptr` is an expression denoting an object of type `char *`. This expression corresponds to the `char` pointer variable located inside the `per` object.

For assignment to be made to the location pointed to by this pointer, i.e., to the expressions:

    *per.name_ptr
    per.name_ptr[n]

without causing a pointer error, the member pointer must point to a safe address first.

The fact that an element of a structure is a pointer is often desired for the structure object to use a dynamically obtained memory area. Examine the following code snippet:

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #define ARRAY_SIZE 100
    struct Person {
        char *name_ptr;
        int no;
    };
    int main()
    {
        struct Person per;
        char name_entry[ARRAY_SIZE];
        printf("enter name : ");
        gets(name_entry);
        
        per.name_ptr = (char *)malloc(strlen(name_entry) + 1); // Dynamic allocation
        if (per.name_ptr == NULL) {
            printf("cannot allocate memory!\n");
            exit(EXIT_FAILURE);
        }
        
        strcpy(per.name_ptr, name_entry); // Copy to dynamic block
        
        printf("enter number : ");
        scanf("%d", &per.no);
        
        printf("name = %s\nNo : %d\n", per.name_ptr, per.no);
        /*...*/
        free(per.name_ptr); // Free the dynamic block
        return 0;
    }

Let's examine what happens in the `main` function sequentially: You first see that a variable named `per` of type `struct Person` is defined. The name entered from the keyboard is first received into the local `name_entry` array with the standard `gets` function. A block of memory one byte larger than the length of the name received into the local array is dynamically obtained with the `malloc` function. Allocating space one byte larger than the string length aims to ensure space for the null terminator at the end of the string. You see that the starting address of the dynamic area is stored in the `name_ptr` member of the `per` object. Then, the name in the local array is copied to the allocated dynamic block using the standard `strcpy` function.

The `per` object thus controls a dynamic area through its member pointer `name_ptr`, right? To access the name held by a `struct Person` object, one can access the `name_ptr` member of the object and access the dynamic block from the value of this member. To prevent a memory leak before the object's lifespan ends, the dynamic block must be returned.

You see that the deallocation operation is performed with the call:

    free(per.name_ptr);

### Initializing Structure Variables

You know that there is a special syntax for initializing arrays. Structure variables can also be initialized with a similar syntax. The given initial values are placed into the structure members sequentially. Initial values can be given for a smaller number of structure members. In this case, uninitialized structure members automatically receive the value **0**.

    #include <stdio.h>
    struct Date {
        int day, month, year;
    };
    int main()
    {
        struct Date x = {10, 12, 1999};
        struct Date y = {10}; // y.month and y.year are initialized to 0
        printf("%d %d %d\n", x.day, x.month, x.year);
        printf("%d %d %d\n", y.day, y.month, y.year);
        return 0;
    }

In the initialization syntax, the assignment operator following the name of the structure object is followed by a block. Initial values are given to the members of the structure object with a comma-separated list inside this block. The value of the first expression is assigned to the first member of the structure object, and the value of the second expression is assigned to the second member of the structure object.

As in arrays, giving initial values for more elements than the members of a structure object is invalid. If the structure contains a `char` array defined to hold a string, this array can also be initialized separately within double quotes:

    #include <stdio.h>
    #define MAX_NAME_LEN 20
    struct Person {
        char name[MAX_NAME_LEN + 1];
        int no;
    };
    int main()
    {
        struct Person per = {"Mustafa", 256}; // String literal initialization
        printf("name : %s\nNo : %d\n", per.name, per.no);
        return 0;
    }

In the `main` function, the variable `per` of type `struct Person` is initialized. The string "Mustafa" is placed into the `char` array named `name` of the defined `per` variable with the initialization syntax. The value 256 is also assigned to the member named `no` of the `per` variable with the initialization syntax.

It is possible to initialize only a specific number of elements of the array member of the structure, not all elements. Compile and run the following example:

    struct Sample {
        int x;
        int a[10];
        double d;
    };
    #include <stdio.h>
    int main()
    {
        struct Sample sam = {20, 1, 2, 3, 7.8}; 
        int k;
        printf("sam.x = %d\n", sam.x); // Output: 20
        for (k = 0; k < 10; ++k)
            printf("sam.a[%d] = %d\n", k, sam.a[k]); // a[0]=1, a[1]=2, a[2]=3, a[3]=7 (int), a[4]-a[9]=0
        printf("sam.d = %lf\n", sam.d); // Output: 0.000000
        return 0;
    }

Suppose the programmer wanted to assign the value 20 to the object `sam.x`, the values 1, 2, 3 to the first three elements of the array `sam.a` respectively, and expected the remaining elements of the `sam.a` array to be automatically zeroed out. Suppose the initial value $7.8$ was desired to be given to the `sam.d` object. The object named `sam` of type `struct Sample` declared is initialized as follows:

    struct Sample sam = {20, 1, 2, 3, 7.8};

However, this cannot be done with the statement above. The compiler places the value 20 into the object `sam.x`, and the values 1, 2, 3, 7 (truncated from 7.8) into the first four elements of the `sam.a` array respectively. Of course, the `double` type value $7.8$ is converted to the `int` type when it is assigned to the fourth element of the array. Since the `double` type object `per.d` is not initialized, this member is automatically initialized with the value 0.

By using a second block in the initialization statement, initial value assignment to the first 3 elements of the array member can be ensured. Change the initialization statement as follows and recompile and run the code:

    struct Sample sam = {20, {1, 2, 3}, 7.8};

In such an initialization operation, the comma-separated values written inside the second pair of curly braces are assigned to the first three elements of the array member, while the value $7.8$ following the closing curly brace is transferred to the member named $d$ of the structure object.

### Addresses and Pointers of Structure Type

The address of a structure object can be obtained by the structure object being the operand of the address-of operator. Pointer variables of a structure type can also be defined. A pointer variable of a structure type must be assigned an address of the same structure type:

    #include <stdio.h>
    struct Point {
        double x, y;
    };
    int main()
    {
        struct Point p;
        struct Point *ptr = &p; // ptr is a pointer to struct Point
        printf("sizeof ptr = %zu\n", sizeof(ptr)); // Size of the pointer itself (e.g., 4 or 8)
        printf("sizeof *ptr = %zu\n", sizeof(*ptr)); // Size of the object pointed to (e.g., 16)
        return 0;
    }

In the `main` function, a variable named $p$ of type `struct Point` is defined. The address of this object is assigned to `ptr`, a pointer variable of type `struct Point *`. After this assignment, the variable $p$ can also be accessed with the pointer variable `ptr`, right?

Regardless of the type of object a pointer variable points to, the $\text{sizeof}$ value of the pointer is 2 or 4 bytes (or 8 on 64-bit systems). $\text{sizeof}(\text{ptr})$ obtains the $\text{sizeof}$ value of the pointer variable $ptr$ itself, while $\text{sizeof}(\text{*ptr})$ obtains the $\text{sizeof}$ value of the object pointed to by $ptr$, i.e., the variable $p$.

#### Accessing Structure Members with a Structure Pointer (Arrow Operator)

Let $ptr$ be a pointer of a structure type, and $mem$ be a member of that structure. The member named $mem$ of the object pointed to by $ptr$ can be accessed as follows:

    (*ptr).mem

Enclosing the expression `*ptr` in parentheses here is **mandatory**. If the expression were written in the form:

    *ptr.mem /* Invalid */

the dot operator would be evaluated first, and the expression $p.mem$ would be processed. Since the left operand of the dot operator is not a structure object (it is a pointer), the expression would be invalid.

A single operator, called the **arrow operator (`->`)**, can be used to access a specific member of the structure object at an address of a structure type:

The arrow operator is formed by concatenating the characters `-` and `>`. It is a **binary infix** operator. The arrow operator is at the **highest precedence level** of the precedence table. The left operand of the `->` operator must be an **address of a structure type**. The right operand of the operator must be a member of the relevant structure. The operator is used to access the member named by the right operand of the structure object at the address that is its left operand.

Let $ptr$ hold the address of a structure type object. The following two expressions are equivalent:

    (*ptr).mem
    ptr->mem

Both the dot operator and the arrow operator are used to access a member. However, the dot operator accesses with the structure variable itself, while the arrow operator accesses with its address.

### Passing Structure Objects to Functions

You know that a function can be called by **value** (call by value) or by **address** (call by reference). A function that performs an operation related to structure objects can also be called by value or by address.

#### Sending the Value of a Structure Object to a Function

The expression that is the argument sent to a function is copied to the function's relevant parameter variable. In this case, if a function's parameter variable is of a structure type, the function can be called with an object of the same structure type. You know that structure objects of the same type can be assigned to each other with the assignment operator. Such an assignment means a **block copy**, which causes a relative loss in terms of both memory and processing time. Furthermore, with this method, the function **cannot modify** the arguments sent to it because the function is called by value. Examine the following example:

    #include <stdio.h>
    #define MAX_NAME_LEN 16
    #define MAX_FNAME_LEN 24
    struct Person {
        char name[MAX_NAME_LEN + 1];
        char fname[MAX_FNAME_LEN + 1];
        int no;
        double wage;
    };
    void display_person(struct Person per) // Call by value
    {
        printf("%d %s %s %.2lf\n", per.no, per.name, per.fname, per.wage);
    }
    int main()
    {
        struct Person person = {"Necati", "ERGIN", 2345, 3.56};
        display_person(person); // Passes a copy of 'person'
        return 0;
    }

The parameter variable of the `display_person` function is an object of type `struct Person`. You see that an object named `person` of type `struct Person` is defined and initialized in the `main` function. The value of the object `person` is used as an argument in the call to the `display_person` function. When the function is called, the value of the variable `person` in the `main` block is copied to the object `per`, which is the parameter variable of the created function. This is a block copy operation. A block of size $\text{sizeof}(\text{struct Person})$ is copied. The object `per` is not the same object as `person`. The object `per` is another object whose value is equivalent to the value of the object `person`. If an assignment like:

    per.wage = 5.60;

were made inside the `display_person` function, the `person` object would undoubtedly **not be affected** by this assignment. The value of a local structure object cannot be changed with such a function, right? A function receiving the value of a structure object often causes an unnecessary block copy. Since inefficiency in terms of memory and processor time usage increases as the $\text{sizeof}$ value of the relevant structure type grows, it is not a highly preferred method. It can be used for small structure objects.

#### Sending the Address of a Structure Object to a Function

If a function's parameter variable is a structure pointer, the function can be called with the address of a structure object of that type. With a call made to such a function, only data the size of $\text{sizeof}$ of a pointer object is sent to the function.

This method is generally better. This method should almost always be used. In this method, regardless of how large the structure is, only address information is transferred. Furthermore, the function can modify the structure variable whose address was sent to it in this method. Undoubtedly, such a transfer operation is possible because the structure object is located as a single block in memory. The `display_person` function defined previously is written this time to receive the address of a structure object:

    void display_person(const struct Person *ptr) // Receives address
    {
        // Accesses members using the arrow operator ->
        printf("%d %s %s %.2lf\n", ptr->no, ptr->name, ptr->fname, ptr->wage);
    }
    int main()
    {
        struct Person person = {"Necati", "ERGIN", 2345, 3.56};
        display_person(&person); // Passes address of 'person'
        return 0;
    }

You see that the parameter variable of the `display_person` function is declared as:

    const struct Person *ptr

The function requests the address of a `struct Person` object from the outside. You know that the `const` keyword used in the declaration communicates the information that no modification will be made to the structure object whose address is received.

The expression `ptr->no` used inside the function's code is of type `int`. This expression corresponds to the object that is the member named `no` of the structure object whose address was received from outside.

### Functions Returning a Structure Type

A function's return value can be a structure type. Examine the following example:

    struct Point {
        double m_x, m_y;
    };
    
    struct Point make_point(double x, double y);
    int main()
    {
        struct Point a;
        a = make_point(3, 5); // Returns a struct Point object
        /***/
        return 0;
    }
    
    struct Point make_point(double x, double y)
    {
        struct Point temp;
        temp.m_x = x;
        temp.m_y = y;
        return temp; // Returns the structure object itself (copy)
    }

You know that functions convey their return values to the outside with the help of a temporary object. The `return` expression used inside a function that produces a return value is assigned to a temporary object that will hold the function's return value. The function call expression also represents the value of this temporary object. This temporary object is created when the function's code execution reaches the `return` statement and is destroyed when the evaluation of the expression containing the function call finishes. The return type of a function is the type of the temporary object that will hold the function's return value.

In the code snippet above, the return value of the `make_point` function is of type `struct Point`. In this case, the temporary object to which the function's return value is transferred is also of type `struct Point`. The return value of such a function can be assigned to a structure variable of the same type.

However, such functions should be used for small structure objects that do not occupy much memory. This is because the assignment is performed from the `return` expression to the temporary area, and then from the temporary area to the variable where the return value will be stored. This is potentially a bad technique. It can be preferred for small structures because its perceptual complexity is lower.

#### Dynamically Obtaining an Area of a Structure Type

Just as memory space can be obtained dynamically for an array, a dynamic memory block can also be obtained for a structure object. Compile and run the following example:

    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #define MAX_NAME_LEN 15
    #define MAX_FNAME_LEN 23
    struct Person {
        char name[MAX_NAME_LEN + 1];
        char fname[MAX_FNAME_LEN + 1];
        int no;
        double wage;
    };
    
    void set_person(struct Person *ptr, const char *name_ptr, const char
                    *fname_ptr, int n, double w)
    {
        strcpy(ptr->name, name_ptr);
        strcpy(ptr->fname, fname_ptr);
        ptr->no = n;
        ptr->wage = w;
    }
    
    void display_person(const struct Person *ptr)
    {
        printf("%d %s %s %.2lf\n", ptr->no, ptr->name, ptr->fname, ptr->wage);
    }
    
    int main()
    {
        struct Person *ptr;
        
        ptr = (struct Person *)malloc(sizeof(struct Person)); // Dynamic allocation
        if (ptr == NULL) {
            printf("cannot allocate memory!\n");
            exit(EXIT_FAILURE);
        }
        
        set_person(ptr, "Kaan", "Aslan", 2345, 4.80);
        display_person(ptr);
        
        free(ptr); // Free the dynamic memory
        return 0;
    }

Examine the `main` function. A memory area the size of an object of type `struct Person` is dynamically obtained with the `malloc` function. The starting address of the dynamic block is stored in `ptr`, a pointer variable of type `struct Person *`. You see that the `set_person` function fills the structure object whose address it receives from outside with the information transferred to its other parameters. The `display_person` function, defined previously, prints the information held by the structure object whose address it receives to the screen. You see that the starting address of the obtained dynamic block is passed as the address of the structure object to these functions.

### Functions Returning an Address of a Structure Type

A function's return value can also be an address of a structure type. In this case, the temporary object that will hold the function's return value is an address of a structure type. The function call can be assigned to a pointer of the function's return value type. Examine the following function definition:

    struct Person *create_person(const char *name_ptr, const char
                                 *fname_ptr, int n, double w)
    {
        struct Person *ptr;
        ptr = (struct Person *)malloc(sizeof(struct Person));
        if (ptr == NULL) {
            printf("cannot allocate memory!\n");
            exit(EXIT_FAILURE);
        }
        set_person(ptr, name_ptr, fname_ptr, n, w);
        return ptr; // Returns the address of the dynamically allocated structure
    }

The `create_person` function fills an object whose space it dynamically allocates with the information transferred to its parameters. It then returns the address of the dynamic object. A code snippet that uses this function can be as follows:

    int main()
    {
        struct Person *ptr;
        ptr = create_person("Kaan", "Aslan", 2345, 4.80);
        display_person(ptr);
        
        free(ptr); // Calling code is responsible for freeing
        /***/
        return 0;
    }

The address returned by the `create_person` function called in the `main` function is stored in `ptr`, a pointer variable of type `struct Person *`. Since the function returns the address of a dynamic object, freeing the dynamic area is the responsibility of the code snippet that calls the function. You see that the dynamic area is returned with the call to the `free` function inside `main`.

Such a function cannot return the address of a local structure variable. Returning the address of a global structure variable also often has little meaning.

The function can return the address of a dynamically allocated structure object. The responsibility for returning the obtained dynamic area to the heap memory area lies with the code snippet that calls the function.

Returning the address of a local structure object is a typical pointer error. Local structure objects can also be declared with the `static` keyword. Undoubtedly, a function returning the address of a static structure object is not a pointer error.

### Composite Objects and Nested Structures

A structure's member can be of another structure type. The fact that a structure's member is of another structure type can be achieved in two separate ways:

First, the structure type used as a member is declared. The declaration of the structure that contains the member is made at a location where this declaration is visible. Examine the following example:

    struct Date {
        int day, month, year;
    };
    struct Student {
        char name[30];
        struct Date birth_date; // Member is of type struct Date
        int no;
    };

In the example above, the `struct Date` structure is declared first. A member of type `struct Date` is then used in the declaration of the `struct Student` type.

In the second method, the declaration of the structure variable that is the member is made inside the declaration of the structure that contains the member:

    struct Student {
        char name[30];
        struct Date {
            int day, month, year;
        } birth_date; // Member declaration inside the struct
        int no;
    };

A structure declared inside another structure, like the `struct Date` structure in the example above, is called a **"nested structure."** Here, the structure declared inside also behaves as if it were declared outside. That is, variables of the structure type declared inside can be defined. The code snippet above corresponds only to a declaration. An object named `birth_date` is not defined. When an object of type `struct Student` is defined, this structure object will have a member named `birth_date` of type `struct Date`.

Let a variable of type `struct Student` be defined after either of the two separate syntaxes:

    struct Student s;

The member named `birth_date` of the structure variable $s$, which is of type `struct Date`, can be accessed with the dot operator:

    s.birth_date

The expression above denotes an object of type `struct Date`. The members named `day`, `mon`, and `year` of this object can be accessed by using the dot operator a second time:

    s.birth_date.mon

The expression denotes an object of type `int`. Recall that the dot operator is at the first precedence level of the operator precedence table, and the associativity for this precedence level is left-to-right.

Structure objects whose one or more members are of a programmer-declared type are called **composite objects**. In the example above, the variable $s$ of type `struct Student` is a composite object.

#### Initializing Composite Objects

Normally, in initialization, the members are assigned sequentially to the structure members, taking the inner structure into account. However, enclosing the values given to the members of the inner structure separately in curly braces is recommended because it increases readability:

    struct Student s = {"Necati Ergin", {10, 10, 1967}, 123};

If the inner structure is enclosed in separate curly braces, it may be possible to initialize a smaller number of members of the inner structure:

    struct Student s = {"Necati Ergin", {10, 10}, 123};

Here, the `year` member of the `birth_date` member of the variable $s$ is not initialized. The compiler automatically places the value 0 in this member. If inner curly braces had not been used here, the initial value 123 would be assigned to the `year` member, and the value 0 would be assigned to the `no` member.

The following declaration is also valid:
```c
    struct Data {
        int a[3];
        long b;
        char c;
    };
    x = {{1, 2, 3}, 50000L, 'A'}, *p;
```
#### Benefits of Creating Composite Objects

When a structure has a member of another structure type, the opportunity arises to benefit from the interface of the structure type to which the member belongs, i.e., the functions that provide service to the outside.

Let a structure be declared as follows:

    struct Person {
        char name[16]
        char fname[20]
        struct Date bdate; // Member of type struct Date
    };

When an object is defined as:

    struct Person per;

the member `per.bdate` of this object corresponds to an object of type `struct Date`. When this member of the `per` object is in question, the functions defined to provide service related to the `struct Date` type can be called. For example, let a function be declared as follows related to the `struct Date` type:

    void display_date(const struct Date *);

The `display_date` function can be called directly to print the date information held in the `per` object to the screen, right?

    void display_person(const struct Person *ptr)
    {
        printf("name        : %s\n", ptr->name);
        printf("surname     : %s\n", ptr->fname);
        printf ("date of birth : ");
        display_date(&ptr->bdate); // Pass address of the struct Date member
    }

The `display_person` function calls the function named `display_date` to print the date information stored in the `bdate` object, which is a member of the `struct Person` type object at the address sent to it, to the screen. It sends the address of the `bdate` member as an argument to the function.

### Why Are Structures Used?

Some benefits can be obtained by using structures:

If related variables are collected in a structure as structure members, perceptual convenience is provided. For example, a point on a plane, date information, or properties related to products in a warehouse can be represented by a structure.

In the C language, a function should take at most 8-10 parameters. Having more parameters is a bad technique. If a function requires too much parametric information, this parametric information should be expressed in the form of a structure. A variable of that structure type should be defined, and the address of this variable should be sent as a parameter to the function. For example, let's design a function that takes a person's identity card information as parameters and prints them to the screen. All the identity card information can be expressed in the form of a structure, and only the address of this structure can be sent as a parameter to the function.

Functions have a single return value. However, functions may be desired to convey a wide variety of information to the calling function. This operation can be done as follows: The information to be conveyed is expressed in the form of a structure. Then, a structure variable of this type is defined, and its address is sent as a parameter to the function. The function then fills the inside of this structure variable. That is, at the function's exit, the information is inside the structure variable.

### Array of Structures

Since structures also specify a type, arrays of a structure type can also be in question. An array of structures is an array whose elements are placed contiguously in memory and whose elements are of the same structure type. Arrays of structures can also be initialized. The inner curly braces used during initialization increase readability. Example:

    #include <stdio.h>
    struct Date {
        int d, m, y;
    };
    int main()
    {
        struct Date bdates[5] = {{10, 10, 1958}, {4, 3, 1964},
                                 {21, 6, 1967}, {22, 8, 1956}, {11, 3, 1970}};
        struct Date *pdate;
        int i;
        pdate = bdates; // pdate gets the address of the first element
        for (i = 0; i < 5; ++i) {
            printf("%02d / %02d / %04d\n", pdate->d, pdate->m, pdate->y);
            ++pdate; // Increments the pointer by sizeof(struct Date)
        }
        return 0;
    }

A function that operates on an array of structures can also be defined. Such a function must receive the starting address and size of the relevant array of structures from the calling code. Below, some functions that operate on arrays of structures are defined. Carefully examine the function definitions:

... (The detailed code implementations follow, which are lengthy but follow the principle of passing the array of structures by pointer and size, and accessing members using the arrow operator `->` or the array notation `ptr[k].member`).

#### Example: Sorting an Array of Structures (by surname)

The `sort_person_array` function sorts the array of structures based on the `m_fname` (surname) member using the bubble sort algorithm.

    void sort_person_array(struct Person *ptr, int size)
    {
        int i, k;
        for (i = 0; i < size - 1; ++i)
            for (k = 0; k < size - 1 - i; ++k)
                // Accessing surname using array notation and dot operator
                if(strcmp(ptr[k].m_fname, ptr[k + 1].m_fname) > 0) 
                    // Swapping the entire structure objects
                    swap_persons(ptr + k, ptr + k + 1); 
    }

### Complex Structure Situations

A structure's member can be a pointer to another structure type. For example:

    struct Date {
        int day, month, year;
    };
    struct Person {
        char name[30];
        struct Date *bdate; // Pointer to struct Date
        int no;
    };

Let a definition be made as:

    struct Person per;

* `per.bdate` is of type **`struct Date *`**. This expression denotes an object (pointer).
* `per.bdate->day` is of type `int`. This expression also denotes an object.
* `&per.bdate->day` is of type `int *`.

In this example, if no value assignment has been made, the pointer specified by `per.bdate` contains a random address. For this pointer to be used without causing a pointer error, it must point to a safe address. For example, this area can be obtained dynamically with the `malloc` function:

    per.bdate = (struct Date *) malloc (sizeof(struct Date));

In the example above, let's assume we only have a pointer of type `struct Person`:

    struct Person *ptr;

1.  `ptr->bdate` is of type **`struct Date *`**.
2.  `ptr->bdate->day` is of type `int`.

In these examples, no memory allocation has been performed yet. Space must be obtained with dynamic memory functions for both pointer variables $ptr$ and $ptr->bdate$:

    ptr = (struct Person *) malloc(sizeof(struct Person));
    ptr->bdate = (struct Date *) malloc(sizeof(struct Date));

The dynamically obtained areas must be freed in reverse order:

    free(ptr->bdate);
    free(ptr);

A structure's member cannot be a structure variable of its own type. For example:

    struct Sample {
        struct Sample a; /* INVALID */ // Undeterminable size
    };

This is because the length of the `struct Sample` structure cannot be determined here. However, a structure's member can be a **pointer to its own type**. For example:

    struct Node {
        int val;
        struct Node *next; // Pointer to its own type is valid
    };

Since the size of a pointer is fixed, regardless of what it points to, there is no obstacle for the compiler to determine the $\text{sizeof}$ value of the `struct Node` type in the declaration above. These types of structures can be used to implement **linked list** and **tree structures (algorithms)**.

### What is a Linked List?

To understand what a linked list is, first recall the **"array"** data structure.

Suppose objects of the same type are desired to be stored in memory. These objects can be stored consecutively in memory, i.e., with no gaps between them. You know that the elements of an array in the C language are stored this way in memory. However, placing objects contiguously in memory is not always desirable. In the case of contiguous placement of objects in memory, access to any of the objects can be done in **constant time**. That is, the cost of accessing any element of the array or dynamic array is not proportional to the number of elements held in the array. Regardless of whether the array holds 100 elements or 1000 elements, the cost of accessing any element is a constant time. Why? Because an element is accessed with an address operation, right? For example, if $pd$ is a pointer holding the starting address of an array, an operation like `pd[n]` corresponds to the operation `*(pd + n)`. It is clear that the cost of this operation is constant.

Lists whose elements are not located sequentially in memory are called **linked lists**. In linked lists, each element also holds the information of where the next element is located. The location of the first element is held in a separate pointer. Thus, all elements of the linked list can be accessed with the address of the first element of the linked list. Each element of the linked list is a structure object. Some members of this structure object hold the values of the linked list elements or other information they will carry, while one member holds the address information of the structure object that is the next linked list element. An element obtained in this manner is called a **"node."** Example:

    struct Node {
        int val;
        struct Node *next; // Pointer to the next node
    };

Let our goal be to store `int` type values in memory as a list. You see the declaration of a structure named `struct Node` above. The `int` type values to be stored will be placed in memory as the value of the `val` member of our structure. The pointer member of the structure, which is also of type `struct Node *`, will hold the address information of the structure object that follows it. Thus, when we have the address of a `struct Node` object, we can access the `int` type data held within this object, and we can also access the next element with the help of the `next` pointer located within the object.

#### Comparison of Linked Lists and Arrays

Any element of an array can be accessed in constant time. This is because accessing an element is done by adding an integer to address information. In linked lists, however, all elements located before it in the linked list must be traversed to access an element. In this case, the average cost of accessing an element is the cost of accessing the element in the middle. This means that the cost of accessing an element increases linearly as the number of elements in the linked list increases.

In arrays, block shifting is required for inserting or deleting elements. However, these operations can be done very easily in linked lists.

Arrays must be sequential in memory. This situation prevents the allocation of arrays of a specific length in cases where memory is fragmented. That is, although there is sufficient free memory space of the desired total size, it is not contiguous. In this case, a linked list is preferred.

During linked list usage, operations such as inserting an element, deleting an element, and traversing the linked list are performed.