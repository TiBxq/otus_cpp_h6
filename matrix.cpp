#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

template<typename T, T value>
class Matrix
{
public:
    T& operator[](std::size_t index)
    {
        return m_values[index];
    }

private:
    std::map<std::size_t, T> m_values;
};

int main(/*int argc, char const *argv[]*/)
{
    Matrix<int, -1> m;
    m[0] = 10;
    std::cout << m[0] << "\t" << m[1] << std::endl;

    return 0;
}
