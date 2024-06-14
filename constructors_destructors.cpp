#include <memory>
#include <stdexcept>
#include <iostream>

class Dangerous {
public:
    Dangerous() {
        std::cout << "Dangerous()" << std::endl;
        throw std::runtime_error("Oh, fuck");
    }

    ~Dangerous() {
        std::cout << "~Dangerous()" << std::endl;
    }
};

class Random {
public:
    Random() {
        std::cout << "Random()" << std::endl;
    }

    ~Random() {
        std::cout << "~Random()" << std::endl;
    }
};

struct Deleter {
    void operator()(int*) const {
        std::cout << "~std::unique_ptr" << std::endl;
    }
};

class Animal {
public:
    Animal() {
        std::cout << "Animal()" << std::endl;
    }

    ~Animal() {
        std::cout << "~Animal()" << std::endl;
    }

private:
    Random a;
    Dangerous b;
};

int main() {
    Animal animal;
}