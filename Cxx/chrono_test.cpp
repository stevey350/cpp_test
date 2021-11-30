

// duration constructor
#include <iostream>
#include <ratio>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <unistd.h>     // 提供sleep()函数
#include <thread>

void duration_test(void)
{
    std::cout << "************duration test*************" << std::endl;
    // 1-时间段duration定义
    std::chrono::minutes t1(10);            // 10分钟
    std::chrono::seconds t2(50);            // 60秒
    std::chrono::milliseconds t3(1000);     // 1000毫秒
    std::chrono::milliseconds t31(t2);      // 充许从大单位(秒)转成小单位(毫秒)
    // std::chrono::seconds t4(t3);            // 不充许从小单位(毫秒)转成大单位(秒) NOT VALID (type truncates)
    std::chrono::seconds t5(std::chrono::duration_cast<std::chrono::seconds>(t3)); // 强制时间单位转换
    std::cout << "t1 " << t1.count() << std::endl;
    std::cout << "t2 " << t2.count() << std::endl;
    std::cout << "t31(ms) " << t31.count() << std::endl;
    std::cout << "t31(s) " << std::chrono::duration_cast<std::chrono::seconds>(t31).count() << std::endl;
    std::cout << "t5 " << t5.count() << std::endl;

    // 1.1-自定义duration类型
    typedef std::chrono::duration<int, std::ratio<60, 1>> my_minutes;
    typedef std::chrono::duration<int, std::ratio<1, 1000>> my_milliseconds;
    my_minutes my_t1(10);
    my_milliseconds my_t2(1000);
    std::cout << "my_t1 " << my_t1.count() << std::endl;
    std::cout << "my_t2 " << my_t2.count() << std::endl;

    // 1.2-duration运算
    std::chrono::seconds delta_seconds = t1 - t2;      // 10*60 - 60 = 540秒
    // std::chrono::minutes delta_minutes = t1 - t2;       // 不允许秒转成分钟
    std::chrono::milliseconds delta_milliseconds = t1 - t2;
    std::cout << "delta seconds " << delta_seconds.count() << " second" << std::endl;
    std::cout << "delta milliseconds " << delta_milliseconds.count() << " milliseconds" << std::endl;
    std::cout << "my_t1 * 10 " << (my_t1*10).count() << " minutes" << std::endl;
}


/**
 * @brief 
 * system_clock：从系统获取的时钟；
 * steady_clock：不能被修改的时钟；
 * high_resolution_clock：高精度时钟，实际上是system_clock或者steady_clock的别名
 */
void time_point_test(void)
{
    std::cout << "************time_point test*************" << std::endl;
    // 1-时间点time_point
    std::chrono::steady_clock::time_point tp1 = std::chrono::steady_clock::now();    // 默认单位是ns
    sleep(1);
    std::chrono::steady_clock::time_point tp2 = std::chrono::steady_clock::now();
    std::cout << "sleep time " << std::chrono::duration_cast<std::chrono::microseconds>(tp2 - tp1).count()
              << "us.\n";   // 转成us为单位输出

    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::chrono::system_clock::time_point nt = now + std::chrono::hours(10);

    // 1.1-时间点time_point的输出
    std::time_t now_c = std::chrono::system_clock::to_time_t( now );
    std::time_t nt_c = std::chrono::system_clock::to_time_t( nt );
    std::cout << std::ctime( &now_c ) << std::endl;
    std::cout << std::ctime( &nt_c ) << std::endl;
    // put_time说明 https://www.yiibai.com/cpp_standard_library/cpp_put_time.html
    std::cout<< std::put_time(std::localtime(&now_c), "%Y-%m-%d %X") << std::endl;  
}


using namespace std;
using namespace std::chrono;

/**
 * @brief 基于chrono库，实现一个简单的定时器
 */
class MyTimer
{
public:
    MyTimer() : m_begin(high_resolution_clock::now()) {}
    void reset() { m_begin = high_resolution_clock::now(); }
    
    //默认输出毫秒
    int64_t elapsed() const {
        return duration_cast<chrono::milliseconds>(high_resolution_clock::now() - m_begin).count();
    }
    
    //微秒
    int64_t elapsed_micro() const {
        return duration_cast<chrono::microseconds>(high_resolution_clock::now() - m_begin).count();
    }
    
    //纳秒
    int64_t elapsed_nano() const {
        return duration_cast<chrono::nanoseconds>(high_resolution_clock::now() - m_begin).count();
    }
    
    //秒
    int64_t elapsed_seconds() const {
        return duration_cast<chrono::seconds>(high_resolution_clock::now() - m_begin).count();
    }
    
    //分
    int64_t elapsed_minutes() const {
        return duration_cast<chrono::minutes>(high_resolution_clock::now() - m_begin).count();
    }
    //时
    int64_t elapsed_hours() const {
        return duration_cast<chrono::hours>(high_resolution_clock::now() - m_begin).count();
    }
private:

    time_point<high_resolution_clock> m_begin;
};

/**
 * @brief 
 * @return int 
 */
int main ()
{
    duration_test();
    time_point_test();

    MyTimer t; //开始计时
    
    // C++的延时函数 http://www.aobosir.com/blog/2017/02/05/cpp-sleep/
    // sleep(1);
    // usleep(1*1000*1000);    
    std::this_thread::sleep_for(std::chrono::seconds(1));

    cout<<t.elapsed()<<endl; //打印fun函数耗时多少毫秒
    cout<<t.elapsed_micro ()<<endl; //打印微秒
    cout<<t.elapsed_nano ()<<endl; //打印纳秒
    cout<<t.elapsed_seconds()<<endl; //打印秒
    cout<<t.elapsed_minutes()<<endl; //打印分钟
    cout<<t.elapsed_hours()<<endl; //打印小时

    return 0;
}



