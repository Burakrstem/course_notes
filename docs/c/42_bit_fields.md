# 🤏 Bit Fields

A member of a structure can be an integer variable stored at the bit level. Such members of structures are called **"bit fields."**

Bit fields are a tool in C that allows bit-level access. The bitwise operators described in the previous section can undoubtedly be used for bit-level access. However, bit fields offer the programmer an easier interface for such access.

A specific syntax rule must be followed to create a bit field within a structure. In the declaration of the member within the structure, the member name is followed by the `:` token. An integer literal indicating how many bits the bit field will occupy is written after this token. Examine the following declaration:

    struct Data {
        unsigned int a: 5;
        unsigned int b: 4;
        unsigned int c: 7;
    };

The member named $a$ of the structure named `struct Data` occupies 5 bits within the structure, while the member named $b$ occupies 4 bits, and the member named $c$ occupies 7 bits. Since the members of the structure are of type `unsigned int`, an object of this type can hold integer values in the following ranges:

* Member $a$: $0 - 31$
* Member $b$: $0 - 15$
* Member $c$: $0 - 127$

### Types of Bit Field Members

A bit field member can be of a **signed or unsigned `int` type**. A bit field member cannot be of a real number type. Although C standards state that bit field members cannot be of `char`, `short`, or `long` types, most C compilers optionally allow this. For portability, using the keywords `signed` or `unsigned` in the declaration of the bit field member is appropriate. This is because the compiler may treat the type of a bit field declared only with the `int` keyword as either a signed or unsigned `int` type.

A bit field member cannot be an array.

### Why Are Bit Fields Used:

* Some external devices may transmit data at the bit level.
* A specific number of bits of an integer may be used in some compression operations.
* Encoding may be performed in specific bit fields of an integer in some encryption operations.
* A large number of flag variables can be held as bit fields.

Undoubtedly, bitwise operators can also be used to perform these operations. However, bit fields offer the programmer a much easier interface for these tasks, simplifying the programmer's job.

For example, the DOS operating system stores date and time information related to files in 16-bit fields:

    struct file_date {
        unsigned int day: 5;  // 5 bits for day (1-31)
        unsigned int mon: 4;  // 4 bits for month (1-12)
        unsigned int year: 7; // 7 bits for year (0-127)
    };

As seen from the declaration above, a 7-bit field is allocated for the year part of the date information. The largest value that can be held in a 7-bit field is 127. In the DOS operating system, the year value plus 1980 is held in such a bit field.

The following function prints the date information held in the `file_date` structure to the screen:

    void display_file_date(const file_date *ptr)
    {
        // ptr->year holds (year - 1980)
        printf("%02u/%02u/%u", ptr->day, ptr->mon, ptr->year + 1980); 
    }

The bit field members of a structure are accessed with the **dot or arrow operators** again. Undoubtedly, the code produced by the compiler ensures that bitwise operations are performed internally.

A structure whose members are bit fields is now declared to hold time information:

    struct file_time {
        unsigned int hour: 5; // 5 bits for hour (0-23)
        unsigned int min: 6;  // 6 bits for minute (0-59)
        unsigned int sec: 5;  // 5 bits for second (0-31)
    };

A 5-bit field is allocated for the seconds value of the time information. The largest value that can be held in a 5-bit field is 31. In the DOS operating system, half of the actual seconds value is held in such a bit field.

The following function prints the time information held in the `file_time` structure to the screen:

    void display_file_time(const file_time *ptr) // Corrected function name
    {
        // ptr->sec holds sec/2
        printf("%02u:%02u:%02u", ptr->hour, ptr->min, 2 * ptr->sec); 
    }

### Addresses of Bit Field Members

The address of a bit field member cannot be taken. It is invalid for a bit field member to be the operand of the address-of operator:

    #include <stdio.h>
    // Assuming file_date structure is visible
    void func();
    {
        struct file_date fdate;
        scanf("%d", &fdate.day); /* Invalid: Cannot take the address of a bit field */
        /***/
    }

### Memory Layout of Bit Fields

Compilers are left largely free regarding the memory layout of a bit field. The memory layout of bit fields is explained with a term called **"storage unit."** A storage unit is a specific byte length and is dependent on the compiler's choice. For example, the storage unit chosen by the compiler can be 1, 2, 4, etc. bytes.

A compiler encountering the declaration of bit fields tries to place the bit fields into a single storage unit without leaving gaps between them. If there is not enough space remaining within the storage unit for a bit field, the next storage unit is moved to. Whether the element that does not fit will be held in both storage units or be entirely placed in the new storage unit is left to the compiler's choice. The layout of the element within the relevant bit field, whether from left to right or from right to left, is also left to the compiler's choice.

The length of a bit field element cannot be greater than the length of the storage unit itself. For example, if the storage unit is 8 bits, a bit field element of 9 bits cannot be used.

The option to **omit the name of the member** has also been introduced to allow more control over the layout of the bit field members. The name of a bit field member may be omitted. The compiler still allocates the necessary space for an unnamed bit field member. Thus, the programmer can adjust the internal layout of the members according to their needs.

    typedef struct {
        int : 5;     // Unnamed 5-bit field (padding)
        int hour: 5;
        int min: 6;
    } Time;

In the example above, the compiler still allocates 5 bits for the unnamed first member of the `Time` structure. That is, the member named `hour` of the structure is placed starting from the 5th bit.

Another possibility is to specify the length of the bit field member as **0**. This has a predetermined special meaning. A compiler that sees the length of a member as 0 starts the next member from a **new storage unit**:

The bit length of the storage unit of the relevant system is obtained below:

    #include <stdio.h>
    #include <limits.h>
    typedef struct {
        int : 1;
        int : 0; // Forces next member to start at the beginning of a new storage unit
        int : 1;
    } StorageCheck;
    
    int main()
    {
        // sizeof(StorageCheck) should be 2 * size of the storage unit (in bytes)
        // because of the 0-length bit field, and we need to convert to bits.
        // Assuming the storage unit is a multiple of CHAR_BIT (e.g., 2 or 4 bytes)
        printf("Storage unit = %zu bits\n", sizeof(StorageCheck) / 2 * CHAR_BIT); 
        return 0;
    }

In the example above, a structure named `StorageCheck` is defined. You see that 1 bit of space is allocated for the unnamed first bit field member of this structure. The length for the second member is specified as 0. The length of the last member is 1 bit again. The compiler allocates the necessary space for the 3rd member from the next storage unit. In this case, if the storage unit is 8 bits, the total length of the structure is 16 bits; if the storage unit is 16 bits, the length of the structure is 32 bits; and finally, if the storage unit is 32 bits, the length of the structure is 64 bits.