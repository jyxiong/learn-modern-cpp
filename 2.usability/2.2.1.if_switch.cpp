#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    // ********************
    // c++17 之前
    std::vector<int> vec = {1, 2, 3, 4};

    const std::vector<int>::iterator iter1 = std::find(vec.begin(), vec.end(), 2);
    if (iter1 != vec.end())
    {
        *iter1 = -2;
    }

    const std::vector<int>::iterator iter2 = std::find(vec.begin(), vec.end(), 4);
    if (iter2 != vec.end())
    {
        *iter2 = -4;
    }

    for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    // *******************
    // c++17 之后
    // 注意，c++17 之前，编译器可能会优化一波，只有警告
    if (const std::vector<int>::iterator iter3 = std::find(vec.begin(), vec.end(), 1);
        iter3 != vec.end())
    {
        *iter3 = -1;
    }

    for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    return 0;
}