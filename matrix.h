#pragma once

#include <map>

template<typename T, T defaultValue>
class Matrix;

template<typename T, T defaultValue>
class MatrixElement
{
public:
    MatrixElement() : m_matrix(nullptr) {}
    MatrixElement(std::pair<std::size_t, std::size_t> index, Matrix<T, defaultValue>* matrix) : m_value(defaultValue), m_index(index), m_matrix(matrix) {}
    T get() const { return m_value; }
    std::pair<std::size_t, std::size_t> getIndex() const { return m_index; }
    T& operator=(const T& value)
    {
        m_value = value;
        if (value != defaultValue)
        {
            m_matrix->Add(*this);
        }
        else
        {
            m_matrix->Remove(*this);
        }
        return m_value;
    }
private:
    T m_value;
    std::pair<std::size_t, std::size_t> m_index;
    Matrix<T, defaultValue>* m_matrix;
};

template<typename T, T defaultValue>
class Matrix
{
public:
    using ValuesContainer = std::map<std::pair<std::size_t, std::size_t>, MatrixElement<T, defaultValue>>;

    void Add(const MatrixElement<T, defaultValue>& value)
    {
        m_values[value.getIndex()] = value;
    }

    void Remove(const MatrixElement<T, defaultValue>& value)
    {
        auto it = m_values.find(value.getIndex());
        if (it != m_values.end())
        {
            m_values.erase(it);
        }
    }

    std::size_t size() { return m_values.size(); }

    typename ValuesContainer::iterator begin() { return m_values.begin(); }
    typename ValuesContainer::iterator end() { return m_values.end(); }

    struct MatrixHelper
    {
        MatrixHelper(Matrix<T, defaultValue>* values, std::size_t x) : m_x(x), m_matrix(values) {}

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