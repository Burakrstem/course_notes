# Programming and C

## What is Software?

**Software** is the name given to programming and the general body of related subjects. When software is mentioned, programming languages, source programs written using these languages, and various files created come to mind.

## What is Hardware?

**Hardware** is the name given to the electronic part and structure of the computer.

## Classification of Software

Software can be divided into various groups according to its application areas:

1.  **Scientific and Engineering Software**
    Software used in solving problems in scientific fields and engineering applications. In this type of software, the amount of data is relatively low, but mathematical and statistical algorithms are used intensively. Such programs predominantly contain computation-oriented operations and intensively use the computer's **Central Processing Unit (CPU)**. Examples of such programs include programs that analyze electronic circuits and statistical analysis packages.

2.  **Application Software**
    Primarily **database-oriented** software. It generally deals with the creation, processing, and storage of data in files. Examples of this type of program include stock control programs, customer tracking programs, and accounting programs.

3.  **Artificial Intelligence (AI) Software**
    Software that mimics human intellectual or learning behavior. Examples include robot software, programs that play chess or bridge, etc.

4.  **Graphical Software**
    Programs where graphical operations and algorithms are used very intensively. Examples include games and **animation** software. These programs predominantly use the computer's graphical interface.

5.  **Simulation Software**
    Software used to simulate a system in a computer environment.

6.  **System Software**
    Software that manages the electronic structure of the computer. Compilers, communication programs, and operating systems are system software. For example, a word processing program is also system software. They perform lower-level operations compared to application programs.

## Evaluation Criteria for Programming Languages

Sources mention the existence of approximately 1000 - 1500 programming languages currently in use. Why are there so many programming languages? Despite this abundance, why are new programming languages still being designed? What characteristics might make one programming language different from the other(s)? Which qualifiers can be used if one were to define a programming language? To answer these questions, there must be criteria that allow for evaluation. These criteria are briefly examined below:

### Level

The **level** of a programming language is the measure of that programming language's proximity to human perception or the machine. A programming language is considered **high-level** the closer it is to human perception. Conversely, a programming language is considered **low-level** the closer it is to the electronic structure and operation of the computer.

The computer's processor has an **instruction set** that it understands. The processor can only execute the instructions within its own instruction set. The text written in the programming language is converted into instructions in the computer processor's instruction set through some processes.

Working with high-level languages is easy for the programmer and does not require extensive algorithm knowledge. In these languages, only *what* needs to be done is communicated to the program, but not *how* it should be done. Generally, as the level of a programming language increases, it becomes easier to learn that language and write programs in it.

**Machine language** is the natural language of the computer, dependent on the computer's hardware design. Machine languages were the first languages used to get computers to perform tasks, coinciding with the development of computers. That is why machine languages are also called **first-generation languages**.

Two fundamental problems were encountered when using machine language in programs. Code written in machine language consists of commands given directly to the machine's processor and hardware components. If a different CPU is used, or if the memory organization is done differently, the program no longer works; the program must be rewritten. This is because machine language is only applicable to a specific CPU or CPU series. Machine language is not **portable**. The other significant problem is that writing code in machine language is very cumbersome. Besides being very time-consuming and tedious to write, reading or understanding the written program is equally difficult. Especially when the program size increases, developing and expanding programs written in machine language become quite complex.

Initially, there was only machine language. That is why machine languages are also referred to as **1st generation languages**. Within the historical development of software and hardware, there is a process that extends from machine language to very high-level languages close to human perception (**4th generation languages**).

In the early 1950s, efforts to eliminate the problems associated with using machine language intensified. During these years, programs written in machine language were loaded into the computer's very limited memory and executed in this way. First, a step was taken that partially eliminated the difficulty of perceiving and understanding machine language: **Symbolic machine languages** were developed. Symbolic machine languages (**Assembly Languages**) consisted of certain abbreviation words and commands that bundled a few machine instructions. The use of symbolic machine languages quickly became widespread. However, symbolic machine languages had a major disadvantage compared to machine languages. Programs written in these languages were loaded into the computer's memory like programs written in machine language, but during the execution phase, the commands of the symbolic language were translated into machine language one command at a time with the help of an **interpreter** program, and the resulting machine code was executed. That is, the computer first translated the program into machine language by interpreting it during the execution phase, and then executed the translated machine code. When programs were executed this way, they slowed down by almost 30 times.

