## CLASSES

Classes are the fundamental building block of the object-oriented programming technique. We can call the object-oriented programming technique the "technique of writing programs using classes." In this section, we will make an introduction to classes and explain the basic concepts related to classes. In the following sections, we will mainly focus on the use of classes.

### What is a Class

We will first consider classes from a syntactical perspective. The class is a tool of the C++ language that allows the programmer to create a new type. In C, it was possible for the programmer to create a new type with the `struct`, `union`, and `enum` tools. In the C++ language, the `class` has been added to these tools.

The class is a new software unit, not present in the C language, that enables the implementation of the object-oriented programming technique. Classes can be likened to structs in C. However, while structs in C only contain members (data), classes in C++ additionally contain both data members and **member functions**.

Classes have many additional features compared to structs. Most of these features have been added to support the Object-Oriented Programming Technique.

Just as a "struct" type is a "user-defined type," classes are also a type defined by the programmer. The programmer first introduces a new type to the compiler, then can define objects, pointers, and references of this new type. The first thing that needs to be done to use classes is to make a class definition. Making a class definition means giving information about this class to the compiler.

As a result of the information it receives, the compiler, if an object of this class type is defined, both knows how much space to allocate in memory and gains the ability to perform some control operations related to the code written by the programmer.

Classes have two main important differences compared to structs:
i. Within a class declaration, the members of the class can be located in three separate regions named **public**, **protected**, or **private**.
ii. Classes contain not only data members but also functions. These functions are called the class's **member functions**.

First, we will focus on these two new features in detail:

### Class Definition

The definition of a class, i.e., its introduction to the compiler, has a special syntax: The general form of a class declaration is as follows:

    class [ class_name] {
        [private:]
            //...
        [protected:]
            //...
        [public:]
            //...
    };

`class` is a keyword. The `class_name` (class tag) in the general form is the name of the declared class. The class name can be any name that conforms to the naming rules.

The block in a class definition consists of three sections named `private`, `protected`, and `public`. `public`, `private`, and `protected` are C++'s keywords. We will call these words **access specifiers** from now on. A section is started with the access specifier followed by a colon (:) separator and continues until another access specifier is used. It is not mandatory for all three sections to be present in a class declaration. If no access specifier is used, the `private` section of the class is understood. That is, the **default** section within a class declaration is the `private` section.

Only the declarations of member functions are written inside the class declaration. The definitions of these functions are done outside the class declaration like a normal function, but with a different syntax rule. However, the definition of member functions can also be done inside the class declaration. We will examine this situation later, under the heading of inline functions within the class.

In C++, new terms are used to distinguish between functions declared inside a class definition and functions declared outside the class. A function declared inside a class is called that class's **member function**, while other functions are called **global functions**. That is, from now on, we will call the functions we were used to defining in the C language global functions.

The members of the class are declared with their type information inside the class, just as in structs. Examine the following example:

    class A {
    private:
        int a;
        void func1();
    protected:
        long b;
        int func2(int);
    public:
        double c;
        double func3();
    };

In the class declaration above, you see that all three sections of the class have been used. In each section of the class, one member and one function are declared. More than one access specifier can be used in a class declaration. For example, the declaration above could also have been made as follows:

    class A {
    protected:
        long b;
    private:
        int a;
    public:
        double func3();
    protected:
        int func2(int);
    public:
        double c;
    private:
        void func1();
    };

If a class declaration is not started with an access specifier, it is understood that operations are being performed on the `private` section. Examine the following example:

    class A {
        long b;
        int a;
    public:
        double func3();
    protected:
        int func2(int);
    public:
        double c;
    private:
        void func1();
    };

In the example above, the `a` and `b` members of the class named `A` are declared in the `private` section of the class. Now examine the following class declaration:

    class Date {
        int day, mon, year;
        bool verify_date();
    public:
        void set_date(int , int, int);
        void display_date();
    };

Above, a class named `Date` is defined. With the definition above, a new data type named `Date` is created. Remember the difference between C and C++ at this point: In C++, the name of this data type is both `class Date` and `Date`. That is, the name `Date` can be used as the name of this type without making a `typedef` declaration. Whereas in the C language, when it comesto structs, a `typedef` declaration must be made to use a struct name (structure tag) as a type name.

A class name (class tag) can be chosen as desired, provided it conforms to the naming rules. However, most programmers choose names where only the first letter is uppercase and the other letters are lowercase.

Let's continue to examine the definition of the `Date` class:
The `int` type members named `day`, `mon`, `year` are declared in the `private` section of the class. It was said that when an access specifier is not used, the `private` section of the class is understood. In other words, `day`, `mon`, and `year` are the private members of the `Date` class. We see that the declarations of three functions named `verify_date`, `set_date`, and `display_date` are made within the declaration of the `Date` class. These functions are the member functions of the `Date` class. While the declaration of the `verify_date` function is made in the `private` section of the class, the declarations of the `set_date` and `display_date` functions are made in the `public` section of the `Date` class. It could also be said: `set_date` and `display_date` are the public member functions of the `Date` class. `verify_date` is the private member function of the `Date` class. So, is there a difference between the class's member functions and the functions we knew before?

What do the member functions of classes do, how are they defined? We will cover all these topics in detail.

Functions that are logically associated with a class are called "member functions". Every member function can directly access the members of the class. The members of the class are variables that are used jointly by the member functions. The member functions of the class perform various sub-operations related to a topic. While doing these operations, they also use the members of the class jointly. Handling a series of functions that perform a job under the class name facilitates perception and design, and allows the compiler to perform some checks.

As with structs, to work with classes, one must first make the class definition, and then define objects of this class type.

Where in the source code should the class definition be made? The definition of a class can be made anywhere in the source code. However, whether the scope of the definition is in file scope or block scope contains different meanings. For example, if the definition of the `Date` class is made outside all blocks, i.e., at the global level, as a result of this declaration in the file scope, all functions in the file will know the `Date` class. That is, the `Date` class can be used at every point from the class declaration to the end of the file. However, if the declaration is made at the local level, i.e., within a block, the relevant class is known only within the block where the declaration is made.

Like structs, classes are mostly defined in header files. Often, a class definition is part of the interface of the codes that provide a service. However, we are leaving the topic of using header files in the C++ language to later sections.

The class definition is the process of introducing a class's members and member functions to the compiler. With the class definition, the compiler does not allocate any space in memory, it only obtains information about the class. To perform some operations on classes, objects of the class type must be defined. Now we will cover the definition of class objects:

### Defining Variables of Class Type

A variable can be defined from a previously declared class type. Variables of a class type are defined in the same way as variables of fundamental types. In the declaration, first comes the word or words specifying the type, then the name of the defined variable. Let's consider the classes named `A` and `Date` defined in the previous examples.

    A a;

The variable `a` is a class variable of type `A`.

    Date date1, date2;

The variables named `date1` and `date2` are of the `Date` class type. You know that in C++, it is not necessary to write the `struct` and `class` keywords when defining variables of struct and class types. Using these keywords does not cause any problems. That is, the declaration above could also have been made as:

    class Date date1, date2;

However, the unnecessary use of the `class` keyword is not a preferred form.

### Defining Member Functions

A class's member function is defined outside the class with a specific syntax:

    [return_value_type] <class_name> :: <function_name> ([parameter_variables])
    {
        // ...
    }

Let's examine the syntax:
First, you see that the function's return value type is written. Then the class's name is written. The `::` atom that comes after is followed by the function's name. The `::` atom, formed by bringing two colons side by side, will be called the **"scope resolution operator"** from now on.

The `display_date` member function of the `Date` class, which has no parameter variables and does not produce a return value, can be defined as follows:

    void Date::display_date()
    {
        // ...
    }

### Accessing Class Members and Member Functions via Class Objects

As with structs, the data members and member functions of a class can be accessed via an object of that class using the **dot operator**. For example, let `object` be an object of a class type, `m` be a member of this class, and `func` be a member function of this class. Access is carried out as follows:

`object.m`

A member function can only be called for a class object. It cannot be called directly from the outside like global functions. For example, if there is a member function named `func` of the class to which the `object` belongs, this function cannot be called as:

`func();`

If such a call is made, the compiler understands that a global `func` function is being called.
The member function call can be made as follows:

`object.func();`

In the statement above, `object` is an object of a class type, and `func` is the name of one of the member functions of the class to which `object` belongs.

A class's member function can also be called via a pointer or reference of the class type. We will cover these situations a little later.

### Writing Member Function Calls to Object Code

We previously touched upon how a call to a global function in C++ is written to the object code. A name was obtained by combining the function name with the number and types of the parameter variables, and this name was written to the object code.
When a class's member function is called, the compiler this time writes the member function name to the object code by combining it with the class's name, in addition to the number and types of the parameter variables. In this case, a global function and a member function of a class with the same name and the same parametric structure can coexist in a program.
No problem arises in writing these two functions to the object code. For example, in the Borland C++ 3.1 compiler, the global function
`void func() ;`
is written to the object code as
`@func$qv`
, while the `X::void func()` function of the `X` class is written as
`@X@func$qv`
.
Compilers can distinguish between global functions and member functions with the same name by looking at their call forms. For example:
A call like `a.func();`, since it is made with a class object, the compiler will look for the function named `func` as a member function of the class to which `a` belongs. However, if the call were made as
`func();`
, the compiler would understand that the global `func` function was called.

In C++, there is no standard for writing functions to object code. Each compiler combines the names of member functions with the class name and parameter types and writes them to the object code. However, a precise notation (writing form) for this writing process has not been determined as a standard. For this reason, problems may arise in linking modules compiled with different C++ compilers.

So, how are the members of a class object placed in memory?
When a class object is defined, the compiler allocates space in memory **only for the data members of the class**. The member functions of the class do not take up any space within the class object. Member functions are only logically associated with the class. Data members written between the two section-specifying keywords of the class are placed contiguously, with the first written at the lower address. The placement of sections relative to each other is not determined by a standard; it can change from compiler to compiler. Examine the following example.

    class A {
    private:
        int a;
        int b;
    public:
        int c;
        int d;
    protected:
        int e;
        int f;
    private:
        int g;
        int h;
    };

Here, the space occupied in memory by a class object of type `A` would be `8 * sizeof(int)`. Within the object, the data members `a` and `b`, `c` and `d`, `e` and `f`, and `g` and `h` are placed contiguously. However, the placement of these groups among themselves may change from compiler to compiler.

Although the placement between sections is not determined by a standard, almost all compilers place the sections written higher at lower addresses. That is, in the example above, the majority of compilers place the data members in order from top to bottom, starting from the low address. Since the inter-section placement is not standard, portability problems may arise in code written regarding the placement of the object's members.

The space occupied by the object in memory may be more than the total length of the data members if the compiler's alignment operations are enabled.

### Basic Access Rule in Classes

In a global function, not every section of the class can be accessed with a class object, pointer, or reference. Which members or which member function can be accessed is related to the place where the members or member functions of the class are placed. We will examine the access rules by dividing them into two parts:

#### Access Rule for Global Functions

From a global function, **only the members and member functions in the `public` section** of the class can be accessed with a class object, pointer, or reference. Within a global function, the members and member functions in the `private` or `protected` sections of the class cannot be accessed via a class object. Examine the following examples:

    #include <iostream>
    #include <cstdlib>

    class Date {
        int day, month, year; // private by default
        bool verify_date(); // private by default
    public:
        void set_date(int, int, int);
        void display_date();
    };

    // ... Member function definitions ...

    using namespace std;
    int main()
    {
        Date date;

        date.day = 10;
        // Invalid! (day is private)
        if (!date.verify_date()) {
        // Invalid! (verify_date is private)
            cout << "Invalid date..." << endl;
            exit(EXIT_FAILURE);
        }

        date.set_date(10, 10, 1997);
        // Valid! (set_date is public)
        date.display_date();
        // Valid! (display_date is public)
        return 0;
    }

Via a class object, reference, or pointer, only the data members and functions in the `public` section of the class can be directly accessed. In the example above, the data access `date.day` and the member function call `date.verify_date()` are therefore invalid. But the calls to the `set_date` and `display_date` member functions, which are in the `public` section of the class, are valid.

These function calls do not cause any problems at compile time. (Translator's Note: The text means the *valid* calls don't. The invalid ones *will* cause a compile-time error.) The messages for errors arising from non-compliance with the access rule in classes are, in Microsoft compilers:
`'xxx' cannot access private member declared in Class 'YYY'`
and in Borland compilers:
`'YYY'::xxx not accessible`

#### Access Rule for Member Functions

A member function of a class, **regardless of which section it is declared in, can directly access the members in every section of the class**. It can call the member functions of the class directly. For example, let the `set_date` member function of the `Date` class, whose declaration we gave above, be defined as follows:

    void Date::set_date(int d, int m, int y)
    {
        day = d; // Valid.
        month = m; // Valid.
        year = y; // Valid.

        if (!verify_date()) { // Valid.
        // (Note: The text has verify_date(d,m,y), but the declaration was bool verify_date())
        // Assuming the check logic is inside verify_date and uses the members...
            cout << "Invalid date..." << endl;
            exit(EXIT_FAILURE);
        }
    }

As seen, within the definition of the `set_date` member function, the `verify_date` member function is called directly. The `verify_date` member function checks whether the date in question is a valid date. If the date is invalid, the program is terminated. Within the `set_date` member function, the `day`, `month`, `year` private members of the class are accessed directly. Also, within the `set_date` function, the `verify_date` function, which is a private member function of the class, is called. Access to these names in the `private` section is valid. **Because a member function can access every section of its own class.**

Objects, references, or pointer variables of the same class defined within the member functions of a class can access every section of the class. For example, if the `Date` class had another member function named `process_date`:

    void Date::process_date()
    {
        Date date;
        date.day = day; // Valid.
        date.month = month; // Valid.
        date.year = year; // Valid.

        if (!date.verify_date()) { // Valid.
            cout << "Invalid date: " << endl;
            exit(EXIT_FAILURE);
        }
    }

With the `date` class variable defined inside the `process_date` member function, every section of the class can be accessed. Because the `date` variable is defined inside the class's member function. The inside of a function's parameter parenthesis is also considered inside the function. In this case, if a member function's parameter variable is an object, reference, or pointer of the same class type, the `private` members or member functions of the class can be accessed by using the dot or arrow operator with the parameter variable.

### Member Functions Accessing Class Members

A member function, when called for a specific class object, uses the data members belonging to **that object**. Examine the following example:

    class A {
    public:
        void set(int, int);
        void display();
    private:
        int a, b;
    };

    void A::set(int x, int y)
    {
        a = x;
        b = y;
    }

    #include <iostream>
    using namespace std;

    void A::display()
    {
        cout << "a = " << a << endl;
        cout << "b = " << b << endl;
    }

    int main()
    {
        A a1;
        a1.set(10, 20);
        a1.display();

        A a2;
        a2.set(30, 40);
        a2.display();
        return 0;
    }

Here, the `a` and `b` members used directly within the `set` and `display` member function definitions are the members of the object with which these functions were called.
In the call `a1.display()`, the members of the `a1` variable are used.
In the call `a2.display()`, the members of the `a2` variable are used.

If one member function calls another member function, the called member function uses the same members as the calling member function. For example, let the `set` member function of class `A` call the `display` member function directly:

    void A::set(int x, int y)
    {
        a = x;
        b = y;
        display();
    }

In this case, whichever class object the `set` member function was called with, the `display` member function also uses its members.

    int main()
    {
        A a1;
        a1.set(10, 20);
        return 0;
    }

In the `main` function above, the called `set` and `display` member functions use the members of the `a1` class object. That is, the `a` and `b` members inside the `set` and `display` functions relate to the `a1` object.

### Accessing Class Members and the `this` Pointer

It was said that a member function can directly access its own class's members and member functions. So, how does this actually happen? What does an object that can only be accessed by a group of functions mean in the C language? How can a function access the members of a struct object not defined within itself? The function must receive the address of this local object, right?

