# 🎭 Unions

Another tool that allows the programmer to create a new type is **"unions."** Unions are very similar to structures. For a union to be used, i.e., for objects of a union type to be defined, the union must first be declared. Union declarations are done the same way as structure declarations. The only difference is the use of the **`union`** keyword instead of the `struct` keyword.

Examine the following example:

    union Dword {
        unsigned char byte;
        unsigned int word;
        unsigned long dword;
    };

With the statement above, a new type named `union Dword` is declared. This type can be used where this declaration is visible. The name of this type can also be ensured to be just `Dword` by making a `typedef` declaration:

    typedef union {
        unsigned char byte;
        unsigned int word;
        unsigned long dword;
    } Dword;

### Defining Variables of Union Type

Union variables are defined just like structure variables. In unions, memory allocation is done with the definition of the union object, not with the union declaration.

    Dword a, b;

After the statement, $a$ and $b$ are two variables of type `Dword`.

Again, as in structures, the declaration and definition operations can be performed together in unions:

    union Double {
        double d;
        unsigned char s[8];
    } a, b, c;

In this case, the scope of the variables $a$, $b$, and $c$ can be local or global, depending on where the union declaration is made.

Union members are accessed with the dot operator, just like structure members. For example, after the definition above, `a.d` specifies the `double` type first member of the union. Similarly, pointer variables that will point to union type objects can also be defined. The arrow operator can be used to access union members via an address, just like in structures:

    union Dword *p;
    p->word = 100;

With the expression `p->word`, the member named `word` of the union object at address $p$ is accessed.

### Memory Layout of Union Objects

Space is allocated for union objects equal to the size of the **longest member** of the union. All members of the union are placed in memory starting from the **same numerical address (origin)**. For example:

    union Dword {
        unsigned char byte;
        unsigned int word;
        unsigned long dword;
    };
    union Dword a;

With the declaration, 4 bytes of space are allocated in memory for the variable $a$ of type `Dword` in Unix/Windows systems. This is because the member named `dword` of the variable $a$, at 4 bytes, is the longest member of the union.

    | Address | Content | Member Accessed |
    | :---: | :---: | :---: |
    | 1F00 | a.byte (Byte 1) | a.byte (full) |
    | 1F01 | a.byte (Byte 2) | |
    | 1F02 | a.byte (Byte 3) | |
    | 1F03 | a.byte (Byte 4) | |
    
    // a.word and a.dword start at 1F00 and occupy 2 or 4 bytes.

If a union contains an array, the array is considered a single member. For example:

    typedef union {
        float f;
        unsigned char bytes[4];
    } Float;
    Float x;

How much space is allocated for the variable $x$ with the definition? The `Float` union has two members. The first is a variable of type `float`, 4 bytes long, and the second is a character array, 4 bytes long. Since both lengths are the same, it can be said that 4 bytes of space will be allocated for the object $x$.

Accordingly:

    Float x;
    x.f = 10.2F;

$x.\text{bytes}[0]$, $x.\text{bytes}[1]$, $x.\text{bytes}[2]$, $x.\text{bytes}[3]$ are the byte values of the `float` type member, respectively.

Examine the following program:

    #include <stdio.h>
    typedef union {
        char ch;
        int i;
        double d;
        char s[4];
    } Data;
    int main()
    {
        Data data;
        printf("&data    = %p\n", &data);
        printf("&data.ch = %p\n", &data.ch);
        printf("&data.i  = %p\n", &data.i);
        printf("&data.d  = %p\n", &data.d);
        printf("data.s   = %p\n", data.s); // Array name decays to address
        return 0;
    }

When the program above is compiled and run, the **same address** is printed to the screen every time.

The fact that union members are placed starting from the same origin, i.e., the same numerical address, means that when the value of one member is changed, the values of the other members also change. This is precisely the main purpose of using unions.

### Initializing Union Objects

