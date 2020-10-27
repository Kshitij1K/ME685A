template <class m_type>
class Matrix {
  private:
    int rows;
    int columns;
    m_type** data;

  public:
    Matrix();
    ~Matrix();
    Matrix(int rows, int columns);
    Matrix(m_type* array_num, int rows, int columns);
    void print();
    // Matrix operator + (Matrix& A, Matrix B);
    // Matrix operator - (Matrix& A, Matrix B);
    // Matrix operator * (Matrix& A, Matrix B);
    // Matrix operator / (Matrix& A, Matrix B);
    // Matrix inv();
};