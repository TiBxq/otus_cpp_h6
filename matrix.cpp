#include <iostream>

#include "matrix.h"

int main(/*int argc, char const *argv[]*/)
{
    Matrix<int, 0> matrix;
    for (std::size_t i = 0; i < 10; ++i)
    {
        matrix[i][i] = i;
        matrix[i][9 - i] = 9 - i;
    }

    for (std::size_t i = 1; i < 9; ++i)
    {
        for (std::size_t j = 0; j < 10; ++j)
        {
            std::cout << matrix[i][j].get() << " ";
        }
        std::cout << std::endl;
    }
       
    std::cout << matrix.size() << std::endl;

    for (auto a : matrix)
    {
        std::pair<std::size_t, std::size_t> index;
        MatrixElement<int, 0> value;
        std::tie(index, value) = a;
        std::cout << index.first << " " << index.second << " " << value.get() << std::endl;
    }

    return 0;
}
