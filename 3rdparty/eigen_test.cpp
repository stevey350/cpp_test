#include <eigen3/Eigen/Eigen>
#include <iostream>

// using namespace std;
// using namespace Eigen;

void Eigen_Map_test(void)
{
    int array[9];
    for(int i = 0; i < 9; ++i)
        array[i] = i;
    Eigen::Map<Eigen::Matrix3i> matrix(array);
    std::cout << matrix << std::endl;
    std::cout << "[0][0] " << matrix(0, 0) << " " << matrix(0, 1) << " " << matrix(0, 2) << std::endl;

    Eigen::Matrix3i matrix2(array);
    std::cout << matrix2 << std::endl;

    Eigen::Matrix<int, 3, 3, Eigen::RowMajor> matrix3(array);
    std::cout << "Row Major matrix\n" << matrix3 << std::endl;
}


int main(int argc, char ** argv)
{
    std::cout << "Hello Eigen" << std::endl;

    Eigen_Map_test();

    return 0;
}
