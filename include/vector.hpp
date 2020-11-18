#pragma once

#include "math.h"
#include "matrix.hpp"

// This is the template for the Vector class, which is derived from the Matrix class.
// Since a vector is essentially a column matrix, I have inherited the properties of the Matrix class
// However, I have also written a few extra methods, like the calculation of norm.
template<class v_type> class Vector : public Matrix<v_type> {
  protected:
    // These variables are just used for defining a custom square root function, which comes in handy if you are using custom datatypes
    // in Vectors, like Complex numbers. In these cases, the C/C++ sqrt() function will not work, and a custom function for the calculation
    // of sqrt needs to be specified.
    bool use_custom_sqrt = false;
    v_type (*sqroot)(v_type var);

  public:
    Vector() {}

    // Can initialize a vector like this {1,3,4, ....}
    Vector(std::initializer_list<v_type> list) {
        this->rows = (long int) list.size();
        this->columns = 1;
        this->data.resize(this->rows);

        for (long int i = 0; i < this->rows; i++) {
            this->data[i].resize(1);
            this->data[i][0] = list.begin()[i];
        }
    }

    // Can also initialize a vector with length row (which is basically a row x 1 matrix)
    Vector(long int row)
        : Matrix<v_type>(row, 1) {}

    // A given column matrix maybe converted to a vector with this method. Number of columns should be 1.
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

    ~Vector() {}

    // Returns the norm of the vector.
    // Uses either the sqrt() built-in function, or a custom function if one is specified
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

    // This can be used to set the custom sqrt function, if the in-built sqrt cannot be used on the datatype.
    void set_sqrt(v_type (*sqrootfun)(v_type var)) {
        sqroot = sqrootfun;
        use_custom_sqrt = true;
    }
};