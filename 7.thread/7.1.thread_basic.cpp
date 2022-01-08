#include <iostream>
#include <thread>

int main()
{
    std::string hello_thread = "Hello thread!";

    auto lambda_function = [&hello_thread](const std::string& hello_world){
        std::cout << hello_thread << std::endl;
        std::cout << hello_world << std::endl;
    };

    std::thread t(lambda_function, "Hello world!");
    t.join();
    return 0;
}