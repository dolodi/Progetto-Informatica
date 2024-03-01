#include <iostream>

// Example function
void sayHello() {
    std::cout << "Hello, world!" << std::endl;
}

// Example class
class MyClass {
public:
    void printMessage() {
        std::cout << "This is MyClass." << std::endl;
    }
};

int main() {
    sayHello();

    MyClass myObject;
    myObject.printMessage();

    return 0;
}