During this period, two interpreter programs notably emerged: John Mauchly's interpreter for UNIVAC 1 (1950) and the "Speedcoding" interpretation system written by John Backus for the IBM 701 in 1953. Although these interpreters ran very slowly compared to machine code, they increased programmer productivity. However, especially old machine language programmers argued that interpreters were too slow and that only programs written in machine language could be called real programs.

This problem was also overcome. The idea, which was considered brilliant for its time, was: Instead of the written code being translated into machine language every time it is run, another program to be developed should translate the code written in symbolic language into machine language once, and then whenever the program is to be run, the computer should execute only the machine code without interpretation. Grace Hopper developed this idea. Grace Hopper's invention was named **"compiler."** (Grace Hopper was also part of the team that developed the Cobol language, and she was the first to use the word "bug.") Programmers were now using Assembly programming languages consisting of symbolic words, the programs they wrote were converted to machine code by the compiler, and the machine code ran at full speed without losing any of its previous speed. Assembly languages took their place in history as **2nd generation languages**.

With the adoption of Assembly languages, computer usage rapidly increased. However, the fact that many commands were required to perform even the simplest operations on the computer initiated a quest to speed up and simplify the programming process, and as a result, higher-level programming languages began to be developed.

Languages developed later than Assembly languages in the historical process and at a higher level are considered **3rd generation languages**. These languages are all algorithmic languages. Few of the hundreds of high-level programming languages developed to date have survived. Almost all 3rd generation languages are derived from three main languages. These three languages, the first of the 3rd generation languages, are still in existence:

**FORTRAN** (FORmula TRANslator) was developed by John Backus for IBM between 1954 and 1957 for use in engineering and scientific applications requiring complex mathematical calculations. The FORTRAN language is still used in scientific applications requiring intensive mathematical calculations. The FORTRAN language has two important versions: FORTRAN IV and FORTRAN 77. ISO and ANSI standards were accepted for a version named FORTRAN-90 in the early nineties. The FORTRAN language is considered the oldest of the 3rd generation languages.

**COBOL** (COmmon Business Oriented Language) was developed in 1959 by a group consisting of computer manufacturers, private sector, and government sector computer users in America. The purpose of developing COBOL was to use a portable programming language for commercial applications requiring data management. The COBOL language is still widely used.

**ALGOL** (The ALGOritmick Language) was developed by a consortium in Europe in 1958. Since IBM adopted the FORTRAN language as the common programming language to be used on its hardware, Europeans also wanted to develop an alternative language. Many design features developed in the ALGOL language are used in all modern programming languages.

In the early 60s, work on programming languages brought the concept of **structured programming** to the agenda. The **PASCAL** language was developed by Professor Niclaus Wirth in 1971 to introduce the concept of structured programming to academic circles. The creator of the language named it after the mathematician and philosopher Blaise Pascal. This language quickly became the programming language used in universities. The fact that the Pascal language lacked some features necessary to support commercial and industrial applications limited its use. The Modula and Modula-2 languages were developed based on the Pascal language.

The **BASIC** language was developed by John Kemeney and Thomas Kurtz in the mid-1960s. It is said that the name BASIC was formed from the initial letters of "Beginner's All Purpose Symbolic Instruction Code." It is one of the oldest and simplest of the high-level languages. Despite all its simplicity, it has been used in many commercial applications. The BASIC language has also been standardized by ANSI. However, there are versions of the BASIC language that include additional features. For example, many features related to object-oriented programming were added to the Visual Basic language released by Microsoft. This language later took the name Visual Basic .NET. In addition, some versions of the BASIC language were generally accepted as the programming language used for writing macros that users would write for customization and automation purposes in application programs, for example, in MS Excel and MS Word programs.

