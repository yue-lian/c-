#define THREAD_

#ifdef THREAD_DEMO


#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>
#include <atomic>
#include <string> // 添加此头文件以解决未定义标识符 "to_string" 的问题

using namespace std;

// 全局共享资源
mutex mtx;
condition_variable cv;
bool ready = false;
atomic<bool> stop_flag{ false };  // 原子变量控制线程停止

// 日志函数，带锁输出
void log_safe(const string& msg) {
    lock_guard<mutex> lock(mtx);
    cout << "[" << this_thread::get_id() << "] " << msg << endl;
}

// 任务1：后台计算线程
void compute_task(int id) {
    log_safe("Compute thread " + to_string(id) + " waiting for start signal...");
    unique_lock<mutex> lock(mtx);
    cv.wait(lock, [] { return ready; });  // 等待主线程发信号
    lock.unlock();

    log_safe("Compute thread " + to_string(id) + " started computing...");

    int result = 0;
    for (int i = 0; i < 5; ++i) {
        if (stop_flag) {
            log_safe("Compute thread " + to_string(id) + " stopped early.");
            return;
        }
        result += i * id;
        this_thread::sleep_for(chrono::milliseconds(200));
    }

    log_safe("Compute thread " + to_string(id) + " finished with result = " + to_string(result));
}

// 任务2：监控线程（检测停止信号）
void monitor_task() {
    while (!stop_flag) {
        this_thread::sleep_for(chrono::milliseconds(500));
        log_safe("Monitor: system running fine...");
    }
    log_safe("Monitor: stop flag detected, exiting monitor thread.");
}

int main() {
    log_safe("Main: launching demo...");

    // 启动监控线程
    thread monitor(monitor_task);

    // 启动多个计算线程
    vector<thread> workers;
    for (int i = 1; i <= 3; ++i) {
        workers.emplace_back(compute_task, i);
    }

    // 主线程准备信号
    this_thread::sleep_for(chrono::milliseconds(1000));
    {
        lock_guard<mutex> lock(mtx);
        ready = true;
    }
    log_safe("Main: notifying all compute threads...");
    cv.notify_all();

    // 模拟运行 3 秒后发出停止信号
    this_thread::sleep_for(chrono::seconds(3));
    stop_flag = true;
    log_safe("Main: sending stop flag...");

    // 等待所有线程结束
    for (auto& t : workers) t.join();
    monitor.join();

    log_safe("Main: all threads finished. Exiting program.");
    return 0;
}

#endif // THREAD_DEMO
