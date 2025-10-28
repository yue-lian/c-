#include <iostream>
#include <memory>
#include <vector>
#define TEST_CASE_10

#ifdef TEST_CASE_
int main() {

}
#endif // TEST_CASE_


#ifdef TEST_CASE_10
/*
* ʵս�� 5����������Ȩ�Ļص�ϵͳ
��Ŀ��
���һ���� std::enable_shared_from_this ���� Listener��
�����ں����ڲ���ȡ����� shared_ptr�������� this����
�����Լ�ע�ᵽһ��ȫ�ֹ������С�
*/

struct Manager {
    std::shared_ptr<class Listener> listener;
    void add(std::shared_ptr<class Listener> l) { listener = l; }
};

Manager globalManager;

struct Listener : std::enable_shared_from_this<Listener> {
    void registerSelf() {
        globalManager.add(shared_from_this()); // ������ shared_ptr ��ȡ��������
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
* ʵս�� 4�����󹤳� + ����ָ���װ
��Ŀ��
ʵ��һ�� EntityFactory�����Զ�̬���� Entity ���󲢷��� std::shared_ptr��
Ҫ��

��¼����������

������ʵ�嶼���ٺ󣬴�ӡ "All entities destroyed"��
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
* ʵս�� 3������ϵͳ��weak_ptr ���ʧЧ��
��Ŀ��
���һ�����׵Ļ����� Cache��

�ڲ�ʹ�� std::weak_ptr �洢����
������������٣��Զ����´��������»��档

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
* ʵս�� 2�����Ӷ����ϵ��ѭ���������⣩
ģ��һ�� Parent �� Child �ࡣ
ÿ�� Parent ӵ��һ�� Child���� Child ���ж� Parent �����á�
Ҫ��

��ֹѭ�����ã�
�������ʱ����ȷ��ӡ����˳��

���˼·������shared_ptr��������ǿ���ã��������� shared_ptr ������С�
��ʹ�� weak_ptr ����һ�ߵġ�ǿ���á�����
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
* ʵս�� 1����Դ����ϵͳ
����һ�� Texture �࣬������Ϸ�е���ͼ��Դ��
ʹ�� std::shared_ptr ��������ͼ���󣬲�����ͼ������ʱ��ӡ��־ "Texture destroyed".
Ҫ��

�ں����з��ظö���

��֤�����뿪��������Զ��ͷš�
*/
struct Texture {
    std::string name;
    Texture(std::string n) : name(n) {}
    ~Texture() { std::cout << name << " destroyed\n"; }
};

std::shared_ptr<Texture> loadTexture(const std::string& name) {
    std::shared_ptr<Texture> tex = std::make_shared<Texture>(name);
    std::cout << "������Դ:" << tex->name << std::endl;
    return tex;// ���ü��� +1
}

int main() {
    loadTexture("BrickWall");
}
#endif // TEST_CASE_6

#ifdef TEST_CASE_5
/*
* ���� 5�����ף������ѭ����������
�����໥�����ã�ʹ������ָ��ʱҪ����ѭ�����á�
���������´��룬ʹ�����������������ã�
*/
struct B;

struct A {
    std::shared_ptr<B> b;
    ~A() { std::cout << "A destroyed\n"; }
};

struct B {
    std::weak_ptr<A> a; // �ĳ� weak_ptr
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
* ���� 4��weak_ptr �������Ƿ��Դ���
����һ�� weak_ptr �۲�һ�� shared_ptr ����
���������ٺ�weak_ptr Ӧ�ܼ�⵽������ʧЧ��
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
* ���� 3��shared_ptr �����ü���
����һ�� shared_ptr�����Ƹ���������������ӡ���ü�����
*/
int main() {
    std::shared_ptr<int> sharePtr1 = std::make_shared<int>(2);
    auto a = sharePtr1;
    auto b = sharePtr1;
    std::cout << "sharePtr1���ü�����" << sharePtr1.use_count() << std::endl;
}
#endif // TEST_CASE_3


#ifdef TEST_CASE_2
/*
* ���� 2��unique_ptr ������Ȩת��
����һ�� unique_ptr<int>��Ȼ�����������Ȩת�Ƹ���һ�� unique_ptr��
Ҫ��ת�ƺ�ԭָ��ӦΪ nullptr��
*/

int main() {

    std::unique_ptr<int> ptr = std::make_unique<int>(10);
    std::unique_ptr<int> ptr1 = std::move(ptr);
    if (!ptr)
    {
        std::cout << "ptr���ͷţ���ǰΪnull" << std::endl;
    }
    else {
        std::cout << "ptr��Ϊ��" << std::endl;
    }
    std::cout << "ptr1 = " << *ptr1 << std::endl;

}
#endif

#ifdef TEST_CASE_1
/*
* ���� 1��unique_ptr �Ļ����÷�
дһ�δ��룬ʹ�� std::unique_ptr ����һ�� Entity ���󣬲������������ʱ�Զ��ͷš�
Ҫ����� "Entity destroyed"��
*/

struct Entity {
    ~Entity() { std::cout << "Entity destroyed\n"; }
};

int main() {
    // TODO: �ڴ˴�ʹ�� unique_ptr ��������
    std::unique_ptr<Entity> uniquePtr = std::make_unique<Entity>();
}
#endif