
#include <iostream>

void print(std::initializer_list<int> vals)
{
    for(auto p=vals.begin(); p!=vals.end(); p++) {
        std::cout << *p << std::endl;
    }
}

int main(int argc, char **argv) 
{
    std::cout << "This is a framework for testing code." << std::endl;

    print({11, 13, 18, 8});

    return 0;
}
