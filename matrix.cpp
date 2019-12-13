#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

template<typename T>
class Matrix;

template<typename T>
class MatrixElement
{
public:
    MatrixElement() : m_index(-1), m_matrix(nullptr) {}
    MatrixElement(T value, int index, Matrix<T>* matrix) : m_value(value), m_index(index), m_matrix(matrix) {}
    T get() { return m_value; }
    T& operator=(const T& value)
    {
        m_value = value;
        m_matrix->Add(*this);
        return m_value;
    }
//private:
    T m_value;
    int m_index;
    Matrix<T>* m_matrix;
};

template<typename T>
class MatrixElementProxy
{
public:
    
};

template<typename T>
class Matrix
{
public:
    Matrix() : m_size( 0 ) {}

    MatrixElement<T> operator[](std::size_t index)
    {
        auto it = m_values.find(index);
        if (it == m_values.end())
        {
          return MatrixElement<T>(-1, index, this);
        }

        //if (index > m_size) m_size = index;
        return m_values[index];
    }

    void Add(const MatrixElement<T>& value)
    {
      m_values.emplace(value.m_index, value);
    }

private:
    std::map<std::size_t, MatrixElement<T>> m_values;
    std::size_t m_size;
    //T m_default = value;
};

int main(/*int argc, char const *argv[]*/)
{
    

    Matrix<int> m;
    //MatrixElement<int> a( -1, &m );
    //a.
    m[0] = 10;
    std::cout << m[0].get() << "\t" << m[1].get() << std::endl;

    return 0;
}
