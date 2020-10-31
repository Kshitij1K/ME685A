#include "integration.hpp"
#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;


// This is the function to be integrated, it can be easily changed
double function (double x) {
    return x*exp(-x);
}

int main() {

    //Creation of object of Integration class (definition given in header file)
    Integration integral(&function, 0, 3);
    
    //Printing output with proper formatting. Calculation of Analytical Solution is in Analyitcal.pdf
    cout.precision(10);
    std::cout << left << setw(6) << "N" << setw(15) << "Exact" << setw(15) << "Trapezoidal" << "Simpson's Rule" << endl;
    std::cout << left << setw(6) << 5 << setw(15) << 1 - 4*exp(-3) << setw(15) << integral.trapezoidal(5) << integral.simpsons(5) << endl;
    std::cout << left << setw(6) << 11 << setw(15) << 1 - 4*exp(-3) << setw(15) << integral.trapezoidal(11) << integral.simpsons(11) << endl;
    std::cout << left << setw(6) << 41 << setw(15) << 1 - 4*exp(-3) << setw(15) << integral.trapezoidal(41) << integral.simpsons(41) << endl;
    std::cout << left << setw(6) << 101 << setw(15) << 1 - 4*exp(-3) << setw(15) << integral.trapezoidal(101) << integral.simpsons(101) << endl;

    return 0;
}
