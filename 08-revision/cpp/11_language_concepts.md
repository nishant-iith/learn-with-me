# 11. Language Concepts

## Value Categories: L-value vs R-value
*   **L-value (Left Value)**: Has an identity (name) and persists beyond the expression. You can take its address (`&x`).
    *   *Example*: `int x = 10;` (`x` is an l-value).
*   **R-value (Right Value)**: Temporary, ephemeral. No name, usually on the right side of assignment. Expires at end of statement.
    *   *Example*: `10`, `x + y`, `FuncReturningInt()`.
*   **X-value (Expiring Value)**: An L-value that is being cast to an R-value (e.g., `std::move(x)`), signaling it can be moved from.

### Move Semantics (C++11)
Optimizes performance by transferring resources instead of copying.
*   **`std::move(x)`**: Does **NOT** move anything. It strictly performs a `static_cast<T&&>(x)`, treating `x` as an R-value so the compiler selects the Move Constructor/Assignment.
*   **`std::forward<T>(x)`**: Used in templates (Perfect Forwarding) to cast `x` to R-value *only if* it was originally an R-value.

### Copy Elision (RVO/NRVO)
Compiler optimization to omit Copy/Move constructors.
*   **RVO (Return Value Optimization)**: Constructing the return value directly in the caller's stack frame. Guaranteed in C++17 (even if side effects exist!).
*   **NRVO (Named RVO)**: Same for named variables. Not guaranteed but widely supported.

<!--
    IMAGE GENERATION PROMPT:
    A conceptual diagram distinguishing L-value and R-value.
    L-value: A named container (Box labeled 'x') with a memory address.
    R-value: An ephemeral value (Cloud labeled '5' or 'x+y') floating without a permanent address, ready to be moved.
    Visual style: Abstract Computer Science concept art, distinct shapes for persistent vs temporary.
-->
![L-value vs R-value](./images/lvalue_vs_rvalue_diagram_1767341504515.png)

## Type Deduction (`auto` & `decltype`)
*   **`auto`**: Deduces type from initializer at compile time.
    *   `auto x = 5;` (int)
    *   `auto& y = x;` (int&)
    *   `const auto* z = &x;` (const int*)
    *   **Gotcha**: `auto` ignores top-level `const/volatile` and references unless specified.
*   **`decltype(expr)`**: Inspects declared type of an entity or expression. Used in template metaprogramming.

## Preprocessor Macros
Text substitution before compilation.
*   **Syntax**: `#define PI 3.14`
*   **Dangers**: No type safety, no scope (global), hard to debug.
*   **Modern Alternatives**:
    *   Constants: `constexpr double PI = 3.14;`
    *   Functions: `inline` or `template` functions.
    *   Conditionals: `if constexpr` (C++17).

## Type Casting
*   **`static_cast<T>`**: Compile-time check. Safe implicit conversions (float->int, Derived*->Base*).
*   **`dynamic_cast<T>`**: Runtime check (RTTI). Downcasting (Base*->Derived*). Returns `nullptr` (ptr) or throws `bad_cast` (ref) on failure. Slow.
*   **`const_cast<T>`**: Removes `const` qualifier. **Undefined Behavior** if you write to an object that was originally declared `const`.
*   **`reinterpret_cast<T>`**: Dangerous. Bitwise reinterpretation (e.g., `int*` to `float*`). Implementation defined.

## Undefined Behavior (UB)
Code where the standard imposes **no requirements**.
*   **Examples**: Dereferencing `nullptr`, Signed Integer Overflow, Accessing out-of-bounds, modifying a string literal.
*   **Consequence**: The compiler can delete your code, travel back in time, or crash. It assumes UB *never happens*.

## Argument Dependent Lookup (ADL) / Koenig Lookup
If you call a function `func(obj)` without a namespace, the compiler looks in the namespace of `obj`'s type.
```cpp
std::vector<int> v;
sort(v.begin(), v.end()); // Finds std::sort via ADL because iterators are defined in std::
```

---

## Interview Questions

### Q1: What happens if I move from an object and then use it?
**Answer**:
*   The object is in a **"valid but unspecified state"**.
*   You can assign a new value to it or destroy it.
*   You *cannot* rely on its previous value (it might be empty, null, or unchanged).

### Q2: Why does `std::move` take a Universal Reference (`T&&`)?
**Answer**:
*   Wait, `std::move` *doesn't* take a Universal Reference. It takes `T&&` where `T` is deduced, but logically it's meant to unconditionally cast to R-value reference.
*   Universal Reference (Forwarding Reference) applies to templates `template<typename T> void foo(T&& x)` where `T` is deduced type.

### Q3: Difference between `glvalue`, `prvalue`, `xvalue`?
**Answer**:
*   **glvalue** (Generalized L-value): Anything with an identity (lvalue + xvalue).
*   **prvalue** (Pure R-value): Temporary without identity (literals).
*   **xvalue** (Expiring L-value): Result of `std::move()`.
*   **rvalue**: prvalue + xvalue.

### Q4: Is `*(int*)nullptr` always a crash?
**Answer**:
*   No, it's **Undefined Behavior**.
*   It *often* crashes (SegFault), but the compiler allows itself to optimize based on the assumption it won't happen (e.g., removing the branch entirely).
