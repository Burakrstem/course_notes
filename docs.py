import os

# 1️⃣ C topics (English translated list)
topics = [
    "Programming and C",
    "Number Systems",
    "General Concepts and Terms",
    "Creating a C Program",
    "Data Types",
    "Declarations and Definitions",
    "Constants",
    "Operators",
    "Functions",
    "Scope and Lifetime",
    "Control Statements",
    "If Statement",
    "Function Declarations",
    "Type Conversions",
    "Loop Statements",
    "Preprocessor Directives - 1",
    "Switch Statement",
    "goto Statement",
    "Random Number Generation and Control Statements",
    "Arrays",
    "Character Arrays and Strings",
    "sizeof Operator",
    "Pointers",
    "Pointer Operators",
    "Standard Functions for String Operations",
    "Pointer Errors",
    "void Type Pointers",
    "Strings",
    "Pointer Arrays",
    "Pointers to Pointers",
    "Multidimensional Arrays",
    "exit, abort and atexit Functions",
    "Dynamic Memory Management",
    "Structures",
    "Structure Variables and Qualifiers",
    "Type Definitions and typedef",
    "Date and Time Standard Functions",
    "Unions",
    "Enumerations",
    "Bitwise Operators",
    "Bit Fields",
    "Command Line Arguments",
    "Files",
    "Macros",
    "Preprocessor Directives - 2",
    "Function Pointers",
    "Variable Argument Functions",
    "References"
]

# 2️⃣ Create folder if not exists
c_dir = "docs/c"
os.makedirs(c_dir, exist_ok=True)

# 3️⃣ Create markdown files
for i, topic in enumerate(topics, start=1):
    filename = f"{i}_{topic.lower().replace(' ', '_').replace(',', '').replace('-', '').replace('/', '_')}.md"
    filepath = os.path.join(c_dir, filename)
    with open(filepath, "w") as f:
        f.write("# 🧠 C Programming Basics\n")
    print(f"Created: {filepath}")

# 4️⃣ Create mkdocs_c.yml
with open("mkdocs_c.yml", "w") as f:
    f.write("nav:\n")
    f.write("  - C Language:\n")
    for i, topic in enumerate(topics, start=1):
        filename = f"{i}_{topic.lower().replace(' ', '_').replace(',', '').replace('-', '').replace('/', '_')}.md"
        f.write(f"      - {topic}: c/{filename}\n")

print("\n✅ All markdown files and mkdocs_c.yml have been created successfully!")
