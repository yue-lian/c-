#include <iostream>
#include <memory>
#include <vector>
#define TEST_CASE_11

#ifdef TEST_CASE_
int main() {

}
#endif // TEST_CASE_


#ifdef TEST_CASE_10
/*
* 实战题 5：共享所有权的回调系统
题目：
设计一个带 std::enable_shared_from_this 的类 Listener，
它能在函数内部获取自身的 shared_ptr（而不是 this），
并将自己注册到一个全局管理器中。
*/

struct Manager {
    std::shared_ptr<class Listener> listener;
    void add(std::shared_ptr<class Listener> l) { listener = l; }
};

Manager globalManager;

struct Listener : std::enable_shared_from_this<Listener> {
    void registerSelf() {
        globalManager.add(shared_from_this()); // 从已有 shared_ptr 获取共享引用
    }
    ~Listener() { std::cout << "Listener destroyed\n"; }
};

int main() {
    auto ptr = std::make_shared<Listener>();
    ptr->registerSelf();
}
#endif // TEST_CASE_10

#ifdef TEST_CASE_9
/*
* 实战题 4：对象工厂 + 智能指针封装
题目：
实现一个 EntityFactory，可以动态创建 Entity 对象并返回 std::shared_ptr。
要求：

记录创建次数；

当所有实体都销毁后，打印 "All entities destroyed"。
*/
struct Entity
{
    int id;
    Entity(int id) :id(id) { std::cout << id << " is created" << std::endl; };
    ~Entity(){ std::cout << id << " is destroyed" << std::endl; }
};

struct EntityFactory
{
    std::vector<std::weak_ptr<Entity>> all;
    std::shared_ptr<Entity> create(int id) {
        auto temp = std::make_shared<Entity>(id);
        all.push_back(temp);
        return temp;
    }
    void check() {
        int createTime = 0;
        for (auto& i : all)
        {
            if (!i.expired()) createTime++;
        }
        if (createTime == 0)
        {
            std::cout << "All entities destoryed!" << std::endl;
            std::cout << "Creation times" << all.size() << std::endl;
        }
        else{
            std::cout << "Currently surviving:" <<createTime<< std::endl;
        }
       
    }
};

int main() {
    EntityFactory ef;
    {
        auto e1 = ef.create(1);
        auto e2 = ef.create(2);
        auto e3 = ef.create(3);
        ef.check();
    }
    auto e3 = ef.create(4);
    ef.check();
}
#endif // TEST_CASE_9

#ifdef TEST_CASE_8
/*
* 实战题 3：缓存系统（weak_ptr 检测失效）
题目：
设计一个简易的缓存类 Cache：

内部使用 std::weak_ptr 存储对象；
如果对象已销毁，自动重新创建并更新缓存。

*/
struct Data {
    int value;
    Data(int v) : value(v) {}
    ~Data() { std::cout << "Data destroyed\n"; }
};

struct Cache {
    std::weak_ptr<Data> cached;
    std::shared_ptr<Data> get() {
        auto sp = cached.lock();
        if (!sp)
        {
            std::cout << "cached missed, create cached!" << std::endl;
            sp = std::make_shared<Data>(100);
            cached = sp;
        }
        return sp;
    }
};

int main() {
    Cache cache;
    {
        auto d1 = cache.get();
        std::cout << d1->value << std::endl;
    }
    auto d2 = cache.get();
}

#endif // TEST_CASE_8


#ifdef TEST_CASE_7
/*
* 实战题 2：父子对象关系（循环引用问题）
模拟一个 Parent 和 Child 类。
每个 Parent 拥有一个 Child，而 Child 持有对 Parent 的引用。
要求：

防止循环引用；
程序结束时能正确打印析构顺序。

解决思路：由于shared_ptr存在两个强引用，导致两个 shared_ptr 互相持有。
、使用 weak_ptr 打破一边的“强引用”链。
*/
struct Child;

struct Parent {
    std::shared_ptr<Child> child;
    ~Parent() { std::cout << "Parent destroyed\n"; }
};

