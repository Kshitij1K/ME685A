/*
This is the class template for the Newton-Raphson method object.
This can be used with any type of function (single valued, vector valued, complex valued, anything really)

The templates are -
    f_type is the return type of the function
    d_type is the return type of the derivative of the function

The following functions are to be set by the user
    bool (*convergence) - This function returns whether the argument satisfies the convergence criteria or not (not required in this assignment)
    f_type (*function) - This returns the value of the function at the given argument
    d_type (*derivative) - This returns the value of the derivative of the function at the given argument
*/
template<class f_type, class d_type> class NR {
  protected:
    bool (*convergence)(f_type current);
    f_type (*function)(f_type var);
    d_type (*derivative)(f_type var);

  public:
    // Sets the function and derivative
    NR(f_type (*func)(f_type var), d_type (*derifunc)(f_type var)) {
        this->function = func;
        this->derivative = derifunc;
    }

    ~NR() {}

    // Sets the convergence check function. Not required in this assignment
    void setConvergence(bool (*convergence)(f_type current)) {
        this->convergence = convergence;
    }

    // Finds the root of the function, and takes the initial guess as the argument. Not required in this assignment
    f_type root(f_type initial) {
        while (!convergence(function(initial))) initial = (initial - (function(initial) / derivative(initial)));
        return initial;
    }

    // Returns the correction term for 1 iteration, given the guessed value.
    f_type correction(f_type initial) {
        return -(function(initial) / derivative(initial));
    }
};