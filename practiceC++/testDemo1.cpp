#include<iostream>
#define POINTER_CASE_

#ifdef POINTER_CASE_2
/*
* 题目 2：函数指针数组 + typedef
要求：
使用 typedef 定义函数指针类型 Operation

typedef int (*Operation)(int, int);

创建函数 add、sub、mul。
定义一个 Operation ops[3] = {add, sub, mul};
输入索引（0、1、2），输出相应运算结果。
*/
int add(int a, int b) {
	return a + b;
}
int sub(int a, int b) {
	return a - b;
}
int mul(int a, int b) {
	return a * b;
}

int main() {
	int a, b, index;
	typedef int (*Operation)(int, int);
	Operation op[3] = { add,sub,mul };
	std::cout << "请分别输入a和b的数值" << std::endl;
	std::cin >> a >> b;
	std::cout << "请输入算法索引（0-加法，1-减法，2-乘法）" << std::endl;
	std::cin >> index;
	switch (index)
	{
	case 0:
		std::cout << "a+b=" << op[0](a, b) << std::endl;
		break;
	case 1:
		std::cout << "a-b=" << op[1](a, b) << std::endl;
		break;
	case 2:
		std::cout << "a*b=" << op[2](a, b) << std::endl;
		break;
	default:
		std::cout << "请输入符合要求的算法索引！";
	}
	return 0;
}


#endif // POINTER_CASE_2



#ifdef POINTER_CASE_1
/*
* 题目 1：函数指针基础
编写一个程序：
定义两个函数：
int add(int a, int b) 返回两数之和
int mul(int a, int b) 返回两数之积
定义一个函数指针 int (*operation)(int, int)
让用户输入一个选项：1 表示加法，2 表示乘法
使用函数指针调用对应函数，输出结果。
*/
int add(int a, int b) {
	return a + b;
}
int mul(int a, int b) {
	return a * b;
}

int main() {
	int (*calculate[2])(int, int) = { add,mul };
	int a = 3;
	int b = 7;
	std::cout << "a+b=" << calculate[0](a,b) << "\na*b=" << calculate[1](a,b) << std::endl;
}


#endif // POINTER_CASE_1
