/**
 * @file string_test.cpp
 * @brief   <string.h>是C版本的头文件，包含strcpy、strcat之类的字符串处理函数
 *          <cstring>是C++版本的头文件，在std和全局命名空间中，包含strcpy、strcat之类的字符串处理函数
 *          <string>是C++标准定义的头文件，在std命名空间中，它定义string字符串类的各种操作，如s.size(), s.erase(), s.insert()等
 * @author sj.su (sj.su@tungthih.com.cn)
 * @version 1.0
 * @date 2021-12-23
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
 *     <th>2021-12-23
 *     <th>v0.0.1
 *     <th>sj.su
 *     <th>原型开发
 * </tr>
 * </table>
 */
#include <iostream>
#include <string>       // std命名空间中C++的字符串类
#include <vector>
#include <limits>
#include <exception>
#include <cstring>      // std和全局命名空间中(为了向前兼容)的C字符串操作函数 strcpy,memset

// using namespace std;

void cstring_test(void)
{
    char a[50] = {};
    char b[50] = {};

    // 字符串操作函数
    memset(a, '1', sizeof(a));      // 在全局命名空间中
    std::strcpy(b, a);              // 在std命名空间中

    // 输出显示
    for(size_t i=0; i<sizeof(a); i++) {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
    for(size_t i=0; i<sizeof(b); i++) {
        std::cout << b[i] << " ";
    }
    std::cout << std::endl;
}

/**
 * @brief
 * begin()函数返回一个迭代器,指向字符串的第一个元素.
 * end()函数返回一个迭代器，指向字符串的末尾(最后一个字符的下一个位置).
 *
 * rbegin()返回一个逆向迭代器，指向字符串的最后一个字符
 * rend()函数返回一个逆向迭代器，指向字符串的开头（第一个字符的前一个位置）
 *
 */
void string_iter_test(void)
{
    const std::string kBinExt = ".bin";
    const std::string file_name = "test.bin";

    // 逆序
    std::cout << "Inverse output" << std::endl;
    for (auto iter = kBinExt.rbegin(); iter != kBinExt.rend(); iter++) {
        std::cout << *iter;
    }

    // 正序
    std::cout << "\nNormal output" << std::endl;
    for (auto iter = kBinExt.begin(); iter != kBinExt.end(); iter++) {
        std::cout << *iter;
    }

    if (std::equal(kBinExt.rbegin(), kBinExt.rend(), file_name.rbegin())) {
        std::cout << "file_name extersion is .bin" << std::endl;
    }
}

/**
 * @brief  将字符串根据分隔符进行切片分割
 * @param  str              需要切割的字符串
 * @param  arr              切割后的字符串数组存放位置
 * @param  delim            需要切割的符号
 */
void str_split(const std::string& str, std::vector<std::string>& arr, const std::string& delim)
{
    std::string::size_type pos1, pos2;
    pos2 = str.find(delim);
    pos1 = 0;
    while (std::string::npos != pos2) {
        arr.push_back(str.substr(pos1, pos2 - pos1));

        pos1 = pos2 + delim.size();
        pos2 = str.find(delim, pos1);
    }
    if (pos1 != str.length()) arr.push_back(str.substr(pos1));
}



void string_split_test(void)
{
    std::string str = "11, 12.1, 13, 14.8";
    std::vector<std::string> result;
    str_split(str, result, ", ");
    for(auto substr: result) {
        std::cout << substr << std::endl;
        double value = std::stod(substr);
        std::cout << value << std::endl;
    }
}


void string_numeric_convert_test(void)
{
    try {
        // string转成数值类型
        std::cout << std::stoi("  77") << std::endl;        // 77
        std::cout << std::stod("  77.7") << std::endl;      // 77.7
        std::cout << std::stoi("-0x77") << std::endl;       // 0

        // 获得第一个未被处理的位置
        std::size_t idx;
        std::cout << std::stoi("  42 is the truth", &idx) << std::endl; // 42
        std::cout << "idx of first unprocessed char: " << idx << std::endl; // 4

        // 指定字符串表示的进制，默认为10进制
        std::cout << std::stoi("42", nullptr, 16) << std::endl;     // 字符串“42”指16进制，输出采用10进制，为66

        // 数值转字符串
        long long ll = std::numeric_limits<long long>::max();
        std::cout << std::to_string(ll) << std::endl;
    }
    catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

int main(int argc, char** argv)
{
    cstring_test();
    // string_iter_test();
    // string_split_test();
    string_numeric_convert_test();

    return 0;
}
