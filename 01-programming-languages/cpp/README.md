# C++

C++ programming language notes, concepts, and examples.

## Resources

### Primary Resources
- **[LearnCpp.com](https://www.learncpp.com/)** - The main bible for C++ learning
- **YouTube Channels:**
  - [The Cherno](https://www.youtube.com/c/TheChernoProject) - General C++ tutorials
  - [Code Beauty](https://www.youtube.com/@CodeBeauty) - OOPS, threading, etc.
  - [CppCon "Back to Basics"](https://www.youtube.com/@CppCon) - Advanced concepts and internals

---

## The C++ Master Stack

### 1. The Primary Source (Text)
**Resource:** [LearnCpp.com](https://www.learncpp.com/)

**Status:** Mandatory. Do not skip.

**Coverage:**
- **Basics:** Chapters 1–10 (Types, Debugging, Flow Control)
- **Memory Depth:** Chapters 11–12 (Pointers, References, Arrays)
- **OOPS (Core):** Chapters 13–16 & 21–25 (Classes, Overloading, Inheritance, Virtual Functions)
- **Concurrency:** (Refer to CppCon below, as LearnCpp is lighter here)

**Instruction:** Read purely sequentially. Solve the "Quiz" at the end of every chapter.

### 2. The Internals & Concurrency (Video)
**Resource:** CppCon "Back to Basics" Playlist (YouTube)

**Status:** Mandatory for specific topics.

**Specific Videos to Watch:**
- Back to Basics: Concurrency (for your project requirements)
- Back to Basics: The Memory Model (crucial for Interviews)
- Back to Basics: Move Semantics (Part 1 & 2)
- Back to Basics: Pointers

### 3. The Professional Edge (Book)
**Resource:** Effective C++ (3rd Edition) by Scott Meyers

**Status:** Supplementary (Post-Basics)

**Usage:** Start this only after you finish Chapter 14 (Classes) in LearnCpp.

**Goal:** It teaches you why to write code a certain way (e.g., "Why use `const &` instead of pass-by-value?"). This is where interview questions come from.

---

## Study Plan

### Phase 1: The "Memory" Phase (Weeks 1-3)
**Goal:** Understand the machine. If you don't understand Stack vs. Heap and Pointers, you cannot do Systems Programming.

#### Week 1: The Basics & The Stack
**LearnCpp:**
- Scan Chapters 1-6 (Variables, Fundamental Types, Operators). Speed run this.
- Deep Read Chapter 7: Scope, Duration, and Linkage. (Crucial for static keyword understanding)

**Video (CppCon):** Watch "Back to Basics: The Memory Model" (First 30 mins)

**Checkpoint Task:**
- Write a code that prints the memory address (`&variable`) of a local variable vs. a global variable to see how far apart they are in RAM.

#### Week 2: Pointers & References (The Hardest Part)
**LearnCpp:**
- Chapter 11: Pointers (Read every single line. Do not skim)
- Chapter 12: Compound Types (References & Pointers)

**Video (CppCon):** Watch "Back to Basics: Pointers"

**Checkpoint Task:**
- Explain (to yourself) the difference between `const int* ptr`, `int* const ptr`, and `const int* const ptr`
- Write a function `swap(int* a, int* b)` using pointers and `swap(int& a, int& b)` using references

#### Week 3: Dynamic Memory & Arrays
**LearnCpp:**
- Chapter 16: Dynamic Arrays (`std::vector`)
- Chapter 25 (Partial): Smart Pointers (Introduction)

**Concept:** Understanding `new` vs `delete` vs `malloc` vs `free`

**Checkpoint Task:**
- Manually allocate an array of 100 ints using `new`, fill it, and delete it. Then do the same with `std::vector` to see how much easier it is.

---

### Phase 2: The "Object" Phase (Weeks 4-6)
**Goal:** Master OOPS. This is 60% of your Interviews.

#### Week 4: Class Fundamentals & Encapsulation
**LearnCpp:**
- Chapter 13: Basic Object-Oriented Programming
- Chapter 14: Introduction to Classes

**Effective C++ (Book):**
- Read Item 4 (Make sure objects are initialized)
- Read Item 5 (Know what functions C++ silently writes and calls)

**Checkpoint Task:**
- Create a class `String` that manages a `char*` buffer. Implement a Constructor and Destructor.

#### Week 5: The "Rule of 5" & Move Semantics (Advanced)
**LearnCpp:**
- Chapter 15: More on Classes (Move Semantics)

**Video (CppCon):** Watch "Back to Basics: Move Semantics" (Part 1)

**Why this matters:** This is the #1 "Advanced C++" interview topic.

**Checkpoint Task:**
- Update your `String` class. Add a "Copy Constructor" (Deep Copy) and a "Move Constructor" (Stealing the pointer).

#### Week 6: Inheritance & Polymorphism
**LearnCpp:**
- Chapter 24: Inheritance
- Chapter 25: Virtual Functions

**Concept:** vtable and vptr. You must understand how the compiler implements virtual functions internally.

**Checkpoint Task:**
- Create a base class `Shape` and derived classes `Circle` and `Square`. Store them all in a `vector<Shape*>` and call `draw()`.

---

### Phase 3: The "Systems" Phase (Weeks 7-10)
**Goal:** Concurrency and Templates. This is for your Core Project.

#### Week 7: Templates
**LearnCpp:**
- Chapter 26: Templates

**Video (CppCon):** "Back to Basics: Templates"

**Checkpoint Task:**
- Write a generic `Stack<T>` class that works for `int`, `double`, and `String`.

#### Week 8-9: Concurrency (Multithreading)
**LearnCpp:** (Not sufficient here)

**Video (CppCon):** "Back to Basics: Concurrency"

**Concepts:** `std::thread`, `std::mutex`, `std::lock_guard`, Deadlocks, Race Conditions

**Checkpoint Task:**
- **Project Starter:** Write a program where 2 threads try to increment a shared counter to 1,000,000. Observe the "Race Condition". Fix it using a mutex.

#### Week 10: The Core Project
**Project Idea:** Thread Pool Library or High-Performance Logger

We will discuss the exact specs of this project when you reach Week 9.

---

## How to Study (The Workflow)

1. **Read:** Open the LearnCpp Chapter. Read it.
2. **Code:** Do not copy-paste. Type the examples into your IDE.
3. **Break:** Try to "break" the code (e.g., delete a pointer twice, access out of bounds) to see what the error looks like.

---

## Notes

_Your learning notes will go here as you progress through the material._
