#include <iostream>
#include <string>

class Foo {
private:
    int value;
    std::string name;

public:
    // Constructor
    Foo(int val, const std::string& n) : value(val), name(n) {
        std::cout << "Constructor called for " << name << std::endl;
    }

    // Destructor
    ~Foo() {
        std::cout << "Destructor called for " << name << std::endl;
    }

    // Copy Constructor
    Foo(const Foo& other) : value(other.value), name("Copy of " + other.name) {
        std::cout << "Copy constructor called for " << name << std::endl;
    }

    // Copy Assignment Operator
    Foo& operator=(const Foo& other) {
        value = other.value;
        name = "Copy of " + other.name;
        std::cout << "Copy assignment operator called for " << name << std::endl;
        return *this;
    }

    // Move Constructor
    Foo(Foo&& other) noexcept : value(other.value), name(std::move(other.name)) {
        std::cout << "Move constructor called for " << name << std::endl;
        other.value = 0;
    }

    // Move Assignment Operator
    Foo& operator=(Foo&& other) noexcept {
        value = other.value;
        name = std::move(other.name);
        std::cout << "Move assignment operator called for " << name << std::endl;
        other.value = 0;
        return *this;
    }

    // Member Function
    void print() const {
        std::cout << "Foo " << name << " has value: " << value << std::endl;
    }

    // Getter
    int getValue() const {
        return value;
    }

    // Setter
    void setValue(int newVal) {
        value = newVal;
    }
};

int main() {
    Foo foo1(42, "foo1");
    Foo foo2 = foo1;  // Copy constructor
    Foo foo3(100, "foo3");
    foo3 = foo1;      // Copy assignment operator
    Foo foo4 = std::move(foo3);  // Move constructor
    foo3 = std::move(foo2);      // Move assignment operator

    foo4.print();
    foo3.print();

    return 0;
}
