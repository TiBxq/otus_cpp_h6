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
    MatrixElement() : m_index(-1), m_matrix(nullptr) {}
    MatrixElement(int index, Matrix<T, defaultValue>* matrix) : m_value(defaultValue), m_index(index), m_matrix(matrix) {}
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
    Matrix<T, defaultValue>* m_matrix;
};

template<typename T, T defaultValue>
class Matrix
{
public:
    Matrix() {}

    void Add(const MatrixElement<T, defaultValue>& value)
    {
        m_values.emplace(value.m_index, value);
    }

    std::size_t size() { return m_values.size(); }

    typename std::map<std::size_t, MatrixElement<T, defaultValue>>::iterator begin() { return m_values.begin(); }
    typename std::map<std::size_t, MatrixElement<T, defaultValue>>::iterator end() { return m_values.end(); }

    //template<typename T, T defaultValue>
    struct MatrixHelper
    {
        MatrixHelper(Matrix<T, defaultValue>* a_values) : m_matrix(a_values) {}

        MatrixElement<T, defaultValue> operator[](std::size_t index)
        {
            auto it = m_matrix->m_values.find(index);
            if (it == m_matrix->m_values.end())
            {
                return MatrixElement<T, defaultValue>(index, m_matrix);
            }

            return m_matrix->m_values[index];
        }

        Matrix<T, defaultValue>* m_matrix;
    };

    MatrixHelper/*<T, defaultValue>*/ operator[](std::size_t)
    {
        return MatrixHelper/*<T, defaultValue>*/(this);
    }

private:
    std::map<std::size_t, MatrixElement<T, defaultValue>> m_values;
};

int main(/*int argc, char const *argv[]*/)
{
    

    Matrix<int, -1> m;
    std::cout << m.size() << std::endl;
    m[0][0] = 10;
    std::cout << m.size() << std::endl;
    std::cout << m[0][0].get() << "\t" << m[1][1].get() << std::endl;

    for (auto a : m)
    {
        int index;
        MatrixElement<int, -1> value;
        std::tie(index, value) = a;
        std::cout << "index: " << index << " value: " << value.get() << std::endl;
    }

    return 0;
}