According to C standards, only the **first member** of union objects can be initialized. Initializing more than one member of a union object is invalid:

    union Dword {
        unsigned char byte;
        unsigned int word;
        unsigned long dword;
    } x = {'m'}; // Valid: initializes 'byte' member

    union Dword y = {'a', 18, 24L}; /* Invalid */ // Initializes more than one member

### Why Are Unions Used?

Unions can be used for three main purposes. The first purpose is aimed at **saving memory space**. Using a union eliminates the need to allocate separate space for multiple variables that will be used at different times. For example, suppose a catalog sells three different products: book, T-shirt, and watch. Assume that besides the stock number, price information, and product type information, other product-dependent features also need to be stored:

* books: name, author, page count.
* t-shirt: pattern, color, size
* watch: model

    typedef struct {
        int stok_no;
        float fiyat;
        int urun_tipi;
        char kitapisim[20];
        char yazar[20];
        int sayfa_sayisi;
        char desen[20];
        int renk;
        int boyut;
        char saatisim[20];
        int model;
    } Katalog; // Catalog

In the declaration above, the member named `urun_tipi` (product\_type) of the `Katalog` structure holds the information about what the product is. The value of this member can only be $\text{BOOK}$, $\text{TSHIRT}$, or $\text{WATCH}$. Assume these are defined as symbolic constants. The structure declared above can hold all the characteristics of the products, but it has a drawback:

If the product type is not $\text{BOOK}$, the members `kitapisim[20]`, `yazar[30]`, and `sayfa_sayisi` are never used. Similarly, if the product type is not $\text{TSHIRT}$, the members `desen[20]`, `renk`, and `boyut` are never used.

The $\text{sizeof}$ value of the `Katalog` type declared above is 108 bytes under Unix/Windows systems (assuming byte alignment). That is, when an object of type `Katalog` is defined, this object occupies 108 bytes of space in memory.

    #include <stdio.h>
    // Assuming Katalog is defined as above
    int main()
    {
        Katalog katalog;
        printf("sizeof(katalog) = %zu\n", sizeof(katalog)); // Output: 108
        return 0;
    }

However, memory savings can be achieved by having one member of the `Katalog` structure be a union type:

    typedef struct {
        char isim[20];
        char yazar[20];
        int sayfa_sayisi;
    } Kitap; // Book

    typedef struct {
        char desen[20];
        int renk;
        int size;
    } Tshirt;

    typedef struct {
        char isim[20];
        int model;
    } Saat; // Watch

    typedef union {
        Kitap kitap;
        Tshirt tshirt;
        Saat saat;
    } Data;

    typedef struct {
        int stok_no;
        float fiyat;
        int urun_tipi;
        Data data; // Union member
    } Katalog;

Examine the declarations above. First, structures named `Kitap`, `Tshirt`, and `Saat` are declared to hold information related to book, T-shirt, and watch. The $\text{sizeof}$ values of the `Kitap`, `Tshirt`, and `Saat` structures are 44, 28, and 24, respectively, in Unix/Windows systems. Then, you see that a union named `Data` is declared. Since the members of this union are of types `Kitap`, `Tshirt`, and `Saat`, the $\text{sizeof}$ value of this union is equal to the $\text{sizeof}$ of its longest member, which is the member of type `Kitap`, i.e., 44.

In the declaration of the `Katalog` structure, there is a member named `data` of type `Data` union. In this case, the $\text{sizeof}$ value of the `Katalog` structure is only 56 (4 + 4 + 4 + 44). The $\text{sizeof}$ value of the `Katalog` structure is reduced from 108 to 56 by using the union.

    #include <stdio.h>
    // Assuming Katalog is defined as above
    int main()
    {
        printf("sizeof(Katalog) = %zu\n", sizeof(Katalog)); // Output: 56
        return 0;
    }