The **ADA** language, on the other hand, was developed starting from the 70s with the support of the U.S. Department of Defense (DoD). DoD is one of the largest computer users in the world. This institution was using a large number of different programming languages to meet different software requirements and began searching for a single language that would meet all its needs. An international competition was organized to design the language. The winning company (CII-Honeywell Bull of France) developed the Ada language as a result of its work based on the Pascal language. The documentation for the Ada language was published in 1983. The name Ada is a reference to the name of Lady Ada Lovelace, the daughter of the philosopher Lord Byron. Ada Lovelace was the assistant of Charles Babbage, who first used punched cards in calculating machines. Charles Babbage worked throughout his life on the construction of machines named "Difference Engine" and "Analytical Machine" but died before realizing these projects. Nevertheless, the designs he developed are considered the ancestors of modern computers. Ada Lovelace prepared the punched cards and algorithms to be used for Charles Babbage's machine. Lovelace is considered to have written the first computer program in the early 1800s. Ada is a general-purpose language, used in many different fields, from commercial applications to guiding rockets. One of the important features of the language is its support for **real-time applications (embedded systems)**. Another feature is that it facilitates the writing of large programs due to its highly modular structure. However, the need for large, complex compilers has made its competition against C, Modula-2, and C++ languages difficult.

Very high-level languages and languages where programs, generally not containing algorithmic structures, are written in a visual environment are called **4th generation languages**. They are usually abbreviated as **4GL** (fourth generation language). They are the languages closest to human perception. The RPG language can be considered the first of the 4th generation languages. It was developed by IBM at the request of companies, especially users of small IBM machines, who wanted an easy language for report generation.

Programming languages can be grouped according to their levels:

* **Very high-level languages** or **visual languages/environments (visual languages)**: Access, Foxpro, Paradox, Xbase, Visual Basic, Oracle Forms.
* **High-level languages**: Fortran, Pascal, Basic, Cobol.
* **Mid-level programming languages**: Ada, **C**. (Mid-level languages run faster because they can be translated into machine language with less loss.)
* **Low-level programming languages**: Symbolic machine language (Assembly language).
* **Machine language**: The lowest-level programming language. Pure machine language consists entirely of 1s and 0s.

### Readability

**Readability** is a term that means the source code can be quickly and well understood. When the readability of the source code is in question, the responsibility lies largely with the programmer who writes the program. However, as with efficiency, this feature also depends to some extent on the design of the programming language, as some languages contain structures and tools that enhance readability. The best program code is not the one "most cleverly written but which no one can understand." In many cases, good programmers are unwilling to sacrifice readability for anything. This is because a readable program allows for updating even years later due to its easy comprehensibility. Readability becomes even more important in large-scale projects where many programmers work on shared code.

Readability is one of the most emphasized concepts in C. You will see frequent mentions of readability in many subsequent sections.

### Portability

**Portability** means that source code written for one system can be compiled without errors and run correctly when transferred to another system. Portability also means standardization. Programming languages are standardized by **ISO (International Standard Organization)** and **ANSI (American National Standard Institute)**. The C Language, whose standards were first established in 1989, is a more portable programming language than other programming languages.

### Efficiency

**Efficiency** is the characteristic of a program running fast and using less memory. The running speed and the amount of memory used by a program depend on many factors. Undoubtedly, the algorithm used also has an effect on speed and memory usage. The computer on which the program is run naturally also has an effect on speed. Efficiency can be considered a criterion related to the memory area used and the running speed when a program written in a programming language is run. When other factors that may play a role in efficiency are kept constant, it can be said that the design of the programming language used is also effective on efficiency. Viewed from this perspective, **C is an efficient language**.

### Usage Area

Some languages are designed for a specific application area. There are programming languages designed and used for system programming, artificial intelligence applications, simulation applications, database queries, and writing game programs. Other languages have a wider scope of use. For example, a language designed for use in database queries can also be used in engineering applications.

Although the C language originated as a system programming language, its powerful structure quickly made it a **general-purpose language**. Pascal and BASIC, on the other hand, are much more general-purpose languages.

C is a language whose main application area is **"system programming."** However, programs have been written in the C language for almost all application areas.

### Classification by Application Area

We can also group programming languages according to their application areas:

1.  **Scientific and Engineering Application Languages**: Pascal, **C**, FORTRAN. The C Programming language is also used intensively in academic work at universities.
2.  **Database Languages**: XBASE (Foxpro, Dbase, CA-Clipper), Oracle Forms, Visual Foxpro.
3.  **General-Purpose Programming Languages**: Pascal, **C**, Basic.
4.  **Artificial Intelligence Languages**: Prolog, Lisp.
5.  **Simulation Languages**: GPSS, Simula 67.
6.  **Macro Languages (Scripting languages)**: awk, Perl, Python, Tcl, JavaScript.
7.  **System Programming Languages**: Symbolic machine languages, BCPL, **C**, C++, occam.

