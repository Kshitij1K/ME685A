#pragma once

#include <iostream>
#include <vector>

template<class m_type> class Matrix {
  protected:
    long int rows = 0;
    long int columns = 0;
    
    std::vector<std::vector<m_type>> data;

  public:
    Matrix();
    ~Matrix();
    Matrix(long int rows, long int columns);
    Matrix(std::initializer_list<std::initializer_list<m_type>> list);

    void print();
    long int numrows();
    long int numcols();

    m_type* operator[](long int row);
    void operator=(Matrix<m_type> A);
    Matrix<m_type> operator+(Matrix<m_type> A);
    Matrix<m_type> operator-(Matrix<m_type> A);
    Matrix<m_type> operator*(Matrix<m_type> A);
    Matrix<m_type> operator/(Matrix<m_type> A);
    Matrix<m_type> operator-();
    Matrix<m_type> operator*(m_type scalar);

    Matrix<m_type> transpose();
    static Matrix<m_type> identity(long int numrows);
    Matrix<m_type> gjinverse();
    m_type det();

};