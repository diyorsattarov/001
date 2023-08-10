#include "foo.h"

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
