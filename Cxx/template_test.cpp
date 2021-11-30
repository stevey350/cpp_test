
#include <iostream>
using namespace std;

// 最终递归函数
void print()
{
  cout << "empty" << endl;  
}


/**
 * @brief           通过递归函数展开参数包，需要提供一个参数包展开的函数和一个递归终止函数，递归终止函数正是用来终止递归的
 * @tparam T 
 * @tparam Args     可变参数模板时需要在typename或class后面带上省略号“...”
 * @param  head             My Param doc
 * @param  args     参数args前面有省略号，所以它就是一个可变模版参数，它里面包含了0到N（N>=0）个模版参数
 */
template <typename T, typename... Args>
void print(T head, Args... args)
{
    cout << head << ",";
    // if (sizeof...(args) !=0 )    // 也可以通过这个判断来终止迭代
    print(args...);     // 如何有参数，会调用自己，没参数则调用print()
}

/**
 * @brief       简单的将可变模版参数的个数打印出来，
 *              如果我们需要将参数包中的每个参数打印出来的话就需要通过一些方法了。
 *              展开可变模版参数函数的方法一般有两种：一种是通过递归函数来展开参数包，
 *                                             另一种是通过逗号表达式来展开参数包。
 * @tparam T 
 * @param  args             My Param doc
 */
template<typename... T>
void fun(T... args)
{
    // 打印参数个数
    cout << sizeof...(args) << endl;  
}

int main()
{
    fun();
    fun(1, 2);

    print(1, 2, 3, 4);
    return 0;    
}
