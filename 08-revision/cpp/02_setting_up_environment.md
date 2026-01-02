# 2. Setting up your Environment

## Installing C++
C++ code requires a **Compiler** to turn source code (`.cpp`) into an executable (`.exe` or binary).
*   **Windows**: MSVC (Visual Studio), MinGW (GCC for Windows).
*   **Linux**: GCC (`g++`) or Clang.
*   **Mac**: Clang (via Xcode Command Line Tools).

## Code Editors vs IDEs
*   **IDE (Integrated Development Environment)**: Comes with compiler, debugger, and build tools built-in.
    *   *Examples*: **Visual Studio** (Standard for Windows), **CLion** (JetBrains, Paid), **Xcode** (Mac).
*   **Code Editor**: Lightweight text editor; requires manual setup of compiler extensions.
    *   *Examples*: **VS Code** (Most popular, extensible), **Sublime Text**, **NeoVim**.

## Running your First Program

### Hello World Code
```cpp
#include <iostream> // Header for Input/Output

int main() {
    // std::cout prints to console
    std::cout << "Hello, World!" << std::endl; 
    return 0; // Exit code 0 means success
}
```

### Compilation Steps (Command Line)
1.  **Preprocessing**: Handles `#include` and macros.
2.  **Compilation**: Translates C++ to Assembly.
3.  **Assembly**: Translates Assembly to Machine Code (Object file `.o` / `.obj`).
4.  **Linking**: Combines object files and libraries into the final executable.

### Execution
```bash
g++ main.cpp -o main
./main
```

<!--
    IMAGE GENERATION PROMPT:
    A horizontal flowchart showing the C++ compilation pipeline: Source Code (.cpp) -> Preprocessor -> Compiler -> Assembler -> Linker -> Executable (.exe).
    Detailed and labeled clearly.
    Visual style: Modern, minimal, linear flow with arrows.
-->
![Compilation Pipeline](./images/cpp_compilation_pipeline_1767336999749.png)

---

## Interview Questions

### Q1: What does `#include <iostream>` do?
**Answer**:
*   It is a **Preprocessor Directive**.
*   It tells the preprocessor to copy the contents of the `iostream` header file (which contains input/output stream definitions like `std::cout`) into the current file *before* compilation begins.

### Q2: Why is `main` function returning an `int`?
**Answer**:
*   It returns an **Exit Status** to the Operating System.
*   `0` typically indicates successful execution.
*   Non-zero values (e.g., `-1`, `1`) indicate an error occurred.

> **Follow-up**: Can `main` be `void`?
> **Answer**: In standard C++, **NO**. `int main()` is the only standard-compliant signature. Some compilers allow `void main()`, but it is non-standard and considered bad practice.

### Q3: What is the difference between `std::endl` and `\n`?
**Answer**:
*   `\n`: Just inserts a newline character. Faster.
*   `std::endl`: Inserts a newline character **AND forces a flush** of the output buffer.
*   **Usage**: Use `\n` for performance; use `std::endl` only when you strictly need immediate output (e.g., debugging).
