#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>

int main()
{
    const int MAX_SIZE = 100;
    const int PRODUCER_NUM = 10;
    const int CUSTOMER_NUM = 10;

    std::queue<int> product_queue;
    std::mutex mtx;
    std::condition_variable con_var;

    auto producer = [&]()
    {
        // lock
        std::unique_lock<std::mutex> lock(mtx);

        // 当商品队列满的时候，producer等待customer消费一波
        while (product_queue.size() > MAX_SIZE)
        {
            std::cout << std::this_thread::get_id() << " queue is full, wait for customer!" << std::endl;
            con_var.wait(lock); // producer线程阻塞
        }

        // 生产
        int product = rand();
        product_queue.push(product);
        std::cout << std::this_thread::get_id() << " produce a number: " << product << std::endl;

        // 通知阻塞线程干活儿了
        con_var.notify_all();
    };
    
    auto customer = [&]()
    {
        // lock
        std::unique_lock<std::mutex> lock(mtx);

        // 当商品队列空的时候，customer等待producer生产一波
        while (product_queue.empty())
        {
            std::cout << std::this_thread::get_id() << " queue is empty, wait for producer!" << std::endl;
            con_var.wait(lock); // customer线程阻塞
        }

        // 消费
        int product = product_queue.front();
        product_queue.pop();
        std::cout << std::this_thread::get_id() << " custom a number: " << product << std::endl;

        // 通知阻塞线程干活儿啦
        con_var.notify_all();
    };
    
    std::vector<std::thread> thread_pool;

    for (int i = 0; i < PRODUCER_NUM; i++)
        thread_pool.push_back(std::thread(producer));

    for (int i = 0; i < CUSTOMER_NUM; i++)
        thread_pool.push_back(std::thread(customer));

    for (auto& thread : thread_pool)
        thread.join();

    return 0;
}