## REFERENCES

References can be thought of as high-level pointers used to achieve certain software goals.

### How References Are Defined

Just as the `*` atom is used before a pointer name when defining a pointer, the `&` atom is written before a reference name when defining a reference. For example:

    int i = 20;
    double d = 10.2;
    int &ri = i;
    // ri is a reference to int.
    double &rd = d; // rd is a reference to double.

Unlike pointer variables, a reference must be defined by being initialized with an object of the same type.
In the example above, the `ri` reference is defined by being initialized with the `int` object `i`, and the `rd` reference with the `double` object `d`. The `&` used in the definitions above is not an operator. It merely informs the compiler that the defined object is a reference. Defining a reference without initialization is invalid. It is evaluated as a compile-time error. For example:

    int &a;

This definition is invalid.

A reference, as an initial value, takes the place of the object assigned to it.
After a definition like:

    int &r = b;

the `r` object now takes the place of the `b` variable at every source code point where it is visible; it can be used in its place. Now, another way to access the `b` variable is to use the name `r` directly instead of using the name `b`. This situation can also be expressed as:
The reference `r` is **bound** to the variable `b`.

### Using a Reference After Definition

If the reference variable is used after the definition process, the variable to which the reference is bound is used:

    #include <iostream>
    int main()
    {
        int a = 10;
        int &r = a;
        r = 20;
        std::cout << "a = " << a << std::endl;
        return 0;
    }

Let's examine the `main` function above:
The reference `r` is bound to the previously defined variable `a`. Thus, the reference `r` takes the place of the variable `a`. The subsequent assignment to the reference `r` is actually made to the variable `a`.

If these operations were done using a pointer variable instead of a reference, code like the following could have been written:

    #include <iostream>
    int main()
    {
        int a = 10;
        int *ptr = &a;
        *ptr = 20;
        std::cout << "a = " << a << std::endl;
        return 0;
    }

Indeed, compilers produce the same machine code for both programs.

When a reference that has received its initial value, i.e., a reference that takes the place of an object, is an operand of an operator, the operator processes the object the reference stands for, not the reference itself:

    #include <iostream>
    using namespace std;
    int main()
    {
        int a = 10;
        int &r = a;
        cout << "a = " << a << endl;
        r += 2;
        cout << "a = " << a << endl;
        r = -r;
        cout << "a = "<< a << endl;
        return 0;
    }

With the statement `r += 2`, the value of the variable `a` is incremented by 2. Now `a`'s new value becomes 12.
With the statement `r = -r;`, the value of the variable `a` is made -12.

To understand the function of a reference well, one can consider the equivalent counterparts of the code created with pointer variables. For example, the equivalent counterpart of the program part above, created with a pointer variable, is as follows:

    #include <iostream>
    using namespace std;
    int main()
    {
        int a = 10;
        int *ptr = &a;
        cout << "a = " << a << endl;
        *ptr += 2;
        cout << "a = " << a << endl;
        *ptr = -*ptr;
        cout << "a = " << a << endl;
        return 0;
    }

### A Defined Reference Cannot Be Re-seated to Another Object

A reference, upon its definition, takes the place of an object. Now, the reference in question always takes the place of the same object within its scope. It is not possible for the reference to be bound to another object later:

    #include <iostream>
    int main()
    {
        int a = 10;
        int b = 20;
        int &r = a;
        r = b;
        std::cout << "a = " << a << std::endl;
        return 0;
    }

The reference `r` defined in the `main` function above takes the place of the variable `a`. The subsequent
`r = b;`
assignment does not mean that the reference `r` now takes the place of the variable `b`. The meaning of this assignment is: the value of the variable `b` is being assigned to the object to which the reference `r` is bound. In terms of the code produced by compilers, this situation can also be evaluated as follows: **References correspond to pointers that are themselves `const`.** Let's consider if the code above was written using a pointer variable instead of a reference:

    #include <iostream>
    int main()
    {
        int a = 10;
        int b = 20;
        int *const ptr = &a;
        *ptr = b;
        std::cout << "a = " << a << std::endl;
        ptr = &b; // Invalid
        return 0;
    }

