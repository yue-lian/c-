#include<iostream>
#include<vector>
#include<stdexcept>
#include<string>
//using namespace std;
#define TEMPLATE_CASE_


#ifdef TEMPLATE_CASE_7
/*
* 1. 智能指针模板
// 实现一个简化的共享指针模板 `SharedPtr`，要求：
// - 引用计数管理
// - 构造函数、拷贝构造函数、拷贝赋值运算符
// - 析构函数
// - 重载 * 和 -> 运算符
// - 成员函数 int use_count() const 返回引用计数

// 测试代码：
SharedPtr<string> ptr1(new string("Hello"));
SharedPtr<string> ptr2 = ptr1;
cout << ptr1.use_count() << endl;  // 输出 2
*/
template<typename T>
class SharedPtr
{
private:
    T* ptr;          // 指向实际对象的指针
    int* refCount;   // 指向引用计数的指针public:

public:
    //构造函数
    SharedPtr(T* p = nullptr):ptr(p) {
        if (p)
            refCount = new int(1);
        else
            refCount = new int(0);
    }

    //拷贝构造函数
    SharedPtr(const SharedPtr& other) :ptr(other.ptr),refCount(other.refCount){
        if (ptr)
        {
            ++(*refCount);
        }
    }

    //拷贝赋值运算符
    SharedPtr& operator=(const SharedPtr& other) {
        if (this == &other)
            return *this;
        release();
        ptr = other.ptr;
        refCount = other.refCount;
        if (ptr)
            ++(*refCount);
        return *this;
    }

    ~SharedPtr() {
        release();
    }

    //解引用
    T& operator*() const{
        return *ptr;
    }

    //成员访问
    T* operator->() const {
        return ptr;
    }

    // 返回引用计数
    int use_count() const {
        return *refCount;

    }

private:
    void release() {
        if (ptr)
        {
            --(*refCount);
            if (*refCount == 0)
            {
                delete ptr;
                delete refCount;
                ptr = nullptr;
                refCount = nullptr;
            }
        }
        else if (refCount)
        {
            delete refCount;
            refCount = nullptr;
        }
    }
};

int main()
{
    SharedPtr<std::string> ptr1(new std::string("Hello"));
    SharedPtr<std::string> ptr2 = ptr1;  // 拷贝构造，共享同一对象
    std::cout << *ptr1 << std::endl;          // 输出 Hello
    std::cout << ptr1.use_count() << std::endl; // 输出 2

    {
        SharedPtr<std::string> ptr3 = ptr2;
        std::cout << ptr1.use_count() << std::endl; // 输出 3
    } // ptr3 离开作用域，引用计数自动减1

    std::cout << ptr1.use_count() << std::endl; // 输出 2

    return 0;
}


#endif // TEMPLATE_CASE_7


#ifdef TEMPLATE_CASE_6
/*
* 模板元编程基础
// 实现一个编译时计算阶乘的模板
// 提示：使用模板特化来实现递归基线情况

// 测试代码：
cout << Factorial<5>::value << endl;  // 输出 120
cout << Factorial<0>::value << endl;  // 输出 1
*/
template<int N>
struct Factorial {
    static const int value = N * Factorial <N - 1 >::value;
};

//模版特化
template<>
struct Factorial<0> {
    static const int value = 1;
};


int main() {
    std::cout << Factorial<5>::value << std::endl;  // 输出 120
    std::cout << Factorial<0>::value << std::endl;  // 输出 1
    return 0;
}


#endif // TEMPLATE_CASE_6



#ifdef TEMPLATE_CASE_5
/*
// 实现一个函数模板 `findMax`，要求：
// 1. 接受一个vector容器
// 2. 返回容器中的最大元素
// 3. 使用 typename 和 const 引用
// 4. 如果容器为空，抛出异常

// 测试代码：
vector<int> v1 = {1, 5, 3, 9, 2};
vector<double> v2 = {1.1, 5.5, 3.3};
cout << findMax(v1) << endl;  // 输出 9
cout << findMax(v2) << endl;  // 输出 5.5
*/

template <typename T>
T findMax(const vector<T>& vec)
{
    if (vec.empty())
        throw runtime_error("vector is empty!");
    T maxValue = vec[0];
    for (const T& val:vec)
    {
        if (maxValue < val)
            maxValue = val;
    }
    return maxValue;
}

int main() {
    vector<int> v1 = { 1,5,3,9,2 };
    vector<double> v2 = { 1.1, 5.5, 3.3 };

    cout << findMax(v1) << endl;
    cout << findMax(v2) << endl;

}


#endif // TEMPLATE_CASE_5












#ifdef TEMPLATE_CASE_4

/*
* 容器类模板
// 实现一个简单的动态数组模板类 `DynamicArray`，要求：
// - 构造函数：DynamicArray(int size)
// - 拷贝构造函数和拷贝赋值运算符（深拷贝）
// - 析构函数（正确释放内存）
// - 重载 [] 运算符
// - 成员函数 int size() const
// - 成员函数 void resize(int newSize)

// 测试代码：
DynamicArray<int> arr(5);
arr[0] = 10;
DynamicArray<int> arr2 = arr;  // 深拷贝
*/
// 模板类定义
using namespace std;
template <typename T>
class DynamicArray
{
private:
    T* data;   // 动态分配的数组
    int length;

public:
    // 构造函数
    DynamicArray(int size)
        : length(size)
    {
        data = new T[size];  // 分配内存
    }

    // 拷贝构造函数（深拷贝）
    DynamicArray(const DynamicArray& other)
        : length(other.length)
    {
        data = new T[length];
        for (int i = 0; i < length; ++i)
        {
            data[i] = other.data[i];
        }
    }

    // 拷贝赋值运算符（深拷贝）
    DynamicArray& operator=(const DynamicArray& other)
    {
        if (this == &other) // 避免自赋值
            return *this;

        // 释放旧内存
        delete[] data;

        // 分配新空间并复制数据
        length = other.length;
        data = new T[length];
        for (int i = 0; i < length; ++i)
        {
            data[i] = other.data[i];
        }

        return *this;
    }

    // 析构函数
    ~DynamicArray()
    {
        delete[] data;
    }

    // 重载下标运算符
    T& operator[](int index)
    {
        return data[index];
    }

    const T& operator[](int index) const
    {
        return data[index];
    }

    // 获取当前大小
    int size() const
    {
        return length;
    }

    // 重新调整大小
    void resize(int newSize)
    {
        T* newData = new T[newSize];
        int copySize = (newSize < length) ? newSize : length;
        for (int i = 0; i < copySize; ++i)
        {
            newData[i] = data[i];
        }

        delete[] data;
        data = newData;
        length = newSize;
    }
};

// 测试代码
int main()
{
    DynamicArray<int> arr(5);
    arr[0] = 10;
    arr[1] = 20;

    cout << "arr[0] = " << arr[0] << endl;
    cout << "arr size = " << arr.size() << endl;

    DynamicArray<int> arr2 = arr; // 调用拷贝构造函数（深拷贝）
    arr2[0] = 99;

    cout << "arr[0] = " << arr[0] << ", arr2[0] = " << arr2[0] << endl;

    arr.resize(8);
    cout << "resized arr size = " << arr.size() << endl;

    return 0;
}
#endif // TEMPLATE_CASE_4









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
