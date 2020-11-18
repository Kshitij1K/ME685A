#pragma once

#include <iostream>
#include <vector>

// This is the template for the Matrix class. I have tried to make it as versatile as possible,
// so that it can be used anywhere with anything, with minimal effort.
// The template variable m_type specifies the datatype of the elements of the Matrix (which can
// be real number, complex number, other matrices, anything really)
template<class m_type> class Matrix {
  protected:
    // This is the number of rows and columns of the matrix
    long int rows = 0;
    long int columns = 0;

  public:
    // This is how the actual data is stored, as a c++ vector of  vectors.
    std::vector<std::vector<m_type>> data;

    Matrix(){};

    ~Matrix(){};

    // Just sets the number of rows and columns of the matrix
    Matrix(long int rows, long int columns) {
        this->rows = rows;
        this->columns = columns;

        data.resize(rows);
        for (long int i = 0; i < rows; i++) data[i].resize(columns);
    }

    // Can be used to initialize the matrix with values, like this {{1,2,4...}, {2,3,4,...}, ...}
    // Size is calculated automatically in this case
    Matrix(std::initializer_list<std::initializer_list<m_type>> list) {
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

    // Just for printing the matrix values
    void print() {
        if (rows == 0)
            std::cout << "Matrix is empty" << std::endl;

        else {
            for (long int i = 0; i < rows; i++) {
                for (long int j = 0; j < columns; j++) std::cout << data[i][j] << " ";
                std::cout << std::endl;
            }
        }
    }

    // Returns the number of rows and columns
    long int numrows() {
        return rows;
    }

    long int numcols() {
        return columns;
    }

    // Next, there will be a lot of operator overloads, so that Matrix operations can be carried out naturally like we do with other datatypes
    // For example, the overloaded + operator allows us to use the expression A+B to get the sum of the 2 matrices.

    // Returns the pointer to the rowth row of the matrix, which can again be dereferenced to get the value at any element [row][column].
    // This makes it very easy to work with elements, as you can simply use M[i][j] to get the (i+1)-(j+1)th element of M
    m_type* operator[](long int row) {
        return data[row].data();
    }

    // Adds 2 matrices together, and returns the result. Matrices must be of the same dimensions, otherwise an exception will be thrown.
    Matrix<m_type> operator+(Matrix<m_type> A) {
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

    // Subtracts 2 matrices together, and returns the result. Matrices must be of the same dimensions, otherwise an exception will be thrown.
    Matrix<m_type> operator-(Matrix<m_type> A) {
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

    // Multiples 2 matrices together, and returns the result. Matrices must be of the correct dimensions, otherwise an exception will be thrown.
    Matrix<m_type> operator*(Matrix<m_type> A) {
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

    // Divides the matrix by A, which is basically multiplying Ainverse with the current matrix
    // This isn't very useful, as everywhere we will be explicitly stating whether we are multiplying
    // the inverse. However since Newton-Raphson has a division step, I have included this overload
    // for it to be compatible with the division step.
    // It uses the Gauss Jordan Elimination method for the calculation of inverse.
    Matrix<m_type> operator/(Matrix<m_type> A) {
        return (A.gjinverse() * (*this));
    }

    // This does a unary negation, which is basically just multiplying each entry with -1
    Matrix<m_type> operator-() {
        Matrix<m_type> result(rows, columns);

        for (long int i = 0; i < rows; i++) {
            for (long int j = 0; j < columns; j++) {
                result[i][j] = data[i][j] * (-1);
            }
        }
        return result;
    }

    // Multiplies a scalar with this matrix. The scalar must be mentioned on the right side of *, for it to work
    Matrix<m_type> operator*(m_type scalar) {
        Matrix<m_type> result(rows, columns);

        for (long int i = 0; i < rows; i++) {
            for (long int j = 0; j < columns; j++) {
                result[i][j] = data[i][j] * scalar;
            }
        }

        return result;
    }

    // Returns the transpose
    Matrix<m_type> transpose() {
        Matrix<m_type> result(columns, rows);

        for (long int i = 0; i < columns; i++) {
            for (long int j = 0; j < rows; j++) {
                result[i][j] = data[j][i];
            }
        }

        return result;
    }

    // Returns an identity matrix of size numrows
    static Matrix<m_type> identity(long int numrows) {
        Matrix<m_type> result(numrows, numrows);
        for (long int i = 0; i < numrows; i++) {
            for (long int j = 0; j < numrows; j++) {
                result[i][j] = (i == j) ? 1 : 0;
            }
        }
        return result;
    }

    // This is the function that calculates the inverse of the matrix, using the Gauss-Jordan Elimination method.
    // The matrix must be square, otherwise an exception will be thrown.
    Matrix<m_type> gjinverse() {
        if (rows != columns) {
            std::invalid_argument e("Matrix is not square, cannot calculate inverse. Aborting.");
            throw e;
        }

        // The result matrix starts out as an identity matrix, and is modified accordingly as copy is modified using row operations.
        Matrix<m_type> result = Matrix<m_type>::identity(rows);
        Matrix<m_type> copy = (*this);

        // This block converts the matrix to Row Echelon form, while simultaneously applying the operations on result
        // If at any point the denominator in the factor becomes 0, it means that the matrix is not invertible.
        // So an exception is thrown if this occurs
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

        // Now it is converted to row-reduced echelon form
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

        // Finally, the matrix's diagonal elements are divided to get a unity matrix on the left side.
        // Note that I only divided the right side of the augmented matrix, as I know the left side will be unity, and I have no use for
        // that matrix
        for (long int i = 0; i < rows; i++) {
            for (long int j = 0; j < rows; j++) {
                result[i][j] /= copy[i][i];
            }
        }

        return result;
    }

    // This is the function that calculates the determinant of a matrix. It also uses row operations, to convert the matrix
    // to row-reduced echelon form, just like the Gauss Jordan Inverse, and then returns the product of all the diagonal elements
    // as the determinant. If at any point in the calculation, the denominator of the factor becomes 0, we know that the matrix is singular, and hence
    // 0 is returned.
    m_type det() {
        if (rows != columns) {
            std::invalid_argument e("Matrix is not square, cannot calculate determinant. Aborting.");
            throw e;
        }
        Matrix<m_type> copy = (*this);

        for (long int i = 0; i < (rows - 1); i++) {
            for (long int j = i + 1; j < rows; j++) {
                if (copy[i][i] == 0) return 0;
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

                if (copy[i][i] == 0) return 0;

                for (long int k = i; k < rows; k++) {
                    copy[j][k] += factor * copy[i][k];
                }
            }
            result *= copy[i][i];
        }

        return result * copy[0][0];
    }
};