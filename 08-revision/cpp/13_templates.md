# 13. Templates

## Basics
Templates allow writing generic code that works with any type. Code is generated at Compile Time.
*   **Function Template**: `template <typename T> T add(T a, T b) { return a + b; }`
*   **Class Template**: `template <typename T> class Box { T value; };`
*   **Deduction (C++17)**: `pair p(1, 2.5);` (Deduces `<int, double>`) instead of `pair<int, double>`.

## Template Specialization
Customizing behavior for specific types.
1.  **Full Specialization**: Providing a distinct implementation for a specific type.
    *   `template <> class Box<int> { ... };`
2.  **Partial Specialization** (Classes only): Customizing for a subset of types (e.g., all pointers `T*`).
    *   `template <typename T> class Box<T*> { ... }; // Specialized for any pointer`

## Variadic Templates (C++11)
Templates that take an arbitrary number of arguments (`Args...`).
*   **Parameter Pack**: `typename... Args`
*   **Expansion**: `func(args...);`
*   **Fold Expressions (C++17)**: `(args + ...)` sums all arguments.
```cpp
template<typename... Args>
auto sum(Args... args) {
    return (args + ...); // Fold expression
}
/* 
   Note: For complex recursion, use 'if constexpr' to stop recursion:
   if constexpr (sizeof...(args) > 0) { ... }
*/
```

## SFINAE (Substitution Failure Is Not An Error)
*   **Concept**: If substituting a type into a template fails (e.g., type doesn't have `::iterator`), the compiler doesn't error out immediately; it just ignores that template overload and tries others.
*   **Enable If**: `std::enable_if` allows enabling functions only for certain types (e.g., `is_arithmetic`).
*   **Concepts (C++20)**: Replaced SFINAE with cleaner syntax. `template<typename T> requires std::integral<T>`.

<!--
    IMAGE GENERATION PROMPT:
    Diagram of Template Instantiation Process.
    Source: "template <typename T> class Box".
    Compiler Action: User writes "Box<int>", "Box<float>".
    Output: Compiler generates two distinct classes "Box_int" and "Box_float" in the object code.
    Visual style: Blueprint turning into multiple concrete instances.
-->
![Template Instantiation](./images/template_instantiation_process_1767341703467.png)

---

## Interview Questions

### Q1: Why must Template definitions be in Header files?
**Answer**:
*   The compiler needs the **full source code** to generate (instantiate) the specific version of the template for the type `T`.
*   If implementation is in `.cpp`, other files can't see it during their compilation, leading to "Undefined Reference" link errors.

### Q2: Difference between Function Overloading and Templates?
**Answer**:
*   **Overloading**: You write multiple functions with same name but different signatures. Code exists for all of them.
*   **Templates**: You write one pattern. Compiler generates only the functions you actually use (Instantiations).

### Q3: What is "Code Bloat" (Template Bloat)?
**Answer**:
*   Since templates generate a new copy of code for every unique type combination (`vector<int>`, `vector<float>`, `vector<double>`), the binary size can grow significantly compared to `void*` based generic programming (Java/C style).

### Q4: Can we having "Virtual Template" functions?
**Answer**:
*   **No**. A function cannot be both `virtual` and a `template`.
*   Reason: The V-Table size must be fixed at compile time. If a function were a template, it could have infinite instantiations, making a fixed-size V-Table impossible.
