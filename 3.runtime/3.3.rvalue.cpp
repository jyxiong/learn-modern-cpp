#include <utility>
#include <iostream>

//// C++14 及以上:
//void f(auto&& t) {
//  // ...
//}

 // C++11 及以上:
 template <typename T>
 void f(T&& t) {
   // ...
   std::cout << "++++++++" << std::endl;
 }

int main()
{
    int x = 0;
    f(0); // T 是 int 类型的右值, 推断为 f(int &&) => f(int&&)
    f(x); // T 是 int& 类型的左值, 推断为 f(int& &&) => f(int&)

    int& y = x;
    f(y); // T 是 int& 类型的左值, 推断为 f(int& &&) => f(int&)

    int&& z = 0; // NOTE: `z` 是 `int&&` 类型的左值.
    f(z); // T 是 int& 类型的左值, 推断为 f(int& &&) => f(int&)
    f(std::move(z)); // T 是 int 类型的右值, 推断为 f(int &&) => f(int&&)

    return 0;
}