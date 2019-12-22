#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

template<typename T, T defaultValue>
class Matrix;

template<typename T, T defaultValue>
class MatrixElement
{
public:
    MatrixElement() : m_matrix(nullptr) {}
    MatrixElement(std::pair<std::size_t, std::size_t> index, Matrix<T, defaultValue>* matrix) : m_value(defaultValue), m_index(index), m_matrix(matrix) {}
    T get() { return m_value; }
    T& operator=(const T& value)
    {
        m_value = value;
        m_matrix->Add(*this);
        return m_value;
    }
//private:
    T m_value;
    std::pair<std::size_t, std::size_t> m_index;
    Matrix<T, defaultValue>* m_matrix;
};

template<typename T, T defaultValue>
class Matrix
{
public:
    Matrix() {}

    using ValuesContainer = std::map<std::pair<std::size_t, std::size_t>, MatrixElement<T, defaultValue>>;

    void Add(const MatrixElement<T, defaultValue>& value)
    {
        m_values.emplace(value.m_index, value);
    }

    std::size_t size() { return m_values.size(); }

    typename ValuesContainer::iterator begin() { return m_values.begin(); }
    typename ValuesContainer::iterator end() { return m_values.end(); }

    struct MatrixHelper
    {
        MatrixHelper(Matrix<T, defaultValue>* values, std::size_t x) : m_matrix(values), m_x(x) {}

        MatrixElement<T, defaultValue> operator[](std::size_t y)
        {
            auto it = m_matrix->m_values.find(std::make_pair(m_x, y));
            if (it == m_matrix->m_values.end())
            {
                return MatrixElement<T, defaultValue>(std::make_pair(m_x, y), m_matrix);
            }

            return m_matrix->m_values[std::make_pair(m_x, y)];
        }

        std::size_t m_x;
        Matrix<T, defaultValue>* m_matrix;
    };

    MatrixHelper operator[](std::size_t x)
    {
        return MatrixHelper(this, x);
    }

private:
    ValuesContainer m_values;
};

int main(/*int argc, char const *argv[]*/)
{
    

    Matrix<int, -1> m;
    std::cout << m.size() << std::endl;
    m[3][4] = 10;
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
