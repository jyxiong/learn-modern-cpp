#include <iostream>
#include <memory>
#include <utility>

// [] () mmutable throw() -> {}

void lambda_capture_value()
{
    int value = 1;

    // 此时已经捕获 value
    auto lambda = [value]()
    {
        int copy_value = value;
        return copy_value;
    };

    value = 100;

    auto copy_value = lambda();

    std::cout << "value capture copy value = " << copy_value << std::endl;
}

void lambda_capture_reference()
{
    int value = 1;

    // 此时隐式捕获 &value
    // [&] 引用捕获所有变量
    // [=] const值捕获所有变量, 不能修改, 可以使用 mutable [=]() mutable {}
    auto lambda = [&]()
    {
        int copy_value = value;
        return copy_value;
    };

    value = 100;

    auto copy_value = lambda();

    std::cout << "reference capture copy value = " << copy_value << std::endl;
}

void lambda_capture_expression()
{
    auto important = std::make_unique<int>(1);

    auto add = [v1 = 1, v2 = std::move(important)](int x, int y)
    {
        return v1 + (*v2) + x + y;
    };

    std::cout << "expression capture value = " << add(1, 1) << std::endl;
}

void lambda_generic()
{
    auto lambda = [](auto x, auto y)
    {
        return x + y;
    };

    std::cout << "generic lambda value = " << lambda(1, 1) << std::endl;
}

int main()
{
    lambda_capture_value();

    lambda_capture_reference();

    lambda_capture_expression();

    lambda_generic();

    return 0;
}