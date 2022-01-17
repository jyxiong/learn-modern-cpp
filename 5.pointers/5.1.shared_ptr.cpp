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
    // 智能指针作为参数传递时，会发生拷贝
    std::cout << "++++++++++++++++++" << std::endl;

    std::shared_ptr<int> a = std::make_shared<int>(10);

    std::cout << "use count before foo: " << a.use_count() << std::endl; // 1

    foo(a);

    std::cout << "use count after foo: " << a.use_count() << std::endl; // 1

    std::cout << *a << std::endl; // 11

    // 智能指针的 拷贝赋值
    std::cout << "+++++++++++++++++++" << std::endl;

    std::shared_ptr<int> ptr1 = std::make_shared<int>(10);
    std::shared_ptr<int> ptr2 = ptr1;
    std::shared_ptr<int> ptr3 = ptr1;

    std::cout << ptr1.use_count() << std::endl;
    std::cout << ptr2.use_count() << std::endl;
    std::cout << ptr3.use_count() << std::endl;

    std::cout << "++++++++++ ptr1.get() +++++++++" << std::endl;

    // 获取原始指针 get()
    int* ptr0 = ptr1.get();
    // delete ptr0; // error: pointer being freed was not allocated

    std::cout << ptr1.use_count() << std::endl; // 3
    std::cout << ptr2.use_count() << std::endl; // 3
    std::cout << ptr3.use_count() << std::endl; // 3

    std::cout << "+++++++++ ptr1.reset() ++++++++++" << std::endl;

    // reset() 释放一个智能指针，如果引用计数为0，释放内存
    ptr1.reset();

    std::cout << ptr1.use_count() << std::endl; // 0
    std::cout << ptr2.use_count() << std::endl; // 2
    std::cout << ptr3.use_count() << std::endl; // 2

    // std::cout << *ptr1 << std::endl; // error: segmentation fault
    std::cout << *ptr2 << std::endl; // 10
    std::cout << *ptr3 << std::endl; // 10

    // 拷贝赋值时，引用计数：左边减一，右边加一
    std::cout << "++++++++++ ptr2.reset(new int(11)) +++++++++" << std::endl;
    std::cout << "++++++++++ ptr1 = ptr2 +++++++++" << std::endl;

    ptr2.reset(new int[2]);
    ptr1 = ptr2;

    std::cout << ptr1.use_count() << std::endl; // 2
    std::cout << ptr2.use_count() << std::endl; // 2
    std::cout << ptr3.use_count() << std::endl; // 1

    std::cout << *ptr1 << std::endl; // 11
    std::cout << *ptr2 << std::endl; // 11
    std::cout << *ptr3 << std::endl; // 10

    std::cout << "+++++++++++ ptr2 = ptr3 ++++++++" << std::endl;

    ptr2 = ptr3;

    std::cout << ptr1.use_count() << std::endl; // 0
    std::cout << ptr2.use_count() << std::endl; // 2
    std::cout << ptr3.use_count() << std::endl; // 2

    // std::cout << *ptr1 << std::endl; // error: segmentation fault
    std::cout << *ptr2 << std::endl; // 10
    std::cout << *ptr3 << std::endl; // 10

    // 数组的智能指针，以及 deleter
    // shared_ptr<int[]>  ==========  new int[]
    // 因为前后对应，默认的使用 default_delete<int[]>
    std::shared_ptr<int[]> x(new int[2]);

    // shared_ptr<int> ============ new int[] + default_delete
    // 前后不对应，调用传入的 default_delete<int[]>
    std::shared_ptr<int> y(new int[2], std::default_delete<int[]>());

    // shared_ptr<int> ============ new int[] + delete function
    // 前后不对应，调用传入的 lambda
    std::shared_ptr<int> z(new int[2], [](int* p) {
        std::cout << "call lambda deleter!" << std::endl;
        delete[] p;
    });

    return 0;
}