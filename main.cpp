#include <iostream>
#include "include/matrix.hpp"
#include "vector.hpp"
#include "include/nr.hpp"

Vector<double> func(Vector<double> Q) {
    Vector<double> result(2);
    result[0][0] = Q[0][0] + Q[1][0]*Q[1][0] - 5;
    result[1][0] = Q[0][0]*Q[1][0] - 2;
    return result;
}

Matrix<double> derivfunc(Vector<double> Q) {
    double dQ = 0.01;
    // return (func(Q + dQ*0.5) - func(Q - dQ*0.5))/dQ;
    Matrix<double> J(Q.numrows(), Q.numrows());
    // Matrix<double> J(2,2);
    J[0][0] = 1;
    J[0][1] = 2*Q[1][0];
    J[1][0] = Q[1][0];
    J[1][1] = Q[0][0];
    // Q.print();
    return J;
}

bool converge(Vector<double> inp) {
    double norm = inp.norm();
    return fabs(norm) < 0.001;
}

int main() {
    Matrix<double> M = {{2,0,0}, {0, -2, 0}, {0, 0, 1}};
    // double result = M.det();
    // Matrix<double> result2 = M.gjinverse();
    // Matrix<int> K = {{1,0}};
    // Matrix<double> N = M.transpose();
    // Matrix<int> N = {{1}, {2}, {3}};
    // Matrix<int> K(2,3);
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
    // Vector<int> bruh = {6,8};
    // std::cout << bruh.norm();
    // result2.print();
    // std::cout << result << std::endl;
    Vector<double> initial = {0.25, 0.5};
    // Vector<double> converge = {0.001, 0.001};
    NR<Vector<double>, Matrix<double>> pipeflow(&func, &derivfunc);

    pipeflow.setConvergence(&converge);
    // initial.print();
    pipeflow.root(initial).print();
    // derivfunc(initial);
    return 0;
}