Code snippets that operate on the `Katalog` structure can first obtain the product type information by looking at the value of the member named `urun_tipi` of the `Katalog` type object, and then use the members named `data` in different ways depending on the situation:

    Katalog katalog;
    /***/
    if (katalog.urun_tipi == KITAP) // Assuming KITAP is a symbolic constant
        puts(katalog.data.kitap.isim);

The second reason for union usage is to perform operations on parts of any data type or to form a whole by operating on the parts. Examine the following example:

Assume the following declarations are made on a system where the `int` type is 2 bytes long:

    typedef struct {
        unsigned char low_byte;
        unsigned char high_byte;
    } Word;

    typedef union {
        unsigned int i;
        Word w;
    } Wordform;

After the declarations, if an object of type `Wordform` is defined, this union object can be used as an integer whose low-order byte (`low_byte`) and high-order byte (`high_byte`) can be accessed separately:

    #include <stdio.h>
    int main()
    {
        Wordform wf;
        wf.w.low_byte = 0x12;
        wf.w.high_byte = 0x34;
        printf("%x\n", wf.i);
        return 0;
    }

That is, when the `main` function above is compiled and run on 16-bit systems with Intel processors (little endian), the number 3412 is printed to the screen with the call `printf("%x\n", wf.i);`. On Motorola processors (big endian), since the low-order byte value is at the low numerical address, the number should be seen in reverse.

A similar theme arises in the software representation of processor registers. The 8086 processors have a total of 14 registers.

* 4 general-purpose registers: AX, BX, CX, DX
* 4 segment registers: CS, DS, ES, SS
* 2 index registers: SI, DI
* 3 pointer registers: IP, BP, SP
* 1 flag register: F

All registers are 16 bits long. The general-purpose registers AX, BX, CX, DX are divided into two 8-bit parts. The general-purpose registers can also be used as independent 8-bit registers as follows:

    AX -> AH, AL
    BX -> BH, BL
    CX -> CH, CL
    DX -> DH, DL

These registers are also parts of the whole; that is, values can be written separately to the AH and AL registers, and the AX register can be retrieved as a whole value. Registers can be represented in memory with a union:

    struct BYTEREGS {
        unsigned char al, ah, bl, bh, cl, ch, dl, dh;
    };
    struct WORDREGS {
        unsigned ax, bx, cx, dx, si, di, flags, cflag;
    };
    union REGS {
        struct BYTEREGS h; // 8-bit registers (high/low parts of 16-bit registers)
        struct WORDREGS x; // 16-bit registers
    };

* `regs.x.ax` contains `regs.h.ah` and `regs.h.al`
* `regs.x.bx` contains `regs.h.bh` and `regs.h.bl`
* ...

### Using Unions in Mixed Data Structures

Arrays whose elements are of different types can be created using unions:

Let the elements of an array be of type `char`, `int`, `double`, or a programmer-created type `Complex`. Let any element of the array be usable in a way that it can be of any of these four types.

First, let's create a type named `Complex`:

    #include <stdio.h>
    #include <stdlib.h>
    typedef struct _Complex {
        double m_r, m_i;
    } Complex;
    
    void set_cr(Complex *p)
    {
        p->m_r = (rand() % 2 ? 1:-1) * ((double)rand() / RAND_MAX + rand()% 9);
        p->m_i = (rand() % 2 ? 1:-1) * ((double)rand() / RAND_MAX + rand()% 9);
    }
    
    void display_c(const Complex *p)
    {
        printf("(%.2lf %+.2lfi)", p->m_r, p->m_i);
    }

The `set_cr` function defined above sets a `Complex` object whose address it receives with a random value. The `display_c` function prints the value of a `Complex` object whose address it receives to the screen.

First, let's define some symbolic constants to increase readability:

    #define CHAR 0
    #define INT 1
    #define DOUBLE 2
    #define COMPLEX 3

Now let's create a union type named `Data`.

    typedef union{
        char ch;
        int i;
        double d;
        Complex c;
    } Data;

