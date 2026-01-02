# Four Pillars of OOPS
Four Pillars or Software Design methods in Object-Oriented Programming are:

1. **Encapsulation** 
- Wrapping data and methods into a single unit (class) and restricting access to some components. (Properly using access modifiers and getter/setter methods)

---
---

2. **Inheritance**
- Mechanism by which one class can inherit properties (attributes ) and behaviors (methods) from another class. From base class to derived class.
- Ex: class Dog inherits from class Animal.
- Syntax in C++:
```cpp
class BaseClass {
  // base class members
};

class DerivedClass : access_modifier BaseClass {
  // derived class members
};
```
- Access modifiers can be `public`, `protected`, or `private` (default).
- Table : 

| Inheritance Type | Public Members | Protected Members | Private Members |
|------------------|----------------|-------------------|-----------------|
| Public           | Public         | Protected         | Inaccessible    |
| Protected        | Protected      | Protected         | Inaccessible    |
| Private          | Private        | Private           | Inaccessible    |


- A special type of inheritance is called **Multiple Inheritance**, where a derived class inherits from more than one base class.
Syntax in C++:

```cpp
class BaseClass1 {
  // base class 1 members
};
class BaseClass2 {
  // base class 2 members
};
class DerivedClass : access_modifier BaseClass1, access_modifier BaseClass2 {
  // derived class members
};
```

### Note :
1. Calling base class constructor in derived class constructor:

```cpp
DerivedClass(args) : BaseClass(args) {
  // derived class constructor body
}
```
2. From the object of the derived class, we can access the members of the base class (depending on access specifiers). And obviously, we can access the members of the derived class.
3. From the object of the base class, we cannot access the members of the derived class.
4. If a derived class does not have a constructor, the base class's default constructor is called automatically.
5. If a base class does not have a default constructor (i.e., it has parameterized constructors), then the derived class must explicitly call one of the base class's constructors in its initializer list.
Ex:

```cpp
class Base {
public:
    Base(int x) { /* ... */ }
};

class Derived : public Base {
public:
    Derived(int x, int y) : Base(x) { /* ... */ }
};
```

6. Object Slicing & Casting (Base vs Derived)

### **1. Derived Object $\rightarrow$ Base Object (Object Slicing)**

When you assign a Derived object to a Base object, C++ allows it. However, since the Base object is smaller (it doesn't have the Derived class's extra variables), the "Derived" parts are sliced off.

* **Status:** **Valid** (Implicit)
* **Result:** **Object Slicing** (Data loss).
* **Why?** The Base copy constructor `Base(const Base&)` is called. It only knows how to copy the Base parts.

**Code:**

```cpp
class Base { public: int b; };
class Derived : public Base { public: int d; };

int main() {
    Derived derivedObj;
    derivedObj.b = 10;
    derivedObj.d = 20;

    // VALID: No error, but 'd' is lost (Sliced)
    Base baseObj = derivedObj; 
    
    // baseObj.b is 10
    // baseObj.d does not exist!
}

```

### **2. Base Object $\rightarrow$ Derived Object**

You cannot assign a Base object to a Derived variable. The Derived class expects more data (its own variables) than the Base class can provide.

* **Status:** **Error** (Compiler Error).
* **Why?** The Derived object needs `d`, but `baseObj` only has `b`. The compiler doesn't know what to fill in `d`.

**Code:**

```cpp
Base baseObj;
Derived derivedObj = baseObj; // ERROR: No matching constructor

```

**Exception (How to make it work):**
You can make this work **only if** you explicitly define a constructor in the Derived class that takes a Base object.

```cpp
class Derived : public Base {
public:
    int d;
    // Custom Constructor to accept Base
    Derived(Base& b_obj) {
        b = b_obj.b;
        d = 0; // Default value
    }
};

Base baseObj;
Derived derivedObj = baseObj; // Valid now because of custom logic

```

---

### **3. Pointers & References (The "Real" Way)**

In LLD and OOP, we rarely assign objects directly (to avoid Slicing). We use **Pointers** or **References**.

#### **Case A: Derived* $\rightarrow$ Base* (Upcasting)**

* **Status:** **Valid** (Implicit).
* **Usage:** This is **Polymorphism**. You can point to a Derived object using a Base pointer.
* **Risk:** None.

```cpp
Derived d;
Base* bPtr = &d; // Valid // No slicing, points to Derived object only (just an address)

```

#### **Case B: Base* $\rightarrow$ Derived* (Downcasting)**

* **Status:** **Explicit Cast Required**.
* **Usage:** When you have a Base pointer, but you are *sure* it actually points to a Derived object.
* **Risk:** High. If the pointer actually points to a Base object, accessing Derived fields causes a crash.

```cpp
Base* bPtr = new Derived(); // Upcasting (Implicit)

// Derived* dPtr = bPtr; // ERROR: Compiler won't allow automatically

// VALID: explicit cast needed
Derived* dPtr = static_cast<Derived*>(bPtr); 

```

---

### **Summary Table**

| Source | Destination | Status | Result |
| --- | --- | --- | --- |
| **Derived Object** | **Base Object** | ✅ Valid | **Object Slicing** (Derived data lost). |
| **Base Object** | **Derived Object** | ❌ Error | Compiler doesn't know how to fill Derived fields. |
| **Derived Pointer** | **Base Pointer** | ✅ Valid | **Polymorphism** (Commonly used). |
| **Base Pointer** | **Derived Pointer** | ⚠️ Cast Needed | **Downcasting** (Risky, use `dynamic_cast` or `static_cast`). |

### **Common Doubts / Interview Questions**

**Q: Why doesn't `Base b = derived;` give a compiler error?**

* Because `Base` has a copy constructor `Base(const Base& other)`. Since `Derived` **IS-A** `Base`, the compiler accepts the `Derived` object as a valid argument for that constructor, copies the `Base` part, and ignores the rest.

**Q: Can I use `static_cast` to assign Base Object to Derived Object?**

* **No.** `static_cast` works on pointers/references or if conversion operators are defined. It cannot magically create data for a Derived object from a smaller Base object.

**Q: How do I avoid Object Slicing?**

* Always pass objects by **Reference** (`Base&`) or use **Pointers** (`Base*`) in your function arguments, not by Value.

```cpp
// BAD: Slicing happens
void func(Base b) { ... }

// GOOD: No Slicing (Polymorphism works)
void func(Base& b) { ... }

```
---
---

3. **Polymorphism**
- Ability of an object to take multiple forms. It allows methods to do different things based on the object it is acting upon, even if they share the same name.
- We can have two or more objects which inherit from same base class but have different implementations of same function.