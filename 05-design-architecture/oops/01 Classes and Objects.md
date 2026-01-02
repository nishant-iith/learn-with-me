# Classes and Objects

### What is OOPs?
Object Oriented Programming (OOP) is a software design method using objects and classes in programming. It aims to implement real world entities in the programming.

### What is a Class?
A class is a blueprint or template for creating objects. It defines the properties (attributes) and behaviors (methods) that the objects created from the class will have.

### What is an Object?
An object is an instance/example of a class. It is created based on the structure defined by the class and can hold specific values for the attributes defined in the class.

## Class and Object Example in C++

```cpp
#include <iostream>
using namespace std;

// Define a class named 'Car'
class Car {
  public:
    // Attributes
    string brand;
    string model;
    int year;

    // Method
    void displayInfo() {
        cout << "Brand: " << brand << ", Model: " << model << ", Year: " << year << endl;
    }
};

int main() {
    // Create an object of the class 'Car'
    Car myCar;

    // Set attributes
    myCar.brand = "Toyota";
    myCar.model = "Corolla";
    myCar.year = 2020;

    // Call method to display information
    myCar.displayInfo();

    return 0;
}
```

### Explanation:
1. We create a class using the `class` keyword followed by the class name `Car`. The class has three attributes: `brand`, `model`, and `year`, and one method `displayInfo()` that prints the car's information.
2. In the `main()` function, we create an object `myCar` of the class `Car`.
3. To access and modify the attributes of the object, we use the dot operator (`.`).


### Access Modifiers:
Access modifiers define the accessibility of class members (attributes and methods). The three main access modifiers in C++ are:
- `public`: Members are accessible from outside the class.
- `private`: Members are accessible only within the class.
- `protected`: Members are accessible within the class and by derived classes.


### Constructors:
- A constructor is a special member function that is automatically called when an object of the class is created. 
- It is used to initialize the object's attributes. 
- It has the same name as the class and does not have a return type.

#### For the above example, we can add a constructor as follows:

```cpp
// Constructor
Car(string b, string m, int y) {
    this->brand = b;
    this->model = m;
    this->year = y;
}
```
### Notes:
1. DRY : Classes and objects are fundamental concepts in OOP that help in organizing code and promoting reusability. 
2. constructors are useful for initializing objects with specific values when they are created.
3. when we write constructors, the default constructor is not created automatically (basically its overridden).
4. `this` pointer is used to refer to the current object within class methods.
5. We can create multiple constructors with different parameters (constructor overloading) to initialize objects in different ways.
6. Parameterized constructors allow us to pass values to the constructor when creating an object. Normally constructors do not take parameters (default constructors).
7. Copy constructors are special constructors used to create a new object as a copy of an existing object. (will see this later in detail).

