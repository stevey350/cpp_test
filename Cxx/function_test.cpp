/**
 * @file function_test.cpp
 * @brief 
 * @author sj.su (sj.su@tungthih.com.cn)
 * @version 1.0
 * @date 2021-11-03
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
 *     <th>2021-11-03
 *     <th>v0.0.1
 *     <th>sj.su
 *     <th>原型开发
 * </tr>
 * </table>
 */
#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

// 用于for_each的测试
struct Play
{
    Play() {
        cout << "Construct a Play without any args" << endl;
    }
    Play(const char *str) : _str(str) {
        cout << "Construct a Play with char * arg" << endl;
    }
    Play(const Play&) {
        cout << "Construct a copy Play" << endl;
    }
    void operator () (int i) {
        cout << _str << i << endl;
    }
    ~Play() {
        cout << "Deconstruct a Play" << endl;
    }

    const char *_str;
};

/**
 * @brief for_each本质是一个function template，需要包含<algorithm>头文件。
 * 从输出结果，可以猜测for_each的执行过程：
 *   Play() 生成一个临时的匿名的Play对象，传入for_each 函数里，然后执行完for_each 函数后，
 *   return一个function时，Play用复制构造函数生成一个Play对象，然后两个Play对象的生命周期都结束，于是依次销毁。
 */
void for_each_test(void)
{
    int a[] = {1, 3, 4, 5};

    vector<int> vc(a, a+sizeof(a)/sizeof(int));
    // for_each(vc.begin(), vc.end(), Play());     // 需要包含<algorithm>头文件
    for_each(vc.begin(), vc.end(), Play("Element: "));

    cout<<"See something"<<endl;
}

/**
 * @brief https://www.jianshu.com/p/f191e88dcc80
 * 一、可调用对象有一下几种定义：
 *   1.是一个函数指针，参考 C++ 函数指针和函数类型；
 *   2.是一个具有operator()成员函数的类的对象；
 *   3.可被转换成函数指针的类对象；
 *   4.一个类成员函数指针；
 * 
 * 二、 std::function
 *   std::function 是一个可调用对象包装器，是一个类模板，可以容纳除了类成员函数指针之外的所有可调用对象，
 *   它可以用统一的方式处理函数、函数对象、函数指针，并允许保存和延迟它们的执行。
 *   定义格式：std::function<函数类型>。
 *   std::function可以取代函数指针的作用，因为它可以延迟函数的执行，特别适合作为回调函数使用。它比普通函数指针更加的灵活和便利。
 * 
 * 三、std::bind
 *   可将std::bind函数看作一个通用的函数适配器，它接受一个可调用对象，生成一个新的可调用对象来“适应”原对象的参数列表。
 *   std::bind将可调用对象与其参数一起进行绑定，绑定后的结果可以使用std::function保存。
 *   std::bind主要有以下两个作用：
 *     将可调用对象和其参数绑定成一个防函数；
 *     只绑定部分参数，减少可调用对象传入的参数。
 */

// 下面是可调用对象的不同定义形式，但却有统一的调用方式：int(int ,int)

// 普通函数
int add(int a, int b)
{
    // cout << "(a, b) = " << a << " " << b << endl;
    return a+b;
} 

// lambda表达式
auto mod = [](int a, int b){ return a % b;};

// 函数对象类
struct divide{
    int operator()(int denominator, int divisor){
        return denominator/divisor;
    }
};


struct Foo {
    void print_sum(int n1, int n2)
    {
        std::cout << "(n1, n2) = " << n1 << " " << n2 << endl;
        std::cout << n1+n2 << '\n';
    }
    int data = 10;
};


ostream & print(ostream &os, const string& s, char c)
{
    os << s << c;
    return os;
}

int main(int argc, char **argv)
{
    for_each_test();

    // 原始调用方式
    struct divide divider;
    cout << "add(1, 2) = " << add(1, 2) << endl;
    cout << "mod(5, 2) = " << mod(5, 2) << endl;
    cout << "divide(5, 2) = " << divider(5, 2) << endl;

    // 采用std::function统一调用
    std::function<int(int ,int)>  a = add; 
    std::function<int(int ,int)>  b = mod ; 
    std::function<int(int ,int)>  c = divide();
    cout << "a(1, 2) = " << a(1, 2) << endl;
    cout << "b(5, 2) = " << b(5, 2) << endl;
    cout << "c(5, 2) = " << c(5, 2) << endl;

    // 采用std::bind封装普通函数
    // bind的第一个参数是函数名，普通函数做实参时，会隐式转换成函数指针。因此std::bind (my_divide,_1,2)等价于std::bind (&my_divide,_1,2)；
    // _1表示占位符，位于<functional>中，std::placeholders::_1；
    auto add_5 = std::bind(add, std::placeholders::_1, 5);
    cout << "add_5(3) = " << add_5(3) << endl;

    // std::bind绑定一个成员函数
    // bind绑定类成员函数时，第一个参数表示对象的成员函数的指针，第二个参数表示对象的地址。
    // 必须显式的指定&Foo::print_sum，因为编译器不会将对象的成员函数隐式转换成函数指针，所以必须在Foo::print_sum前添加&；
    // 使用对象成员函数的指针时，必须要知道该指针属于哪个对象，因此第二个参数为对象的地址 &foo；
    Foo foo;
    auto f = std::bind(&Foo::print_sum, &foo, std::placeholders::_1, 95);
    f(5);

    // std::bind绑定一个引用参数
    // ostream不能拷贝，若希望传递给bind一个对象，
    // 而不拷贝它，就必须使用标准库提供的ref函数
    vector<string> words{"helo", "world", "this", "is", "C++11"};
    ostringstream os1;
    char c_space = ' ';
    for_each(words.begin(), words.end(),
                   bind(print, ref(os1), std::placeholders::_1, c_space));
    cout << os1.str() << endl;

    return 0;
}