#include <iostream>
#include <type_traits>

void func(int a)
{
    std::cout << "func(int a) is called" << std::endl;
}

void func(int* a)
{
    std::cout << "func(int* a) is called" << std::endl;
}

// C: NULL = 0 or (void*)0
// C++1.0: NULL = 0
// C++2.0: NULL = 0 or nullptr

int main()
{
    if (std::is_same<decltype(NULL), decltype(0)>::value)
    {
        std::cout << "NULL == 0" << std::endl;
    }

    if (std::is_same<decltype(NULL), decltype((void*)0)>::value)
    {
        std::cout << "NULL == (void*)0" << std::endl;
    }

    if (std::is_same<decltype(NULL), decltype(nullptr)>::value)
    {
        std::cout << "NULL == nullptr" << std::endl;
    }

    if (std::is_same<decltype(nullptr), decltype(0)>::value)
    {
        std::cout << "nullptr == 0" << std::endl;
    }

    if (std::is_same<decltype(nullptr), decltype((void*)0)>::value)
    {
        std::cout << "nullptr == (void*)0" << std::endl;
    }

    func(0);
    // func(NULL);
    func(nullptr);

    return 0;
}