The $\text{sizeof}$ value of the `Data` type is equal to the $\text{sizeof}$ value of its longest member, which is the member named `c` of type `Complex`, right? The $\text{sizeof}$ value of the `Data` type is 16 bytes in Unix/Windows systems. Now let's create a structure type named `Element`:

    typedef struct {
        char type; // Discriminator member
        Data data;  // Union member
    } Element;

Since the $\text{sizeof}$ value of the `Element` type is the sum of the $\text{sizeof}$ values of its members (assuming byte alignment is active), an object of type `Element` occupies 17 bytes in memory in Unix and Windows systems. The elements of the array to be created will be of type `Element`. The `type` member of the `Element` type holds the information of which member of the `data` member of the `Element` type object is currently used.

Now let's define a function that sets an object of type `Element` with a random value:

    void set_elem_random(Element *ptr)
    {
        switch (rand() % 4) {
            case CHAR:
                ptr->type = CHAR; 
                ptr->data.ch = rand() % 26 + 'A';
                break;
            case INT:
                ptr->type = INT; 
                ptr->data.i = rand(); 
                break;
            case DOUBLE:
                ptr->type = DOUBLE;
                ptr->data.d = (double)rand() / RAND_MAX + rand() % 10;
                break;
            case COMPLEX: 
                ptr->type = COMPLEX; 
                set_cr(&ptr->data.c); // Pass address of the Complex member
                break;
        }
    }

Now let's define a function that prints the value of an object of type `Element` to the screen:

    void display_elem(const Element *ptr)
    {
        switch (ptr->type) { // Check the type member to know which union member is active
            case CHAR: 
                printf("(%c)", ptr->data.ch); 
                break;
            case INT: 
                printf("(%d)", ptr->data.i); 
                break;
            case DOUBLE: 
                printf("(%.2lf)", ptr->data.d); 
                break;
            case COMPLEX: 
                display_c(&ptr->data.c); // Pass address of the Complex member
                break;
        }
    }

Now let's write functions that set an array of type `Element` with random values and print the elements of the array to the screen:

    void display_array(const Element *ptr, int size)
    {
        int k;
        for (k = 0; k < size; ++k) {
            if (k && k % 5 == 0)
                printf("\n");
            display_elem(ptr + k);
        }
    }

    void set_array(Element *ptr, int size)
    {
        int k;
        for (k = 0; k < size; ++k)
            set_elem_random(ptr + k);
    }

Now examine the following `main` function:

    #define ARRAY_SIZE 50
    int main()
    {
        Element a[ARRAY_SIZE];
        srand(time(0));
        set_array(a, ARRAY_SIZE);
        display_array(a, ARRAY_SIZE);
        return 0;
    }

In the `main` function, an array named $a$ of type `Element` is defined. Random values are assigned to the elements of array $a$ with the call `set_array(a, ARRAY_SIZE);`. Of course, the elements of the array are randomly chosen from `char`, `int`, `double`, or `Complex` types in this case. The values of the elements of the array are printed to the screen with the call `display_array(a, ARRAY_SIZE);`. An example screen output obtained by running the program is given below:

    (1.07)(4.49)(19755)(1.69 -8.82i)(0.91)
    (4.45)(9.35)(1.41)(V)(5.57 +5.51i)
    (K)(T)(11331)(7.78)(22316)
    (26066)(28923)(2.36 -2.31i)(C)(8.39)
    (9951)(8.79)(28301)(7.50)(18583)
    (20564)(7.02)(-0.23 -5.46i)(28931)(-4.76 +2.32i)
    (5850)(14891)(J)(-5.40 +8.65i)(H)
    (7.50 -3.32i)(-3.81 +3.17i)(D)(-5.38 -6.72i)(2.15 +2.47i)
    (-4.04 +2.10i)(4737)(-0.21 -0.61i)(-9.00 -3.72i)(4276)
    (12552)(-6.95 -0.11i)(E)(0.71)(-4.72 +7.21i)