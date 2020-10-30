#include "matrix.hpp"

template <class m_type>
Matrix<m_type> Matrix<m_type>::transpose() {
    Matrix<m_type> result(columns, rows);
    
    for (long int i = 0; i < columns; i++) {
        for (long int j = 0; j < rows; j++) {
            result[i][j] = data[j][i];
        }
    }

    return result;
}

template <class m_type>
Matrix<m_type> Matrix<m_type>::identity(long int numrows) {
    Matrix<m_type> result(numrows, numrows);
    for (long int i = 0; i < numrows; i++) {
        for (long int j = 0; j < numrows; j++) {
            result[i][j] = (i == j) ? 1 : 0;
        }
    }
    return result;
}

template <class m_type>
Matrix<m_type> Matrix<m_type>::gjinverse() {
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

    for (long int i = 0; i < rows; i++) {
        if (copy[i][i] == 0) {
            std::invalid_argument e("Matrix is non-invertible. Aborting.");
            throw e;
        } 
        for (long int j = 0; j < rows; j++) {
            result[i][j] /= copy[i][i];
        }
    }

    return result;
}

template <class m_type>
m_type Matrix<m_type>::det() {
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