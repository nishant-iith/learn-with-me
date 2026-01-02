# How C++ works

C++ code example: 

```cpp
#include <iostream>
int main() {
    std::cout << "Hello, World!" << std::endl;
    std::cin.get();
    return 0;
}
```

Now here, we have some statement with `#` for example : the `#include <iostream>` is a preprocessor statement. 
This line tells the compiler to include the content of the iostream standard library.

So the preprocessor runs first, and it processes all the preprocessor directives (like `#include`, `#define`, etc.) in the code.

1. `include` directive (also called header): This tells the compiler to look for the specified file (in this case, `iostream`) and copy/paste its contents in the program before compilation.
2. `main()` function: This is the entry point of any C++ program. When the program is executed, the execution starts from the `main` function. The execution of the program is line by line.
    - you need not to write `return 0;` at the end of the `main` function in C++ as it is optional. If you omit it, the compiler automatically adds it for you. (This happens only with the `main` function, not with other functions.)
3. `std::cout`: This is the standard output stream in C++. It is used to print output to the console. The `std::` prefix indicates that `cout` is part of the standard namespace.
4. `<<` operator: This is an overloaded operator in C++ (operators are same as functions ex: print(parameters)). 