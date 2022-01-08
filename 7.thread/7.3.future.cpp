#include <iostream>     // std::cout
#include <future>       // std::packaged_task, std::future
#include <chrono>       // std::chrono::seconds
#include <thread>       // std::thread, std::this_thread::sleep_for

// count down taking a second for each value:
int countdown (int from, int to) {
    for (int i=from; i!=to; --i) {
        std::cout << i << " seconds in thread" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "Finished!" << std::endl;
    return from - to;
}

int main ()
{
    std::packaged_task<int(int,int)> task(countdown); // 设置 packaged_task
    std::future<int> ret = task.get_future(); // 获得与 packaged_task 共享状态相关联的 future 对象.

    // std::thread th(std::move(task), 10, 0);   //创建一个新线程完成计数任务.
    // th.join(); // 等待 th 线程构造时传入的方法执行完

    std::thread(std::move(task), 10, 0).detach(); // 创建一个新的线程并挂起
    // ret.wait(); // 设置屏障，阻塞并等待 future 完成

    // ********* do anything else

    // 如果 th.join() 放在后面
    // 打印结果会与 th 线程里的混在一起
    for (int i = 0; i < 10; i++)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << i << std::endl;
    }
    
    // ********* do anything else

    // th.join();
    ret.wait();

    std::cout << "The countdown lasted for " << ret.get() << " seconds." << std::endl;

    return 0;
}