Today, we can say that almost all system software is written in the C language. For example, 80% of the UNIX operating system is written in the C language, and the rest is written in symbolic machine language. This operating system was first created at BELL Laboratories. Its source codes were not kept secret, making it possible to develop it from various branches. UNIX-based operating system applications developed later were given different names.

C is a general-purpose system programming language that can be used in scientific and engineering fields.

### Subprogramming Capability

The method of breaking down problems that are difficult to solve as a whole into parts, solving these parts separately, and then connecting the parts is a frequently used method in programming. If a programming language has tools that allow this, it can be said that the programming language has **subprogramming capability**. Subprogramming capability means that a programming language supports writing the program in parts.

Subprogramming is also an indispensable part of the **Structured Programming Technique**. Subprogramming brings some significant benefits. Subprograms reduce the size of the source code. Writing frequently repeated operations using subprograms reduces the size of the executable program code. This is because subprograms are written into the executable code only once. The program code can be made to jump to the location of the subprogram, allowing this segment to be executed multiple times.

Subprogramming facilitates comprehension, increases readability, and also makes source code easier to test and update more easily. One of the most important benefits of subprogramming is the **reusability** of the created subprograms in multiple projects.

**C is a language with high subprogramming capability.** Subprograms in C are called **functions**. Functions are the building blocks of the C language.

### Ease of Learning and Teaching

The difficulty level of learning each programming language and developing applications in the learned programming language is not the same. Generally, as the level of programming languages increases, it becomes easier to learn and teach that programming language to others. An important reason for the popularity of widely used high-level programming languages today is that these languages are very easy to learn. However, gaining proficient skill by learning high-level languages often involves other difficulties. Such languages contain a large number of ready-made tools. For example, in a high-level programming environment, dozens of options may be presented to change the properties of a ready-made menu bar related to the GUI. In this case, the programmer has to learn the meaning of each option. That is, in some cases, although the increase in the level of the programming language brings a perceived convenience to the programmer, it also brings a learning burden to the programmer, especially regarding ready-made tools.

### Supports Provided for Programming Techniques

In the historical development process of programming, certain **programming techniques (paradigms)** have emerged. Since the sizes of programs written in the early days of programming were very small, there was little need to use a special technique when writing programs. This is because a program was small and simple enough for a single programmer to handle all aspects of it. There was no serious cost to changing a program or adding to a program.

Technical developments in computer hardware, increased user expectations from computer programs, and the effective use of graphical interfaces have led to a gradual increase in program sizes. With the growth of programs, different techniques and methods for writing programs have been developed. Examples of these techniques include **"procedural programming," "modular programming," "object-based programming," "object-oriented programming," and "generic programming."**

"Procedural programming" and **"structured programming"** are often used interchangeably. Structured programming is a programming technique. Today, almost all programming languages are designed to support structured programming to a greater or lesser extent. The idea of structured programming was developed in the 1960s. The structured programming technique is based on four main principles:

1.  **Divide and conquer**
    Programs that are difficult to write as a single whole are divided into smaller, more manageable pieces. That is, the program is divided into its smallest possible components (**functional decomposition**). These components are called subprograms, functions, procedures, etc. The benefits of subprogramming were explained earlier.
2.  **Data hiding**
    In the structured programming technique, variables that cannot be accessed from other parts of the program and that have a limited scope, i.e., variables to be used only in a certain part of the code, can be defined. These types of variables are generally called **"local variables."** Limiting the scope of variables reduces the risk of making errors, and also allows programs to be modified more easily and program segments to be reused in other programs. Information about *how* a subprogram or module performs a task is hidden from the user (client) of that subprogram or module. For the user (client), *what* the subprogram or module does is important, not *how* it does the task.
3.  **Single entry, single exit**
    In languages that support the structured programming technique, there is a single entry and a single exit mechanism to enter each subprogram segment. This tool is in harmony with the top-to-bottom flow of the program. Program segments can only be entered from a single point.
4.  **Loops, other control structures**
    Loops and other control statements are frequently used in the structured programming technique.

Almost all programming languages in use today support the structured programming technique to a greater or lesser extent.

