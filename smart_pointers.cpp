#include <iostream>
#include <memory>

class Base {
public:
    ~Base() {
        std::cout << "~Base()" << std::endl;
    }
};

class Derived : public Base {
public:
    ~Derived() {
        std::cout << "~Derived()" << std::endl;
    }
};

template<typename TFrom, typename TTo, typename TOriginDelete>
struct Delete : TOriginDelete {
    explicit Delete(TOriginDelete&& other) : TOriginDelete(std::forward<TOriginDelete>(other)) {}

    void operator()(TTo* p) {
        TOriginDelete::operator()(static_cast<TFrom*>(p));
    }
};

template<typename TTo, typename TFrom, typename TFromDelete>
auto unique_pointer_cast(std::unique_ptr<TFrom, TFromDelete>&& from) {
    using TToDelete = Delete<TFrom, TTo, TFromDelete>;
    return std::unique_ptr<TTo, TToDelete>(static_cast<TTo*>(from.release()), TToDelete(std::move(from.get_deleter())));
}

int main() {
    auto derived = std::make_unique<Derived>();

    auto base = unique_pointer_cast<Base>(std::move(derived));
    derived = unique_pointer_cast<Derived>(std::move(base));

    // auto base = std::unique_ptr<Base, decltype(derived)::deleter_type>(derived.release()); // not compilled
    // auto base = std::unique_ptr<Base>(derived.release()); // wrong destructor
}