In the example above, `ptr` is a pointer variable that is itself `const`. After the definition of the `ptr` variable, the address of another object can no longer be assigned to `ptr`, right?

### Declaring References as `const`

A reference can be defined with the `const` keyword. The `const` keyword is written before the `&` atom. The object that a reference defined in this way stands for cannot be modified through the reference. For example:

    int main()
    {
        int a = 10;
        const int &r = a;
        r = 20;
        // Invalid!
        return 0;
    }

The statement `r = 20` located in the `main` function is not valid. The assignment is actually made to the variable `a`. Using a `const` reference, the object it stands for cannot be changed. But, of course, the `const` reference can be used as an r-value in operations. The equivalent C counterpart of the program part above, created with pointers, would be:

    int main()
    {
        int a = 10;
        const int *const ptr = &a;
        *ptr = 20;
        //Invalid
        return 0;
    }

Here, `ptr` is a pointer variable that is **both itself `const` and the location it points to is `const`**. Just as assignments to `ptr` itself are invalid, assignments to the object `ptr` points to are also invalid.

So, can the `const` keyword be used after the `&` atom, before the reference's name? When the `const` keyword was used after the `*` atom before the pointer name, it meant that the pointer itself was `const`.

    int x;
    int *const ptr = &x;
    int &const r = x;
    //Invalid!

The definition of the reference named `r` above is invalid. Because references are, by their definition, created to take the place of only a specific object. That is, a reference, after receiving its initial value with an object, can no longer take the place of another object. References, in this sense, are already `const` objects themselves. Therefore, there is no need to use the `const` keyword in the manner above.

Recall that the address of a `const` object can only be assigned to a pointer whose pointed-to location is `const`:

    const int x = 10;
    int *p1 = &x;
    //Invalid
    const int *p2 = &x;
    //Valid

Similarly, a non-`const` reference cannot take the place of a `const` object. Only a `const` reference can take the place of a `const` object.

    const int x = 10;
    int &r1 = x;
    //Invalid!
    const int &r2 = x; //Valid

### Why `const` References are Used

`const` references are used for the same purpose as pointers whose pointed-to location is `const`. With `const` references, the objects they are bound to cannot be changed. Such references take the place of objects for read-only purposes.

### Using References as Parameter Variables

In C++, references are generally used as parameter variables in function definitions. Functions whose parameter variables are references must be called with an object of the same type. As a result of such a call, the reference, which is the parameter variable, takes the place of the object, which is the argument:

    #include <iostream>
    void func(int &r)
    {
        r = 20;
    }

    int main()
    {
        int a = 10;
        func(a);
        std::cout << a << std::endl;
        return 0;
    }

Let's remember that parameter variables are created automatically when the function is called.
For example, with the call to the function named `func` in the form:
`func(a);`
the variable `a` is actually assigned as the initial value to the reference parameter of the function `func`. That is, with the call to the function, the parameter variable `r` (a reference) takes the place of the variable `a`. It is the variable `a` itself that is sent to the `func` function.

In fact, when it comes to the code produced by the compiler, an address transfer is actually taking place. Note that a function whose parameter is a reference is called with the object itself, not with an address value. Even though the call is made in this form, an address transfer is actually involved.

Examine the following example:

    #include <iostream>
    using namespace std;

    void swap(int &a, int &b)
    {
        int temp = a;
        a = b;
        b = temp;
    }

    int main()
    {
        int x = 10;
        int y = 20;
        cout << "x = " << x << endl;
        cout << "y = " << y << endl;
        swap(x, y);
        cout << "x = " << x << endl;
        cout << "y = " << y << endl;
        return 0;
    }

Here, the function named `swap` swaps the values of two variables. The function is called in the form `swap(x, y);`. The references, which are the parameter variables of the `swap` function, take the place of the `x` and `y` objects.
Undoubtedly, the addresses of the `x` and `y` variables are actually passed to the function. `a` used inside the function actually takes the place of `x`, and `b` takes the place of `y`. The equivalent C counterpart of the above program, created with pointer variables, is also as follows:

    #include <iostream>
    using namespace std;

    void swap(int *a, int *b)
    {
        int temp;
        temp = *a;
        *a = *b;
        *b = temp;
    }

    int main()
    {
        int x = 10;
        int y = 20;
        cout << "x = " << x << endl;
        cout << "y = " << y << endl;
        swap(&x, &y);
        cout << "x = " << x << endl;
        cout << "y = " << y << endl;
        return 0;
    }

