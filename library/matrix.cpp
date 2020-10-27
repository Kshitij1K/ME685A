#include "include/matrix.hpp"
#include <iostream>

template <class m_type>
Matrix<m_type>::Matrix()
    : data(NULL) {
}

template <class m_type>
Matrix<m_type>::~Matrix() {
}

template <class m_type>
Matrix<m_type>::Matrix(int rows, int columns) {
    if (data != NULL) {
        for (int i = 0; i < rows; i++)
            delete[] data[i];
        delete[] data;
    }

    this->rows = rows;
    this->columns = columns;

    data = new m_type*[rows];
    for (int i = 0; i < rows; i++)
        data[i] = new m_type[columns];
}

template <class m_type>
Matrix<m_type>::Matrix(m_type* array_num, int rows, int columns) {
    if (data != NULL) {
        for (int i = 0; i < rows; i++)
            delete[] data[i];
        delete[] data;
    }

    this->rows = rows;
    this->columns = columns;

    data = new m_type*[rows];
    for (int i = 0; i < rows; i++) {
        data[i] = new m_type[columns];
        for (int j = 0; j < columns; j++)
            data[i][j] = array_num[(i * rows) + columns];
    }
}

template <class m_type>
void Matrix<m_type>::print() {
    if (data == NULL)
        std::cout << "Matrix is empty" << std::endl;

    else {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++)
                std::cout << data[i][j] << " ";
            std::cout << std::endl;
        }
    }
}