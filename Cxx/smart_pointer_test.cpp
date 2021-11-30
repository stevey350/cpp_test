/**
 * @file smart_pointer_test.cpp
 * @brief  shared_ptr的使用和陷阱: https://blog.csdn.net/qq_33266987/article/details/78784852
 *         unique_ptr的使用和陷阱: https://blog.csdn.net/qq_33266987/article/details/78784286#comments_18669844
 * @author sj.su (sj.su@tungthih.com.cn)
 * @version 1.0
 * @date 2021-11-18
 * 
 * @copyright Copyright (c) 2021 Xiamen Tung Thih Electron CO.,LTD
 * 
 * @par History:
 * <table>
 * <tr>
 *     <th>Date
 *     <th>Version
 *     <th>Author
 *     <th>Description
 * </tr>
 * <tr>
 *     <th>2021-11-18
 *     <th>v0.0.1
 *     <th>sj.su
 *     <th>原型开发
 * </tr>
 * </table>
 */
#include <iostream>
#include <memory>

using namespace std;


void shared_ptr_test1(void)
{
    // 1-shared_ptr创建
    shared_ptr<int> p = make_shared<int>(100); // make_shared<int>分配一块int类型大小的内存，并值初始化为100,
                                                // 返回值是shared_ptr类型，因此可以直接赋值给sp
    // shared_ptr<int> sp1 = new int(100);      // 错误！ 不会进行隐式转换，类型不符合
    shared_ptr<int> q(new int(100000));       // 正确，直接初始化调用构造函数

    // 2-shared_ptr操作
    p.get();        // 返回p保存的指针

    swap(p, q);      // 交换p、q中保存的指针

    shared_ptr<int> sp(q);     // sp是q的拷贝，它们指向同一块内存，互相关联

    p = q;          // 用q为p赋值，之后p、q指向同一块内存，q引用计数+1，p（原来内存空间的）引用计数-1

    p.use_count();  // 返回与p共享对象的智能指针数量

    // shared_ptr<T> p(q, d);   // q是一个可以转换为T*的指针，d是一个可调用对象（作为删除器），p接管q所指对象的所有权，用删除器d代替delete释放内存

    p.reset();      // 将p重置为空指针

    // p.reset(q);     // 将p重置为p（的值）

    // p.reset(p, d);  // 将p重置为p（的值）并使用d作为删除器
}

/**
 * @brief shared_ptr的关联与独立
 */
void shared_ptr_test2(void)
{
    shared_ptr<int> sp1(new int(10));
    shared_ptr<int> sp2(sp1), sp3;
    sp3 = sp1;

    // 一个典型的错误用法
    shared_ptr<int> sp4(sp1.get()); 
    cout << sp1.use_count() << " " << sp2.use_count() << " " 
         << sp3.use_count() << " " << sp4.use_count() << endl;      // 输出 3 3 3 1
    // sp1,sp2,sp3是相互关联的共享指针，共同控制所指内存的生存期，sp4虽然指向同样的内存，却是与sp1,sp2,sp3独立的，sp4按自己的引用计数来关联内存的释放。
    // 该函数执行完，会报错：free(): double free detected in tcache 2   Aborted (core dumped)
    // 结论：只有用一个shared_ptr为另一个shared_ptr赋值时，才将这连个共享指针关联起来，直接使用地址值会导致各个shared_ptr独立。
}

/**
 * @brief 向shared_ptr传递删除器
 * 问题来源：用智能指针管理非new的对象，或者是没有析构函数的类，
 * 由于shared_ptr默认使用delete来释放内存并执行析构函数，对于以上的两种情况是不适用的，所以我们要传递特别的删除器
 */
struct MyStruct {                   // 没有析构函数的类
    int *p;
    MyStruct():p(new int(10)) { }   // 构造函数中申请了一块内存, 用裸指针管理，不用时需要手动释放
};
void shared_ptr_test3(void)
{
    MyStruct st;    // st是局部的对象，存放在栈区, 并非由new申请，不可用delete释放内存
    //一个作用域
    {
        shared_ptr<MyStruct> sp(&st, [](MyStruct *ptr) {
            delete(ptr->p);
            ptr->p = nullptr;
            cout << "destructed." << endl;
        });
        cout << "sp construct complete" << endl;
    }
    // 离开作用域，调用传递的删除器释放sp所指的内存空间
    cout << "sp deconstruct complete" << endl;

    // 首先不可以用delete来释放局部对象，然后MyStruct也没有析构函数来释放申请的空间，所以向管理它的shared_ptr传递一个删除器来做这两件事
}

/**
 * @brief shared_ptr的陷阱
 */
void shared_ptr_test4(void)
{
    // 错误场景1
    int *x(new int(10));
    shared_ptr<int> p1(x);
    // shared_ptr<int> p2(x);      // 如果放开注释，会报错free(): double free detected in tcache 2
    //虽然p1、p2都指向x所指的内存，但他们是独立的，
    //会在其他shared_ptr还在使用内存的情况下就释放掉内存
    //失去了设计共享指针的意义
    //同时，使用裸指针x本身也是很危险的，x随时可能变成空悬指针而无从知晓

    // 错误场景2
    shared_ptr<int> sp1(new int(10));
    shared_ptr<int> sp2(sp1.get()),sp3;     // sp2与sp1独立
    sp3.reset(sp1.get());                   // sp3与sp1独立
    // 总结：不要用p.get()的返回值为shared_ptr赋值，
    //      p.get()的返回值就相当于一个裸指针的值
}



