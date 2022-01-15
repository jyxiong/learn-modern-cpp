#include <memory>
#include <iostream>

void foo(std::shared_ptr<int> a)
{
    // 临时变量拷贝了一份智能指针
    std::cout << "use count in foo: " << a.use_count() << std::endl; // 2

    ++(*a);
    // 销毁智能指针
}

int main()
{
    std::shared_ptr<int> a = std::make_shared<int>(10);

    std::cout << "use count before foo: " << a.use_count() << std::endl; // 1

    foo(a);

    std::cout << "use count after foo: " << a.use_count() << std::endl; // 1

    std::cout << *a << std::endl; // 11

    std::cout << "+++++++++++++++++++" << std::endl;

    std::shared_ptr<int> ptr1 = std::make_shared<int>(10);
    std::shared_ptr<int> ptr2 = ptr1;
    std::shared_ptr<int> ptr3 = ptr1;

    std::cout << ptr1.use_count() << std::endl;
    std::cout << ptr2.use_count() << std::endl;
    std::cout << ptr3.use_count() << std::endl;

    std::cout << "+++++++++++++++++++" << std::endl;

    // 获取原始指针
    int* ptr0 = ptr1.get();
    // delete ptr0; // error: pointer being freed was not allocated

    std::cout << ptr1.use_count() << std::endl; // 3
    std::cout << ptr2.use_count() << std::endl; // 3
    std::cout << ptr3.use_count() << std::endl; // 3

    std::cout << "+++++++++++++++++++" << std::endl;

    // reset() 释放一个智能指针，如果引用计数为0，释放内存
    ptr1.reset();

    std::cout << ptr1.use_count() << std::endl; // 0
    std::cout << ptr2.use_count() << std::endl; // 1
    std::cout << ptr3.use_count() << std::endl; // 1

    // std::cout << *ptr1 << std::endl; // error: segmentation fault
    std::cout << *ptr2 << std::endl; // 11
    std::cout << *ptr3 << std::endl; // 10

    std::cout << "+++++++++++++++++++" << std::endl;

    ptr2.reset(new int(11));

    std::cout << ptr1.use_count() << std::endl; // 0
    std::cout << ptr2.use_count() << std::endl; // 2
    std::cout << ptr3.use_count() << std::endl; // 2

    // std::cout << *ptr1 << std::endl; // error: segmentation fault
    std::cout << *ptr2 << std::endl; // 10
    std::cout << *ptr3 << std::endl; // 10

    return 0;
}