struct Child {
    std::weak_ptr<Parent> parent;
    ~Child() { std::cout << "Child destroyed\n"; }
};

int main() {
    auto p = std::make_shared<Parent>();
    auto c = std::make_shared<Child>();
    p->child = c;
    c->parent = p;
}

#endif // TEST_CASE_7


#ifdef TEST_CASE_6
/*
* 实战题 1：资源管理系统
创建一个 Texture 类，代表游戏中的贴图资源。
使用 std::shared_ptr 来管理贴图对象，并在贴图被销毁时打印日志 "Texture destroyed".
要求：

在函数中返回该对象；

验证对象离开作用域后自动释放。
*/
struct Texture {
    std::string name;
    Texture(std::string n) : name(n) {}
    ~Texture() { std::cout << name << " destroyed\n"; }
};

std::shared_ptr<Texture> loadTexture(const std::string& name) {
    std::shared_ptr<Texture> tex = std::make_shared<Texture>(name);
    std::cout << "加载资源:" << tex->name << std::endl;
    return tex;// 引用计数 +1
}

int main() {
    loadTexture("BrickWall");
}
#endif // TEST_CASE_6

#ifdef TEST_CASE_5
/*
* 例题 5（进阶）：解决循环引用问题
两个类互相引用，使用智能指针时要避免循环引用。
请修正以下代码，使得析构函数正常调用：
*/
struct B;

struct A {
    std::shared_ptr<B> b;
    ~A() { std::cout << "A destroyed\n"; }
};

struct B {
    std::weak_ptr<A> a; // 改成 weak_ptr
    ~B() { std::cout << "B destroyed\n"; }
};

int main() {
    auto a = std::make_shared<A>();
    auto b = std::make_shared<B>();
    a->b = b;
    b->a = a;
}
#endif // TEST_CASE_5


#ifdef TEST_CASE_4
/*
* 例题 4：weak_ptr 检测对象是否仍存在
创建一个 weak_ptr 观察一个 shared_ptr 对象。
当对象销毁后，weak_ptr 应能检测到对象已失效。
*/

int main() {
    std::weak_ptr<int> w;
    {
        std::shared_ptr<int> b = std::make_shared<int>(1);
        w = b;
        std::cout << "Alive? " << !w.expired() << std::endl;
    }
    std::cout << "Alive? " << !w.expired() << std::endl;

}
#endif // TEST_CASE_4


#ifdef TEST_CASE_3
/*
* 例题 3：shared_ptr 的引用计数
创建一个 shared_ptr，复制给两个变量，并打印引用计数。
*/
int main() {
    std::shared_ptr<int> sharePtr1 = std::make_shared<int>(2);
    auto a = sharePtr1;
    auto b = sharePtr1;
    std::cout << "sharePtr1引用计数：" << sharePtr1.use_count() << std::endl;
}
#endif // TEST_CASE_3


#ifdef TEST_CASE_2
/*
* 例题 2：unique_ptr 的所有权转移
创建一个 unique_ptr<int>，然后把它的所有权转移给另一个 unique_ptr。
要求：转移后原指针应为 nullptr。
*/

int main() {

    std::unique_ptr<int> ptr = std::make_unique<int>(10);
    std::unique_ptr<int> ptr1 = std::move(ptr);
    if (!ptr)
    {
        std::cout << "ptr已释放，当前为null" << std::endl;
    }
    else {
        std::cout << "ptr不为空" << std::endl;
    }
    std::cout << "ptr1 = " << *ptr1 << std::endl;

}
#endif

#ifdef TEST_CASE_1
/*
* 例题 1：unique_ptr 的基本用法
写一段代码，使用 std::unique_ptr 创建一个 Entity 对象，并在作用域结束时自动释放。
要求输出 "Entity destroyed"。
*/

struct Entity {
    ~Entity() { std::cout << "Entity destroyed\n"; }
};

int main() {
    // TODO: 在此处使用 unique_ptr 创建对象
    std::unique_ptr<Entity> uniquePtr = std::make_unique<Entity>();
}
#endif