/***********************unique_ptr******************/
/**
 * @brief 
 * 1. 与shared_ptr不同，unique_ptr没有定义类似make_shared的操作，因此只可以使用new来分配内存
 * 2. 与shared_ptr不同，unique_ptr拥有它所指向的对象，在某一时刻，只能有一个unique_ptr指向特定的对象。
 *    当unique_ptr被销毁时，它所指向的对象也会被销毁。因此不允许多个unique_ptr指向同一个对象，所以不允许拷贝与赋值。
 */
struct UniqueTest {
    UniqueTest() {cout << "UniqueTest construct" << endl; }
    ~UniqueTest() {cout << "UniqueTest deconstruct" << endl; }
};
void unique_ptr_test1(void)
{
    // 由于unique_ptr不可拷贝和赋值，初始化unique_ptr必须使用直接初始化的方式
    unique_ptr<int> up1(new int());    //okay,直接初始化
    // unique_ptr<int> up2 = new int();   //error! 构造函数是explicit
    // unique_ptr<int> up3(up1);          //error! 不允许拷贝

    unique_ptr<UniqueTest> up(new UniqueTest());
    // up = nullptr;       // 释放up指向的对象(会调用析构函数)，将up置为空
    // up.release();       // up放弃对它所指对象的控制权，并返回保存的指针，将up置为空，不会释放内存(不会调用析构函数)
    up.reset();             // 参数可以为:空、内置指针，先将up所指对象释放(会调用析构函数)，然后重置up的值
    cout << "Hello" << endl;
}

/**
 * @brief 传递unique_ptr参数和返回unique_ptr
 * 不能拷贝unique_ptr的规则有一个例外：我们可以拷贝或赋值一个将要被销毁的unique_ptr （C++ Primer 5th p418）
 */
unique_ptr<int> func1(int a) {  // 从函数返回一个unique_ptr
    return unique_ptr<int> (new int(a));
}
unique_ptr<int> func2(int a) {  // 返回一个局部对象的拷贝
    unique_ptr<int> up(new int(a));
    return up;
}
void func3(unique_ptr<int> &up) {
    cout << "func3 *up = " << *up << endl;
}
unique_ptr<int> func4(unique_ptr<int> up) {
    cout << "func4 *up = " << *up << endl;
    return up;
}

void unique_ptr_test2(void)
{
    // 可以拷贝或赋值一个将要被销毁的unique_ptr
    unique_ptr<int> up1 = func1(10);
    unique_ptr<int> up2 = func2(100);
    cout << "*up1 = " << *up1.get() << endl;      
    cout << "*up2 = " << *up2 << endl;      // unique_ptr有重载了operator*()

    // 传unique_ptr参数可以使用引用避免所有权的转移，或者暂时的移交所有权
    func3(up1);      // 传引用，不拷贝，不涉及所有权的转移
    unique_ptr<int> up = func4(unique_ptr<int> (up2.release())); // 暂时转移所有权，函数结束时返回拷贝，重新收回所有权
    //注意：如果不用up重新接受func2的返回值，这块内存就泄漏了
}


/**
 * @brief 类似shared_ptr，用unique_ptr管理非new对象、没有析构函数的类时，需要向unique_ptr传递一个删除器。
 *  unique_ptr<T,D> up(d) // 空的unique_ptr同上，接受一个D类型的删除器d，使用删除器d来释放内存
 */
void unique_ptr_test3(void)
{
    MyStruct st;    // st是局部的对象，存放在栈区, 并非由new申请，不可用delete释放内存
    //一个作用域  ?? 如何传递删除器的类型
    // {
    //     unique_ptr<MyStruct> up(&st, [](MyStruct *ptr) {
    //         delete(ptr->p);
    //         ptr->p = nullptr;
    //         cout << "destructed." << endl;
    //     });
    //     cout << "up construct complete" << endl;
    // }
    // 离开作用域，调用传递的删除器释放sp所指的内存空间
    cout << "up deconstruct complete" << endl;

    // 首先不可以用delete来释放局部对象，然后MyStruct也没有析构函数来释放申请的空间，所以向管理它的shared_ptr传递一个删除器来做这两件事
}

/**
 * @brief unique_ptr的陷阱
 *  1. 不要与裸指针混用
 *     unique_ptr不允许两个独占指针指向同一个对象，
 *     在没有裸指针的情况下，我们只能用release获取内存的地址，同时放弃对对象的所有权，这样就有效避免了多个独占指针同时指向一个对象;
 *     而使用裸指针就很容器打破这一点
 *  2. 记得使用u.release()的返回值, 
 *     在调用u.release()时是不会释放u所指的内存的，这时返回值就是对这块内存的唯一索引，
 *     如果没有使用这个返回值释放内存或是保存起来，这块内存就泄漏了
 */
void unique_ptr_test4(void)
{
    // 不要与裸指针混用
    int *x(new int());
    unique_ptr<int> up1,up2;

    up1.reset(x);   
    // up2.reset(x);    // 会使up1 up2指向同一个内存
}

// TODO: 系统性的对智能指针进行学习
int main(int argc, char **argv)
{
    shared_ptr_test1();
    // shared_ptr_test2();
    // shared_ptr_test3();
    // shared_ptr_test4();

    unique_ptr_test1();
    unique_ptr_test2();
    unique_ptr_test3();
    unique_ptr_test4();

    return 0;
}