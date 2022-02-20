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
#include <list>
#include <deque>
#include <algorithm>
#include <iterator>
#include <set>

using namespace std;

void single_range_test(void)
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
}

void multiple_range_test(void)
{
    list<int> coll1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    deque<int> coll2;

    coll2.resize(coll1.size());
    std::copy(coll1.cbegin(), coll1.cend(),     // source源区间
              coll2.begin());                   // destination目标区间

    if(std::equal(coll1.rbegin(), coll1.rend(), // 第一个区间
                  coll2.rbegin())) {            // 第二个区间
        cout << "coll1 and coll2 is equal" << endl;
    }
}

int print(int elem)
{
    cout << elem << " ";

    return elem * elem;     // 平方
}

/**
 * @brief 以函数作为算法的实参，如transform和for_each
 */
void transform_test(void)
{
    list<int> coll1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int> coll2;

    std::transform(coll1.begin(), coll1.end(),      // source
                   std::back_inserter(coll2),       // destination
                   print);                          // operation
    
    cout << endl;
    for_each(coll2.cbegin(), coll2.cend(),          // range
             [](int elem) {cout << elem << " "; }); // operation
}

/**
 * @brief   更易型算法manipulating algorithm只适用于序列型容器,不适用于关联式和无序型容器 
 *          常见的更易型算法有：remove, reorder, modify
 *          - 此例显示了STL将容器与算法弹性分离所付出的代价
 *          remove()并没有改变集合中元素的数量，cend()返回的是当初那个终点，size()返回当初那个大小
 *          庆幸remove()返回了一个新的终点
 */
void seq_container_remove_test(void)
{
    list<int> coll;

    // 插入数据
    for(size_t i=0; i<6; i++) {
        coll.push_back(i);
        coll.push_front(i);
    }

    // 输出未remove前的数据
    copy(coll.cbegin(), coll.cend(), 
        ostream_iterator<int>(cout, " "));
    cout << endl;

    // 算法1-使用通用算法删除指定元素(通用算法，不能充分利用list的链接link来安插、移动、移除元素)
    // list<int>::iterator end = remove(coll.begin(), coll.end(), 3);  // 通用删除算法 poor performance
    // copy(coll.begin(), end, ostream_iterator<int>(cout, " "));      // 输出经过remove操作后的数据
    // cout << endl;
    // cout << "number of removed elements: " << distance(end, coll.end()) << endl;
    // coll.erase(end, coll.cend());   // 使用容器提供的删除成员函数才能'斩草除根'

    // 算法2-使用成员函数删除指元素，会充分利用list的特性
    coll.remove(3);          // good performance

    copy(coll.cbegin(), coll.cend(), ostream_iterator<int>(cout, " "));
    cout << endl;
}

void asso_container_remove_test(void)
{
    set<int> coll = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    copy(coll.begin(), coll.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    // 通用算法remove不能用于关联型/无序型容器，故该容器会提供对应的成员函数
    int num = coll.erase(3);

    cout << "number of removed elements: " << num << endl;

    copy(coll.begin(), coll.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}

int main(int argc, char **argv)
{
    // single_range_test();
    // multiple_range_test();
    // transform_test();
    // seq_container_remove_test();
    asso_container_remove_test();

    return 0;
}
