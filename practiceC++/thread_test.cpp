#include<iostream>
#include<thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <queue>

#define THREAD_CASE_10

#ifdef THREAD_CASE_1

#endif // THREAD_CASE_1

#ifdef THREAD_CASE_10
/*
* 题目 10：条件变量实现生产者-消费者模型
要求：

使用 std::queue<int> 实现经典生产者-消费者模型；
生产者放入数据（1~10）；
消费者读取并打印；
使用 std::condition_variable 保证同步。
*/

/*
和题目9差不多，就是生产之后需要线程通讯告知消费者
*/

//公共参数
std::queue<int> q;



//生产者
void producer() {

}

//消费者
void consumer() {

}

int main() {

}


#endif // THREAD_CASE_10


#ifdef THREAD_CASE_9
/*
* 题目 9：安全队列封装

封装一个线程安全的 SafeQueue<int>。
支持以下操作：
void push(int x)
bool pop(int &value)
确保多线程同时 push / pop 时不会出现竞态。
用两个线程测试：一个不断 push，另一个不断 pop。
*/

/*
分析：
1.首先保证push和pop要为原子操作，利用锁即可实现
2.输出用到的cout不是原子操作，既可以通过我下面用到的先存进去，再统一输出
3.也可以用其他方法，包装成一个新方法，方法里面给cout加个锁

*/
class SafeQuene {
private:
	std::queue<int> q;
	mutable std::mutex mtx;

public:
	void push(int x) {
		std::lock_guard<std::mutex> lock(mtx);
		q.push(x);
	}

	bool pop(int& value) {
		std::lock_guard<std::mutex> lock(mtx);
		if (q.empty())
		{
			return false;
		}
        value = q.front();
		q.pop();
		return true;
	}


};

int main() {
	SafeQuene sq;
	// 在生产消费完成后再输出结果
	std::vector<int> produced, consumed;
	std::thread producer([&]() {
		for (int i = 1; i < 6; ++i)
		{
			sq.push(i);
			produced.push_back(i);
		}
		});
	std::thread consumer([&]() {
		int val;
		for (int i = 0; i < 5;)
		{
			if (sq.pop(val))
			{
				consumed.push_back(val);
				++i;
			}
		}
		});

	producer.join();
	consumer.join();
	for (int i = 0; i < 5; i++)
	{
		std::cout << "producer:" << produced[i] << std::endl;
		std::cout << "consumer:" << consumed[i] << std::endl;
	}
}




#endif // THREAD_CASE_9



#ifdef THREAD_CASE_8
/*
* 题目 8：线程安全的日志输出
写一个函数 void log(string msg)，在多线程调用时不出现乱序输出；
启动多个线程随机打印日志；
日志应整齐输出，不交叉。
*/
std::mutex mtx;


void log(const std::string &msg) {

	std::lock_guard<std::mutex> lock(mtx);
	for (int i = 0; i < msg.length(); i++)
	{
		std::cout << msg << i << std::endl;
	}
}

void worker(const std::string &msg) {
	log(msg);
}

int main() {
	std::thread t1(worker, "hello");
	std::thread t2(worker, "world");
	t1.join();
	t2.join();

	return 0;
}


#endif // THREAD_CASE_8




#ifdef THREAD_CASE_7
/*
* 题目 7：两个线程交替打印 A / B

启动两个线程，一个打印 "A"，另一个打印 "B"；
输出顺序严格为 A B A B A B（共 10 次）。
*/
std::mutex mtx;
std::condition_variable cv;
bool printA_ready = true;

void printA() {
	for (int i = 0; i < 5; ++i)
	{
		std::unique_lock<std::mutex> lock(mtx);
		cv.wait(lock, []{return printA_ready; });
		std::cout << "A ";
		printA_ready = false;
		cv.notify_one();
	}
}
void printB() {
	for (int i = 0; i < 5; ++i)
	{
		std::unique_lock<std::mutex> lock(mtx);
		cv.wait(lock, [] {return !printA_ready; });
		std::cout << "B ";
		printA_ready = true;
		cv.notify_one();
	}
}

int main() {
	std::thread t1(printA);
	std::thread t2(printB);
	t1.join();
	t2.join();
	return 0;
}

#endif // THREAD_CASE_7


#ifdef THREAD_CASE_6
/*
* 题目 6：条件变量启动信号

子线程在启动时先进入等待状态；
主线程等待 1 秒后发出“开始”信号；
子线程收到信号后输出 "Thread started!"
*/
std::mutex mtx;
std::condition_variable cv;
bool ready = false;
int counter = 0;


void worker() {
	std::unique_lock<std::mutex> lock(mtx);
	cv.wait(lock, [] { return ready; });  // 等待主线程发信号
	std::cout << "Thread started" << std::endl;
}

int main() {
	std::thread t1(worker);
	std::cout << "The thread will start in one second" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	{
		std::lock_guard<std::mutex> lock(mtx);
		ready = true;
	}
	cv.notify_one();//唤醒子线程
	t1.join();
	return 0;
}


#endif // THREAD_CASE_6




#ifdef THREAD_CASE_5
/*
* 题目 5：使用 mutex 修复竞态条件
在题 4 的基础上添加 std::mutex。
使用 std::lock_guard<std::mutex> 保护 ++counter。
*/
int counter = 0;
std::mutex mtx;

void worker() {
	for (int i = 0; i < 100000; ++i)
	{
		std::lock_guard<std::mutex> lock(mtx);
		++counter;
	}
}

int main() {
	std::thread t1(worker);
	std::thread t2(worker);
	t1.join();
	t2.join();
	std::cout << "counter = " << counter << std::endl;
}


#endif // THREAD_CASE_5





#ifdef THREAD_CASE_4
/*题目 4：共享计数器（竞态条件）
* 
定义 int counter = 0;
启动两个线程，每个循环 100000 次执行 ++counter
打印最终结果。
*/
int counter = 0;

void worker() {
	for (int i = 0; i < 100000; ++i)
	{
		++counter;
	}
}

int main() {
	std::thread t1(worker);
	std::thread t2(worker);
	t1.join();
	t2.join();
	std::cout << "counter = " << counter << std::endl;
}

#endif // THREAD_CASE_4


#ifdef THREAD_CASE_3
/*
* 题目 3：Lambda 线程
使用 Lambda 启动一个线程，打印数字 1~5。
每次间隔 100ms。
主线程打印 "Done!"。
*/


int main() {
	
	std::thread t1([]() {
		for (int i = 1; i <= 5; ++i) {
			std::cout << i << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		});
	t1.join();
	std::cout << "Done!" << std::endl;
	return 0;
}

#endif // THREAD_CASE_3



#ifdef THREAD_CASE_2
/*
* 题目 2：带参数的线程
要求：

写一个函数 void greet(std::string name)，输出 "Hello, <name>!"。
使用 std::thread 启动此函数，并传入 "Alice"。
*/
void greet(std::string name) {
	std::cout << "Hello," << name << "!" << std::endl;
}

int main() {
	std::thread t1(greet,"Alice");
	t1.join();
	return 0;
}


#endif // THREAD_CASE_2


#ifdef THREAD_CASE_1
/*
* 题目 1：最简单的线程
要求：

启动一个线程打印 "Hello from thread"。
主线程打印 "Hello from main"。
确保两个输出都能执行。
提示： 使用 std::thread 启动线程，记得 join()。
*/

//创建新线程
void worker() {
	std::cout << "Hello from thread" << std::endl;
}

int main() {
	std::thread t1(worker);
	std::cout << "Hello from main" << std::endl;
	t1.join();
	return 0;
}



#endif // THREAD_CASE_1

