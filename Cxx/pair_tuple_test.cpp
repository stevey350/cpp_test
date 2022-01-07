#include <iostream>
#include <tuple>
#include <string>
#include <functional>
#include <complex>

using namespace std;

/**
 * @brief 泛型模版函数
 */
template <typename T1, typename T2>
void pair_print(std::pair<T1, T2> &p)
{
    cout << "[" << p.first << ", " << p.second << "]" << endl;
}

class Foo {
public:
    Foo(tuple<int, float> &p) {
        cout << "Foo::Foo(tuple)" << endl;
    }
    template <typename... Args>
    Foo(Args... args) {
        cout << "Foo::Foo(args ...)" << endl;
    }
};

/**
 * @brief pair可以接收处理两个类型不同的值
 */
void pair_basic_test(void)
{
    std::pair<int, float> p1;           // 没有指定初值的构造函数，则默认使用数据类型默认的构造函数进行初始化
    pair_print(p1);                     // 这里输出为[0, 0]
    
    std::pair<int, float> p2(42, 3.14); // 指定初值的构造函数
    pair_print(p2);                     // 这里输出为[42, 3.14]

    auto p3 = std::make_pair(42, "$$"); // 便捷的template函数
    pair_print(p3);

    // 逐块式构造(piecewise construction)
    // 第一个参数传递std::piecewise_construct，则后面参数必须是tuple类型
    tuple<int, float> t(1, 2.22);
    pair<int, Foo> p4(4, t);
    pair<int, Foo> p5(std::piecewise_construct, std::make_tuple(5), t);
    // pair<int, Foo> p5(std::piecewise_construct, std::make_tuple(5, 1, 2.22));       // ERROR
    pair<int, float> p6(std::piecewise_construct, std::make_tuple(5), std::make_tuple(1.22));   // OK
    // pair<int, float> p6(std::piecewise_construct, std::make_tuple(5, 1.2));     // ERROR
    cout << "p5.first: " << p5.first << endl;
}

void pair_basic_test2(void)
{
    // move语义测试
    std::string str1 = "hello";
    std::string str2 = "world";
    auto p1 = std::make_pair(std::move(str1), std::move(str2)); // 采用move语义，表示后面不再使用
    cout << str1 << " " << str2 << endl;

    // reference语义测试
    int i = 0;
    auto p2 = std::make_pair(std::ref(i), std::ref(i));
    p2.first++;
    p2.second++;
    cout << "i: " << i << endl;

    int j=0;
    pair<int&, int&> p3(j, j);
    p3.first++;
    p3.second++;
    cout << "j: " << j << endl;
}

/**
 * @brief tuple可以接收处理任意（不超过10个）个类型不同的元素
 */
void tuple_basic_test(void)
{
    tuple<string, int, int, complex<double>> t;     // 没有指定初值的构造函数
    tuple<string, int, int> t1("nico", 1, 2);       // 指定初值的构造函数

    auto t2 = std::make_tuple("hello", 2, 3);       // 便捷函数，类型自动推导
    cout << get<0>(t1) << " ";
    cout << get<1>(t1) << " ";
    cout << get<2>(t1) << endl;

    get<1>(t1)  = get<1>(t2);       // 元素赋值

    if(t1 > t2) {                   // 比较
        t1 = t2;                    // 整体赋值
    }
    cout << get<0>(t1) << " ";
    cout << get<1>(t1) << " ";
    cout << get<2>(t1) << endl;
}


void tuple_basic_test2(void)
{
    // 运用reference和make_tuple, 将t内的元素，赋给对应变量i, f, s
    std::tuple<int, float, std::string> t(77, 1.1, "more light");

    int i;
    float f;
    std::string s;
    // std::make_tuple(std::ref(i), std::ref(f), std::ref(s)) = t;
    std::tie(i, f, s) = t;          // tie()可以建立一个内含reference的tuple，与上等效
    cout << "i: " << i << " f: " << f << " s: " << s << endl;

    // 使用tie()局部提取tuple的元素值, std::ignore允许忽略tuple的某些元素
    std::tie(i, std::ignore, s) = std::make_tuple(33, 2.2, "tie");
    cout << "i: " << i << " f: " << f << " s: " << s << endl;
}

int main(int argc, char *argv[])
{
    // pair_basic_test();
    // pair_basic_test2();
    // tuple_basic_test();
    tuple_basic_test2();

    return 0;
}