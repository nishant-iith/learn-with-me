# 6. Data Types & Enums

## Type System & Primitive Types
*   **Static Typing**: Types checked at compile time.
*   **Data Models**: The size of `int`, `long` varies by OS (ILP32 vs LP64). **Always use fixed-width types** for serialization/systems code.
    *   `<cstdint>`: `int8_t`, `uint16_t`, `int32_t`, `uint64_t`.
    *   **`std::byte` (C++17)**: Typesafe byte. Unlike `char`, it is not an integer and not a character. It's just bits. Use for raw memory.
*   **Floating Point**: `float`, `double`, `long double`. Be aware of precision errors (epsilon comparison).

## Enums vs Scoped Enums
*   **Classic Enum (`enum`)**:
    *   **Unscoped**: Names leak (pollution).
    *   **Implicit Conversion**: Converts to `int` implicitly (Safety risk).
    *   **Unknown Size**: Compiler decides size (int? char?). Hard to forward declare.
*   **Scoped Enum (`enum class`)** (C++11):
    *   **Strongly Scoped**: `Color::RED`.
    *   **No Implicit Conversion**: Must use `static_cast` to convert to int.
    *   **Specifiable Underlying Type**: `enum class Color : uint8_t { ... }` (Saves memory).

## Runtime Type Information (RTTI)
A mechanism to expose type information at runtime. Enabled by default (can be disabled via `-fno-rtti`).
*   `dynamic_cast<Type*>(ptr)`:
    *   Used for downcasting (Base -> Derived).
    *   **Requirement**: Polymorphic Base Class (must have at least one `virtual` function).
    *   **Cost**: Traverses inheritance tree at runtime (Slow).
*   `typeid(obj)`: Returns `std::type_info` (name, comparison).

## Const Qualifiers
*   `const`: "I promise not to change this". Read-only at runtime.
    *   `const int*` (Pointer to constant data) vs `int* const` (Constant pointer).
*   `constexpr` (C++11/14/17): **Evaluation at Compile Time** is *possible*.
    *   Variables: Must be compile-time constants.
    *   Functions: Can run at compile-time *if* inputs are constants, otherwise runs at runtime.
*   `consteval` (C++20): **Evaluation at Compile Time** is *mandatory*.
    *   If it can't be computed at compile-time, it's a compiler error.

<!--
    IMAGE GENERATION PROMPT:
    A timeline diagram comparing "const", "constexpr", and "consteval".
    Axis: Time (Compilation Time -> Runtime).
    'consteval': Strictly in Compilation Time.
    'constexpr': Spans Compile to Runtime (Flexible).
    'const': Mostly Runtime (Read-only).
    Visual style: Timeline with distinct colored blocks for execution phases.
-->
![Const Qualifier Timeline](./images/constexpr_timeline_1767340434123.png)

---

## Interview Questions

### Q1: Why prefer `enum class` over `enum`?
**Answer**:
*   **Scope Safety**: No namespace pollution.
*   **Type Safety**: No accidental int conversion.
*   **Forward Declaration**: Since you can fix the underlying type (e.g., `: int`), headers can forward declare `enum class Foo;` without including the full definition, reducing compile dependencies.

### Q2: What is the cost of RTTI?
**Answer**:
*   **Memory**: Extra data in the Virtual Table (v-table) for type_info.
*   **Speed**: `dynamic_cast` performs a runtime lookup/traversal of the class hierarchy, which is significantly slower than `static_cast`.

### Q3: Explain `const int * const ptr`.
**Answer**:
*   Read backwards: "ptr is a **const pointer** to an **int** that is **const**."
*   You cannot change the pointer (address) -> `ptr = &y` // Error.
*   You cannot change the value pointed to -> `*ptr = 5` // Error.

### Q4: When would you use `consteval`?
**Answer**:
*   When you need to guarantee logic happens at compile time, such as compile-time string hashing or validating format strings in a zero-overhead logging library. It ensures no code is generated for runtime.

### Q5: What is `auto` vs `decltype`?
**Answer**:
*   `auto`: Deduces type from the **initializer** (strips top-level const/references).
*   `decltype(expr)`: Deduces **exact** type of the expression (preserves const/references). Used in generic programming/templates.
