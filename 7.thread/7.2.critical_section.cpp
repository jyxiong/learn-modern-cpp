#include <iostream>
#include <mutex>
#include <thread>

int v = 0;

void add0()
{
    for (int i = 0; i < 1000000; i++)
        v++;
}

void add1()
{
    // mutex 必须是全局的，站在更高一层上看待多个线程，这样才能控制线程不要冲突访问
    // 否则每个线程都实例化自己的mutex，看不到其他线程，不起作用
    static std::mutex mtx;
    mtx.lock();
    // **** critical section
    for (int i = 0; i < 1000000; i++)
        v++;
    // **** critical section
    mtx.unlock();
}

void add2()
{
    static std::mutex mtx;

    // 实例化lock，构造函数会调用 mutex.lock()
    std::lock_guard<std::mutex> lock(mtx);
    // **** critical section
    for (int i = 0; i < 1000000; i++)
        v++;
    // **** critical section
    // 析构lock，析构函数会调用 mutex.unlock()
}

void add3()
{
    static std::mutex mtx;

    std::unique_lock<std::mutex> lock(mtx);
    // **** critical section
    for (int i = 0; i < 1000000; i++)
        v++;
    // **** critical section

    lock.unlock();

    std::cout << "do something without mutex!" << std::endl;

    lock.lock();
    // **** critical section
    for (int i = 0; i < 1000000; i++)
        v++;
    // **** critical section
}

void apply_add(void (*p_add)())
{
    std::thread t1(*p_add), t2(*p_add);

    t1.join();
    t2.join();

    std::cout << "result of add function: " << v << std::endl;
}


int main()
{
    apply_add(add0);

    v = 0;

    apply_add(add1);

    v = 0;

    apply_add(add2);

    v = 0;

    apply_add(add3);

    return 0;
}