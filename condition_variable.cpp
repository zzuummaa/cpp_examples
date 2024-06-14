#include <condition_variable>
#include <thread>
#include <iostream>

// Возможно мьютекс не нужен

int main() {
    std::string str;
    std::mutex m;
    std::condition_variable cv;

    std::thread thread1{[&]() {
        {
            std::unique_lock l(m);
            str = "hello world!";
        }
        cv.notify_one();
    }};

    std::thread thread2{[&]() {
        std::unique_lock l(m);
        cv.wait(l, [&](){ return !str.empty(); });

        std::cout << str << std::endl;
    }};

    thread1.join();
    thread2.join();

    // Если бы cv.wait не атомарно добавлял cv на ожидание notify вместе с разлочиванием m:
    // thread2: cv.wait: m.unlock()
    // thread1: m.lock()
    // thread1: m.unlock()
    // thread1: cv.notify_one()
    // thread2: cv.wait: wait notify

    // Вариант 1
    // thread1: m.lock()
    // thread2: m.lock() - повис, т.к. m уже залочен
    // thread1: cv.notify_one()
    // thread1: m.unlock()
    // thread2: m.lock()
    // thread2: cv.wait() - !str.empty() истинно
    // thread2: cout
    // thread2:: m.unlock()
}