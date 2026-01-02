# 15. Standards

## C++11 (Variable Templates, Move Semantics, Smart Pointers)
*   **Move Semantics**: `std::move`, R-value references (`&&`).
*   **Smart Pointers**: `unique_ptr`, `shared_ptr`, `weak_ptr`.
*   **Auto**: Type deduction (`auto x = 5;`).
*   **Lambda Expressions**: `[](){}`.
*   **Threading**: `std::thread`, `std::mutex`.

## C++14 (Binary Literals, Generic Lambdas)
*   **Generic Lambdas**: `[](auto x) { return x; }`.
*   **`make_unique`**: Added `std::make_unique<T>()`.
*   **Binary Literals**: `0b1010`.

## C++17 (Structured Bindings, `if constexpr`, Filesystem)
*   **Structured Bindings**: `auto [x, y] = pair;`.
*   **`if constexpr`**: Compile-time branching.
*   **`std::filesystem`**: Modern file operations.
*   **`std::optional`**, `std::variant`, `std::any`.
*   **Inline Variables**: `inline static int x = 5;` (ODR safe).

## C++20 (Concepts, Modules, Coroutines)
*   **Concepts**: Logic for Template Constraints (`template<typename T> requires Integral<T>`).
*   **Modules**: Replaces Headers (`import std.core;`). Faster builds, no macro leaks.
*   **Coroutines**: Functions that can suspend/resume (`co_await`, `co_return`).
*   **Spaceship Operator**: `<=>` (Three-way comparison).
*   **Ranges**: Functional pipeline (`v | views::filter | views::transform`).

## C++23 (Deducing `this`, `std::print`)
*   **Deducing `this`**: Explicit `this` parameter in member functions (`void func(this auto& self)`). Comparison operators simplified.
*   **`std::print`**: Faster, type-safe alternative to `cout`/`printf`.

<!--
    IMAGE GENERATION PROMPT:
    Timeline of C++ Standards Evolution.
    Axis: Time (1998 -> 2023).
    Milestones: C++98 (Legacy), C++11 (Modern Era Starts), C++14, C++17, C++20 (Big Leap: Modules/Concepts), C++23.
    Visual style: Road map or DNA double helix evolving.
-->
![C++ Standards Timeline](./images/cpp_standards_timeline_1767341810669.png)

---

## Interview Questions

### Q1: Difference between `const` and `constexpr`?
**Answer**:
*   **`const`**: Read-only. Can be initialized at runtime.
*   **`constexpr`**: Constant Expression. **Must** be computable at Compile Time. (Note: C++20 allows even more complex logic in constexpr).
*   **`consteval`** (C++20): Immediate function. **Must** produce a compile-time constant (error if runtime).

### Q2: What are C++20 Concepts?
**Answer**:
*   A way to constrain template types with readable names instead of obscure SFINAE or `enable_if`.
*   Example: `void sort(Sortable auto& c)` instead of `template<typename T, ...> void sort(T& c)`.
*   Improves error messages dramatically.

### Q3: Why use `std::filesystem` over legacy C-style `fopen`?
**Answer**:
*   **Portability**: Works across Windows/Linux paths (`\` vs `/`).
*   **Safety**: Type-safe paths (`std::filesystem::path`).
*   **Functionality**: Easy recursive directory iteration, file info query (`exists`, `is_directory`).

### Q4: Major advantage of Modules (C++20)?
**Answer**:
*   **Performance**: Modules are compiled once and imported (binary format), unlike headers which are text-pasted and recompiled in every CPP file.
*   **Isolation**: No macro pollution. Internal symbols stay internal.
