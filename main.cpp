#include <iostream>
#include "include/matrix.hpp"
#include <math.h>
// #include "include/vector.hpp"
// #include "include/nr.hpp"

double func(double Q) {
    // Vector<double> result(2);
    // result[0][0] = Q[0][0] + Q[1][0]*Q[1][0] - 5;
    // result[1][0] = Q[0][0]*Q[1][0] - 2;
    return ((5*log(Q) + 2)*Q*Q) - 9.06;
}

double derivfunc(double Q) {
    double dQ = 0.01;
    return (func(Q + dQ*0.5) - func(Q - dQ*0.5))/dQ;
    // Matrix<double> J(Q.numrows(), Q.numrows());
    // Matrix<double> J(2,2);
    // J[0][0] = 1;
    // J[0][1] = 2*Q[1][0];
    // J[1][0] = Q[1][0];
    // J[1][1] = Q[0][0];
    // Q.print();
    // return J;
}

bool check(double value) {
    // double norm = value.norm();

    if (fabs(value) < 0.001) return true;
    else return false;
}

int main() {
    Matrix<double> M = {{2,0,0}, {0, -2, 0}, {0, 0, 1}};
    // double result = M.det();
    // Matrix<double> result2 = M.gjinverse();
    // Matrix<int> K = {{1,0}};
    // Matrix<double> N = M.transpose();
    // Matrix<int> N = {{1}, {2}, {3}};
    // Matrix<double> K(2,3);
    // K.print();
    // catch (const char* msg) {
    //     std::cerr << msg << std::endl;
    //     return -1;
    // }
    // (M.gjinverse()*N).print();
    // N.print();
    // N.print();
    // NR<Matrix<int>> y(&yo);
    // Matrix<int> result = y.ddx(M);
    // result.print();
    // Vector<double> bruh = {6,8};
    // M.print();
    M.transpose();
    // std::cout << bruh.norm();
    // result2.print();
    // std::cout << result << std::endl;
    // Vector<double> initial = {0.25, 0.5};
    // std::cout << initial.numrows();
    // Vector<double> converge = {0.001, 0.001};
    // initial = initial - converge;
    // converge.print();
    // initial.print();
    // NR<double, double> pipeflow(&func, &derivfunc);

    // pipeflow.setComparison(&check);
    // pipeflow.setConvergence(&check);
    // initial.print();
    // std::cout << pipeflow.root(1.2);
    // derivfunc(initial);
    return 0;
}