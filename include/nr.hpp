#pragma once

#include <unistd.h>
template<class f_typ, class d_type> class NR {
  protected:
    bool (*convergence)(f_typ current);
    f_typ (*function)(f_typ var);
    d_type (*derivative)(f_typ var);

  public:
    NR(f_typ (*func)(f_typ var), d_type (*derifunc) (f_typ var)) {
        this->function = func;
        this->derivative = derifunc;     
    }
    ~NR() {
    }

    f_typ ddx(f_typ var) {
        return derivative(var);
    }

    void print(f_typ var) {
        std::cout << derivative(var) << std::endl;
    }

    void setConvergence(bool (*convergence)(f_typ current)) {
        this->convergence = convergence;
    }

    f_typ root(f_typ initial) {
        while (!convergence(function(initial))) initial = (initial - (function(initial)/derivative(initial)));

        return initial;
    }
};