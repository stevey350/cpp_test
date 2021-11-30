
#include <iostream>
#include <vector>

using namespace std;

/**
 * @brief 深拷贝测试
 */
void vector_test1(void)
{
    std::vector<int> v_point1(3, 1);        // 3个元素，每个元素均为1
    std::vector<int> v_point2 = v_point1;   // 深拷贝
    cout << "v_point1 size " << v_point1.size() << endl;

    cout << "v_point[1]=" << v_point1[1] << endl;
    v_point2[1] = 10;
    cout << "v_point[1]=" << v_point1[1] << endl;
    cout << "v_point2[1]=" << v_point2[1] << endl;
}

int main(int argc, char **argv)
{


    vector<int> v_a {1, 2, 3, 4};           // 初始化列表
    cout << "v_a = " << v_a[2] << endl;

    vector<int> v_b;
    v_b.assign(++v_a.begin(), v_a.end() );
    for(auto iter : v_b) {
        cout << iter << " ";
    }
    cout << endl;

    return 0;
}
