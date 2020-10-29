#include <vector>
#include <iostream>
#include "include/matrix.hpp"
#include "include/vector.hpp"

int main() {
    // std::vector<std::vector<double>> yo;

    // yo.resize(2);
    // yo[0].resize(2);
    // yo[1].resize(2);
    // yo[0][0] = 1;
    // yo[0][1] = 2;
    // yo[1][0] = 3;
    // yo[1][1] = 4;

    // std::cout << yo[0][0] << std::endl;
    // std::cout << yo[0][1] << std::endl;
    // std::cout << yo[1][0] << std::endl;
    // std::cout << yo[1][1] << std::endl;
    Vector<double> N(2);
    Vector<double> M(2);
    N[0][0] = 2;
    N[1][0] = 9;
    M[0][0] = 11;
    M[1][0] = 13;


    (N - M).print();
    // Matrix<double> M = {{1,67,0}, {0, 1, 0.78}, {2.345, 0, 1}};
    // std::vector<double> q = M[0];
    // q[1] = 100;
    // std::cout << q[1] << std::endl;
    // N.print();

    return 0;
}