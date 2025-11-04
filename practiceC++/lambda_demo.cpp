#include<iostream>
#include<functional>
#define LAMBDA_CASE_

#ifdef LAMBDA_CASE_2
/*
* 题目 2：Lambda 回调函数实现
实现一个函数 process(int x, int y, std::function<int(int, int)> op)，
该函数调用 op(x, y) 并打印结果。

要求：
调用 process() 两次：
第一次传入一个 Lambda 实现加法
第二次传入一个 Lambda 实现乘
输出应分别为加法和乘法的结果。
*/

void process(int x, int y, std::function<int(int, int)> op) {
	std::cout << "result=" << op(x, y) << std::endl;
}

int main() {
	process(1, 2, [](int a, int b) {
		return (a + b);
		});
	process(2, 4, [](int a, int b) {
		return (a * b);
		});
}

#endif // !LAMBDA_CASE_2


#ifdef LAMBDA_CASE_1
/*
* 题目 1：Lambda 捕获机制对比

编写一个程序，完成以下要求：
定义一个 int counter = 0;
定义两个 Lambda：
inc_by_value：按值捕获 counter，并在内部执行 counter++
inc_by_ref：按引用捕获 counter，并在内部执行 counter++
分别调用各自的 Lambda 一次。
输出最终的 counter 值。
预测输出是什么？为什么？
*/
int main() {
	int counter = 0;
	auto inc_by_value = [=]() mutable {
		counter++;
		std::cout << "value counter：" << counter << std::endl;
		};
	
	auto inc_by_ref = [&]() {
		counter++;
		std::cout << "ref counter：" << counter << std::endl;
		};
	inc_by_value();//修改的是副本，不修改原counter
	std::cout << "counter：" << counter << std::endl;
	inc_by_ref();//修改的是引用，直接修改原counter
	std::cout << "final counter：" << counter << std::endl;


}


#endif // LAMBDA_CASE_1