**Object-oriented programming (OOP)** is also a programming technique. While the structured programming technique came to the fore in the 1960s, the object-oriented programming technique became widespread in the 1980s. This technique was developed due to the need arising from the excessive growth of source code. In the years when the C language was designed, the source codes of the largest imaginable programs were only a few thousand lines. With developments in computer hardware, increased user expectations from computer programs, and the effective use of graphical interfaces, the size of computer programs grew significantly. The size of many programs in use is measured in hundreds of thousands or even millions of lines.

The object-oriented programming technique is designed, first and foremost, as a technique for writing large programs better. When the C language was created, the emergence of such a technique was not possible because programs were already very small by today's standards.

In the object-oriented programming technique, the data related to the program and the code that processes this data are combined under a unit called an **object**. That is, the building blocks of this technique are objects. The most important difference of this technique from procedural programming is that the programmer thinks and constructs the program directly on the plane of the problem itself, rather than on the plane of the programming language. This allows a problem related to real life to be modeled much better in software.

With the widespread adoption of the object-oriented programming technique, new versions of many programming languages have been created by adding tools that facilitate the application of this technique to their structures. For example, the **C++** language was developed by making additions to the C language to enable the object-oriented programming technique to be applied. For similar purposes, the Delphi language was developed by making additions to the Pascal language, Oocobol by renewing the Cobol language, and Ada 95 by renewing the Ada language.

Some programming languages have been designed and developed to directly support the object-oriented programming technique. Such languages are also called pure object-oriented languages. For example, Java, Eiffel, and C# are pure object-oriented languages.

In summary, one of the most important questions to be asked about a programming language is perhaps whether that programming language has the tools to support a particular programming technique.

**The C language is a language that fully supports the procedural programming technique with its existing tools.**

### Input/Output Ease

The ability to access sequential, indexed, and random files, and to retrieve, update, and query database records. The database programming languages (DBASE, PARADOX, etc.) have superior capabilities in this regard compared to others. This constitutes their most typical feature. However, **C is a language with weak input/output ease.** Special libraries must be used in C for the management of databases.

## What Kind of Programming Language is C?

After examining the criteria, the C language can be placed in a specific position:

**C is a mid-level programming language.** The level of the C language is lower compared to other structured programming languages. The C language has both the advantages of high-level languages, such as control statements and data structures, and operators that reflect machine code statements, such as bitwise operators. That is, **C is a language close to both the machine's perception and human perception.** This is one of the main reasons why it is preferred.

Writing a program using the C language is much easier than writing the same program in machine language, but the efficiency of a program written in C does not decrease proportionally. **C is preferable to machine language directly for many applications in terms of efficiency.** Programming in the C language instead of machine language does not significantly reduce the efficiency of the created program.

The main application area of the C language is **"System programming."** What does system programming mean? Programs written for the management, direction, and control of hardware, which interact directly with the machine's hardware, are called system programs. For example, operating systems, compilers, interpreters, device drivers, programs related to computer communication, and automation programs are system programs.

Before C, system programs were written in Assembly languages. Today, it can be said that the C language is almost the only option for writing system programs. Today, C codes are running everywhere, from mobile phones to airplanes.

**C is an algorithmic language.** To write programs in the C language, it is not enough to know only the syntax and semantic structure of the language; general algorithm knowledge is also required.

**C is a highly portable language** compared to other languages. This is because it has had generally accepted standards since 1989.

**C is a language with high expressive power and strong readability characteristics.** The high readability of a text written in the C language is not due to it being a verbal language or a language close to the language used by humans.

**C is a very flexible language.** It does not impose restrictions on the programmer like other languages. It better reflects the capabilities of the machine to the programmer.

**C is a powerful language, designed very well.** Many of the operators and structures related to C have been adopted by other programming languages later.

**C is an efficient language.** Programs written in C run fast due to the low level of the language. It can compete with Assembly languages in terms of efficiency.

**C is a natural language.** C is compatible with the computer system.

**C is a small language.** Writing a compiler for new systems is not difficult.

**C has a standard library.** This library provides a common interface for frequently performed operations.

**Learning C is more difficult** compared to other computer languages.

The C language is integrated with the UNIX operating system. Some tools used in the UNIX operating system assume that the user knows the C language.

Like all other computer programming languages, the C language also has its weak sides. Being a flexible and powerful language increases the programmer's risk of making errors. Mistakes made in code written in the C language can be more difficult to find than in other languages.