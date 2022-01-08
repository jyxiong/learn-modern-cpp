cmake_minimum_required(VERSION 3.16)

project(thread)

set(CMAKE_CXX_STANDARD 11)

add_executable(7.1.thread_basic 7.1.thread_basic.cpp)

add_executable(7.2.critical_section 7.2.critical_section.cpp)

add_executable(7.3.future 7.3.future.cpp)

add_executable(7.4.producer_customer 7.4.producer_customer.cpp)