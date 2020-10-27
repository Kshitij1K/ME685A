#include "include/matrix.hpp"

int main() {
    int a[] = {1,2,3};

    Matrix<int> M(new int[8] {1,2,3,4,5,6,7,8}, 2, 4);
    M.print();
}