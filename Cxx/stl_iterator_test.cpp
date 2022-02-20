
/**
 * @file stl_iterator_test.cpp
 * @brief 迭代器分为普通迭代器和迭代适配器
 *           普通迭代器：
 *           迭代适配器：
 * @author sj.su (sj.su@tungthih.com.cn)
 * @version 1.0
 * @date 2021-12-27
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
 *     <th>2021-12-27
 *     <th>v0.0.1
 *     <th>sj.su
 *     <th>原型开发
 * </tr>
 * </table>
 */
#include <iostream>
#include <iterator>
#include <list>
#include <deque>
#include <vector>
#include <set>
#include <string>
#include <algorithm>

using namespace std;

/**
 * @brief 普通迭代器，与指针操作数组元素的使用方法一致，基本操作如下：
 *        operator *        获取当前位置上的元素值
 *        operator ++/--    使迭代器前进/后退一步   
 *        operator ==/!=    判断两个迭代器是否指向同一个位置
 *        operator =        指定迭代器所指向的元素的位置
 */
void iterator_test(void)
{
    list<char> coll;
    for(char c='a'; c<='z'; c++) {
        coll.push_back(c);
    }

    list<char>::const_iterator pos;
    for(pos=coll.cbegin(); pos!=coll.cend(); pos++) {
        cout << *pos << " ";
    }
    cout << endl;
}

/**
 * @brief 迭代适配器-插入型迭代适配器
 */
void inserter_iterator_test(void)
{
    list<int> coll1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    vector<int> coll2;
    std::copy(coll1.cbegin(), coll1.cend(), 
              back_inserter(coll2));        // back_inserter内部调用push_back()

    deque<int> coll3;
    std::copy(coll1.cbegin(), coll1.cend(), 
              front_inserter(coll3));       // front_inserter内部调用push_front()

    set<int> coll4;
    std::copy(coll1.cbegin(), coll1.cend(),
              inserter(coll4, coll4.begin()));
}

/**
 * @brief 如何输入end of source结束符
 *        On ubuntu linux: ctrl+d
 *        On Win: ctrl+z
 */
void stream_iterator_test(void)
{
    vector<string> coll;
    cout << "input word by word" << endl;
    copy(istream_iterator<string>(cin),         // start of source
         istream_iterator<string>(),            // end of source
         back_inserter(coll));                  // destination
    
    cout << "sorting..." << endl;
    sort(coll.begin(), coll.end());

    // 向标准输出流cout输出数据，并且每个string元素间以换行符分隔
    unique_copy(coll.begin(), coll.end(), ostream_iterator<string>(cout, "\n"));
}

void reverse_iterator_test(void)
{
    vector<int> coll = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    copy(coll.crbegin(), coll.crend(),
         ostream_iterator<int>(cout, " "));
    cout << endl;
}

int main(int argc, char *argv[])
{
    // iterator_test();
    // inserter_iterator_test();
    // stream_iterator_test();     // 串流迭代器
    reverse_iterator_test();    // 返向迭代器

    return 0;
}