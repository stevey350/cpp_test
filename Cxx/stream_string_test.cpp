
#include <iostream>
#include <sstream>

using namespace std;

/**
 * @brief  将string类型转换成int, float, double类型
 * @tparam T 
 * @param  value            输出的转换后的值
 * @param  str              待转换的字符串
 */
template < class T >  
void convert_from_str(T &value, const std::string &str)
{
    std::stringstream ss(str);
    ss >> value;
}


int main(int argc, char **argv)
{
    std::string str = "12";
    double value;
    convert_from_str(value, str);

    return 0;
}

