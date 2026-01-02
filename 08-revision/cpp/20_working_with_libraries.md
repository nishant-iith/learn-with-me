# 20. Working with Libraries

## Linking Context
*   **Header Files (`.h`)**: Promise to the compiler that a symbol *exists*. "There is a function `void foo();` somewhere."
*   **Library Files (`.lib`, `.a`, `.so`, `.dll`)**: The actual implementation.

## Library Types
1.  **Static Library (`.a` / `.lib`)**:
    *   Archive of object files.
    *   Linked at compile time.
    *   Code is copied into your executable.
2.  **Shared Library (`.so` / `.dll`)**:
    *   Linked at runtime.
    *   Executable only stores a "reference".
    *   OS loads the library into memory when the app starts.

## ABI (Application Binary Interface)
*   The binary agreement on how functions are called (register usage, stack alignment, name mangling).
*   **Compatibility**: Changing a class layout (adding a member) breaks ABI. Old apps linked against the old DLL will crash if they load the new DLL without recompilation.

## Dynamic Loading
Loading a library manually during execution (Plugins).
*   **Linux**: `dlopen()`, `dlsym()`.
    *   *Hack*: `LD_PRELOAD=/path/to/mylib.so ./app`. Forces loading your lib *first*. Used to hook/override system functions (e.g., overriding `malloc` for profiling).
*   **Windows**: `LoadLibrary()`, `GetProcAddress()`.

<!--
    IMAGE GENERATION PROMPT:
    Diagram of Dynamic Loading Mechanism.
    Process Memory. Main Exe triggers 'LoadLibrary("plugin.dll")'.
    OS maps 'plugin.dll' into the process address space.
    Function pointer returned to Main.
    Visual style: Memory map diagram with injection arrow.
-->

---

## Interview Questions

### Q1: What is "Dependency Hell"?
**Answer**:
*   When App depends on Lib A and Lib B.
*   Lib A needs Lib C (v1.0).
*   Lib B needs Lib C (v2.0).
*   You can't link two versions of Lib C into the same process (usually). Conflict!

### Q2: How does the OS find Shared Libraries?
**Answer**:
*   **Windows**: Checks Exe folder, System32, and `PATH`.
*   **Linux**: Checks `LD_LIBRARY_PATH`, `/usr/lib`, and cache in `/etc/ld.so.conf`.
*   **Common Error**: "Shared object file not found" means the OS loader can't find the `.so` file in those search paths.

### Q3: What is "Mangling"?
**Answer**:
*   C++ supports function overloading, C does not.
*   To support `foo(int)` and `foo(float)`, the compiler renames them in the object file to something like `_Z3fooi` and `_Z3foof`.
*   `extern "C"` disables mangling to allow linking with C code (or simple DLL exports).

### Q4: Why is ABI stability important for C++ Standard Library?
**Answer**:
*   So that code compiled with GCC 4.8 can run on a system with GCC 9's runtime libraries without crashing.
*   This constrains the Standard Committee (e.g., they couldn't just add a member to `std::string` easily to fix performance without breaking ABI).
