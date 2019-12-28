#include <iostream>

#include "matrix.h"

int main(/*int argc, char const *argv[]*/)
{
    Matrix<int, -1> m;
    std::cout << m.size() << std::endl;
    m[3][4] = 10;
    std::cout << m.size() << std::endl;
    std::cout << m[3][4].get() << "\t" << m[1][1].get() << std::endl;
    m[3][4] = 5;
    std::cout << m.size() << std::endl;
    std::cout << m[3][4].get() << "\t" << m[1][1].get() << std::endl;
    m[3][4] = -1;
    std::cout << m.size() << std::endl;
    std::cout << m[3][4].get() << "\t" << m[1][1].get() << std::endl;
    m[3][4] = 8;
    std::cout << m.size() << std::endl;
    std::cout << m[3][4].get() << "\t" << m[1][1].get() << std::endl;

    for (auto a : m)
    {
        std::pair<std::size_t, std::size_t> index;
        MatrixElement<int, -1> value;
        std::tie(index, value) = a;
        std::cout << "index: " << index.first << "," << index.second << " value: " << value.get() << std::endl;
    }

    return 0;
}
