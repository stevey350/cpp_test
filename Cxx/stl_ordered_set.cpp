/**
 * @file stl_ordered_set.cpp
 * @brief  关联式容器(set, multiset, map, multimap)通常由二叉树实现出来。在二叉树中，每个元素（节点）都有一个父节点和两个子节点；
 *         左子树的所有元素都比自己小，右子树的元素都比自己大。
 *         关联式容器的优点：可以快速找出具有某特定value的元素
 *                   缺点：不可以更改元素的value，因为那会破坏元素的自动排序
 *         set: 元素依据其value自动排序，每个元素只能出现一次，不允许重复
 *         multiset: 和set唯一区别是元素可以重复
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
#include <set>
#include <iostream>
#include <string>

using namespace std;

/**
 * @brief Set容器每个元素只能出现一次
 */
void set_basic_test(void)
{
    // multiset<string> cities = {
    set<string> cities = {
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

/**
 * @brief Set容器默认是以操作符‘<’作为排序依据
 */
void set_order_test(void)
{
    set<int, greater<int>> coll = {3, 1, 5, 4, 1, 6, 2};    // greater<int>递增方式

    for(auto elem: coll) {
        cout << elem << " ";
    }
    cout << endl;
}

int main(int argc, char *argv[])
{
    // set_basic_test();
    set_order_test();

    return 0;
}