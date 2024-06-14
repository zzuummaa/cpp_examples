#include <iostream>

class Animal {
public:
    Animal() {
    }

    Animal(const Animal& other) {
        std::cout << "Animal(const Animal&)" << std::endl;
    }

    Animal(Animal&& other) {
        std::cout << "Animal(Animal&&)" << std::endl;
    }

    Animal& operator=(const Animal& other) {
        std::cout << "operator=(const Animal&)" << std::endl;
        return *this;
    }

    Animal& operator=(Animal&& other) noexcept {
        std::cout << "operator=(Animal&&)" << std::endl;
        return *this;
    }
};

int main() {
    Animal a;

    Animal b = a; // Animal(const Animal&)
    Animal c = std::move(a); // Animal(Animal&&)

    b = c; // operator=(const Animal&)
    a = std::move(c); // operator=(Animal&&)
    return 0;
}