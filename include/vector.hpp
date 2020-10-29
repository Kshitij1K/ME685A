#pragma once

#include "math.h"
#include "matrix.hpp"

template<class v_type> class Vector : public Matrix<v_type> {
  protected:
    bool use_custom_sqrt = false;
    v_type (*sqroot)(v_type var);

  public:
    Vector() {
    }
    Vector(std::initializer_list<v_type> list) {
        this->rows = (long int) list.size();
        this->columns = 1;
        this->data.resize(this->rows);

        for (long int i = 0; i < this->rows; i++) {
            this->data[i].resize(1);
            this->data[i][0] = list.begin()[i];
        }
    }

    Vector(long int row) : Matrix<v_type> (row, 1){}

    void operator=(Vector<v_type> A) {
        this->rows = A.numrows();
        this->columns = 1;

        this->data.resize(this->rows);

        for (long int i = 0; i < this->rows; i++) {
            this->data[i].resize(this->columns);
            this->data[i][0] = A[i][0];
        }
    }

    Vector(Matrix<v_type> M) {
        if (M.numcols() != 1) {
            std::invalid_argument e("Argument isn't a column matrix, cannot convert to vector. Aborting");
            throw e;
        }

        this->rows = M.numrows();
        this->columns = 1;

        this->data.resize(this->rows);
        for (long int i = 0; i < this->rows; i++) {
            this->data[i].resize(1);
            this->data[i][0] = M[i][0];
        }
    }
    
    ~Vector() {
        
    }

    v_type norm() {
        v_type result = 0;
        for (long int i = 0; i < this->rows; i++) {
            result += this->data[i][0] * this->data[i][0];
        }
        if (!use_custom_sqrt)
            return v_type(sqrt(result));
        else
            return sqroot(result);
    }
 
    void set_sqrt(v_type (*sqrootfun)(v_type var)) {
        sqroot = sqrootfun;
        use_custom_sqrt = true;
    }
};