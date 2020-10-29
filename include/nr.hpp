#include <unistd.h>
template<class f_typ, class d_type> class NR {
  protected:
    f_typ convergence;
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

    void setConvergence(f_typ convergence) {
        this->convergence = convergence;
    }

    f_typ root(f_typ initial) {
        while (function(initial) > convergence || function(initial) < (-convergence)) {
            // derivative(initial).gjinverse().print();
            // f_typ error = (derivative(initial).gjinverse())*function(initial);
            d_type ddx = derivative(initial);
            f_typ fx = function(initial);
            d_type error = fx/ddx;
            // (myass*myass2).print();;
            error.print();
            initial.print();
            std::cout << std::endl;
            // error.print();
            // f_typ k = (initial - error);
            // sleep(2);
            break;
            // break;
        }

        return initial;
    }
};