/**
 * @file meta_program.cpp
 * @brief 相关元编程，查阅：https://www.cnblogs.com/qicosmos/p/4480460.html
 * @author sj.su (sj.su@tungthih.com.cn)
 * @version 1.0
 * @date 2021-11-01
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
 *     <th>2021-11-01
 *     <th>v0.0.1
 *     <th>sj.su
 *     <th>原型开发
 * </tr>
 * </table>
 */
#include <iostream>
#include <type_traits>

using namespace std;

int main() {
  std::cout << "int: " << std::is_const<int>::value << std::endl;
  std::cout << "const int: " << std::is_const<const int>::value << std::endl;

  //判断类型是否相同
  std::cout<< std::is_same<int, int>::value<<"\n";// true
  std::cout<< std::is_same<int, unsigned int>::value<<"\n";// false

  //添加、移除const
  cout << std::is_same<const int, add_const<int>::type>::value << endl;
  cout << std::is_same<int, remove_const<const int>::type>::value << endl;

  //添加引用
  cout << std::is_same<int&, add_lvalue_reference<int>::type>::value << endl;
  cout << std::is_same<int&&, add_rvalue_reference<int>::type>::value << endl;

  //取公共类型
  typedef std::common_type<unsigned char, short, int>::type NumericType;
  cout << std::is_same<int, NumericType>::value << endl;

  return 0;
}
