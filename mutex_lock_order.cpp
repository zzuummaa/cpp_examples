#include <algorithm>
#include <array>
#include <iostream>
#include <map>
#include <mutex>
#include <vector>
#include <thread>

struct Record {
    int val1;
    int val2;
    std::mutex m;

    Record(const int val1, const int val2) : val1(val1), val2(val2) {}
};

struct Table {
    std::map<std::string, std::unique_ptr<Record>> records;
};

int main() {
    Table table;
    table.records.emplace("a", std::make_unique<Record>(1,2));
    table.records.emplace("b", std::make_unique<Record>(2,3));

    std::thread thread1{[&]() {
        auto& r1 = table.records.at("a");
        auto& r2 = table.records.at("b");

        std::array<std::mutex&, 2> ms{ r1->m, r2->m };
        std::sort(
            std::begin(ms),
            std::end(ms),
            [](auto& lhs, auto& rhs){ return lhs.native_handle() < rhs.native_handle(); });

        std::for_each(std::begin(ms), std::end(ms), [](auto& m){ m.lock(); });

        r1->val1 = std::rand();
        r2->val1 = std::rand();

        std::for_each(std::begin(ms), std::end(ms), [](auto& m){ m.unlock(); });
    }};

    std::thread thread2{[&]() {
        auto& r1 = table.records.at("a");
        auto& r2 = table.records.at("b");

        std::scoped_lock l(r2->m, r1->m);

        r1->val1 = std::rand();
        r2->val1 = std::rand();
    }};

    thread1.join();
    thread2.join();

    return 0;
}
