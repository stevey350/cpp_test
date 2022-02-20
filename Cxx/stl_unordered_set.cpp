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
#include <unordered_set>

using namespace std;

void unordered_set_basic_test(void)
{
    unordered_multiset<string> cities = {
    // unordered_set<string> cities = {
        "Quanzhou", "Fuzhou", "Putian", "Xiamen", "Jinjiang"
    };

    for(const auto &elem: cities) {
        cout << elem << " ";
    }
    cout << endl;

    cities.insert({"Zhangzhou", "Quanzhou"});
    for(const auto &elem: cities) {
        cout << elem << " ";
    }
    cout << endl;
}

void unordered_set_test(void)
{
    unordered_set<int> myset;
    myset.insert(3);
    myset.insert(5);
    myset.insert(3);        // 容器是个集合，所以重复插入相同的值是没有效果的
    cout << "myset size: " << myset.size() << endl;
    myset.erase(3);
    if(myset.find(3) == myset.end()) {
        cout << "could not find 3" << endl;
    }
}

int main(int argc, char **argv)
{
    cout << "Hello, unordered set" << endl;

    unordered_set_basic_test();
    // unordered_set_test();

    return 0;
}
