/**
 * @file unordered_set_map.cpp
 * @brief C++ 11中出现了两种新的关联容器:unordered_set和unordered_map，其内部实现与set和map大有不同，
 *        set和map内部实现是基于RB-Tree，而unordered_set和unordered_map内部实现是基于哈希表(hashtable)
 * 
 * 接口：unordered_set可以把它想象成一个集合，它提供了几个函数让我们可以增删查：
 *    unordered_set::insert
 *    unordered_set::emplace
 *    unordered_set::find
 *    unordered_set::erase
 * 
 * 时间复杂度: 对于unordered_set，insert/find/erase的平均复杂度是O(1)，但是最坏复杂度是O(N)的，这里N是指容器中元素数量。
 * 有两种情况会出现O(N)复杂度。
 * 1. 是你的哈希函数太烂了，导致很多不同元素的哈希值都相同，全是碰撞，这种情况复杂度会变成O(N)。
 *    但是这种情况一般不用担心，因为对于string以及int double之类的基本数据类型，都有默认的哈希函数，而且默认的哈希函数足够好，不会退化到O(N)。
 *    如果是你自定义的哈希函数，那你要小心一点，别写的太差了。
 * 2. 是如果insert很多数据，会触发rehash。就是整个哈希表重建。这个过程有点类似向vector里不断添加元素，vector会resize。
 *    比如你新建一个vector时，它可能只申请了一块最多保存10个元素的内存，当你插入第11个元素的时候，它会自动重新申请一块更大空间，比如能存下20个元素。
 *    哈希表也是类似，不过rehash不会频繁发生，均摊复杂度还是O(1)的，也不用太担心。
 * @author sj.su (sj.su@tungthih.com.cn)
 * @version 1.0
 * @date 2021-11-02
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
 *     <th>2021-11-02
 *     <th>v0.0.1
 *     <th>sj.su
 *     <th>原型开发
 * </tr>
 * </table>
 */
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <vector>

using namespace std;


/**
 * @brief 保存一系列key/value对，并且可以按key来查询
 */
void unordered_map_test(void)
{
    unordered_map<string, int> my_map;
    my_map.insert(make_pair("C++", 100));
    my_map.insert(make_pair("java", 90));
    my_map["C++"] = 110;
    cout << "C++ count in my_map: " << my_map.count("C++") << endl;

    // unordered_map<string, int>::iterator it = my_map.find("C++");
    auto it = my_map.find("C++");
    cout << "my_map: " << it->first << " " << it->second << endl;
    my_map.erase("java");
    if(my_map.find("java") == my_map.end() ) {
        cout << "could not find java" << endl;
    }

    // unordered_map重载了[]运算符，我们可以把key放在中括号里，像操作数组一样操作unordered_map
    my_map["C++"] = 110;
    my_map["C++"]++;
    cout << "my_map: " << my_map["C++"] << endl;

}

bool comp( const pair<int, string>& a,  const pair<int, string> &b){
    return a.first < b.first;
}

void unordered_map_sort_test(void)
{
    unordered_map <int, string> int_string_map;

    int_string_map.insert(make_pair<int, string>(1, "hello1"));
    int_string_map.insert(make_pair<int, string>(3, "hello3"));
    int_string_map.insert(make_pair<int, string>(2, "hello2"));
    int_string_map.insert(make_pair<int, string>(8, "hello8"));

    std::vector<std::pair<int, string>> tmp;
    for(auto iter: int_string_map) {
        tmp.push_back(iter);
    }

    for(auto x : tmp)
        cout<< x.first << " " << x.second << " " <<endl;

    sort(tmp.begin(), tmp.end(), 
        [=](std::pair<int, string> &a, std::pair<int, string> &b) { return a.first < b.first; });
    // sort(tmp.begin(), tmp.end(), comp);

    for(auto x : tmp)
        cout<< x.first << " " << x.second << " " <<endl;
}

int main(int argc, char **argv)
{
    cout << "Hello, unordered map" << endl;

    // unordered_map_test();
    unordered_map_sort_test();

    return 0;
}
