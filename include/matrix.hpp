#pragma once

#include <iostream>

template<class m_type> class Matrix {
  private:
    int rows;
    int columns;
    m_type** data;
    bool is_initialized = false;
    bool is_declared = false;

  public:
    Matrix()
        : data(NULL){};

    ~Matrix(){};

    Matrix(int rows, int columns) {
        this->rows = rows;
        this->columns = columns;

        data = new m_type*[rows];
        for (int i = 0; i < rows; i++)
            data[i] = new m_type[columns];
        is_declared = true;
    }

    Matrix(m_type* array_num, int rows, int columns) {
        this->rows = rows;
        this->columns = columns;

        data = new m_type*[rows];

        for (int i = 0; i < rows; i++) {
            data[i] = new m_type[columns];
            for (int j = 0; j < columns; j++){
                data[i][j] = array_num[(i * columns) + j];
            }
        }

        is_initialized = true;
        is_declared = true;
    }

    void print() {
        if (!is_declared)
            std::cout << "Matrix is empty" << std::endl;

        else if (!is_initialized)
            std::cout << "Matrix is " << rows << "x" << columns << std::endl << "Using this matrix without initialization might give errors" << std::endl;

        else {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < columns; j++)
                    std::cout << data[i][j] << " ";
                std::cout << std::endl;
            }
        }
    }
    // Matrix operator + (Matrix& A, Matrix B);
    // Matrix operator - (Matrix& A, Matrix B);
    // Matrix operator * (Matrix& A, Matrix B);
    // Matrix operator / (Matrix& A, Matrix B);
    // Matrix inv();
};