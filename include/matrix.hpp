#pragma once

#include <iostream>
template<class m_type> class Matrix {
  protected:
    long int rows = 0;
    long int columns = 0;
    m_type** data;

  public:
    Matrix()
        : data(NULL){};

    ~Matrix(){
        // if (rows !=0) {
        //     for (long int i = 0; i < rows; i++) {
        //         delete data[i];
        //     }

        //     delete data;
        // }
    };

    Matrix(long int rows, long int columns) {
        this->rows = rows;
        this->columns = columns;

        data = new m_type*[rows];
        for (long int i = 0; i < rows; i++)
            data[i] = new m_type[columns];
    }

    Matrix(std::initializer_list<std::initializer_list<m_type>> list) {
        this->columns = (long int) (list.begin())->size();
        ;
        this->rows = (long int) list.size();

        data = new m_type*[rows];

        for (long int i = 0; i < rows; i++) {
            data[i] = new m_type[columns];
            for (long int j = 0; j < columns; j++) {
                data[i][j] = ((list.begin() + i)->begin())[j];
            }
        }
    }

    void print() {
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

    long int numrows() {
        return rows;
    }

    long int numcols() {
        return columns;
    }

    m_type* operator[](long int row) {
        return data[row];
    }

    Matrix<m_type> operator+(Matrix<m_type>& A) {
        if (this->rows != A.numrows() || this->columns != A.numcols()) {
            std::out_of_range e("The dimensions of the matrix do not match, while addition. Aborting.");
            throw e;
        }

        Matrix<m_type> result(this->rows, this->columns);
        for (long int i = 0; i < A.rows; i++) {
            for (long int j = 0; j < A.columns; j++) {
                result[i][j] = A[i][j] + data[i][j];
            }
        }

        return result;
    }

    Matrix<m_type> operator-(Matrix<m_type>& A) {
        if (this->rows != A.numrows() || this->columns != A.numcols()) {
            std::out_of_range e("The dimensions of the matrix do not match, while subtraction. Aborting.");
            throw e;
        }

        Matrix<m_type> result(this->rows, this->columns);
        for (long int i = 0; i < A.rows; i++) {
            for (long int j = 0; j < A.columns; j++) {
                result[i][j] = data[i][j] - A[i][j];
            }
        }

        return result;
    }

    Matrix<m_type> operator*(Matrix<m_type>& A) {
        if (this->columns != A.numrows()) {
            std::invalid_argument e("The dimensions of the matrix do not match, while multiplication. Aborting.");
            throw e;
        }

        Matrix<m_type> result(this->rows, A.numcols());

        for (long int i = 0; i < this->rows; i++) {
            for (long int j = 0; j < A.numcols(); j++) {
                result[i][j] = 0;
                for (long int k = 0; k < A.numrows(); k++) {
                    result[i][j] += (data[i][k] * A[k][j]);
                }
            }
        }

        return result;
    }

    Matrix<m_type> operator/(Matrix<m_type>& A) {
        return (*this) * (A.inverse());
    }

    void operator=(Matrix<m_type> A) {
        if (rows != 0) {
            for (long int i = 0; i < rows; i++) {
                delete[] data[i];
            }

            delete[] data;
        }

        rows = A.numrows();
        columns = A.numcols();

        data = new m_type*[rows];

        for (long int i = 0; i < rows; i++) {
            data[i] = new m_type[columns];
            for (long int j = 0; j < columns; j++) {
                data[i][j] = A[i][j];
            }
        }
    }

    Matrix<m_type> transpose() {
        Matrix<m_type> result(columns, rows);

        for (int i = 0; i < columns; i++) {
            for (int j = 0; j < rows; j++) {
                result[i][j] = data[j][i];
            }
        }

        return result;
    }

    Matrix<m_type> operator*(m_type scalar) {
        Matrix<m_type> result(rows, columns);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                result[i][j] = data[i][j] * scalar;
            }
        }

        return result;
    }

    static Matrix<m_type> identity(long int numrows) {
        Matrix<m_type> result(numrows, numrows);
        for (int i = 0; i < numrows; i++) {
            for (int j = 0; j < numrows; j++) {
                result[i][j] = (i == j) ? 1 : 0;
            }
        }
        return result;
    }

    Matrix<m_type> gjinverse() {
        if (rows != columns) {
            std::invalid_argument e("Matrix is not square, cannot calculate inverse. Aborting.");
            throw e;
        }
        Matrix<m_type> result = Matrix<m_type>::identity(rows);
        Matrix<m_type> copy = (*this);

        for (long int i = 0; i < (rows - 1); i++) {
            for (long int j = i + 1; j < rows; j++) {
                if (copy[i][i] == 0) {
                    std::invalid_argument e("Matrix is non-invertible. Aborting.");
                    throw e;
                }
                m_type factor = -copy[j][i] / copy[i][i];
                for (long int k = 0; k < rows; k++) {
                    copy[j][k] += factor * copy[i][k];
                    result[j][k] += factor * result[i][k];
                }
            }
        }

        for (long int i = rows - 1; i > 0; i--) {
            for (long int j = i - 1; j >= 0; j--) {
                if (copy[i][i] == 0) {
                    std::invalid_argument e("Matrix is non-invertible. Aborting.");
                    throw e;
                }                
                m_type factor = -copy[j][i] / copy[i][i];
                for (long int k = 0; k < rows; k++) {
                    copy[j][k] += factor * copy[i][k];
                    result[j][k] += factor * result[i][k];
                }
            }
        }

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < rows; j++) {
                result[i][j] /= copy[i][i];
            }
        }

        return result;
    }

    m_type det() {
        if (rows != columns) {
            std::invalid_argument e("Matrix is not square, cannot calculate determinant. Aborting.");
            throw e;
        }
        Matrix<m_type> copy = (*this);

        for (long int i = 0; i < (rows - 1); i++) {
            for (long int j = i + 1; j < rows; j++) {
                if (copy[i][i] == 0) {
                    std::invalid_argument e("Matrix is singular. Aborting.");
                    throw e;
                }
                m_type factor = -copy[j][i] / copy[i][i];
                for (long int k = i; k < rows; k++) {
                    copy[j][k] += factor * copy[i][k];
                }
            }
        }

        m_type result = 1;

        for (long int i = rows - 1; i > 0; i--) {
            for (long int j = i - 1; j >= 0; j--) {
                m_type factor = -copy[j][i] / copy[i][i];

                if (copy[i][i] == 0) {
                    std::invalid_argument e("Matrix is singular. Aborting.");
                    throw e;
                }

                for (long int k = i; k < rows; k++) {
                    copy[j][k] += factor * copy[i][k];
                }
            }
            result *= copy[i][i];
        }

        return result * copy[0][0];
    }
};