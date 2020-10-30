#include "matrix.hpp"
    
template <class m_type>
Matrix<m_type>::Matrix(){};

template <class m_type>
Matrix<m_type>::~Matrix(){};

template <class m_type>
Matrix<m_type>::Matrix(long int rows, long int columns) {
    this->rows = rows;
    this->columns = columns;

    data.resize(rows);
    for (long int i = 0; i < rows; i++)
        data[i].resize(columns);
}

template <class m_type>
Matrix<m_type>::Matrix(std::initializer_list<std::initializer_list<m_type>> list) {
    this->columns = (long int) (list.begin())->size();
    this->rows = (long int) list.size();

    data.resize(rows);

    for (long int i = 0; i < rows; i++) {
        data[i].resize(columns);
        for (long int j = 0; j < columns; j++) {
            data[i][j] = ((list.begin() + i)->begin())[j];
        }
    }
}

template <class m_type>
void Matrix<m_type>::print() {
    if (rows == 0)
        std::cout << "Matrix is empty" << std::endl;

    else {
        for (long int i = 0; i < rows; i++) {
            for (long int j = 0; j < columns; j++)
                std::cout << data[i][j] << " ";
            std::cout << std::endl;
        }
    }
}

template <class m_type>
long int Matrix<m_type>::numrows() {
    return rows;
}

template <class m_type>
long int Matrix<m_type>::numcols() {
    return columns;
}