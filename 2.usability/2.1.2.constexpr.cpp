#include <iostream>

constexpr int NUM = 5;

int len_foo()
{
    int i = 2;
    return i;
}

constexpr int len_foo_constexpr()
{
    // c++11 中不能定义局部变量/循环/分支等，c++14开始可以了
    int i = 2; // c++11 warning: variable declaration in a constexpr function is a C++14 extension [-Wc++14-extensions]
    return i;
}

// c++11 中不能定义局部变量/循环/分支等，c++14开始可以了
constexpr int fibonacci0(const int n) {
    if(n == 1) return 1;
    if(n == 2) return 1;
    return fibonacci0(n-1) + fibonacci0(n-2);
}

constexpr int fibonacci(const int i)
{
    return i == 1 || i == 2 ? 1 : fibonacci(i - 1) + fibonacci(i - 2);
}

int main()
{
    int arr0[5];

    const int len = 5;
    int arr1[len]; // 非法，但能通过编译，因为编译器会优化一波

    int arr2[NUM];

    // ++++++++++++
    int arr3[len_foo()]; // 非法，但能通过编译，因为编译器会优化一波

    int arr4[len_foo_constexpr()];

    // ************
    int arr5[len_foo() + 1]; // 非法，但能通过编译，因为编译器会优化一波

    int arr6[len_foo_constexpr() + 1];

    // +++++++++++
    std::cout << fibonacci0(10) << std::endl;
    std::cout << fibonacci(10) << std::endl;

    return 0;
}

// 总的来说，
// const(常量) = 不会变化的变量 = 只读，可以用 const_cast() 改为 非const
// constexpr(常量表达式) = 一旦求出了结果，就再也不会变了 = 编译时就确定了值/表达式
