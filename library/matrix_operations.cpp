    #include "matrix.hpp"
    
    template <class m_type>
    m_type* Matrix<m_type>::operator[](long int row) {
        return data[row].data();
    }

    template <class m_type>
    Matrix<m_type> Matrix<m_type>::operator+(Matrix<m_type> A) {
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

    template <class m_type>
    Matrix<m_type> Matrix<m_type>::operator-(Matrix<m_type> A) {
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

    template <class m_type>
    Matrix<m_type> Matrix<m_type>::operator*(Matrix<m_type> A) {
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

    template <class m_type>
    Matrix<m_type> Matrix<m_type>::operator/(Matrix<m_type> A) {
        return (A.gjinverse()*(*this));
    }

    template <class m_type>
    void Matrix<m_type>::operator=(Matrix<m_type> A) {
        rows = A.numrows();
        columns = A.numcols();

        data.resize(rows);

        for (long int i = 0; i < rows; i++) {
            data[i].resize(columns);
            for (long int j = 0; j < columns; j++) {
                data[i][j] = A[i][j];
            }
        }
    }

    template <class m_type>
    Matrix<m_type> Matrix<m_type>::operator- () {
        Matrix<m_type> result(rows, columns);

        for (long int i = 0; i < rows; i++) {
            for (long int j = 0; j < columns; j++) {
                result[i][j] = data[i][j] * (-1);
            }
        }
        result.print();
        return result;        
    }

    template <class m_type>
    Matrix<m_type> Matrix<m_type>::operator*(m_type scalar) {
        Matrix<m_type> result(rows, columns);

        for (long int i = 0; i < rows; i++) {
            for (long int j = 0; j < columns; j++) {
                result[i][j] = data[i][j] * scalar;
            }
        }

        return result;
    } 