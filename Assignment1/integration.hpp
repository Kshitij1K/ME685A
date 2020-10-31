#include <stdexcept>

/*
This is the Integration class, for carrying out integration of a function using numerical methods. Its variables are :-
--> function := The pointer to the function to be integrated
--> num_points := Number of points in the numerical approximation
--> lower_limit := Lower limit of the integration
--> upper_limit := Upper limit of the integration
*/

class Integration {
  private:
    double (*function)(double x);
    long int num_points;
    double lower_limit;
    double upper_limit;

  public:

    // Constructor function of the class. Sets the values of the function, upper_limit and lower_limit variable properly. 
    Integration(double (*function)(double x), double lower_limit, double upper_limit) {
        this->function = function;
        this->upper_limit = upper_limit;
        this->lower_limit = lower_limit;
    }

    //Function for carrying out integration of the function between the given bounds, using trapezoidal approximation. Takes the number of points as the argument
    double trapezoidal(long int num_points) {

        // Calculate the step size
        double delta_x = (upper_limit - lower_limit) / (num_points - 1);
        
        // Initial value of result is f1
        double result = function(lower_limit);

        // Loop carries out the summation part. Note that i of this loop corresponds to the i+1 in the formula (the first element is i=0, added above)
        for (int i = 1; i < num_points - 1; i++) {
            result += (2 * function(lower_limit + delta_x * i));
        }

        // Returns the value obtained after adding fN and multiplying by the required factor
        return ((result + function(upper_limit)) * delta_x) / 2;
    }

    //Function for carrying out integration of the function between the given bounds, using Simpson's 1/3 rule. Takes the number of points as the argument
    double simpsons(long int num_points) {
        
        // The umber of points must be an odd number, else the Simpson's rule doesn't work. Throw an error if the number of points given is even
        if (!(num_points % 2)) {
            std::invalid_argument e("The number of points for applying Simpson's 1/3 rule must be odd, whereas the number of points given is even. Aborting.");
            throw e;
        }

        // Calculate the step size
        double delta_x = (upper_limit - lower_limit) / (num_points - 1);
        
        // Initial value of result is f1
        double result = function(lower_limit);

        // Loop carries out the summation part. Note that i of this loop corresponds to the i+1 in the formula (the first element is i=0, added above)
        // The alternate 2 and 4 factors appearing in the formula have been taken care of. 
        for (int i = 1; i < num_points - 1; i++) {
            result += (2 * (1 + (i % 2)) * function(lower_limit + delta_x * i));
        }

        // Returns the value obtained after adding fN and multiplying by the required factor
        return ((result + function(upper_limit)) * delta_x) / 3;
    }
};