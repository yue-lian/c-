#include<iostream>
#define TEMPLATE_CASE_3
/*
* 请实现一个函数模板 `swapValues`，用于交换两个同类型变量的值
// 测试代码：
int a = 5, b = 10;
swapValues(a, b);
// 现在 a 应该是 10, b 应该是 5

double x = 1.5, y = 2.5;
swapValues(x, y);
// 现在 x 应该是 2.5, y 应该是 1.5

*/

#ifdef TEMPLATE_CASE_1
template<typename T> 
void swapValues(T &a,T &b) {
    T temp;
    temp = a;
    a = b;
    b = temp;
};

int main() {
    //int a = 2;
    //int b = 4;
    //swapValues(a, b);
    //std::cout << "a=" << a << ",b=" << b << std::endl;

    double a = 1.5;
    double b = 2.5;
    swapValues<double>(a, b);

    std::cout << "a=" << a << ",b=" << b << std::endl;
}


#endif // TEMPLATE_CASE_1



#ifdef TEMPLATE_CASE_2
/*
// 请实现一个简单的类模板 `Box`，包含：
// - 一个私有成员 T content
// - 构造函数 Box(const T& value)
// - 成员函数 T getContent() const
// - 成员函数 void setContent(const T& value)

// 测试代码：
Box<int> intBox(42);
Box<string> stringBox("Hello");
*/

template<typename T> class Box {
private:
    T content;
public:
    Box(const T& value):content(value) {

    }
    T getContent() const {
        return content;
    }
    void setContent(const T& value) {
        content = value;
    }
};

int main() {
    Box<int> intBox(42);
    Box<std::string> stringBox("Hello");

    std::cout << "intBox = " << intBox.getContent() << std::endl;
    std::cout << "stringBox = " << stringBox.getContent() << std::endl;
    stringBox.setContent("World");
    std::cout << "stringBox = " << stringBox.getContent() << std::endl;

}

#endif // TEMPLATE_CASE_2


#ifdef TEMPLATE_CASE_3
/*
// 为下面的模板类编写一个针对 const char* 的特化版本
template<typename T>
class Printer {
public:
    void print(T value) {
        cout << "Value: " << value << endl;
    }
};

// 请编写特化版本，使得对于 const char* 类型，输出带引号的字符串
*/

template<typename T>
class Printer {
public:
    void print(T value) {
        std::cout << "Value: " << value << std::endl;
    }
};


// 针对 const char* 的特化版本
template<>
class Printer<const char*> {
public:
    void print(const char* value) {
        std::cout << "Value: \"" << value << "\"" << std::endl;
    }
};

int main() {
    Printer<const char*> demo;
    demo.print("hello");
}

#endif // TEMPLATE_CASE_3