### Functions with `const` Reference Parameters

A function's parameter can also be a `const` reference. Such a function is one that does not make changes to an object, but only uses the value of that object.

    void access(const T &r);

Let's assume the name `T` in the declaration above is type information. The function named `access` can operate on an object of type `T`, but it cannot change the object in question. The `access` function only makes use of the value of an object of type `T`.

    void mutate(T &r);

The function named `mutate` also operates on an object of type `T`, but it *can* change the object in question.
From a syntactical rules perspective, there is undoubtedly no obligation for the `mutate` function to change the `T` type object that comes to it. However, it should be assumed that such a function *will* change the object that comes to it. If it did not change the object, the function's parameter would have been chosen as `const`.

In this case, we can also say this: If a function will not make a change to the object whose address it receives via reference, the function's parameter should be made a `const` reference. If a function's parameter is a non-`const` reference and the function does not make changes to the object it receives, this situation should be evaluated as a programming error.
Programmers who see the function's interface, i.e., its declaration, will think that the function will make changes to the sent object.

### Passing Struct Objects to Functions by Reference

You know that a struct object can be passed to a function in two ways.

**1. Passing the struct object's value (call by value).** In this case, the function's parameter variable is a struct variable. The function is called with another struct variable itself. Since two struct variables of the same type can be assigned to each other, this call form is also valid. Examine the following example:

    #include <iostream>
    struct Person {
        char name[30];
        int no;
    };

    void display_person(Person y)
    {
        std::cout <<
            y.name << '\n' <<
            y.no << std::endl;
    }

    int main()
    {
        Person per = {"Necati Ergin", 123};
        display_person(per);
        return 0;
    }

In this type of transfer, there is a relative time loss because the corresponding members of the struct are block-copied to each other. For this reason, this type of transfer is considered a bad technique in the C language and is not used much. Of course, very small struct objects may be transferred in this way. Since the function is called by value, i.e., the argument struct object in the function call expression is transferred by being copied to the function's parameter variable, it is not possible for the argument struct object to be changed by the function this way.

**2. Passing the struct object's address to the function (call by reference).** (Note: The text calls this "call by reference", but it's technically pass-by-pointer). In this case, the function is called with the address of the struct variable. The function's parameter variable also becomes a struct pointer of the same type. In this transfer form, no matter how large the struct object is, what is actually transferred is a single address value. To access the members of the struct whose address is taken within the function definition, the pointer, which is the parameter variable, becomes the operand of the `->` operator. Struct variables are mostly passed to functions in this way. Examine the following example:

    void display_person(const Person *ptr)
    {
        std::cout <<
            ptr->name << '\n' <<
            ptr->no << std::endl;
    }

    int main()
    {
        Person per = {"Necati Ergin", 123};
        display_person(&per);
        return 0;
    }

Since references in the C++ language are a type of pointer, an efficient transfer of structs by the reference method is also possible. In such a transfer form, the function is called with the struct object itself. The function's parameter variable becomes a reference of the same struct type. In such a call, the reference, which is the function's parameter variable, takes the place of the struct object sent as an argument to the function. So, how are the struct object's members accessed within the function? With the dot operator or the arrow operator? Yes, with the **dot operator**. Because, when a struct reference is used, since the reference will take the place of the object sent from outside, the parameter reference takes the place of the struct object sent from outside. That is, the use of the reference does not specify an address. Therefore, the dot operator is used to access struct members with a struct reference. Examine the following example:

    #include <iostream>
    using namespace std;
    struct Person {
        char name[30];
        int no;
    };

    void display_person(const Person &r)
    {
        cout <<
            r.name << '\n' <<
            r.no << endl;
    }

    int main()
    {
        Person per = {"Necati Ergin", 123};
        display_person(per);
        return 0;
    }

### Should a Function's Parameter Variable be a Pointer or a Reference?