C is a more "natural" language than C++. That is, it better describes what happens on the computer. If an operation is done in a different way in many programming languages, in reality, the operation is done in a way similar to that in C. Researching what an operation corresponds to in the C language means researching how it actually is, i.e., what it corresponds to at the machine language level. For example, since there is no such concept as "class scope" in the C language, this situation is not "natural". It can actually be met by other natural mechanisms in C.

A member function's access to the class's members is done via an address secretly passed to the member function. This address is the address of the object with which the member function was called. For example, if a member function has no parameter variables, it actually has a **hidden parameter variable**. The address of a class object is passed to that parameter variable with the function call. For example, let's examine the `display` member function of the `Myclass` class defined below.
Apparently, the `display` function has no parameters:

    void Myclass::display()
    {
        cout << "a = " << a << endl;
        cout << "b = " << b << endl;
    }

However, an argument is actually sent to the function secretly. This argument is the address of the class object in the call expression. In fact, if the machine code of the `display` function is examined, it can be seen that such an argument is passed. In this case, the C equivalent of the `display` function would be:
(Translator's Note: The text writes `void A::display(A *const this)`, which seems to be a typo for `Myclass`.)

    void Myclass::display(Myclass *const this)
    {
        cout << "a = " << this->a << endl;
        cout << "b = " << this->b << endl;
    }

When a member of the class is used within a member function, the compiler accesses that member via an address secretly passed to the function. The secret passing of the address is designed to provide easy syntax. For example, if a member function has four explicitly written parameters, in reality, the compiler passes five arguments to this function.

Although the object's address is passed to the member function secretly, this address can be used within member functions with the **`this`** keyword. For example, there is no difference between the definition:

    void Myclass::display()
    {
        cout << "a = " << a << endl;
        cout << "b = " << b << endl;
    }

and the definition:

    void Myclass::display()
    {
        cout << "a = " << this->a << endl;
        cout << "b = " << this->b << endl;
    }

In fact, for example, even if `this->a` is not said, when the `a` member is used, the compiler accesses the `a` member with the secretly passed class object address. `this` is a keyword and specifies an address of the class type for whichever class's member function it is used in. For example, if the `this` keyword is used within a member function of the `Myclass` class, `this` specifies an address of type `Myclass *`.

`this` is also a pointer that is itself `const`. The address inside it cannot be changed. An assignment like
`this = adr;`
inside a member function is invalid.

The address of the object for which the member function was called is passed to the `this` pointer. Of course, if the member function is called via an address, the address inside the pointer with which the member function was called is passed to the `this` pointer. For example, let `func` be a member function of class `X`, `a` be an object of this class type, and `p` be a pointer of this class type.
The C equivalent of the call
`a.func();`
is
`Xfuncv(&a);`
. Similarly, the C equivalent of the call
`ptr->func();`
is
`Xfuncv(ptr);`
. (While writing the C equivalents, we added prefixes and suffixes to emphasize that member functions are combined with class names and parameter types.)

Write and run the following program:

    #include <iostream>
    using namespace std;

    class X {
    public:
        void display();
        void set(int);
    private:
        int a;
    };
    
    void X::set(int val)
    {
        cout << "X::set() was called" << endl;
        cout << "this = " << this << endl;
        a = val;
    }
    
    void X::display()
    {
        cout << "X::display() was called!" << endl;
        cout << "this = " << this << endl;
        cout << "a = " << a << endl;
    }
    
    int main()
    {
        X myx;
        cout << "&myx = " << &myx << endl;
        myx.set(10);
        myx.display();
        
        X *ptr = &myx;
        ptr->display();
        return 0;
    }

The address values obtained are identical, right?

In this case, it is also clear what it means for one member function to call another member function. The member function secretly passes the `this` address it received from the outside to another member function.

    void A::set(A *const this, int x, int y)
    {
        this->a = x;
        this->b = y;
        display(this);
    }

So, what happens if a member function is called with a class pointer that has a garbage value in it?
For example:

    int main()
    {
        X *p;
        p->func(); // UNDEFINED BEHAVIOR
        return 0;
    }

Here, since `p` is a local pointer variable, it contains a garbage value. In this case, a garbage value is passed to the `func` function as the `this` address. That is, the `func` function uses a random memory region as if it were a class object. Such a situation leads to a pointer error.

Now let's ask a question: Since a class's member function can directly access the class object's members, why is there a keyword called `this`? What are the benefits of being able to obtain the address of the class object within a member function? The `this` address can be used for the following purposes within a member function:

**1. The address of the class object for which the member function was called can be sent as an argument to another function within the member function definition:**

    class A {
    public:
        //...
        void a_func();
    private:
        //...
    };
    
    void g_func(A *);
    
    void A::a_func()
    {
        //...
        g_func(this);
    }
    
    int main()
    {
        A a;
        a.a_func();
        return 0;
    }

In the program above, the `this` address is sent as an argument to the global function `g_func` called within the `a_func` member function of class `A`. When the `a_func` member function is called with the `a` object of type `A` defined in the `main` function, the address of the `a` object is secretly passed to the `a_func` function. From within this function, this address is sent to the global `g_func` function.

**2. Within the member function, the class object itself that called the member function can be accessed.** Since the `this` address is the address of the class object that called the member function, the expression `*this` is this object itself, right? Examine the code below:

    void g_func(A);
    
    void A::a_func()
    {
        A a;
        a = *this;
        //...
        g_func(*this);
    }
    
    int main()
    {
        A x;
        x.a_func();
        return 0;
    }

The expression `*this` is assigned to the `a` object of type `A` defined in the `a_func` function of class `A`. Since the `a_func` function is called with the `x` object in the `main` function, the value of the `x` object is assigned to `a` inside the `a_func` function. This time, you see that the parameter variable of the global `g_func` function is of type `A`. Thus, the value of the local `x` object in the `main` function is passed to the global `g_func` function called within the `a_func` member function.

**3. A called member function can return the class object itself, or the address of that class object, for which it was called.** This situation is used intensively in some tools that will be explained later. Examine the following example carefully:

    class A {
    public:
        //...
        A a_func1();
        A *a_func2();
        A &a_func3();
    private:
        //...
    };

Of the member functions of class `A`, `a_func1` returns a value of `A` class type, `a_func2` returns an address of `A` class type, and `a_func3` returns a reference of `A` class type.

Now let's look at the definitions of these functions:

    A A::a_func1()
    {
        //...
        return *this;
    }
    
    A *A::a_func2() // (The text has m_func2, likely a typo)
    {
        //...
        return this;
    }
    
    A &A::a_func3() // (The text has m_func3, likely a typo)
    {
        //...
        return *this;
    }

* `a_func1` returns the value of the class object for which it was called.
* `a_func2` returns the address of the class object for which it was called.
* `a_func3` returns the class object itself (as a reference) for which it was called.

**4. The `this` pointer is also used to access class members when they are masked (hidden) by local variables.** This situation will be examined under the "Class Scope" heading.

### Class Scope

Recall that scopes in the C language are divided into four. These are, from narrow to wide, "function prototype scope", "block scope", "function scope", and "file scope".
Block scope means a name is known only within a block, function scope means it is known everywhere in a function, and file scope means it is known, usable, within all functions. In C++, in addition to these scopes, a **class scope** has also been defined. Class scope means a name is known both within the class declaration and within all member functions of the class. The members and member functions of the class adhere to the class scope rule. Note that class scope is between function scope and file scope in terms of narrowness/wideness. In this case, the scopes in C++ from narrow to wide are:

1.  Function prototype scope
2.  Block scope
3.  Function scope
4.  **Class scope**
5.  File scope

Now let's take a look at the situation of variables with the same name: Let's recall this rule about variables with the same name: In C++, as in C, more than one variable with the same name cannot be defined in the same scope. But more than one variable with the same name belonging to different scopes can be defined. If more than one variable with the same name is active in a block, the one with the narrow scope can be accessed in that block.

Examine the following example:

    #include <iostream>
    
    void func(); // function declaration
    
    int a = 50; // global variable
    
    class X {
    public:
        void foo(int);
        void func();
    private:
        int a;
    };
    
    using namespace std;
    
    void X::func()
    {
        cout << "X class's member function named func..." << endl;
    }
    
    void func()
    {
        cout << "Global function named func..." << endl;
    }

In this example, both a global variable named `a` is defined, and there is a member named `a` of the `X` class. Let the `foo` member function of the class be defined as follows:

    void X::foo(int a)
    {
        cout << a << endl;
        // The parameter variable a
        {
            int a = 30;
            cout << a << endl;
            // The a inside the block
        }
        func();
        // The member function func
    }

Now there are four `a`s. The global `a`, the class member `a`, the parameter variable `a`, and the `a` defined in the inner block. According to the rule of accessing the one with the narrow scope, the `a` used in the inner block is the `a` variable defined in that block. The one in the outer block is the function's parameter variable. The called function is the member function named `func`. Because function names are also treated like variables, they follow the same scope rule. Global functions have file scope, while member functions have class scope. Now let's change the name of the `foo` function's parameter variable:

    void X::foo(int x)
    {
        a = x;
        // The class member a
        {
            int a = 30;
            cout << a << endl;
            // The a inside the block
        }
        func();
        // The member function func
    }

Now the `a` in the outer block is treated as the class member `a`. So, is it possible to access global variables or functions with the same name as class members or member functions within a member function? This is made possible with the scope resolution operator.

### Scope Resolution Operator

The scope resolution operator is obtained by bringing two `:` characters side by side as `::`. The scope resolution operator has two uses: unary prefix and binary infix. First, we will focus on the unary prefix form:

#### Unary Prefix Use of the Scope Resolution Operator

In this usage form, the scope resolution operator has a single operand. The operator, in this case, always provides access to the **global** name. Examine the following example:

    #include <iostream>
    using namespace std;
    
    int a = 10;
    
    int main()
    {
        int a = 20;
        ::a = 50;
        // Global a
        cout << a << endl;
        // Local a
        {
            int a = 30;
            ::a = 100;
            // Global a
            cout << a << endl;
            // Local a
        }
        cout << ::a << endl;
        // Global a
        return 0;
    }

The scope resolution operator can be used to access the global one in a situation where both a local and a global variable with the same name are defined. In the example above, the global `a` variable is accessed by using the `a` variable with the `::` operator inside the blocks.

Let's make a warning here: The `::` operator does not provide access to the one defined in the parent block, but **always to the global one**. There is no serious benefit to accessing the block one level up. However, access to the global variable may be necessary in many cases.

The unary prefix use is frequently used to provide access to the global one when global variables with the same name as class members are present within a class's member functions. Let's examine the following example:

    #include <iostream>
    
    void func();
    // Global function
    
    class X {
    public:
        void func();
        void foo();
    };
    
    using namespace std;
    
    void func()
    {
        cout <<"Global function named func..." << endl;
    }
    
    void X::func()
    {
        cout << "X class's member function named func..." << endl;
    }
    
    void X::foo()
    {
        cout << "X class's foo member function..." << endl;
        func(); // The one belonging to class X is called
        ::func(); // The global one is called
    }

In the `foo` member function, the `func()` called normally is the `func` function belonging to the `X` class, according to the narrow scope rule. However, the one called as `::func();` is the global `func` function.

Some programmers call global functions with the `::` operator within member functions to increase readability, even if there is no member function with the same name as the global one. For example:

    CMyDialog::CMyDialog()
    {
        hProcess = ::GetProcessHeap();
    }

Let's assume the `GetProcessHeap` function is not a member function of the `CMyDialog` class. In this case, there is no need to call the function with the `::` operator, right? Because since there is no scope conflict, the global one is understood anyway when `GetProcessHeap` is said. However, the programmer may have wanted to emphasize the situation to help the person examining the code. You can encounter such emphases quite often in libraries where classes are used intensively.

#### Binary Infix Use of the Scope Resolution Operator

The scope resolution operator is also used as binary infix. In such a use, the left operand must be a class name, and the right operand must be a member or member function of the class.
With this use, the member or member function belonging to the class is always accessed. For example, let a class named `Date` have data members named `day`, `month`, `year` of `int` type. `set_date` being a member function of this class:

    class Date {
    public:
        void set_date(int, int, int);
    private:
        int day, month, year;
    };
    
    void Date::set_date(int day, int month, int year)
    {
        Date::day = day;
        Date::month = month;
        Date::year = year;
    }

Note that the names of the parameter variables are the same as the names of the class members. In this case, the binary scope resolution operator is used to access the class members within the member function.
Examine the usage form:
`Date::month = month;`
The `month` name used on the left side of the assignment operator relates to the class member, while the `month` name on the right side of the assignment operator relates to the parameter variable.

As seen, the binary infix form of the scope resolution operator is used to access the class members when there are local variables or parameter variables with the same name as the class members.
Apart from this, you will see that the scope resolution operator is used for similar purposes in class derivation operations.

### Class Constructor Functions

When a class object is created, a member function called a **constructor** is automatically called by the compiler. The compiler identifies constructor functions by looking at their names. **The name of constructor functions is the name of the class they belong to.** Constructor functions **do not have return values**. By "do not have return values," we do not mean that their return value is `void`. These functions do not have a concept of return values. Nothing is written in place of a return value when writing them. The parametric structure of constructor functions can be of any form.

Examine the following class declaration:

    class Date {
    public:
        Date();
        void display();
    private:
        int day, month, year;
    };

The function declared as `Date();` is the class's constructor function. Note that the name of this function is the same as the class name. Nothing is written in place of a return value in the declaration. This situation, as we stated above, does not mean the return value is `int` or `void`. The definition of the `Date` class's constructor function is done like other member functions:

    // Class name   // Function name
    Date::Date()
    {
        //...
    }

In the example below, which one is the constructor function of the `Person` class?

    class Person {
    public:
        Person(const char *, int); // Constructor function
        void display();
        void set_name(const char *);
        void set_no(int );
        // ...
    private:
        char *name;
        int no;
    };

The constructor function of the `Person` class is the function declared as `Person(const char *, int );`. The definition of this function can be as follows:

    Person::Person(const char *nm, int n)
    {
        //...
    }

The parametric structure of constructor functions can be of any form. Since there can be functions with the same name but different signatures in C++, a class can also have more than one constructor function with different signatures. In otherD words, **constructor functions can also be overloaded**. For example, a class named `Date` can have more than one constructor function:

    class Date {
    public:
        Date();
        Date(int, int, int);
        Date(const char *);
        // ...
    private:
        int day, month, year; // (Text has 'int month', assumed typo for ',')
    };

Above, three constructor function declarations are made for the `Date` class defined: one with no parameter variables, one with three parameter variables, and one with a single parameter variable. A constructor function of a class that has no parameter variables, or whose all parameter variables take default arguments, is called the **"default constructor"**.

Constructor functions are automatically called by the compiler when class objects are created. That is, the compiler first allocates space in memory for the class object, then calls the appropriate constructor function. Recall that local variables are created when the program's flow reaches the definition point, and global variables are created when the program is loaded into memory. Accordingly, the constructor function for a local class object is called at the point where the object is defined, and the constructor function for a global class object is called when the program is loaded into memory, i.e., **before the `main` function**. In the C++ language, there can also be code that runs before the `main` function.

Since a class can have more than one constructor function, how does the compiler determine which one to call?
Which constructor function is called is determined by the object's definition expression. If parentheses are opened after the object name and an argument list is written inside the parentheses, the constructor function with the appropriate signature is called. For example:
With a definition like
`Date bdate(6, 1, 1966);`
, the class's constructor function with the parameter structure
`Date(int, int, int);`
is called. Here, 6, 1, and 1966 are the arguments sent to the function in the call to the class's constructor function. Similarly:
In an object definition like
`Complex c(10.2, 5.3);`
, the constructor function with the parameter structure
`Complex(double, double);`
can be called. Recall that literals that contain a dot and have no suffix are treated as `double` type literals. So, in the following example, which constructor function of the `Person` class is called?

    Person y("Necati Ergin");

Recall that when strings are put into an operation, they are automatically converted to `const char *` type by type conversion. In this case, with the definition of the `y` class object, the constructor function of the `Person` class that has a pointer parameter of `const char *` type is called.

If the definition operation is done without opening parentheses, as with objects of other types, the default constructor, i.e., the constructor with no parameters, is called when the object is created. For example:

    Date date;
    Person person;
    Complex c;

For the `date`, `person`, and `c` objects above, the default constructor functions are called.

If a class object is defined by being initialized, the constructor function appropriate for the type given as the initial value is called. `X` being a class:
The definition `X a = b;`
is completely equivalent to the definition
`X a(b);`
. In this case, for example:
A definition like
`Person y = "Necati Ergin";`
has the same meaning as the definition
`Person y("Necati Ergin");`
. Only single-parameter constructor functions can be called in this way. In fact, class objects cannot be initialized with more than one value. (Translator's Note: This is an oversimplification, but true for this `=` syntax). It is also not possible to initialize class objects between curly braces as in structs. For example:

    X a = {10, 20, 30};
    // Invalid

If `a` is a class object of type `X`, it cannot be initialized in this way. (Translator's Note: This was true in C++98, but aggregate initialization rules have changed in modern C++.) In fact, as an exception, special classes can be initialized with curly braces. However, we will cover this topic later.

Examine the class declaration below, write and run the following example:

    #include <iostream>
    #include <ctime>

    class Date {
    public:
        Date();
        Date(int, int, int);
        void display();
    private:
        int day, month, year;
    };
    
    using namespace std;
    
    Date::Date()
    {
        time_t timer = time(0);
        tm *tptr = localtime(&timer);
        day = tptr -> tm_mday;
        month = tptr -> tm_mon + 1;
        year = tptr -> tm_year + 1900;
    }
    
    Date::Date(int d, int m, int y)
    {
        day = d;
        month = m;
        year = y;
    }
    
    void Date::display()
    {
        cout << day << '/' << month << '/' << year;
    }
    
    int main()
    {
        Date date1;
        date1.display();
    
        Date date2(28, 10, 1998);
        cout << endl;
        date2.display();
        cout << endl;
        return 0;
    }

In our example, with the definition
`Date date1;`
, the class's default constructor function is called. The default constructor function gets the system date and places it in the class's members. For example, let the members of the `date` (date1) object be filled as follows when the constructor function is run.
(e.g., `day = 1`, `month = 1`, `year = 2006`)

In our example, you see that the call
`date1.display();`
is made afterward. The `day`, `month`, and `year` printed to the screen with the `display` function are the members of the `date1` object, right? Since constructor functions for local class objects are called when the program's flow reaches the object's definition point,
with a definition like
`Date date2(4, 3, 1964);`
(Translator's note: the example code has 28, 10, 1998)
the constructor function appropriate for the
`Date(int, int, int);`
declaration is called. This function places the values sent as arguments into the class's members. In this case, the members of the `date2` object, after the constructor function is called, become:
(`day = 4`, `month = 3`, `year = 1964`)

In our example, you see that the data members of the `date2` object are printed with
`date2.display()`
afterward.

Since global variables are created when the program is loaded into memory, the constructor functions for global class objects are also run **before the `main` function**. Examine the following example:

    #include <iostream>
    using namespace std;
    
    class X {
        int a;
    public:
        X(int);
        void display();
    };
    
    X::X(int n)
    {
        a = n;
        cout << "X class's constructor function" << endl;
    }
    
    void X::display()
    {
        cout << a << endl;
    }
    
    X g = 20;
    
    int main()
    {
        cout << "main function started..." << endl;
        g.display();
        return 0;
    }

In our example, the constructor function for the `g` class object is called before the `main` function. You should see the following on the screen:

    X class's constructor function
    main function started...
    20

If more than one global class object is defined, the call order of the constructor functions is from top to bottom. That is, the constructor function of the class object defined higher up is called earlier.

Constructor functions can also have default arguments. Examine the `Complex` class given in the example below:

    #include <iostream>
    using namespace std;

    class Complex {
        double real, imag;
    public:
        Complex(double, double = 0.);
        void display();
    };
    
    Complex::Complex(double r, double i)
    {
        real = r;
        imag = i;
    }
    
    void Complex::display()
    {
        cout << real;
        if (imag != 0)
            cout << (imag > 0 ? "+" : "") << imag; // (Text has '+', improved to handle negative)
        cout << '\n';
    }
    
    int main()
    {
        Complex c1(10);
        // Complex x(10, 0) (This is a comment in the text)
        c1.display();
    
        Complex c2(10, 20);
        c2.display();
        return 0;
    }

If all parameter variables of a constructor function take default values, that constructor function can also be used as the default constructor. For example, let the constructor function of the `Complex` class be declared as follows:

    class Complex {
    public:
        Complex(double = 0, double = 0);
        // ...
    };

All of the following definitions are valid:

    Complex x;
    // same meaning as Complex(0, 0)
    Complex y(10);
    // same meaning as Complex(10, 0)
    Complex z(10, 20);

No constructor function may be written for a class. In this case, the compiler writes the default constructor itself. That is, even if no constructor function is written for a class, an object can be defined as if there were a default constructor. For example:

    class Point {
    public:
        void set(int, int);
        void display();
    private:
        int x, y;
    };

As seen, the `Point` class has no constructor function. In this case, defining an object as if there were a default constructor does not lead to any error.

    Point pt;
    // Valid

So, what exactly does the default constructor written by the compiler do? We will cover this topic later. For now, we can think like this: There are some internal operations that a constructor function must do. These operations must be done in any case. The compiler writes code for these internal operations. This code written by the compiler is added to the very beginning of every constructor function written by the programmer. If the constructor function is not defined by the programmer, the default constructor written by the compiler consists only of the code part written by the compiler.

If a class has at least one constructor function, but does not have a default constructor, in this case, it is invalid to define an object in a way that would call the default constructor. Because in this case, the compiler **no longer automatically writes the default constructor**. For example:
After a class declaration like

    class Point {
    public:
        Point(int, int);
        //...
    private:
        int x, y;
    };

, an object cannot be defined as:

    Point pt;
    // Invalid!

But, of course, an object definition like
`Point pt(10, 20);`
is valid.

### Declaring the Constructor Function in the class's `protected` or `private` Section

Just as a member function can be declared in any section of the class, the class's constructor function can also be declared in any section of the class. That is, it is not mandatory for the constructor function to be declared in the `public` section of the class.

Let's assume the constructor function is declared in the `private` section of the class. So, what happens in this case? Since the `private` section of the class cannot be accessed from within a global function, a compile-time error occurs if a class object is created, right?

Examine the following example:

    class A {
    private:
        A();
        void foo();
    };

    int main()
    {
        A a;
        // Invalid! (Constructor A::A() is private)
    }

Another member function declared in the `private` section can be called from within a member function, right? In this case, for example, an object of type `A` can be defined within `foo`, which is another member function of class `A`:

    void A::foo()
    {
        A a;
        // Valid (A::foo() is a member and can access the private constructor)
    }

Later, we will also examine some code patterns where benefit can be gained from declaring the constructor function in the `private` or `protected` section.

Another feature that distinguishes constructor functions from other member functions is that these functions **cannot be called directly by the programmer**:

    class X {
    public:
        X();
    };

    void foo()
    {
        X object;
        X.X();
        // Invalid!
    }

### The Class's Destructor Function

The member function called by the compiler when a class object is about to be deallocated from memory is called the class's **destructor function**. Just as the constructor function is called when the object is created, the destructor function is called when the object is about to be deallocated from memory, i.e., when the object's lifetime ends.

The destructor function's name is the same as the class name. However, the `~` (tilde) atom is added before the name. That is, the destructor function's name is in the form `~ClassName`. Examine the following class declaration:

    class Person {
    public:
        Person(const char *);
        // Constructor function
        // Other member functions
        ~Person();
        // Destructor function
    private:
        char *name;
        int no;
    };

The destructor function of the `Person` class is the one specified by the `~Person();` declaration. The definition of this function is also done according to the rule, as:

    Person::~Person()
    {
        //...
    }

Destructor functions also **do not have return values**. Nothing is written in place of the return value type. This does not mean they have an `int` or `void` return value.
A class's destructor function is unique. Its parameter must be `void`. That is, it must have no parameters. Recall that in C++, writing `void` inside the parameter parenthesis and writing nothing mean the same thing. In this case, a class cannot have more than one destructor function.

The class's destructor function is called when the class object is about to be deallocated from memory. Recall that local variables are deallocated when the program flow exits the block where they are defined, and global variables are deallocated when the program terminates. Accordingly, the destructor functions for local class objects are called at the end of the block where the variable is defined, and the destructor functions for global class objects are called when the `main` function terminates.

Examine the following example:

    #include <iostream>
    #include <cstdio>
    #include <cstdlib>

    class File {
    public:
        File(const char *);
        void type();
        ~File();
    private:
        FILE *fp;
    };

    using namespace std;

    File::File(const char *fname)
    {
        if ((fp = fopen(fname, "r")) == NULL) {
            cout << "Cannot open file..." << endl;
            exit(EXIT_FAILURE);
        }
    }

    void File::type()
    {
        int ch;
        fseek(fp, 0L, SEEK_SET);
        while ((ch = fgetc(fp)) != EOF)
            putchar(ch);
    }

    File::~File()
    {
        fclose(fp);
    }

    int main()
    {
        File file = "c:\\autoexec.bat";
        {
            File file = "c:\\config.sys";
            file.type();
        } // Destructor for inner 'file' (config.sys) is called here
        
        file.type();
        return 0;
    } // Destructor for outer 'file' (autoexec.bat) is called here

In the example given, the constructor function of the `File` class opens the file whose name it takes. The `FILE` type address for the opened file is stored in the `fp` member of the class. The destructor function closes the opened file. You see that the file opening and closing operations are done automatically by the constructor and destructor functions. Pay attention to the call locations of the constructor and destructor functions in our example. For local class objects, destructor functions are called at the ends of the blocks where they are defined.

In C++, there is a rule that is always valid for constructor and destructor functions: **Destructor functions are called in the reverse order of constructor functions.** That is, the destructor function of the class object whose constructor function was run earlier is run later. For example, if the constructor function of object `a` was called before the constructor function of object `b`, the destructor function of object `a` is also called after the destructor function of object `b`.

This feature is more important for class objects within the same scope. For example:

    {
        Date date1, date2;
        //...
    }

Here, the constructor functions are called in the order `date1` then `date2`, and the destructor functions are called in the reverse order, i.e., first `date2` then `date1`.

Destructor functions for global class objects are called after the `main` function. According to the rule given above, if there is more than one global class object, the destructor functions are called in the reverse order of the constructor function call order. That is, the destructor function of the object defined lowest in the source code is called first.

In what order are the constructor and destructor functions called in the following program?

    class X {
        // ...
    };

    X a;
    X b;

    int main()
    {
        X c;
        X d;
        // ...
        {
            X e;
            // ..
        } // e.~X()
    } // d.~X(), c.~X()
    // b.~X(), a.~X()


Here, considering the program flow, the call order of constructor functions is `a`, `b`, `c`, `d`, `e`, and the call order of destructor functions is `e`, `d`, `c`, `b`, `a`.

If a function is terminated with a `return` statement, before the function is terminated, the destructor functions are called for all local class objects defined up to that point. `X` being a class, for example:

    int foo()
    {
        X a;
        // ...
        {
            X b;
            // ...
            if (func())
                return -1; // Destructors for b, then a are called
            // ...
        } // Destructor for b would be called here if no return
        X c;
        // ...
        return 0; // Destructors for c, then a are called
    }

In the `foo` function above, the `func` function is called in the inner block, and its return value is tested. If the return value of this function is a non-zero value, the function is terminated. The compiler also calls the destructor functions for the `a` and `b` objects that were created, before the function terminates. You see that the `c` object is not defined until the program flow reaches the point where the `return` operation is done. Of course, in this case, the destructor function is not called for the `c` object.

It is not mandatory to write a destructor function for a class. If a destructor function is not written, the compiler writes the class's destructor function itself. For now, you can assume the destructor function that the compiler will write is as follows:

    Myclass::~Myclass()
    {
    }

In fact, not every class needs to have a destructor. But if it is desired to automatically reverse what was done with the constructor function, writing the destructor function is meaningful. In general, classes that use an external resource release or give back a resource, which was bound to them by their constructor functions, with their destructor functions.

Finally, let's dwell on the termination of the entire program with the `exit` function within any function. Wherever the `exit` function is called, the destructor functions, if any, are called for all global class objects defined in the program. Of course, in case of terminating the program with the `exit` function, the destructor functions are not called for local class objects.

### For What Purpose Are Constructor and Destructor Functions Used

Constructor functions are defined to give specific initial values to the class's members and to perform various initial operations. The fact that various initial operations are done secretly by constructor functions when a class object is defined facilitates perception. Thus, the codes that use the class object (clients) do not have to perform any operation before using the class object. The necessary operations are done by the class's own code. In this way, it is ensured that a class object receives its initial value in a stable manner. If the initialization operation were done not by an automatically called function, but by a function that must be explicitly called by the code part using the class, the risk of error would be much higher, right? Constructor functions are one of the basic tools that enable the realization of the **data hiding** principle.

Likewise, the destructor function is used to reverse the initial operations done with the constructor function. For example, if the constructor function opened a file, the destructor function can close the file. Or the constructor function might have set the serial port with various values. In this case, the destructor function can also restore these settings. However, the most common situation is that the constructor function dynamically allocates a place in memory with the `new` operator, and the destructor function gives this area back with the `delete` operator. (This is known as **RAII - Resource Acquisition Is Initialization**). Examine the following example:

    #include <iostream>
    #include <cstdlib>

    class Array {
    public:
        Array(int);
        void display();
        int get_item(int);
        void set_item(int, int);
        int get_max();
        ~Array();
    private:
        int *pArray;
        int size;
    };

    using namespace std;

    Array::Array(int length)
    {
        pArray = new int[length]; // (Text has 'size = length', which is a bug)
        size = length;
    }

    Array::~Array()
    {
        delete [] pArray;
    }

    void Array::display()
    {
        cout << '(';
        for (int i = 0; i < size; ++i)
            cout << pArray[i] << ' ';
        cout << ')';
    }

    int Array::get_item(int index)
    {
        if (index < 0 || index >= size) {
            cout << "Invalid index: " << index << endl;
            exit(1);
        }
        return pArray[index];
    }

    void Array::set_item(int index, int val)
    {
        if (index < 0 || index >= size) {
            cout << "Invalid index: " << index << endl;
            exit(EXIT_FAILURE);
        }
        pArray[index] = val;
    }

    int Array::get_max()
    {
        int max = pArray[0];
        for (int i = 1; i < size; ++i)
            if (max < pArray[i])
                max = pArray[i];
        return max;
    }

    const int size = 10;

    int main()
    {
        Array x = size; // (Text has '= size', should be '(size)')
        Array x(size);
        
        for (int i = 0; i < size; ++i)
            x.set_item(i, rand());
        
        x.display();
        cout << "max = " << x.get_max() << endl;
        return 0;
    }

In our example, an `int` array is represented by a class. The class's constructor function has allocated a block from the free store area for an array, and the destructor function is giving this dynamic block back. You see that the `get_item` and `set_item` functions perform the operations of placing an element in the array and getting the value of the array's element by doing bounds checking. Also, the `get_max` function finds the largest element of the array. The `display` function prints all elements of the array to the screen.

### Pointers and Addresses of Class Type

The address of a class object can be taken. The address obtained is of the type of the class to which the object belongs; it must be assigned to a pointer variable of the same type. Let a pointer variable be defined for the `Date` class declared in previous examples:

    Date *p;

With `Date *p;`, the place the `p` pointer variable points to, i.e., `*p`, is of the `Date` class type. In other words, there is an object of the `Date` class type at the place the `p` pointer points to. The compiler treats the first `sizeof(int)` bytes starting from this address as the `day` member of the class, and the next two `sizeof(int)` bytes as the `month` and `year` members, respectively. Now let's examine step by step what happens when the address of a class object is assigned to a class pointer:

(The text includes a diagram showing `date` object at address `00501FC0`, with `day`, `month`, and `year` members at `...FC0`, `...FC4`, `...FC8` respectively.)

    Date date;
    // Space is allocated for the data members of the Date class.
    
    Date *ptr;
    ptr = &date;

Now, the information starting from the `ptr` address is interpreted as the members of the `date` class object. In this case, the expression `*ptr` and `date` specify the same objects.

Via a class type pointer, the class's members and member functions can be accessed with the `->` (arrow) operator. For example, now:
`ptr->display()`
can call the `display` member function. In this case, the `display` member function uses the members at the `ptr` address, i.e., starting from the address that is the value of `ptr`. To explain more clearly,
in a call like
`date.display();`
, the `display` member function uses the data members of the `date` object. That is, the `day`, `month`, `year` variables used inside the `display` function are the members of the `Date` class. And so,
with the call
`ptr->display();`
, the `display` member function also uses the members of the object at the `p` (ptr) address. Since the `ptr` address
`ptr = &date`
holds the address of the `date` object with the assignment, the `display` function also uses `date`'s members, right?
That is, the two operations are equivalent.

Of course, instead of the `->` operator, the precedence parenthesis and dot operators can also be used:
`(*ptr).display();`
is equivalent to
`ptr->display();`
. The class members can also be accessed via the class pointer with the `->` operator. But, undoubtedly, the members must be accessible, i.e., declared in the `public` section of the class. For example:
For an expression like
`ptr->day = 10;`
to be valid, the `day` member must be in the `public` section of the class. Write and test the following code:

    int main()
    {
        Date x;
        Date *p;
        p = &x;
        p->display();
        return 0;
    }

The class's constructor function is only called when a class object is created. When a pointer variable of a class type is defined, the constructor function is **not** called. For example:

    Date date; // Constructor function is called, because an object is created!
    Date *p; // Constructor function is not called, only a pointer is created!

### References of Class Type

A reference variable can also take the place of a class object. References of a class type are defined by being initialized with a class object of the same type:

    Complex a(10, 20);
    Complex &r = a;

Here, the reference named `r` of the `Complex` class type is initialized with the `a` object, also of the `Complex` class type. Thus, the `r` reference now takes the place of the `a` object. Wherever `r` is used, the `a` object is used. Since the `r` reference takes the place of the `a` object, the class's members and member functions are accessed via the reference with the **dot operator** - just as in structs. For example, let's assume the `Complex` class has a member function named `display`. This member function can be called with the `r` reference as:

`r.display();`

When a member function is called with a reference, the member function uses the members of the object the reference stands for. For example, in the call above, the `display` member function uses the members of the object the `r` reference stands for.

The operation of initializing a class type reference with a literal or with an object of another type can be valid in some cases. We will cover this situation under the heading "conversion constructor". Write and run the following example:

    #include <iostream>

    class Complex {
    public:
        Complex(double = 0, double = 0);
        void display();
    private:
        double real, imag;
    };
    
    using namespace std;
    
    Complex::Complex(double r, double i)
    {
        real = r;
        imag = i;
    }
    
    void Complex::display()
    {
        cout << real;
        if (imag > 0)
            cout << "+ ";
        else
            cout << " ";
        cout << imag << "i";
    }
    
    int main()
    {
        Complex a(10, -20);
        Complex &r = a;
        r.display();
        return 0;
    }

First, let's make a clarification on one point. The parameter variables of the `Complex` class's constructor function take default values. This constructor function can be used both as a single-parameter constructor function and as a default constructor function. In our example, you see that the reference named `r` is initialized with the `a` object. In this case, the `r` reference takes the place of the `a` variable. Now, in the `r.display()` call, the `display` member function uses the members that the `r` reference stands for.

### Passing Class Objects to Functions

The jobs related to a class object do not have to be done by a class's member functions. Undoubtedly, global functions can also perform operations on class objects. Now we will focus on passing class objects to functions. Passing class objects to functions can be done in three ways, just like in structs.

#### Passing the Class Object's Value to the Function

This method is nothing other than the "call by value" method we know. In this method, the function's parameter variable becomes an object of the class type. The function is also called with the value of another class object. Because in C++, just like structs, class objects of the same type can also be directly assigned to each other. During such an assignment, the members of the class are copied to each other one-to-one.

In C++, if a class object is defined by being initialized with another class object, a special constructor function is called for the defined class object. This constructor function is called the **"copy constructor"**. If the programmer does not define the copy constructor, the compiler defines it itself. The copy constructor written by the compiler assigns the values of the members of the initializing class object to all members of the created class object. We will cover the copy constructor under a separate heading later.

Examine the following example using the `Date` class we gave earlier:

    void func(Date d)
    {
        // ...
        d.display(); // (Text has a.display(), assumed typo for d)
    }
    
    int main()
    {
        Date date;
        func(date);
        return 0;
    }

In this example, the `date` variable used in the `func` function call gives its initial value to the `d` variable, which is the parameter variable of the `func` function. In this case, all members of the `date` variable are copied one-to-one to the members of `d`. However, such a call is mostly not preferred as it requires copying all members of the object. This situation creates an unnecessary time loss during transfer. The called function cannot change the local (original) class object.

#### Passing the Object's Address to the Function

In this call form, the address of a class object is sent to the function. The function's parameter variable also becomes a pointer variable of the same class type. In this case, only the address of the data block for the class object is passed to the function. Within the function, the object's members and the class's member functions can be accessed with the `->` operator.

Examine the following example:

    void func(Date *pdate)
    {
        // ...
        pdate -> display();
    }
    
    int main()
    {
        Date date;
        func(&date);
        return 0;
    }

Undoubtedly, passing a class object by address to functions is possible because the class's members are located contiguously in memory. With this method, the function can also change the object at the address it receives as a parameter.

#### Passing the Object by Reference to the Function

Since references are also variables that hold addresses, the object's address can also be passed to functions via reference. In this method, the function is called with the class object itself.
The function's parameter variable also becomes a reference of the class type. The reference, which is the function's parameter variable, takes the place of the argument object sent to the function. Now, within the function, the object's members and the class's member functions are accessed with the reference, which is the operand of the dot operator.

Examine the following example as well:

    void func(Date &rdate)
    {
        //...
        rdate.display();
    }
    
    int main()
    {
        Date date;
        func(date);
        return 0;
    }

Passing a class object by reference is equivalent in efficiency to passing by pointer. However, as also stated on the topic of references, if a function does not change the information at the address it receives, a `const` reference or `const` pointer should be preferred for readability.

### Meaning of Class Sections and Access Rules

As we explained before, the member functions and members of the class can be placed in any section of the class. That is, the programmer is free in this regard. However, generally, the declarations of the member functions that provide services to the outside are placed in the `public` section of the class, and the data members of the class are placed in the `private` section. When you examine the examples given above, you will see that this has been the trend.

If the member functions that provide services to the outside are placed in the `public` section, and the class members in the `private` section, the member functions can be accessed from the outside via a class object or pointer, but the class members cannot be accessed. In this case, the members cannot be used directly, but only with the help of the class's member functions.

(A diagram shows: [CLASS OBJECT OR POINTER] -> [MEMBER FUNCTIONS (public)] -> [MEMBERS (private)])

In such a case, if the person writing the class codes wants to provide access to the class members, they can write a group of member functions that get the values of the class's private members and place values in them. These member functions are generally named in English as **GetXXX** or **SetXXX**. For example:

    class Date {
    private:
        int day, month, year; // (mDay, mMonth, mYear)
    public:
        Date();
        Date(int d, int m, int y);
        void display();
        
        // Member functions that get the values of class members
        int get_day();
        int get_month();
        int get_year();
        
        // Member functions that place values in class members
        void set(int, int, int);
        void set_day(int);
        void set_month(int);
        void set_year(int);
        
        // Other member functions...
    };

The `day`, `month`, and `year` members of the `Date` class given above are placed in the `private` section. Therefore, it is not possible to access these members directly. For example, let `date` be an object of type `Date`. Let's say we want to get the value of the `date` object's `year` member or give a value to the `year` member.
Operations like

    x = date.year;
    // Invalid!
    date.year = 2000;
    // Invalid!

are not valid according to the access rules. However, these operations can be performed by calling the `get_year` and `set_year` member functions:

    x = date.get_year();
    date.set_year(2000);

Often, a class provides services to other code parts. The codes that receive services from the class codes (client codes) are written according to the `public` interface of the class. In fact, as explained before, it is not possible for a code part that receives service from the class to access the `private` section of the class. The `public` section of the class, or the `public` interface of the class, is the section declared under the `public` access specifier in the class declaration.

The most important benefit of placing the class members in the `private` section is **preventing the codes that receive service from the class from being affected when the general structure of the class members is changed**. That is, provided that one adheres to the `public` interface of the class, as a result of changes made in the `private` part of the class, it is not necessary to make a change in the codes that receive service from the class. In fact, the work done can be defined as separating the class's **interface** from the class's own codes (**implementation**). Changing the class's own codes without making a change in the class's interface prevents making a change in the codes that use the class. When it comes to large projects, the cost of making a change in the codes is greatly reduced. Examine the codes of the following `Date` class and an example code that uses it:

(The text shows the implementation of the `Date` class with `set_date`, `get_day`, `get_month`, `get_year` etc. It then shows a `main` function that *directly accesses* the members.)

    int main()
    {
        Date date;
        int d, m, y;
        d = (date.day > 15) ? date.day - 1 : date.day + 1;
        m = (date.month > 6) ? date.month - 1 : date.month + 1;
        y = date.year; // (Text has set_date(d,m,y), but y is uninitialized)
        date.set(d, m, y); // (Text has set_date, but class has set)
        // ...
        return 0;
    }

Here, an object of the `Date` class type is also defined. The current date information is placed in the members of the `Date` class object by the class's constructor function. Then, the day and month values of this date information are checked, and according to the situation, these values are incremented or decremented by one. Then you see that the obtained value is placed back into the class's data members with the `set_date` (or `set`) member function. You may not find the code here very meaningful; The example was given only as an example of the code using the class. Of course, you should not think that the code using the class is only `main`.

Could there be a benefit to placing the class members in the `private` section and accessing them via member functions? Now let's give an example for this: Let's assume the general structure of the data members of the `Date` class above is changed. For example, let it be decided that the date information will now be kept not in `int` type `day`, `month`, `year` data members, but in an 11-element `char` array in the "dd/mm/yyyy" format. In this case, will the code that directly uses the class members remain valid? No! For example:

    d = (x.day > 15) ? x.day - 1 : x.day + 1;
    m = (x.month > 6) ? x.month - 1 : x.month + 1;

Now that the `Date` class no longer has members named `day` and `month`, this code also becomes invalid. In that case, all codes using the class must be rewritten. But if these members had not been placed in the `public` section, then they would not have been accessed directly. To access them, the `public` member functions of the class would have been used mandatorily. For example, if the `day`, `month`, `year` members of the class were in the `private` section, the user codes would have been written as follows:

    int main()
    {
        Date x;
        int d, m, y;
        d = (x.get_day() > 15) ? x.get_day() - 1 : x.get_day() + 1;
        m = (x.get_month() > 6) ? x.get_month() - 1 : x.get_month() + 1;
        y = x.get_year(); // (Text has set_day(d,m,y), which is wrong)
        x.set(d, m, y); // (Text has set_day, which is wrong)
        return 0;
    }

Now, when the data structure of the class is changed, the codes using the class do not need to be reorganized. The only thing to do is to rewrite the member functions in accordance with the new data structure. For example, if the date information is to be kept in the form of a character string, if the member functions of the class are changed as follows, none of the codes using the class need to be changed:

    class Date {
    public:
        //... (public interface remains the same)
    private:
        char date[11];
    };
    
    using namespace std;
    
    Date::Date()
    {
        time_t timer = time(NULL);
        struct tm *tptr = localtime(&timer);
        sprintf(date, "%02d/%02d/%04d", tptr->tm_mday, tptr->tm_mon + 1, tptr->tm_year + 1900);
    }
    
    Date::Date(int d, int m, int y)
    {
        sprintf(date, "%02d/%02d/%04d", d, m, y);
    }
    
    void Date::display()
    {
        puts(date);
    }
    
    int Date::get_day()
    {
        return atoi(date);
    }
    
    int Date::get_month()
    {
        return atoi(date + 3);
    }
    
    int Date::get_year()
    {
        return atoi(date + 6);
    }
    
    void Date::set_date(int d, int m, int y)
    {
        // (Text has 'day = d;', which is now wrong)
        sprintf(date, "%02d/%02d/%04d", d, m, y);
    }
    
    void Date::set_day(int d)
    {
        sprintf(date, "%02d", d);
        date[2] = '/';
    }
    
    // (Implementations for set_month and set_year are also shown)
    // ...

Let's summarize the result: If it is desired that the codes using the class are not affected when the internal structure of the class is changed, the members of the class should be placed in the `private` section, and accesses should be made with member functions. Thus, when the data structure of the class is changed, it is sufficient to rewrite only the member functions.

### Dynamic Class Objects

With the `new` operator, dynamic objects can be created not only for C++'s fundamental data types but also for classes and structs:
For example:

    class Date {
    public:
        Date();
        Date (int, int, int);
        // Other member functions
    private:
        int day, month, year;
    };
    
    Date *p = new Date;

With the statement `Date *p = new Date;`, a dynamic block of `sizeof(Date)` length is obtained. The starting address of the obtained dynamic block is assigned to the `p` pointer variable. Thus, the `p` pointer variable points to the `Date` object.
Now, the member functions can be called by using the `p` pointer variable with the arrow operator. For example,
in an operation like `p->display();`, the `display` member function uses the members of the object at the address in the `p` pointer, i.e., the one obtained dynamically.

The class's constructor function is called not only when an object is created by definition, but also when an object is created dynamically. For example,
with the operation
`p = new Date; // Constructor function is called`
, a dynamic object of `Date` type is created. The constructor function is also called for this created dynamic object.
That is, in the operation above, the following are done in order:
1.  A dynamic block of `sizeof(Date)` length is obtained on the free store.
2.  The constructor function is called for the obtained dynamic block. The starting address of the obtained block is passed to the called constructor function as the `this` pointer.
3.  The address of the created object is assigned to the `p` pointer.

So, which constructor function is called for dynamically created class objects? If parentheses are not opened and a parameter list is not written after the class name, the **default constructor** is called. Let's give an example:

`p = new Date;`

Here, the default constructor function is called for the created space. If parentheses are opened after the class name and a parameter list is written, then the constructor function suitable for the parameter variable list is called. For example:
With a memory allocation operation like
`p = new Date(2, 2, 1989);`
, the constructor function with the parametric structure
`Date(int, int, int);`
is called. So, in a memory allocation operation like the following, which constructor function of the `Person` class is called?

`p = new Person("Erdem Eker");`

Since strings specify an address of `const char` type, the constructor function whose parameter is a pointer of `char` (or `const char`) type is called. Also, not writing anything inside the parentheses after the class name is also a valid situation. This means that the default constructor function will be called for the created dynamic object.

`p = new Date();`
is completely synonymous with
`p = new Date;`

More than one dynamic object can be created with the `new[]` operator. For example:
`p = new Date[n];`
Here, a memory block large enough to fit `n` objects of `Date` type is obtained. The starting address of the obtained block is assigned to the `p` pointer variable.

(Diagram shows `ptr` pointing to the start of a block, which contains `ptr[0]`, `ptr[1]`, ... `ptr[n-1]`)

When space is allocated for more than one class object in this way, the **default constructor function is called one by one for each class object**. There is no way to call another constructor function for the class objects. You might think that a syntax like the following could be valid:

`p = new Date[10](10, 10, 20);`

However, such a syntax is **not valid**!

Now you can perhaps better understand why an operator like `new` is used for dynamic memory management in C++ instead of the `malloc` function. For the compiler to be able to call the constructor function after the dynamic space acquisition operation, it must be known at compile time for which type of object the space allocation operation is done. If there were no such keyword, if the space allocation operations were still being done with the `malloc` function, how could the compiler understand that a space allocation operation was done for a class object?

The memory block dynamically allocated for a class object can be returned to the free store area with the `delete` operator. In this case, the compiler calls the class's **destructor function** before returning the dynamic memory area.
For example, let `p` be an address of `Date` type:
With the operation `delete p;`, first, the destructor function is called for the object at the `p` address. Then the space allocated for this object is returned.

If space has been dynamically allocated for an array of class objects, the compiler calls the destructor functions one by one for all dynamic objects:

    #include <iostream>
    class A {
    public:
        A();
        ~A();
    };
    
    A::A()
    {
        std::cout << "A::A()" << std::endl;
    }
    
    A::~A()
    {
        std::cout << "A::~A()" << std::endl;
    }
    
    int main()
    {
        A *pd = new A[5];
        delete[] pd;
        return 0;
    }

When deallocating the space allocated for a dynamic class array, the `[]` must not be forgotten. If `[]` is forgotten, problematic situations may be encountered. We will cover this situation in the section where the `new` and `delete` operators are explained in detail.

### For What Purpose Are Dynamic Class Objects Used

As we know, constructor functions are called when an object is created, and destructor functions are called when the object is deallocated from memory. In this case, the creation and deallocation of local class objects depend on the definition point. Creating a class object at a desired point and destroying it at a desired point can only be achieved with dynamic memory management. For example:

    {
        p = new X;
    }
    
    delete p;

Look at the places where objects are created and deallocated. If the object were created locally, could such a result be obtained with this block structure? Situations where a class object is created within one member function of a class and destroyed within another member function are frequently encountered. For example:

    void Wnd::initialize()
    {
        pScr = new Scr;
        //...
    }
    
    void Wnd::close()
    {
        //...
        delete pScr;
    }

Here, the object of `Scr` class type is created dynamically within the `initialize` member function of the `Wnd` class and destroyed within the `close` member function. This operation can only be performed by creating the object dynamically. As can beseen from these examples, the main reason for creating the object dynamically is not to use dynamic memory. It is to ensure that the class's constructor function and the class's destructor function are called at the desired places.

### `const` Member Functions and `const` Class Objects

First, let's remember the meanings of the `const` keyword we learned earlier: When the `const` keyword was used in the definition of a variable, it indicated that the value of the defined variable could not be changed:

    const int x = 5;
    x = 10;
    // The value of the x object cannot be changed.
    // Invalid

If the variable was a pointer, the meaning given by the `const` keyword changed according to where the keyword was used:

    int x = 5;
    const int *ptr = &x;
    *ptr = 1;
    // Invalid!

In the example above, `ptr` is a pointer variable whose pointed-to location is `const`. Another address can be assigned to the `ptr` variable, but `*ptr`, i.e., the object `ptr` points to, cannot be changed via assignment.

    int x = 5, y = 10;
    int * const ptr = &x;
    ptr = &y;
    // Invalid!

In the example above, `ptr` is a pointer that is itself `const`. An assignment can be made to the object the `ptr` pointer points to, i.e., the expression `*ptr`. However, an assignment cannot be made to the `ptr` object. That is, the `ptr` pointer cannot be made to point to another object.

    int x = 5, y = 10;
    const int * const ptr = &x;
    *ptr = 1; // Invalid!
    ptr = &y; // Invalid!

In the example above, both meanings of the `const` keyword are combined. That is, `ptr` is a pointer variable that is both itself `const` and its pointed-to location is `const`. An assignment can be made neither to the `ptr` object nor to the object `ptr` points to, i.e., the `*ptr` object.

The `const` keyword can also be written before the type information of the function's return value in a function declaration or definition:

    const char *func();

From the declaration above, the conclusion is drawn that the object at the address, which is the return value of the `func` function, cannot be changed:

    *func() = 'm';
    // Invalid!

Undoubtedly, all of the rules above are also valid for references.

    int x = 5;
    const int &r = x;
    r = 20;
    // Invalid!

    const char &func();
    func() = 5;
    // Invalid!

### A New Meaning of the `const` Keyword

In the C++ language, a member function can be declared with the `const` keyword. For this, it is necessary to place the `const` keyword to the **right of the parameter parenthesis** in both the function's declaration and the function's definition. For example:

    class Date {
    public:
        Date(int, int, int);
        void set(int, int, int);
        int get_day() const;
        int get_mon() const;
        int get_year() const;
        void display() const;
        //...
    private:
        int day, mon, year;
    };

In the example above, the `get_day`, `get_mon`, `get_year`, and `display` member functions of the class named `Date` are declared as `const` member functions. The definitions of these functions can also be made as follows:

    #include <iostream>
    int Date::get_day() const
    {
        return day;
    }
    
    int Date::get_mon() const
    {
        return mon;
    }
    
    int Date::get_year() const
    {
        return year;
    }
    
    void Date::display() const
    {
        std::cout << day << " " << mon << " " << year;
    }

It is mandatory to write the `const` keyword not only in the function's declaration but also in the function's definition. Writing it in only one is invalid. Furthermore, attention must be paid to the place where the `const` keyword is placed. If this keyword had been placed on the far left, it would mean that the function's return value was `const`, i.e., it could not be changed.

### What Does a `const` Member Function Mean

A `const` member function **cannot change the members of the class it belongs to**. In the example above, the `get_day`, `get_mon`, `get_year`, and `display` functions can use the values of the `day`, `mon`, `year` members of the `Date` class. However, they cannot change the values inside them. Even if the `day`, `mon`, `year` members were in the `public` section of the class, they could not be changed by these functions. The `const` keyword, with this use, increases readability. If the person examining the code knows that these functions will not change the members, they will have obtained more information about the code. In a good design, the `const` keyword must be used in a stable manner. If it is used in a stable manner, it can now be thought that non-`const` member functions will change the class members.

Only member functions can be `const`. A global function cannot be defined with the `const` keyword.

### `const` Member Functions Calling Other Member Functions of the Class

Let's remember that another member function can be called directly within a member function, and in this case, the called member function uses the members of the same class object as the calling member function. It is **invalid** to call a non-`const` member function within a `const` member function. In the example above, the `display` member function of the `Date` class is a `const` member function. It is invalid for this function to call a non-`const` member function. If this situation were allowed by the compiler, the `display` function, for example, could change the class members in an indirect way by calling the `set` function:

    void Date::set(int d, int m, int y)
    {
        day = d;
        mon = m;
        year = y;
    }
    
    void Date::display() const // (Text has int return, but declaration is void)
    {
        set(3, 5, 1980);
        // Invalid.
        std::cout << day << " " << mon << " " << year;
    }

In the example above, the call to the `set` function of the same class within the `display` function of the `Date` class is invalid. A `const` member function cannot call a non-`const` member function.

### `const` Member Functions Returning Addresses of Class Members

Within a `const` member function, the members of the class are assumed to be `const`. If a `const` member function is to return with the address of a class member, since the member is assumed to be `const`, the return value of the function must also be a `const` pointer or `const` reference.

    class A {
        int a;
    public:
        //...
        int *get_adr() const;
    };
    
    int *A::get_adr() const
    {
        return &a; // Invalid
    }

In the example above, the `get_adr` function of class `A` is a `const` member function. Within the function's definition, the members of the object for which it was called are also treated as `const`. In this case, in the function above, the address of a `const` object is assigned to a pointer whose pointed-to location is not `const`. To eliminate the error situation, either the function's return value must be `const int *` or the `get_adr` function must not be a `const` member function.

Undoubtedly, the situation described above is also valid for member functions that return a reference. That is, if a `const` member function is to return with the class member itself, in this case, the function's return value must be a `const` reference.

### Constructor and Destructor Functions Cannot Be `const`

The class's constructor and destructor functions cannot be `const`. Since constructor functions are used to give initial values to the class members, there is no meaning in them being `const`. Similarly, since destructor functions may also need to change the class members, it is forbidden for them to be defined as `const`.

### Bitwise and Logical States of Class Objects

A class object occupies a place in memory; in this respect, the object is a collection of bytes and the bits that make up the bytes. However, the class object corresponds to an entity in the problem plane.
When the bitwise values of the object's members change, there may not be a change in the observable state of the object. On the other hand, it is also possible to create a change in the observable state of the object without changing the bitwise values of the object's members.
A class object may be controlling one or more resources outside the space it occupies in memory. For example, some class objects control a memory area obtained dynamically. Examine the following example:

    class Name {
        char *pstr;
        int len;
    public:
        Name(const char *);
        void set_at(int, int);
        //...
    };

    #include <iostream>
    #include <cstring>
    
    Name::Name(const char *str)
    {
        len = strlen(str);
        pstr = new char[len + 1];
        strcpy(pstr, str);
    }
    
    void Name::set_at(int index, int ch)
    {
        pstr[index] = ch;
    }

In the example above, the constructor function of the `Name` class obtains a dynamic space for the class object. The starting address of the obtained dynamic block is stored in the member named `pstr`, which is a `char` pointer. The `set_at` function assigns the value sent to the second parameter variable to the object at the `index` index in the obtained dynamic block.

Should the `set_at` function be defined as `const`? Even though the `set_at` function does not change the class members, i.e., the `len` and `pstr` members, it should **not** be defined as `const`. Even if no data is written to the memory block where the class object is located, because a change is made to the *value* (the abstract state) of the class object, the `set_at` function must not be `const`. That is, in the decision of whether a member function should be `const` or not, not the change in the object's **physical state**, but the change in its **abstract state** should be taken into account. The object should not be evaluated only by its physical or concrete state, i.e., the space it occupies in memory. Sometimes a member function can change the state of a class object, although it does not transfer any data to the space the class object occupies in memory. The task of a `Name` object is to hold a name, right? A change in the name held by a `Name` object means that the abstracted state of the object has also changed. Such a change can be realized without making a change in the physical state of the `Name` object. The `set_at` function above can be an example for this situation. In this case, the function must be a non-`const` member function.

### Meaning of `const` Member Functions from the Compiler's Perspective

From the compiler's perspective, what does it mean for a member function to be `const`? You know that member functions actually have a hidden parameter variable. Whichever class object a member function is called with, the address of that object is passed to the member function's hidden parameter variable, right? You remember that this pointer can be accessed within a member function with the `this` keyword.

    class A {
        int x;
    public:
        void member_func();
    };

In the class declaration above, you see that the member function named `member_func`, which is a `public` member function of class `A`, has no parameter variables. However, from the compiler's perspective, this function has a parameter variable:

`void A::member_func(A *const this);`

Let's recall that the `this` pointer is itself a `const` pointer. In this case, an assignment cannot be made to the `this` pointer within the function. For example, the following code is invalid:

    A a;
    void A::member_func()
    {
        this = &a; // Invalid!
    }

However, the `this` pointer is not a pointer whose pointed-to location is `const`. That is, an assignment can be made to the object the `this` pointer points to. Or, an assignment can be made to the members of the object the `this` pointer points to.

So, if one wanted to prevent the class object, whose address is secretly taken from the outside, from being changed by assignment within the member function, it would be preferred for the `this` pointer to be a pointer whose pointed-to location is `const`, right?

`void A::member_func(const A *const this);`

In such a case, just as an assignment could not be made to the object the `this` pointer points to, i.e., the `*this` object, assignment to the members of the object the `this` pointer points to would also be prevented. This is exactly what a `const` member function means from the compiler's perspective. The `this` pointer of a function declared as `const` is a pointer whose pointed-to location is `const`.

The class members can be accessed directly within the member function. But in reality, the compiler uses the `this` pointer to reach these members.

    void A::member_func()
    {
        x = 10;
        // equivalent to: this->x = 10;
    }

When the member function is `const`, since the `this` pointer is also a pointer whose pointed-to location is `const`, this assignment is no longer valid:

    void A::foo() const
    {
        x = 10;
        // Invalid! (because 'this' is 'const A *const')
    }

Now let's consider the case of calling another member function of the class within the definition of a member function. Let's look at this situation from the compiler's perspective. The calling member function secretly passes the address it received from the outside, i.e., the value of the `this` pointer, as a secret argument to the function it calls. That is, the `this` pointer of the calling member function is assigned to, or copied to, the `this` pointer of the called member function.

In C++, it is not valid to assign the value of a pointer whose pointed-to location is `const` to a pointer whose pointed-to location is not `const`:

    const int *cptr;
    int *p;
    p = cptr; // Invalid! (Text has 'p = ptr', assumed typo)

### The `mutable` Keyword

Even if a member function changes the value of a member of the class object that calls it, it may not have made any observable change on the abstracted meaning of the object. In this case, for readability, the function in question should undoubtedly be a `const` member function.

So, since a `const` member function cannot change the class members, how is this possible? In this case, the class member is declared with the **`mutable`** keyword. The information given to the compiler by declaring a class member with the `mutable` keyword is: **This member can also be changed by `const` member functions.**

Examine the following example:

    class X {
        mutable bool flag;
        //..
    public:
        //...
        void foo() const;
    };
    
    void X::foo() const
    {
        flag = false;
        //...
    }

The `bool` type member named `flag` of the `X` class is declared with the `mutable` keyword. It is valid for the `const` member function named `foo` of the class to make an assignment to the `flag` member of the class.

### `const` Class Objects

A `const` class object is a class object whose value will never change.
A class object can be defined as `const`. The members of a `const` class object can be used, but they cannot be changed in any way. For example:
With a declaration like
`const Date birth_date(4, 3, 1964);`
, the class object named `birth_date` is defined as `const`. Now the members of the `birth_date` object cannot be changed. Even if the `day`, `month`, and `year` members of the `Date` class were in the `public` section,
it would not be possible to change the member with an assignment like:

`birth_date.day = 10;`

The members of a class object can also be changed by the member functions of the class. In that case, a `const` class object **must not be able to call a member function that can change the class members**! For example:

    const Date birth_date(4, 3, 1964);
    birth_date.set(6, 1, 1966); // Invalid.

In an operation like this, the `set` member function would change the members of the `birth_date` object. For security and readability, this situation must also be prevented. But, how does the compiler understand whether the `set` function will change the class members? It may not be possible to get this information by looking at the function's code. Because the program may be written in several modules. The relevant function may not be in that module. According to the rules of the language, **a `const` class object can only call the `const` member functions of the class**. Because it is already guaranteed by another check that `const` member functions will not change the class members.

For example:

    const A a;
    a.func();

In the code snippet above, the compiler looks at the declaration of the `func` function related to class `A` and determines whether it is a `const` member function. If `func` is a `const` member function, the call is valid; if not, the call is invalid. The situation is reported with an error message.

From the compiler's perspective, the situation is extremely clear:
With the call `a.func();`, the address of the `const a` object is secretly assigned to the parameter variable of the `func` function. The address of the `a` object is of type
`(const A *)`.
This address can only be assigned to a pointer whose pointed-to location is `const`. However, if the `func` function is not a `const` member function, the hidden parameter variable of the function is of type
`(A *const)`. (Translator's Note: The text writes `A*`, but it's `A *const this`).
Therefore, the function call is invalid. (Assigning `const A*` to `A *const` is invalid).

A class pointer whose pointed-to location is `const` or a `const` class reference can also be in question. The members of a class object cannot be changed via such a pointer or reference. Examine the following example:

    void display_totaldays(const Date *pDate)
    {
        cout << pDate->totaldays();
        // Invalid if totaldays function is not const!
    }
    
    int main()
    {
        Date date;
        display_totaldays(&date);
        return 0;
    }

Here, the parameter variable of the `display_totaldays` function is a class pointer whose pointed-to location is `const`. The members of the class object this pointer points to cannot be changed, and a non-`const` member function of the class cannot be called for this object. The same situation is also true for `const` references. We are converting our example to the following form:

    void display_totaldays(const Date &r)
    {
        cout << r.totaldays();
        // Invalid if totaldays function is not const!
    }
    
    int main()
    {
        Date date;
        display_totaldays(date);
        return 0;
    }

Let's recall that the `const` keyword is generally used to increase readability. The programmer who sees a `const` class pointer or reference in the interface of the class they will receive service from, gains more information by understanding that the class members cannot be changed via this pointer or reference. If a function will not change the members of the class object whose address it takes, i.e., if it is not a "set" function, the function's parameter variable should be a pointer or reference whose pointed-to location is `const`.

### Calling the Constructor Function for `const` Class Objects

When a `const` class object is created, the constructor functions of the class are called normally. Because the purpose of constructor functions is to give an initial value to a class object. Just as an initial value can be given to a `const` object of fundamental types, an initial value can also be given to a `const` class object with the help of the constructor function. That is, the calling of the constructor function does not mean changing the object's value, but giving the object its initial value. For example:
With the statement
`const Date d(29, 5, 1992);`
, the class's constructor function gives the class object's members their initial values with the arguments sent to the function. That is, the constructor function does not assign to the class members; it gives them their initial values.

If functions that do not change the class members are not defined as `const` member functions, these functions are prevented from being called by `const` class objects. That is, these functions cannot serve `const` class objects.

### `const` Members of a Class

The `const` keyword has one more use in the C++ language. A member of a class can also be declared as `const` when declaring the class:

    class A {
        int a;
        const int b;
        //...
    public:
        void func();
    };
    
    void A::func()
    {
        b = 10;
        // Invalid!
    }

In the declaration above, the `b` member of class `A` is declared as `const`. The value of the `b` member cannot be changed within the member functions of class `A`.
However, if a class member is declared as `const`, the class's constructor function must be defined according to a special syntax rule. We will touch upon this rule, which we will call **M.I.L (Member Initializer List)** syntax, in detail later.

### `const` Overloading

A class can have two member functions with the same name and the same parameter structure, one `const` and one non-`const`. This situation is called **"`const` overloading"**.
When writing member functions to object code, the `const` keyword is also encoded in some way, in addition to the class names and parameter types. In other words, `const` is part of the function's signature. In such a case, when the member function with the same name is called, which member function is actually called is determined by looking at whether the object used in the call expression is `const`. If the call operation is done with a `const` class object, it is understood that the `const` member function is called; if it is done with a non-`const` class object, the non-`const` member function is called.

Compile and run the following code:

    #include <iostream>
    using namespace std;

    class A {
    public:
        A() {}
        void func();
        void func() const;
    };
    
    void A::func()
    {
        cout << "A::func()" << endl;
    }
    
    void A::func() const
    {
        cout << "A::func() const" << endl;
    }
    
    int main()
    {
        A a;
        const A ca;
        
        a.func();  // Calls A::func()
        ca.func(); // Calls A::func() const
        
        return 0;
    }

### Copy Constructor Function

A class's **copy constructor** is a special constructor function that is called when an object of that class is created by being initialized. As you will recall, initialization is a declaration statement and has different characteristics from an assignment statement.

`int x = 10;`

In the statement above, the `int` variable `x` is created by taking the initial value 10. A class object can also be defined by taking its initial value from another class object of the same type:

    class A {
    public:
        A();
    };
    
    int main()
    {
        A a1; // Default constructor is called for a1.
        A a2(a1); // a2 is created by taking its initial value from a1.
        return 0;
    }

Let's remember that in C++, a constructor function is automatically called in every situation where a class object is created. A constructor function is also called when a class object is created by taking its initial value from another class object. This function is named the "copy constructor". If the copy constructor is not defined by the programmer, it is **automatically defined by the compiler**.

The copy constructor that the compiler will automatically write is an `inline` function considered to be declared in the `public` section of the class, and its parametric structure is as follows:

    class A {
        //...
    public:
        A(const A&);
        // Copy constructor
    };

The copy constructor written by the compiler copies the values of the relevant members of the class object on the right side of the initialization operation to the members of the class object for which it was called, i.e., the `*this` object. Such a copy is known as **"memberwise copy"** (or shallow copy).

### In Which Situations Is the Copy Constructor Called

A class object can be initialized in three different ways:

**1. In explicit initialization form**

    A a1;
    A a2(a1);

In the code snippet above, the `a2` object is created by taking its value from the previously defined `a1` object. The copy constructor written by the compiler is called for the defined `a2` object. The `a1` object is passed to this function by reference.
You know that single-parameter constructor functions can also be called in the following form:

    A a2 = a1;

In this case, too, the copy constructor is called for the `a2` object. The `a1` object is passed to this function by reference.

**2. Pass-by-value from arguments to parameter variables**
An argument sent to a function gives its initial value to the function's parameter variable object. That is, when the function is called, the parameter variable object is created by taking its initial value from the expression sent as an argument to the function:

    void func(A p)
    {
        //...
    }
    
    void foo()
    {
        A a;
        func(a);
    }

In the code snippet above, the parameter variable of the `func` function is of class type `A`. The value of the local `a` object is sent as an argument to the `func` function called within the `foo` function. The parameter variable `p` of type `A`, which is created when the `func` function is called, is created by taking its initial value from the `a` object. In this case, the copy constructor is called for the parameter variable `p`. The `a` object is passed to the called copy constructor by reference.

**3. You know that functions transfer their return values to the outside by creating a temporary object.** When the `return` statement is executed during the running of the code of a function that produces a return value, a temporary object of the function's return value type is created by initialization. The created temporary object takes its initial value from the `return` expression. If a function returns a class type, the `return` expression must also be a class object, right? In this case, the temporary object that will carry the return value is created by taking its initial value from the object that is the `return` expression. That is, the copy constructor is called for the temporary object that will carry the return value. The class object, which is the `return` expression, is also passed to the copy constructor by reference. Examine the following code snippet:

    A func()
    {
        A a;
        //...
        return a;
    }

In the function above, the temporary object created when the `return` statement is executed takes its initial value from the local `a` object. That is,
an operation like `A temp_object = a;` is in question.

As you know, a class can have more than one constructor function with different signatures, but the class's destructor function is unique. In all three situations above, the class's destructor function is called for the class objects created with the copy constructor when the lifetime of these objects ends.

If the compiler writes the copy constructor itself when the programmer does not write one, and the copy constructor written by the compiler assigns all members to each other one-to-one, why would the programmer need to write a copy constructor?

**In some cases, the one-to-one assignment of the members of objects is not a desired situation!**
In some classes, some members of the class objects control external resources. The assignment of the values of these members to each other can lead to undesirable results. Let's consider a class named `String` defined to hold strings. Let the simplified design of the class be as follows:

    // string.h
    class String {
        char *m_p;
        int m_len;
    public:
        String(const char *str);
        ~String();
        void make_upper();
        void print() const;
    };
    
    // string.cpp
    // #include “string.h”
    #include <iostream>
    #include <cstring>
    #include <cctype>
    
    using namespace std;
    
    String::String(const char *str)
    {
        m_len = strlen(str);
        m_p = new char[m_len + 1];
        strcpy(m_p, str);
    }
    
    String::~String()
    {
        delete[] m_p;
    }
    
    void String::make_upper()
    {
        for (int k = 0; k < m_len; ++k)
            m_p[k] = toupper(m_p[k]);
    }
    
    void String::print() const
    {
        cout << m_p;
    }

Examine the following `main` function that uses the defined `String` class carefully:

    int main()
    {
        String s1("Necati");
        {
            String s2 = s1;
            s2.print();
            //...
        } // s2.~String() is called here
        
        s1.make_upper(); // Undefined Behavior
        s1.print();      // Undefined Behavior
        return 0;
    } // s1.~String() is called here

With the operation of the constructor function called when the `s1` object is created, a dynamic area of 7 characters length is created. The starting address of the created dynamic area is stored in the pointer member named `m_p`, which is a member of the `s1` object.
Then, inside the block, this time the `s2` object is created by taking its initial value from the `s1` object.
Since the copy constructor written by the compiler will assign the values of the members of the `s1` object to the members of the `s2` object, the pointer, which is the `m_p` member of the `s2` object, also points to the same dynamic area, right?
At the end of the block where the `s2` object is defined, since the lifetime of the `s2` object will be completed, the class's destructor function is called for the `s2` object. The destructor function is defined to return the previously obtained dynamic block to the "free store". The dynamic area pointed to by the `m_p` member of the `s2` object is returned to the free store. However, the starting address of this dynamic block is also the value of the `m_p` member of the `s1` object. Although the `s2` object has completed its life, the `s1` object is still alive. However, the dynamic area of the `s1` object has now been freed. Since the `make_upper` and `print` member functions of the class operate on the allocated dynamic area, the `s1.make_upper()` and `s1.print()` function calls cause a pointer error at runtime.
Of course, meanwhile, when the `s1` object completes its life, the destructor function is also called for the `s1` object, and this function also tries to return the previously returned dynamic area to the free store again. This is another runtime error (undefined behavior). For the defined `String` class, similar errors could have appeared in different forms:

    void func(String s)
    {
        //...
    } // s.~String() is called here
    
    int main()
    {
        String name("Necati");
        func(name);
        name.print();
        // Runtime error
        //...
        return 0;
    }

In the `main` function, an object named `name` of `String` class type is defined. Then the `name` object is sent as an argument to the `func` function. The parameter variable of the called `func` function is of `String` class type. In this case, with the calling of the function, the copy constructor is called for the `s` object, which is the parameter variable. When the end of the main block of the `func` function is reached, this time the destructor function is called for the `s` object.
The area pointed to by the object's `m_p` member is returned to the free store. However, after the function call, the lifetime of the `name` object is still ongoing. When the `print` member function of the `name` object is called, this member function accesses a block that has already been returned. That is, it causes a pointer error.

### Writing the Copy Constructor

If the programmer writes a copy constructor, the compiler no longer automatically writes one. Most of the time, the copy constructor written by the programmer, instead of directly associating the created object with the source of the object that gives the initial value, creates a different resource for the created object. Thus, the errors arising from the sharing of the same resource by more than one object are eliminated. Below, a copy constructor is declared and defined for the `String` class defined earlier:

    class String {
        //...
    public:
        String(const String &);
        //...
    };
    
    String::String(const String &r)
    {
        m_len = r.m_len; // (Text has strlen(r.m_p), but r.m_len is better)
        m_p = new char[m_len + 1];
        strcpy(m_p, r.m_p);
    }

Let's examine the written copy constructor function:
The reference `r`, which is the parameter variable of the function, takes the place of the object that gives the initial value to the created `String` object. First, the length of the string held by the object that gives the initial value is assigned to the `m_len` member of the created class object. Then, a block of `m_len + 1` bytes length is obtained dynamically with the `new[]` operator. The starting address of the dynamic block is stored in the `m_p` member of the newly created object. Then, with the standard `strcpy` function, the string, which is held in the dynamic area of the object that gives the initial value, is copied to the new block.
With the execution of the code of the written copy constructor, the created object now comes to use its own dynamic area. When the destructor function is called for this object, the `delete[]` operator used within the destructor function returns only the block allocated for that object. The copy constructor did not directly transfer the values of the class members to each other; it created a new resource for the created object and accessed the resource used by the object that gives the initial value, and ensured copying to the newly obtained resource. Such copying is called **"deep copy"**.

### Can the Parameter of the Copy Constructor Be an Object Instead of a Reference?

Let's assume the copy constructor for the `String` class defined above is declared in the following form:

    class String {
        //...
    public:
        String(String);
        //...
    };

Let's assume an object of `String` class type is sent to a function by value:

    void foo(String);
    void func()
    {
        String str("Necati");
        foo(str);
        //...
    }

In this case, the copy constructor is called to create the parameter variable object of the `foo` function. However, since the parameter of the copy constructor is also an object of `String` class type, this time the copy constructor is called again for the `String` class type object that is the parameter of the copy constructor. In this case, the recursively called copy constructor consumes the stack area after a certain time. (This is why the parameter **must** be a reference).

### Assignment Operator Overloading Function

When a class object is assigned to a class object of the same type, a function is also automatically called. We will name this called function the **"assignment operator function"**. The assignment function is also a special function. That is, if the programmer does not define this function, this function is also **written automatically by the compiler**. The assignment function that the compiler automatically writes is a non-static member function of the class and is declared as `inline`.

For example, the declaration of the assignment function written by the compiler for a class named `A` is as follows:

    class A {
        //...
    public:
        A &operator=(const A&);
        //...
    };

The assignment function written by the compiler assigns the members of the class object on the right side of the assignment operator to the members of the object on the left side of the assignment operator, one-to-one. The function returns the class object on the left side of the assignment operator by reference.
`a1` and `a2` being objects of class type `A`,
an assignment like
`a1 = a2;`
is converted by the compiler into a call to the assignment function of class `A`:

`a1.operator=(a2);`

The address of the object on the left of the assignment operator, i.e., the address of the `a1` object, is passed as the `this` address to the called member function.

In cases where the one-to-one assignment of the members of class objects is not appropriate, the assignment function written by the compiler is not desired. In this case, the programmer can write an assignment function themselves to ensure the assignment is done as they wish. If the programmer writes an assignment operator function, the compiler no longer writes this function. If it is necessary to define a copy constructor for a class, it is often necessary to write the assignment function for the same class as well. Consider the `String` class given as an example earlier:

    int main()
    {
        String name1("Deniz");
        {
            String name2("Yusuf");
            name2 = name1;
        } // name2.~String() called
        name1.print();
        //...
    } // name1.~String() called

Let's examine the code above:
At the beginning of the `main` function's main block, an object named `name1` of `String` class type is defined. The called constructor function dynamically obtains a 6-character block and stores the starting address of this block in its pointer member named `m_p`. It copies the string "Deniz" to this block. In the inner block located in the `main` function, this time an object named `name2` is created. This object similarly holds the string "Yusuf".
With the assignment `name2 = name1`, the assignment function written by the compiler is called. Since this function assigns the members of the objects, which are the operands of the assignment operator, to each other one-to-one, the value of the `m_p` member of the `name1` object is assigned to the `m_p` member of the `name2` object. In this case, the `m_p` member of both objects points to the same dynamic block, i.e., the dynamic block where the string "Yusuf" is. (Translator's Note: The text is wrong here. `name2 = name1` means `name2`'s pointer will point to `name1`'s data, which is "Deniz". The "Yusuf" block is now leaked). In this case, the connection with the block where the string "Deniz" (Yusuf in text) is, is lost. But the main big error occurs with the termination of the inner block.

At the end of the inner block, the destructor function is called for the `name2` object. You know that the called destructor function returns the block pointed to by the object's `m_p` member to the free store. However, after the inner block closes, the `name1` object is still alive, but the `m_p` pointer of this object now points to a block that has been returned.
With the call `name1.print();`, a dynamic block that has been returned is accessed. This is a pointer error. On top of this many errors, the last error also occurs when the `name1` object's life ends. This time, the destructor function called for the `name1` object tries to return the previously returned dynamic block a second time. This is also undefined behavior.

### Writing the Assignment Function

If it is not desired for the resource used by the object on the right side of the assignment operator to be shared by the object on the left side of the operator, a function must be written for the assignment operator. The assignment function for the `String` class declared earlier can be defined as follows:

    String &String::operator=(const String &r)
    {
        if (this == &r)
            return *this;
        
        delete [] m_p;
        
        m_len = r.m_len;
        m_p = new char[m_len + 1];
        strcpy(m_p, r.m_p);
        
        return *this; // (Text is missing return *this)
    }

Let's examine the written function. We will touch upon the `if` statement at the entrance of the function later. The assignment function has an important difference from the copy constructor. Whichever class object the copy constructor is called for, that class object does not exist before the function call. The object starts its life with the calling of the constructor function. However, the situation is different when it comes to the assignment function. Whichever object the function is called for, this object has already been created before. A block has already been obtained for the use of this previously created object.
The assignment function written for the `String` class must first return the dynamic block allocated for the object:
This is provided with the statement:
`delete [] m_p;`
Later, for the object on the left side of the assignment operator, i.e., the `*this` object,
a new dynamic block is obtained with the statement
`m_p = new char[m_len + 1];`
, and with the call
`strcpy(m_p, r.m_p);`
, the string held in the dynamic block of the object on the right side of the assignment operator is copied to the newly obtained dynamic block. You see that the function returns with the value
`*this`.
The function returns the class object, for which it was called, by reference. In other words,
the function call to which the assignment `name1 = name2` is transformed returns the `name1` object by reference. So, why might this be necessary?
When it comes to fundamental types, you know that the value produced by the assignment operator is the value assigned to the object. The same feature can be provided within a class type object by having the function that overloads the assignment operator return the `*this` object. Examine the code below:

    int main()
    {
        String name1("Deniz");
        String name2("Yusuf");
        String name3("Huseyin");
        String name4("İbrahim");
        
        name1 = name2 = name3 = name4;
        
        name1.print();
        name2.print();
        name3.print();
        name4.print();
        return 0;
    }

You know that the associativity of the assignment operator is **right-to-left**. (Translator's Note: The text says left-to-right, which is incorrect.)
The statement
`name1 = name2 = name3 = name4;`
is converted by the compiler into a chain of function calls as follows:
(Translator's Note: The text's `name1.operator=(name2.operator=(name3.operator=(name4)));` is correct for right-to-left.)

`name1.operator=(name2.operator=(name3.operator=(name4)));`

You know that assigning an object to itself does not constitute a syntax error.
Let's assume an object of `String` class type is assigned to itself:

    int main()
    {
        String name("Necati");
        name = name;
        //...
    }

What happens when the assignment function we wrote is called? The assignment function, called for the object that is the left operand of the assignment operator, first returns the dynamic block pointed to by the `m_p` pointer. However, since the object that is the right operand of the assignment operator is also the same object,
the expression `strcpy(m_p, r.m_p);` causes a pointer error. Because the `r.m_p` object is now pointing to a block that has been returned.
How can the error be fixed? If the object that is the left operand of the assignment operator and the object on its right side are the same, no operation should be done:

    if (this == &r)
        return *this;

Let's examine the statement above: The `this` pointer used inside the assignment function is the address of the class object that is the left operand of the operator, right? The `r` reference has also taken the place of the object that is the right operand of the assignment operator. Then the expression `&r` is the address of the object that is the right operand of the assignment operator. Two objects with the same address are the same object. If the object is being assigned to itself, the function returns the `*this` object by reference without doing any operation.

Should the check of whether the object is being assigned to itself be made in the code of the assignment operator function?
You might think: Why would a programmer assign a class object to itself for no reason?
This error is mostly related to pointers, references, and function calls.

    *ptr = x;

In the assignment statement above, let `ptr` be a pointer of a class type and `x` be an object of the same class type. If `ptr` points to the `x` object before this assignment operation, the object is assigned to itself.

### Conversion Constructor

Constructor functions of a class that can be called with a single argument are called **conversion constructors**. Such a constructor function either has a single parameter, or its other parameters take default values.

    class Account {
        int acc_no;
        double balance;
    public:
        Account(double);
        // Conversion constructor
        //...
    };

In the `Account` class defined above, the constructor function declared as `Account(double) ;` is a conversion constructor. The function has a single parameter variable.

    class Complex {
        double r, i;
    public:
        Complex(double r, double i = 0);
        // Conversion constructor
        //...
    };

Again, in the `Complex` class defined above, the constructor function declared as `Complex(double r, double i = 0);` is a conversion constructor. The function can be called with a single argument.

A class's conversion constructor allows an expression of another type to be **automatically converted** to a temporary object of the class type.
For example, for the `Account` class defined above, all of the following statements are valid:

    void func(Account p)
    {
        //...
    }
    
    int main()
    {
        Account a1 = 200.;
        a1 = 300.;
        func(200.);
        return 0;
    }
    
    Account foo()
    {
        double x;
        //...
        return x;
    }

With the first statement in the `main` function, the `a1` object of `Account` type is created by taking the initial value `200.`. In this case, the value `200.` is converted to a temporary object of `Account` class type via the conversion constructor. The temporary object gives its initial value to the `a1` object with the copy constructor. That is, from the compiler's perspective, such a statement
`Account a1 = Account(200.);`
or
`Account a1 = (Account) 200.;`
can be considered equivalent to these statements. Let's recall that the functional form of the C++ type-casting operator is also valid.
Most C++ compilers, for optimization purposes, directly call the class's constructor function for the `a1` object in this case, instead of first creating a temporary object and calling the copy constructor with the temporary object. We will re-examine this situation later.

Let's get to the second statement:
`a1 = 300.;`
As we know from C, a struct object can only be assigned another object of that struct type. That is, in the C language, an expression of another type is never automatically converted to a struct type. However, in C++, the compiler, seeing an expression of another type assigned to a class object, queries whether a conversion constructor exists to understand if the assignment is possible. If such a constructor function exists, automatic type conversion is done. If such a function does not exist, since conversion is not possible, a compile-time error occurs.
The assignment statement above is treated by the compiler as follows:

`a1.operator=(Account(300.));`

That is, first, the value `300.` is passed as an argument to the conversion constructor, and a temporary object of `Account` class type is created. The value of the created temporary object is passed as an argument to the assignment operator function called for the `a1` object.

A similar situation is in question for the `func(200.)` call. The expression `200.`, which is the argument sent to the `func` function, is first converted to a temporary object of `Account` class type with the conversion constructor. The parameter variable of the `func` function takes its initial value from this temporary object via the copy constructor. That is, the meaning of the code from the compiler's perspective
is equivalent to a statement like:
`func(Account(200.));`

Now let's examine the code of the `foo` function. The `return` statement of the `foo` function gives its initial value to the temporary object that will carry the function's return value. The `double` type `x`, which is the `return` expression, automatically causes the creation of a temporary object of `Account` class type. The temporary object that will carry the function's return value takes its initial value from this temporary object via the copy constructor. In these situations, the compiler can again produce shorter codes for optimization purposes, but we will not go into this topic for now.

The type conversions above could be done by the programmer using type-casting operators, as well as being done automatically by the compiler. Now let's change the `main` function to use type-casting operators:

    int main()
    {
        Account a1 = Account(200.); // Account a1 = (Account)200;
        a1 = Account(300.); // a1 = (Account)300.;
        func(Account(500.)); // func((Account)500.);
        return 0;
    }

In the comment lines, the type-casting operators were used in C-style.
In our future lessons, we will learn C++'s new type-casting operators that are not in C. Let's say for now that C++'s new type-casting operator, `static_cast`, can also be used for the type conversions above.

For automatic or explicit conversion to be performed, the type of the expression to be converted to a temporary class object does not have to be exactly the same as the parameter of the conversion constructor. Automatic conversions related to fundamental data types can be done before the conversion constructor is called. Let's assume the `func` function declared above is called as follows:

`func(10);`

An `int` type expression is sent as an argument to the `func` function. The parameter of the `func` function is of `Account` class type. For the `Account` class's
`Account(double);`
function to be called, first, the `int` value 10 is converted to `double` type by automatic type conversion, and then to a temporary object of `Account` class type with the conversion constructor. That is, for the compiler,
a call like `func(10)`
is equivalent to the call:
`func(Account(double(10)))`

The automatic conversion of a non-class type expression to a class type may not always be desired. In some cases, such a conversion prevents a coding error that occurred while writing the program from being found by the compiler. Examine the code below:

    int main()
    {
        int a;
        Account ac(400.);
        func(a);
        //...
        return 0;
    }

Let's assume the programmer who wrote the function, instead of sending the `Account` class object `ac` as an argument to the `func` function, mistakenly sent the value of the `int` type `a` object. For the compiler,
the call `func(a)`
is completely valid. The `a` expression is first converted to `double` type, and then from `double` type to `Account` class in the way we explained above, and sent as an argument to the `func` function. That is, the function call expression is treated by the compiler as:
`func(Account(double(a)));`

If it is not desired for a non-class type expression to be converted to a class type with a conversion constructor, this situation can be declared to the compiler with the **`explicit`** keyword.

### The `explicit` Keyword

The `explicit` keyword can be used in the declaration of a class's constructor function. The `explicit` keyword is written only in the function's declaration; if the constructor function is defined outside the class, it does not appear in the function definition.
A constructor function declared with the `explicit` keyword is a conversion constructor that **cannot be used for automatic type conversion**. If the constructor function is declared with the `explicit` keyword, conversion can still be performed explicitly, i.e., by using type-casting operators, but automatic conversion is prevented by the compiler's error mechanism. Try to recompile our example above in the following form:

    class Account {
        int acc_no;
        double balance;
    public:
        explicit Account(double); // explicit Conversion constructor
        //...
    };
    
    void func(Account p)
    {
        //...
    }
    
    int main()
    {
        Account a1 = 200.; // Invalid. automatic conversion cannot be done!
        a1 = 300.; // Invalid. automatic conversion cannot be done!
        func(200.); // Invalid. automatic conversion cannot be done!
        return 0;
    }
    
    Account foo()
    {
        double x;
        //...
        return x;
        // Invalid. automatic conversion cannot be done!
    }

### Friend Declarations

Any function that is not a member function of a class can be given access rights to the `private` and `protected` sections of that class.
A function can be declared as a **friend function** of a class. To declare a function as a friend function of a class, the `friend` keyword is written in front of the function declaration. Examine the following class declaration:

    class Account {
        int account_no;
        double balance;
    public:
        //...
        friend double balance_dif(const Account &, const Account &);
        //...
    };

In this example, `balance_dif` is a global function. However, it is declared as a friend function within the `Account` class with the `friend` keyword. Friend functions are functions that are privileged only in terms of access. If an object, pointer, or reference of the befriended class is defined within a friend function, every section of the class can be accessed via that object, pointer, or reference. In the example above, the `balance_dif` function is declared as a friend function of the `Account` class. Therefore, every section of the class can be accessed with a class object of the `Account` class defined within the `balance_dif` function.

    class A {
        int x, y; // (Text has 'int x, int y', assumed typo)
    public:
        A(int, int);
        friend void func();
    };

Let's examine the example above. Class `A` has two private members named `x` and `y`. The global function `func` is declared as a friend function of the class. Although `func` is a global function, the access restriction is removed for the private members of objects of type `A` defined within the `func` function:

    void func()
    {
        A a(10, 20); // (Text has 'A a', but A has no default constructor)
        a.x = 10; // Accessing private section, but valid
        a.y = 20; // Accessing private section, but valid
        //...
    }

If `func` were a normal function, i.e., not a friend function of class `A`, the `a.x` and `a.y` accesses would be invalid. The `friend` keyword must be used only in the function's declaration. Writing the `friend` keyword in the function's definition is a syntax error.

Friend functions are **not** member functions of the class. The only difference friend functions have from other global functions is that they have access privilege. The `this` pointer is not passed to friend functions. Therefore, the class members cannot be accessed directly within friend functions (they must use an object).

In applications, the parameter variable of a friend function is usually a pointer or a reference to the befriended class. Let's examine the `balance_dif` function for the `Account` class from the first example:

    double balance_dif(const Account &r1, const Account &r2)
    {
        return r1.balance - r2.balance;
    }

The parameter variables of functions are within the function's scope. That is, if the parameter variable of a friend function is an object, a pointer, or a reference to the befriended class, every section of the class can be accessed with this object, pointer, or reference. In the definition of the `balance_dif` function above, the private member named `balance` is accessed by using the references `r1` and `r2`, which are the parameter variables of the function, with the dot operator. Undoubtedly, after the `balance_dif` function is declared as a `friend` function within the `Account` class, it could also have been defined in the following forms:

    double balance_dif(const Account a1, const Account a2)
    {
        return a1.balance - a2.balance;
    }

or

    double balance_dif(const Account *p1, const Account *p2)
    {
        return p1->balance - p2->balance;
    }

A function can be a friend function of more than one class. It does not matter at all in which section of the class the friend function declaration is made. In the example above, the `balance_dif` function was declared as a friend in the `public` section in the `Account` class. However, no difference would have occurred if it had been declared in the `private` or `protected` section.

Not only global functions, but also **member functions of other classes** can be friend functions. For example:

    class Myclass {
        //...
        void myfunc();
    };
    
    class Herclass {
        //...
        friend void Myclass::myfunc();
    };

In the example above, the `Herclass` class declares the `myfunc` function of the `Myclass` class as a friend.
The friend function declaration also serves as the function's declaration. In this case, the scope of the function declaration is determined by the place where the class declaration is made. For example:

    int main()
    {
        class X {
            //...
            friend void f();
        };
        
        f();
        // Valid
        // ...
    }
    
    void func()
    {
        //...
        f();
        // Invalid! Function declaration is not recognized in this block!
    }

Here, the friendship declaration of the `f` friend function inside the class is also accepted as the function's prototype declaration. However, the scope of this declaration is the same as the scope of the `X` class. That is, this declaration is only known within the `main` function. Therefore, when the `f` function is called inside the `func` function, a function that has not been declared before is called.

### When Should Friend Functions Be Used

Since friend functions are privileged functions in terms of access, they reduce the protection of the class's private members. Since friend functions can access every section of the class, when a change is made to the class's private members, not only the member functions but also the friend functions must be rewritten. Using friend functions too much means accepting the reduction of the importance of the class's `private` section.

Friend functions should be used to facilitate design and operations in complex situations. It is not a good idea to unnecessarily give friendship to some functions to make the code easier to write.
The most typical example that can make the use of friend functions necessary is the writing of global functions that overload operators. We will cover such functions later.

### Friend Classes

We mentioned that friendship can be given to a member function of another class. A class can give friendship to all member functions of another class. A **friend class** is the situation where all member functions of one class are the friend functions of another class. To make a class a friend class, the declaration
`friend class <class_name>;`
must be made within the befriended class. It does not matter in which section of the class this declaration is made. In this case, all member functions of the class specified as a friend can access every section of the class via an object, pointer, or reference of the relevant class type.

Examine the following example:

    class Node {
        int val;
        Node *next;
        friend class LList;
    };
    
    class LList {
    public:
        void add(int val);
        void remove(size_t n); // (Text has 'delete', which is a keyword)
        Node *get_head();
        // ...
    private:
        Node *phead;
        Node *pnode;
        size_t size;
    };

In the example above, the `LList` class is a friend class of the `Node` class. Within all member functions of the `LList` class, every section of the `Node` class can be accessed via an object, pointer, or reference related to the `Node` class. Note that the members of the `Node` class are in the `private` section, and although an object of `Node` class type can be defined within any function, the private members of the class cannot be accessed with the help of that object (outside of `LList`).

Friend classes can also be used to provide ease of access, just like friend functions. Of course, we must say that friend classes will also reduce the protection of private members.

### Friendship Declaration Is Not Bidirectional

A class giving friendship to another class does not lead to the conclusion that friendship is also received from the class given friendship. Examine the following example:

    class A {
    public:
        friend class B;
        void func();
    };
    
    class B {
        int b;
        //...
    };
    
    void A::func()
    {
        B object;
        object.b = 1;
        // Invalid!
    }

In the example above, class `A` gives friendship to class `B`. This does not lead to the conclusion that class `B` also gives friendship to class `A`. The attempt to access the private member of the `object` object of type `B` defined within the `func` member function of class `A` is invalid; it causes a compile-time error.

### "My Friend's Friend Is My Friend"

This sentence is not true when it comes to friendship declarations. The transitivity property is not in question for friendship declarations. Examine the following example:

    class A {
        int a;
    public:
        friend class B;
    };
    
    class B {
        friend class C;
        //...
    };
    
    class C {
    public:
        void func();
    };
    
    void C::func()
    {
        A object;
        object.a = 1;
        // Invalid
    }

In the example above, class `A` gives friendship to class `B`, and class `B` to class `C`. A conclusion such as class `A` gives friendship to class `C` does not come out of this situation. The attempt to access the `private` part of class `A` within the `func` member function of class `C` results in an error at compile time.

### Static Members and Functions of a Class

First, let's recall some points related to the use of the `static` keyword with local and global variables. When the `static` keyword is used with local variables, it is decisive on the **storage duration** of the defined variable. That is, a `static` local variable is not created at the beginning of the block where it is defined and deallocated from memory when the block terminates; it is created when the program is loaded, just like global variables; it stays in memory until the program terminates. `static` local variables are static-duration variables that adhere to block scope and are often used as an alternative to global variables.

Global variables defined with the `static` keyword belong to **internal linkage**. That is, `static` global variables cannot be used in another module even if an `extern` declaration is made. A function can also be defined as "static" in this sense. `static` functions cannot be called from other modules.

In the C++ language, the members and functions of a class can also be declared with the `static` keyword. Now let' incexamine the use of the `static` keyword related to classes:

### Static Members of a Class

In some cases, all objects defined from a class type need to access a global object. As an example, you can think of the situation where a global variable is needed to hold the value of how many objects of a class type have been created. Or, you can think of a global pointer variable holding the starting address of a dynamic block allocated for the entire class, and all class objects thus accessing this dynamic area.

If this information is kept as a member of the class, both the class objects grow unnecessarily, and if these values are changed, the change needs to be made separately for all existing class objects. If this information is kept in global variables, a coding detail that concerns only the class in question, not the outside, is leaked. Another disadvantage of a global variable is that it is not possible to ensure that only the class can reach them and prevent access outside the class. That is, a global variable cannot be `public` or `private` *for a class*. Yet another disadvantage is that a global variable used for this purpose unnecessarily pollutes the global namespace.

If a member of a class is declared by prefixing it with the `static` keyword within the class declaration, it is treated as a kind of class-specific global variable. Such a member is called a **static member** of the class. There is no difference between a static member of a class and global variables in terms of the way they are written to object code. Only, the static members of the class are combined with the class names and written into the object code. `static` members **do not take up space within the class object**. They are stored outside like global variables. They are only logically associated with the class. `static` members of the class, like global variables, **must be defined separately outside**. The definition operation is necessary and valid, regardless of which section of the class the declaration was made in. The definition of `static` members is done as follows:

`<type> <class_name> :: <variable_name> [ = initial_value];`

As can be seen from the general form, `static` members are defined by being specified together with the class name. For example, a `static` member named `s` of `int` type of class `X` is defined as follows:

`int X::s;`

The static members of the class are not located inside the created class object. That is, static members do not increase the `sizeof` value of the class object. There is **only one** instance of a static member of a class. Static members are actually global variables. They are only logically associated with the class.

Examine the following example:

    class Person {
    private:
        char *name;
        int no;
    public:
        Person(const char *, int);
        ~Person();
        void display() const;
    public:
        static int count;
    };

    #include <iostream>
    #include <cstring>
    using namespace std;
    
    int Person::count = 0;
    
    Person::Person(const char *nm, int n)
    {
        name = new char[strlen(nm) + 1];
        strcpy(name, nm);
        no = n;
        ++count;
    }
    
    void Person::display() const
    {
        cout << name << " " << no;
    }
    
    Person::~Person()
    {
        delete [] name;
        --count; // (Translator's Note: Added decrement, which is missing in text)
    }
    
    int main()
    {
        Person person("Burak Gencer", 120);
        cout << sizeof(person) << endl;
        return 0;
    }

In the example above, the size of the `person` object of `Person` class type is obtained with the `sizeof` operator. The size obtained is only `sizeof(char *) + sizeof(int)`. The `count` member, which is the `static` member of the class, is actually a global variable. It is created to be static-duration without the need to define a class object. Therefore, it does not take up space in the class object. In the program above, if you are working under DOS and in near models, you get 4; if you are working under DOS and in far models, 6; if you are working in UNIX or Win32 systems, you get 8. In our example, you also see that the `static` member of the class is also defined globally by specifying the class name as follows.

`int Person::count = 0;`

As you can see, `static` members can also be given an initial value during definition. However, `static` members of fundamental types that are not given an initial value contain zero, just like global and `static` local variables.
If a `static` member of a class is not defined outside the class, a compile-time error does not occur when the `static` member is used. The error occurs at the **link stage**.

A `static` member of a class can be accessed from the outside via an object, pointer, or reference of the relevant class type. Of course, the `static` member must have been declared in the `public` section.

Examine the following `main` function:

    int main()
    {
        Person x("Ali Serçe", 25);
        cout << x.count;
        // 1
        Person y("Ahmet Altıntartı", 32);
        cout << y.count;
        // 2
        return 0;
    }

Here, the `count` variable accessed with `x.count` and the `count` variable accessed with `y.count` are the **same variable**. It does not matter which class object is used to access a `static` member of a class. Therefore, `static` members can also be accessed **without a class object**, using the class name and the scope resolution operator. For such an access to be valid, the declaration must have been made in the `public` section. Examine the following `main` function:

    int main()
    {
        Person x("Ali Serçe", 25); // (Text has no 'no', added for constructor)
        cout << Person::count << endl;
        // 1
        Person y("Ahmet Altıntartı", 32); // (Text has no 'no', added for constructor)
        cout << Person::count << endl;
        // 2
        return 0;
    }

In the example, access is done in the form `Person::count` without using any class object. Since the member named `count` is declared in the `public` section of the class, the access is valid. `static` members can be accessed directly within member functions like normal members. For example, access is provided in this way within the constructor function of the `Person` class:

    Person::Person(const char *nm, int n)
    {
        name = new char[strlen(nm) + 1];
        strcpy(name, nm);
        no = n;
        ++count;
    }

The `static` member of a class can be an array or a pointer. If it is an array, the size of the array may not be specified during the declaration. However, the size of the array must be specified during the definition of the array. A `static` array belonging to a class can also be given an initial value in curly braces during definition. In this case, the array size may not be specified. For example:

    class Date {
    private:
        int day, month, year;
        static const char *week_days[];
    public:
        // ...
    };
    
    const char *Date::week_days[] = {"Pazartesi", "Salı", "Çarşamba",
    "Perşembe", "Cuma", "Cumartesi", "Pazar"};

The `static` members of a class must be defined only once. For this, the definition operation must be done in a **`.cpp` file**. If the definition is made in a `.h` file, and this file is included in more than one place in the project, an error will occur at link time. There is no need to define an object of that class type to use a `static` member of a class. That is, even if no object of the class type is defined, the `static` members of the class can still be used.

### When Should Static Members Be Used

The `static` members of a class are actually global variables logically associated with the class. While global variables can be accessed within all functions, `static` members can be directly accessed only within the member functions of the class. `static` members of a class can also be accessed from the outside with a class object, pointer, or reference, or with the class name and the scope resolution operator. If a global variable is meaningful only for one class, defining it as a `static` member instead of a normal global variable narrows the scope from a perceptual point of view. Thus, the person examining the code understands the variable's relation to the code better.

Recall the `totaldays` and `revdays` member functions that perform conversions related to the number of days passed since 01/01/1900, given in the `Date` class example. These functions obtained the information of how many days the months have from a global array named `mon_days`. Although the `mon_days` array is global, it is used only for the purpose of determining how many days the months have. That is, `mon_days` is a global array used only by the member functions of the `Date` class. If this array were made a normal member of the class, it would unnecessarily take up space inside all `Date` type objects, right? Therefore, to both leave it as global and associate it with the class, the `mon_days` array was defined as a `static` member. Also, the `display_text` function of the class can be rearranged to also print the month names as text. Month names and day names can be placed in `static` pointer arrays of `char` type. We will give a slightly more developed form of the `Date` class later.

The `static` members of a class are also members of the class. However, in terms of some features, the `static` members of a class differ from other members:

A member of a class **cannot be** of the same class type, but a class **can have** a `static` member of the same class type. Examine the following class declaration:

    class A {
        static A sa; // Valid
        A *mptr; // Valid
        A ax; // Invalid
    };

A `static` member of a class can be used as a default argument in a member function of the same class. However, a non-`static` member of a class cannot be used in this way:

    class A {
        int m_x;
        static int ms_y;
    public:
        void func(int = m_x); // Invalid
        void foo(int = ms_y); // Valid
    };

### Static Member Functions of a Class

A function can be declared by prefixing it with the `static` keyword within the class declaration. Such functions are called **static member functions** of the class. `static` member functions of a class are like a global function. However, they are logically associated with the class. The **`this` pointer is not passed** to these functions. The fact that the `this` pointer is not passed to the `static` member functions of a class means that the members and other member functions of the class cannot be accessed directly within those functions.

Although a `static` member function of a class is like a global function, its definition is done by specifying the class name, as with member functions. We are making some changes in the `Date` class:

    class Date {
    private:
        int day, month, year;
        static int mon_days[12];
        static char *mon_tab[12];
        static char *day_tab[7];
    public:
        enum Days {Sunday , Monday, Tuesday, Wednesday, Thursday, Friday,
        Saturday};
        Date();
        Date(int, int, int);
        void display() const;
        void display_text() const;
        long totaldays() const;
        void revdays(long);
        int weekday() const;
        static bool isleap(int);
        // static member function
    };

In the previous form, the `isleap` function, which finds whether a year is a leap year, was a normal global function. However, this function has a meaningful function only with date operations. Therefore, it has been logically associated with the `Date` class, and perception has been strengthened. The `isleap` function can be defined outside as follows:

    bool Date::isleap(int year)
    {
        return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    }

Note that the `static` keyword is written only during the declaration, not during the definition.
The `day`, `month`, and `year` members of the class cannot be accessed directly within `isleap`. The other member functions of the class cannot be called directly without a class object.

As you can see, global functions that are logically related to the class on the outside but do not use the members and member functions of the class can be made `static` functions of the class. A `static` member function of a class can be called with a class object, pointer, or reference. Or, if it is in the `public` section of the class, the call can also be made directly by specifying the class name with the `::` scope resolution operator:

    int main()
    {
        Date x;
        if (x.isleap(1996))
            cout << "is a leap year" << endl;
        else
            cout << "is not a leap year" << endl;
        
        if (Date::isleap(2000))
            cout << "is a leap year" << endl;
        else
            cout << "is not a leap year" << endl;
        
        return 0;
    }

Here, two calls are made in the form `x.isleap` and `Date::isleap`. Since `isleap` is in the `public` section of the class, both call forms are valid. However, it is still recommended that `static` member functions be called with the class name, without using a class object. After all, the class object used in the call has no special meaning.

A `static` function of a class can be called directly within a member function of the class. For example, in the program above, the `isleap` function is called directly within the `totaldays` function.

`static` members can be used directly within a `static` member function of a class. Recall that `static` members of a class do not take up space in the class object. In this case, the `this` pointer is not needed to access `static` members. An example related to this use is given below:

    class Person {
    private:
        char *name_;
        int no_;
        static int count_;
    public:
        Person(const char *nm, int n);
        ~Person();
        void display() const;
        static int get_count();
    };

    #include <iostream>
    #include <cstring>
    using namespace std;
    
    int Person::count_ = 0;
    
    Person::Person(const char *nm, int n)
    {
        name_ = new char[strlen(nm) + 1];
        strcpy(name_, nm);
        no_ = n;
        ++count_;
    }
    
    void Person::display() const
    {
        cout << name_ << endl;
        cout << no_ << endl;
    }
    
    int Person::get_count()
    {
        return count_;
    }
    
    Person::~Person()
    {
        delete [] name_;
        --count_; // (Translator's Note: Added decrement, missing in text)
    }
    
    int main()
    {
        Person x("Necati Ergin", 25);
        Person y("Haluk Yetis", 34);
        cout << Person::get_count();
        return 0;
    }

In this example, we made some changes to the `Person` class we gave earlier. For example, we placed the `static` `count_` member in the `private` section of the class. We added a `static` member function named `get_count` to get the value of this member. Note that the `get_count` function is only related to `count_`, which is a `static` member of the class.

A global function with the same name and parameter structure as a `static` member function of a class can exist. Because `static` functions of a class are written into the object code by being combined with the class name. The constructor and destructor functions of a class cannot be `static` member functions. If we think that these functions must operate directly on the created and destroyed object, it is also clear that they should not be `static` member functions.

A `static` member function also **cannot be declared as `const`**. Because a `const` member function means a member function whose `this` pointer points to a `const` object. Since `static` member functions do not have a `this` pointer, they cannot be `const` either.

Since a `static` member function of a class is, in the end, a member function related to the class, when an object related to the class is defined within `static` member functions, every section of the class can be accessed from the outside via that object.

    class Sample {
        int x;
    public:
        static void func();
    };
    
    void Sample::func()
    {
        Sample sam;
        sam.x = 20;
        // Valid (sam.x is accessed from within a member function)
        //...
    }

Sometimes `static` member functions are used in specific code patterns to achieve special goals. For example, let's assume it is desired to allow only dynamic objects of a class type to be created. `DynamicOnly` being a class,
let creating an object in the form
`DynamicOnly d;`
be prevented. Let it be a requirement that all objects related to the `DynamicOnly` class be created dynamically, i.e., with the `new` operator. How can this be ensured?
If the constructor functions of the class are placed in the `private` section of the class,
a definition in the form `DynamicOnly d;` becomes invalid, right? However, in this case, an object cannot be created with the `new` operator either.
As you will recall, when a class object is created with the `new` operator, first, a dynamic space as large as the class object will occupy is allocated, then the starting address of this space is passed to the class's constructor function as the `this` address. Since the constructor function is in the `private` section of the class, creating an object is still not possible, right?

However, if the class's constructor function is in the `private` section, and since another `private` member function of the class can be called within a member function of the class, a dynamic object can be created within a member function of the `DynamicOnly` class. So, since it is necessary to call a member function with a class object, how will such a class object be obtained? This is where a `static` member function can be used: A `static` member function that returns with the address of a dynamic class object:

    class DynamicOnly {
        DynamicOnly(); // constructor is private
    public:
        static DynamicOnly *create_object();
    };
    
    DynamicOnly * DynamicOnly::create_object()
    {
        return new DynamicOnly;
        // Valid because another private function can be called within a member function.
    }

    #include <iostream>
    using namespace std;
    
    int main()
    {
        // DynamicOnly d;
        // Invalid!
        
        // DynamicOnly *ptr = new DynamicOnly;
        // Invalid!
        
        DynamicOnly *ptr = DynamicOnly::create_object();
        // Valid because the create_object function is in the public section
        
        delete ptr;
        // The created dynamic object is destroyed.
        return 0;
    }

In our example above, the constructor function of the `DynamicOnly` class is declared in the `private` section. Thus, creating an object of `DynamicOnly` class type within a global function is prevented. However, an object can be created within a member function. The `static` member function named `create_object`, which is placed in the `public` section of the class, returns with an address of `DynamicOnly` class type.
The `create_object` function returns with the address of an object created with the `new` operator. Since our function has the status of a member function, it is valid to call the `private` constructor function of the `DynamicOnly` class within our function.

Now let's take a look at the `main` function. Within the `main` function, the `create_object` function, which is a `static` member function,
can be called in the form
`DynamicOnly::create_object()`.
Thus, the created dynamic object can be used as desired with the address of the dynamic object, which is the return value of the function.

### `const static` Members of Classes

A `static` member of a class can be declared with the `const` keyword. In this case, a class-specific member whose value will not change is created. If a `const static` member of a class is of an integer type, this member can be **initialized within the class**:

    class Myclass {
        const static int size = 100;
        int a[size];
        //...
    };

A `const static` member that has been initialized with a constant expression can be used as a constant expression. Such members can serve as symbolic constants that concern only one class.