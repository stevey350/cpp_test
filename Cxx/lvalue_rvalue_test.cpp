#include <iostream>
#include <cstring>

using namespace std;

/**
 * @brief 定义：左值指的是可以取地址的变量，左值与右值的根本区别在于能否获取内存地址
 *             可通过是否可以用取地址符&来判断是否为左值
 */
void lvalue_rvalue_test(void)
{
    // 基本例子
    int var;        // var左值
    var = 4;        // 4为右值

    // 4 = var;        // ERROR!
    // (var + 10) = 4; // ERROR!

    // 左值和右值的转换
    int a = 1;     // a是一个左值
    int b = 2;     // b是一个左值
    int c = a + b; // ＋需要两个右值，所以a和b都转换成右值，并且返回一个右值

    int arr[] = {1, 2};
    int* p = &arr[0];
    *(p + 1) = 10;    // 对的：p+1是一个右值，但是*(p+1)是一个左值

    int var1 = 10;
    // int* bad_addr = &(var + 1); // 错误：‘&’运算符要求一个左值
    int* addr = &var1;          // 正确：var1是左值
    // &var1 = 40;                  // 错误：赋值运算符的左操作数要求一个左值
}

/**
 * @brief 右值引用和相关的移动语义是C++11标准中引入的最强大的特性之一
 */
class Intvec
{
public:
    explicit Intvec(size_t num = 0)
        : m_size(num), m_data(new int[m_size]) {
        log("constructor");     // 构造函数
    }

    ~Intvec() {
        log("destructor");      // 析构函数
        if (m_data != nullptr) {
            delete[] m_data;
            m_data = 0;
        }
    }

    // 1-copy constrcutor和move constructor
    Intvec(const Intvec& other) 
        : m_size(other.m_size), m_data(new int[m_size]) {
        log("copy constructor");            // copy constructor
        for (size_t i = 0; i < m_size; ++i)
            m_data[i] = other.m_data[i];
    }

    Intvec(Intvec&& other)
        : m_size(0), m_data(nullptr) {
        log("move constructor");
        m_size = other.m_size;
        m_data = other.m_data;

        // 防止源对象other的析构函数将其掌握的资源析构
        other.m_size = 0;
        other.m_data = nullptr;
    }

    // 2-copy assignment和move assignment
    Intvec& operator=(const Intvec& other) {
        log("copy assignment operator");    // copy assign拷贝赋值操作
        if(this == &other) return *this;    // 防止自我赋值

        // 实现方式1
        // Intvec tmp(other);
        // std::swap(this->m_size, tmp.m_size);
        // std::swap(this->m_data, tmp.m_data);

        // 实现方式2（更合理）
        if(m_data) delete[] m_data;         // 删除自身的资源
        m_size = other.m_size;
        m_data = new int[m_size];
        memcpy(m_data, other.m_data, m_size);

        return *this;
    }

    Intvec& operator=(Intvec&& other) {
        log("move assignment operator");    // move assign-&&表示右值引用
        if(this == &other) return *this;    // 防止自我赋值

        // 实现方式1
        // std::swap(m_size, other.m_size);
        // std::swap(m_data, other.m_data);

        // 实现方式2（更合理）
        if(m_data) delete[] m_data;         // 删除自身的资源
        m_size = other.m_size;
        m_data = other.m_data;

        other.m_size = 0;
        other.m_data = nullptr;

        return *this;
    }

    bool set_data(size_t idx, int value) {
        if(idx >= m_size)
            return false;
        m_data[idx] = value;
    }

    void print_data(void) {
        for(size_t i=0; i<m_size; i++) {
            cout << m_data[i] << " ";
        }
        cout << endl;
    }

    size_t size(void) { 
        return m_size;
    }

private:
    void log(const char* msg) {
        cout << "[" << this << "] " << msg << "\n";
    }

    size_t m_size;
    int* m_data;
};

/**
 * @brief 右值引用测试
 *        std::move并不能移动任何东西，它唯一的功能是将一个左值强制转化为右值引用，继而可以通过右值引用使用该值，以用于移动语义，
 *        确切地说，它使一个值易于移动。从实现上讲，std::move基本等同于一个类型转换：static_cast<T&&>(lvalue);
 *
 */
void rvalue_reference_test(void)
{
    Intvec v1(5);       // 左值
    Intvec v2;          // 左值

    for(size_t i=0; i<5; i++) {
        v1.set_data(i, i);
    }
    v1.print_data();

    cout << "assigning lvalue...\n";
    v2 = v1;
    v2.set_data(0, 5);
    v1.print_data();
    cout << "ended assigning lvalue...\n";

    v2 = std::move(v1);
    // v1.~Intvec();        // v2与v1共用，不能调用v1的析构
    v2.set_data(0, 5);
    v1.print_data();
}

void rvalue_reference_test2(void)
{
    // 右值可以看作程序运行中的临时结果，右值引用可以避免复制提高效率
    cout << "before copy constructor" << endl;
    Intvec v1 = Intvec();       // 编译器未优化情况，会有构造和拷贝赋值
    cout << "after copy constructor" << endl;

    Intvec &&v2 = Intvec();     // 只有一个构造，直接引用Intvec()返回的对象
}

void move_assignment_test(void)
{
    Intvec v1(5);       // 左值
    Intvec v2(3);       // 左值

    for(size_t i=0; i<v1.size(); i++) {
        v1.set_data(i, i);
    }
    for(size_t i=0; i<v2.size(); i++) {
        v2.set_data(i, i);
    }
    cout << "v1 data: ";
    v1.print_data();
    cout << "v2 data: ";
    v2.print_data();

    v1 = std::move(v2);
    cout << "v1 data: ";
    v1.print_data();
    cout << "v2 data: ";
    v2.print_data();
}


int main(int argc, char **argv)
{
    // lvalue_rvalue_test();
    // rvalue_reference_test();
    // rvalue_reference_test2();    // 右值引用
    move_assignment_test();

    return 0;
}