In C++, should a pointer or a reference be used for argument passing? When it comes to object-oriented programming, it can be said that references should be used as much as possible instead of using pointers. Many programmers adopt this principle:
**"Use references wherever you can, use pointers when you have to!"**

However, the C++ language does not have to be used only for writing programs with the object-oriented programming technique. Programs can, of course, also be written with C++ using the "procedural" programming technique. If your aim is to use C++ as a better C and to write programs with the procedural programming technique, you might prefer to use pointers because they better describe what is happening at the machine level.

In C++, let's assume a function call like the following is made, where `a` is an object:
`func(a);`
The name of the object `a` is written in the argument expression. In this case, there are two possibilities:

1.  The function's parameter variable is an object of the same type. In this case, the compiler produces code that will copy the value of the argument object to the parameter variable. For example:

    void func(int val)
    {
        val = 20;
    }
    int main()
    {
        int a = 5;
        func(a);
        return 0;
    }
    In the example above, the value of the variable `a` is copied to the parameter variable `val`, which is created when the function is called. Therefore, the assignment `val = 20;` made in the `func` function has nothing to do with `a` in the `main` function. The assignment is made to the `val` variable, which is the parameter of the `func` function. `func` is a function called by value (call by value).

2.  The function's parameter variable is a reference of the same type. In this case, there is a hidden address transfer. That is, the compiler produces code that will copy the address of the object used as an argument in the call expression to the reference parameter of the called function.

    #include <iostream>
    using namespace std;
    void func(int &r)
    {
        r = 20;
    }
    int main()
    {
        int a = 5;
        func(a);
        cout << "a = " << a << endl;
        return 0;
    }

With the assignment `r = 20`, the variable `a` defined inside the `main` function is actually changed. `r` used inside the `func` function takes the place of the `a` object. You can see this as the `a` object itself being sent to the `func` function.

In C++, a programmer who sees a function being called as `func(a);`, if they have not seen the function's definition or declaration, might get the wrong idea by thinking, with their standard C habit, that the function cannot change the variable `a`. The fact that it's not clear whether the object's value or its address is being copied can, in some cases, reduce readability. To prevent this situation, attention should be paid to the use of references.

However, the Object-Oriented Programming Technique (OOP) aims for the program to be written not at the working plane of the programming language, but at the plane of the problem itself. In this case, in an object-oriented program, the person reading the program does not wonder whether the value or the address of the object `a` is sent to the function; they are concerned with the meaning of the `func` function in the problem plane. That is, this situation, which is seen as a deficiency in terms of readability in the C language, is seen as a kind of "information hiding" in the C++ language. This is one of the main difficulties C programmers face when switching to C++. In programming with the C language, the general principle is that there is no confidentiality in the open. However, this is not the case when C++ is used for OOP. Because the main purpose is to get closer to the problem's own plane. The person writing the program thinks with the parts of the problem that is the purpose of writing the program, not with the tools of the programming language, when thinking about the program.

We mentioned that references can be used in situations where the parameter will not be changed. Since there is no such change, the reference should also be defined as `const` to increase readability.

### Similarities and Differences Between References and Pointers

Both pointer variables and references are objects that hold address information. However, when pointer variables are used, the address information inside them is considered, whereas when a reference is used, the object to which the reference is bound is considered. Let's examine the following codes:

    #include <iostream>
    int main()
    {
        int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int *p = &a[0];
        //int *p = a;
        *p = 10;
        ++p;
        *p = 20;
        std::cout << a[0] << " " << a[1];
        return 0;
    }

Now let's examine the code below:

    #include <iostream>
    using namespace std;
    int main()
    {
        int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int &r = a[0];
        r = 10;
        ++r;
        r = 20;
        cout << a[0] << " " << a[1];
        return 0;
    }

