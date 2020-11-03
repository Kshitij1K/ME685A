#include <iostream>

class Integration {
  private:
    double (*function)(double x);
    long int num_points;
    double lower_limit;
    double upper_limit;
    double delta_x;

  public:
    Integration() {
    }
    Integration(double (*function)(double x), double lower_limit, double upper_limit) {
        this->function = function;
        this->upper_limit = upper_limit;
        this->lower_limit = lower_limit;
    }

    double trapezoidal(long int num_points) {
        delta_x = (upper_limit - lower_limit) / (num_points - 1);
        double result = function(lower_limit);
        for (int i = 1; i < num_points - 1; i++) {
            result += (2 * function(lower_limit + delta_x * i));
        }

        return ((result + function(upper_limit)) * delta_x) / 2;
    }

    double simpsons(long int num_points) {
        delta_x = (upper_limit - lower_limit) / (num_points - 1);
        double result = function(lower_limit);

        if (!(num_points % 2)) {
            std::invalid_argument e("The number of points for applying Simpson's 1/3 rule must be odd, whereas the number of points given is even. Aborting.");
            throw e;
        }

        for (int i = 1; i < num_points - 1; i++) {
            result += (2 * (1 + (i % 2)) * function(lower_limit + delta_x * i));
        }

        return ((result + function(upper_limit)) * delta_x) / 3;
    }
};