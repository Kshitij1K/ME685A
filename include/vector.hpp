#pragma once

#include "math.h"
#include "matrix.hpp"

template<class v_type> class Vector : public Matrix<v_type> { 
    protected:
        bool use_custom_sqrt = false;
        v_type (*sqroot)(v_type var);
    
    public: 
        Vector(std::initializer_list<v_type> list) {
            this->rows = (long int) list.size();
            this->columns = 1;
            this->data = new v_type*[this->rows];

            for (long int i = 0; i < this->rows; i++) {
                this->data[i] = new v_type;
                this->data[i][0] = list.begin()[i];
            }
        }

        Vector(long int rows) {
        this->rows = rows;
        this->columns = 1;
        this->data = new v_type*[rows];
        for (long int i = 0; i < rows; i++)
            this->data[i] = new v_type;
        }

        v_type norm() {
            v_type result = 0;
            for (long int i=0; i<this->rows; i++) {
                result += this->data[i][0]*this->data[i][0];
            }
            if (!use_custom_sqrt) return v_type(sqrt(result));
            else return sqroot(result); 
        }

        void set_sqrt(v_type (*sqrootfun)(v_type var)) {
            sqroot = sqrootfun;
            use_custom_sqrt = true;
        }

};