(Translator's note: The second example is tricky. `++r` increments the *value* of `a[0]`, not the reference itself. `a[0]` becomes 10, then `++r` makes it 11, then `r = 20` makes it 20. The output is `20 2`.)

References are related to the address of a single element. An address is placed in a reference when it is initialized. This address information cannot be changed later. For example:

    int a = 10;
    int x = 20;
    int &r = a;
    r = x;

When these operations are done, the value `x` is transferred not to the reference, but to the object the reference stands for, i.e., `a`.

References, in the background, correspond to pointer variables that are themselves `const`. However, a pointer variable, if not `const` itself, can dynamically point to different objects within the program.

A function that performs general operations on an array could be defined. The starting address and size of the array were sent as arguments to such functions. A pointer was used to send the starting address of the array to the function. So, can the parameter of such a function be a reference? No! This job cannot be done with references as it is with pointers. However, just as there is a pointer that points to an `int` array of 10 elements, a reference that takes the place of an `int` array of 10 elements can also be defined. Examine the code below:

    #include <iostream>
    using namespace std;
    
    void display(int(&r)[10])
    {
        int k;
        for (k = 0; k < 10; ++k)
            cout << r[k] << " ";
        cout << endl;
    }
    
    int main()
    {
        int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        display(a);
        return 0;
    }

References can mostly be used to pass a single object to a function by the address method. For example, a single `int` value or a single struct variable can be passed to a function by reference. However, an `int` array or a struct array cannot be passed to a function in a natural way with this method.

Syntactically, the uses of references are narrower than those of pointers. There can be arrays of pointers, but there cannot be arrays of references. There can be pointers to pointers, but there cannot be references to references.

But, of course, there can be a reference that takes the place of a pointer. Examine the code below:

    #include <iostream>
    int main()
    {
        int x = 10;
        int *ptr = &x;
        int *&r = ptr;
        *r = 20;
        std::cout << "x = " << x << std::endl;
        return 0;
    }

Just as there are function pointers, there can also be function references. We will examine function references in detail later.

### The NULL Address and References

A pointer variable whose value is the `NULL` address is a pointer variable that points nowhere. You know how widely the `NULL` address is used in C: A function that returns an address can return the `NULL` address to indicate failure. For example, the standard C function `strchr` searches for a character in a string. If it finds the searched character in the string, it returns with the address of the place it found; if not, with the `NULL` address.

The `NULL` address can be passed to a function that takes an address from outside to convey special information. For example, if the standard `time` function is sent the `NULL` address, it does not write the calendar time value, i.e., the `time_t` type value, to an address, it only produces it as a return value. The `NULL` address can be used as a flag value for a pointer. For example, different jobs can be done in a control statement based on whether the value of a pointer is the `NULL` address or not.

However, a reference that does not take the place of any object cannot be defined. When a reference is defined, it must take the place of an object.

With the addition of references in C++, the need for pointers has not been completely eliminated. However, the easy and natural application of the "Object-Oriented Programming Technique" in particular requires the use of references.

### Address Operations on References

The address of a reference can be taken with the address operator. In this case, the address value of the object the reference stands for is obtained. For example:

    #include <iostream>
    int main()
    {
        int a = 10;
        int &r = a;
        int *p = &r;
        *p = 20;
        std::cout << "a = " << a << std::endl;
        return 0;
    }

Examine the operations. Here:
In the statement `p = &r;`, the reference has become the operand of the address operator. In this case, the address value of the object the reference stands for is obtained. In our example, this address is actually the address of the variable `a`. Note that the address obtained is of the same type as the reference type. Finally,
with `*p = 20;`, the value 20 is actually assigned to the object `a`.

The equivalent C counterpart of the program part above, created with pointer variables, is as follows:

    #include <iostream>
    int main()
    {
        int a = 10;
        int *p = &a;
        int *ptr = &*p;
        *ptr = 20;
        std::cout << "a = " << a << std::endl;
        return 0;
    }

### Case of Initializing References with an Object of a Different Type

We mentioned that a reference must be defined by being initialized with a variable of the same type.
Defining a reference by initializing it with a variable of a different type is invalid. Examine the following example:

    void func()
    {
        double d = 10.5;
        int &r = d;
        //Invalid
        //...
    }

However, initializing a `const` reference with an object of another type is valid:

    void func()
    {
        double d = 10.5;
        const int &r = d;
        // Valid
        //...
    }

In this case, first, the value of the object of a different type, which is bound to the `const` reference, is assigned to a temporary object created from the reference's type. The reference is then bound to this temporary object. That is, the compiler produces code like the following:

    int main()
    {
        double d = 10.5;
        int temp = (int)d;
        const int &r = temp;
        return 0;
    }

### Initializing References with Literals

Initializing a reference with a literal is also invalid. However, a `const` reference can be initialized with a literal:

    int &r = 10;
    const int &r = 10;
    // Invalid!
    // Valid

In this case, the compiler first creates a temporary object. It assigns the literal to the temporary object and produces code that binds the reference to the temporary object. In the assignment above, the following is actually done in the background:

    int temp = 10;
    // temporary object is created with the value 10.
    const int &r = temp;
    // r reference is bound to the temporary object.

### Functions Returning a Reference

Recall that the return values of functions are first taken into a temporary area by the compiler and then drawn from there and used. For example:
In a call like `x = func();`, first, the function named `func` is called. The function's return value is stored in a temporary object. Then it is drawn from this temporary object and used:
We can show this as rough code in the following form:

    temp = return expression;
    x = temp;

In fact, the return value type of the function specifies the type of this temporary object.

    double func()
    {
        // ...
        return expression;
    }

For example, the temporary area where the return value of the `func` function above will be placed is of type `double`. That is, with the `return` statement, this temporary object is actually being initialized.

If the function's return value is a reference, it means the temporary area is a reference. In this case, the `return` expression gives a reference its initial value, right? Examine the following example:

    #include <iostream>
    int x = 10;

    int &func()
    {
        return x;
    }

    int main()
    {
        func() = 20;
        std::cout << "x = " << x << std::endl;
        return 0;
    }

Here, the temporary area is a reference to `int`. So, what is actually done with the `return` statement is:
an operation like `int &temp = x;`.
In this case, the temporary object, which is a reference, is bound to the `x` object. Thus, the function call expression has now come to specify an object. In this case,
the assignment `func() = 20;` is actually made to the global `x` variable.

You can think of functions whose return value is a reference as conveying the object itself directly to the code part that calls them. The call expressions for such functions specify an object. That is, they can be used as l-values. The call expressions of functions whose return value is a reference mean the object specified by the `return` statement. The `return` statements of such functions must also specify an object of the same type.

The counterpart of the above program, created with pointer variables, would be as follows:

    #include <iostream>
    int x = 10;

    int *func()
    {
        return &x;
    }

    int main()
    {
        *func() = 20;
        std::cout << "x = " << x << std::endl;
        return 0;
    }

The machine codes to be produced for both programs are completely equivalent. Can you see that functions whose return value is a reference actually return with an address, but are used by accessing their contents via this address?

In the program above, let's examine the statement `*func() = 20;`. There are three operators in this expression. First, the function call operator is handled; the `func` function is called. This function returns an address value. Then, the object at this address is accessed with the `*` operator. The object accessed is the `x` object itself. Finally, with the assignment operator, the value 20 is assigned to the object whose address the function returned, i.e., the `x` variable.

### Functions Returning a Reference Should Not Return a Local Object

In the example above, could the `x` variable have been local? A function returning a reference that returns with a local object is an error equivalent to a function returning an address that returns with the address of a local variable. That is, it is a pointer error. The lifetime of the local object, which the function conveys to the code part that calls it via the return value, ends when the execution of the function's code is completed. However, this situation does not cause an error at compile time. Most compilers report this situation with a logical warning message.

### Why References Are Used

References are basically used to express address operations with a simpler syntax.
For example, if a function's parameter variable is a reference instead of a pointer, it is not necessary to use the `*` or `->` operator when the object is accessed with the help of the address inside the function. Thus, expressions can be written in a simpler form. Using the `&` or `*` operator brings the writing of the program closer to the plane of the programming language, while it has an effect that distances it from the plane of the problem itself.

Not using the address or indirection operator does not create a reduction in the produced machine code. Because the compiler performs the accesses made via reference with address operations, just as with pointers.
Apart from this, the reference type has been needed in various forms for the application of the object-oriented programming technique in the C++ language. That is, references are necessary for the application of many topics we will see later in C++.