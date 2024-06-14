cmake_minimum_required(VERSION 3.28)
project(cpp_examples)

set(CMAKE_CXX_STANDARD 17)

add_executable(mutex_lock_order mutex_lock_order.cpp)

add_executable(condition_variable condition_variable.cpp)

add_executable(constructors_destructors constructors_destructors.cpp)

add_executable(virtual_methods virtual_methods.cpp)

add_executable(copy_move copy_move.cpp)

add_executable(smart_pointers smart_pointers.cpp)