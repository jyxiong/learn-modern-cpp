#include <cassert>
#include <iostream>
#include <memory>

struct B {
    virtual ~B() = default;

    virtual void bar() { std::cout << "B::bar()" << std::endl; }
};

struct D : B {
    D() { std::cout << "D::D()" << std::endl; }
    ~D() { std::cout << "D::~D()" << std::endl; }

    void bar() { std::cout << "D::bar()" << std::endl; }
};

std::unique_ptr<D> pass_through(std::unique_ptr<D> d)
{
    d->bar();

    return d;
}

int main()
{
    std::cout << "11111111111111111111" << std::endl;

    std::unique_ptr<D> p = std::make_unique<D>();
    // 如果不用 move，参数传入是个拷贝，而 unique_ptr 是不能拷贝的
    // 为什么可以 return 呢？有两种方式
    // 1.先 construct 一个，再 move 过去
    // 2.move construct
    // 看起来 2 更靠谱一点
    // +++++++++++++++++++++++++
    // update:
    // 并不是 1 或 2
    // 这叫返回值优化 RVO: 编译器会返回对象直接构造到接收的地方
    // Named RVO: 具名的RVO, 进一步优化
    std::unique_ptr<D> q = pass_through(std::move(p));

    assert(!p);

    std::cout << "22222222222222222222" << std::endl;

    /*
    D::D()
    D::D()
    D::D()
    D::~D()
    D::~D()
    D::~D()
    */
    std::unique_ptr<D[]> a(new D[3]);

    return 0;
}