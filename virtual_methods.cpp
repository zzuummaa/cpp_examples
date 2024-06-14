#include <memory>
#include <string>
#include <vector>
#include <iostream>

// struct AnimalVTable {
// }

// struct CatVTable {
// }

// struct DogVTable {
// }

struct Animal {
    // AnimalVTable* _vtablePtr;

    virtual ~Animal() = default;
    virtual std::string say() {
        return "hello";
    }
};

struct Cat : Animal {
    // CatVTable* _vtablePtr;
    std::string say() override {
        return "Meau";
    }
};

struct Dog : Animal {
    // DogVTable* _vtablePtr;
    std::string say() override {
        return "Gav";
    }
};

int main() {
    std::vector<std::unique_ptr<Animal>> animals;
    animals.push_back(std::make_unique<Cat>());
    animals.push_back(std::make_unique<Dog>());

    for (auto& animal: animals) {
        std::cout << animal->say() << std::endl;
    }
}