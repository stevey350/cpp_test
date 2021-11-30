/**
 * @file algorithm_test.cpp
 * @brief 为了处理容器内的元素，STL提供了一些标准算法，如查找，排序，拷贝，重新排序，修改
 *        操作对象是迭代器
 * @author sj.su (sj.su@tungthih.com.cn)
 * @version 1.0
 * @date 2021-10-25
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
 *     <th>2021-10-25
 *     <th>v0.0.1
 *     <th>sj.su
 *     <th>原型开发
 * </tr>
 * </table>
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char **argv)
{
    vector<int> coll = {2, 5, 4, 1, 6, 3};

    // 查找最大最小值
    auto min_pos = min_element(coll.begin(), coll.end());
    auto max_pos = max_element(coll.cbegin(), coll.cend());
    cout << "min element: " << *min_pos << endl;
    cout << "max element: " << *max_pos << endl;
    std::pair<std::vector<int>::const_iterator, std::vector<int>::const_iterator> min_max_pos = minmax_element(coll.cbegin(), coll.cend());
    cout << "min element: " << min_max_pos.first[0] << endl;
    cout << "max element: " << min_max_pos.second[0] << endl;

    // 排序
    cout << "before sort" << endl;
    vector<int>::const_iterator it = coll.begin();
    while(it != coll.end()) {
        cout << *it << " " << endl;
        it++;
    }
    sort(coll.begin(), coll.end());
    cout << "after sort" << endl;
    it = coll.begin();
    while(it != coll.end()) {
        cout << *it << " " << endl;
        it++;
    }

    // 查找
    auto spec_pos = find(coll.begin(), coll.end(), 4);
    if (spec_pos != coll.end() ) {
        cout << "found the value" << endl;
        cout << "spec pos value: " << *spec_pos << endl;
        // *spec_pos = 40;     // 修改
    }
    
    // 逆序
    reverse(spec_pos, coll.end());

    for (auto elem: coll) {
        cout << elem << " ";
    }

    // 执行完nth_element后:
    // 第n个元素之前的元素都小于它，但不必是有序的。同样，第n个元素后的元素都大于它，但也不必是有序的。
    // n从0开始算
    nth_element(coll.begin(), coll.begin()+3, coll.end());
    cout << "\n3th element" << endl;
    for (auto elem: coll) {
        cout << elem << " ";
    }


    return 0;
}
