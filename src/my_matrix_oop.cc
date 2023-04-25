#include "my_matrix_oop.h"

MyMatrix::MyMatrix() {
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

MyMatrix::MyMatrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (cols <= 0 || rows <= 0) {
    throw std::invalid_argument("Incorrect input, parameters should be > 0");
  }
  CreateMatrix();
}

MyMatrix::MyMatrix(const MyMatrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  if (&other == this) {
    throw std::out_of_range(
        "Incorrect input, copying into itself is prohibited");
  }
  CreateMatrix();
  for (auto row = 0; row < rows_; row++) {
    for (auto col = 0; col < cols_; col++) {
      matrix_[row][col] = other.matrix_[row][col];
    }
  }
}

MyMatrix::MyMatrix(MyMatrix&& other) : rows_(other.rows_), cols_(other.cols_) {
  matrix_ = other.matrix_;
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

MyMatrix::MyMatrix(int rows, int cols, const double data[])
    : rows_(rows), cols_(cols) {
  CreateMatrix();
  int count = 0;
  for (int row = 0; row < rows_; row++) {
    for (int col = 0; col < cols_; col++) {
      matrix_[row][col] = data[count];
      count++;
    }
  }
}

MyMatrix::~MyMatrix() {
  if (matrix_) {
    Clear();
  }
  rows_ = 0;
  cols_ = 0;
}

int MyMatrix::get_rows() const { return rows_; }

int MyMatrix::get_cols() const { return cols_; }

void MyMatrix::set_row(int rows) {
  MyMatrix temp_matrix(rows, cols_);
  int temp = rows;
  if (rows_ < rows) {
    temp = rows_;
  }
  for (auto row = 0; row < temp; row++) {
    for (auto col = 0; col < cols_; col++) {
      temp_matrix.matrix_[row][col] = matrix_[row][col];
    }
  }
  Clear();
  rows_ = rows;
  CreateMatrix();
  for (auto row = 0; row < rows_; row++) {
    for (auto col = 0; col < cols_; col++) {
      matrix_[row][col] = temp_matrix.matrix_[row][col];
    }
  }
}

void MyMatrix::set_col(int cols) {
  MyMatrix temp_matrix(rows_, cols);
  int temp = cols;
  if (cols_ < cols) {
    temp = cols_;
  }
  for (auto row = 0; row < rows_; row++) {
    for (auto col = 0; col < temp; col++) {
      temp_matrix.matrix_[row][col] = matrix_[row][col];
    }
  }
  Clear();
  cols_ = cols;
  CreateMatrix();
  for (auto row = 0; row < rows_; row++) {
    for (auto col = 0; col < cols_; col++) {
      matrix_[row][col] = temp_matrix.matrix_[row][col];
    }
  }
}

bool MyMatrix::EqMatrix(const MyMatrix& other) const {
  bool result = true;
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    result = false;
  }
  if (result) {
    for (auto row = 0; row < rows_; row++) {
      for (auto col = 0; col < cols_; col++) {
        if (fabs(matrix_[row][col] - other.matrix_[row][col]) > EPS) {
          result = false;
          break;
        }
      }
      if (!result) {
        break;
      }
    }
  }
  return result;
}

void MyMatrix::SumMatrix(const MyMatrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  for (auto row = 0; row < rows_; row++) {
    for (auto col = 0; col < cols_; col++) {
      matrix_[row][col] = matrix_[row][col] + other.matrix_[row][col];
    }
  }
}

void MyMatrix::SubMatrix(const MyMatrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  for (auto row = 0; row < rows_; row++) {
    for (auto col = 0; col < cols_; col++) {
      matrix_[row][col] = matrix_[row][col] - other.matrix_[row][col];
    }
  }
}

void MyMatrix::MulNumber(const double num) {
  for (int row = 0; row < rows_; row++) {
    for (int col = 0; col < cols_; col++) {
      matrix_[row][col] = num * matrix_[row][col];
    }
  }
}

void MyMatrix::MulMatrix(const MyMatrix& other) {
  if (cols_ != other.rows_)
    throw std::logic_error(
        "Incorrect input, cols of 1st matrix should be same with rows of 2nd "
        "matrix");
  MyMatrix result(rows_, other.cols_);
  for (int row = 0; row < rows_; row++) {
    for (int col = 0; col < other.cols_; col++) {
      for (int count = 0; count < cols_; count++) {
        result.matrix_[row][col] +=
            matrix_[row][count] * other.matrix_[count][col];
      }
    }
  }
  cols_ = other.cols_;
  for (int row = 0; row < rows_; row++) {
    for (int col = 0; col < cols_; col++) {
      matrix_[row][col] = result.matrix_[row][col];
    }
  }
  result.Clear();
  result.rows_ = 0;
  result.cols_ = 0;
}

MyMatrix MyMatrix::Transpose() const {
  MyMatrix result(cols_, rows_);
  for (int row = 0; row < rows_; row++) {
    for (int col = 0; col < cols_; col++) {
      result.matrix_[col][row] = matrix_[row][col];
    }
  }
  return result;
}

MyMatrix MyMatrix::CalcComplements() {
  if (rows_ <= 0 || rows_ != cols_) {
    throw std::logic_error("Incorrect input, matrix should be square");
  }
  MyMatrix result(rows_, cols_);
  if (rows_ == 1) {
    result.matrix_[0][0] = 1.0;
  } else {
    for (auto row = 0; row < rows_; row++) {
      for (auto col = 0; col < cols_; col++) {
        MyMatrix minor_matrix = GetMinor(row, col);
        result.matrix_[row][col] =
            minor_matrix.Determinant() * (((row + col) % 2) ? -1 : 1);
      }
    }
  }
  return result;
}

double MyMatrix::Determinant() {
  if (rows_ <= 0 || rows_ != cols_) {
    throw std::logic_error("Incorrect input, matrix should be square");
  }
  double result = 0.0;
  if (rows_ == 1) {
    result = matrix_[0][0];
  } else {
    MyMatrix algebraic_additions = CalcComplements();
    for (auto row = 0; row < rows_; row++) {
      result += matrix_[row][0] * algebraic_additions.matrix_[row][0];
    }
  }
  return result;
}

MyMatrix MyMatrix::InverseMatrix() {
  if (rows_ <= 0 || rows_ != cols_) {
    throw std::logic_error("Incorrect input, matrix should be square");
  }
  if (Determinant() == 0) {
    throw std::logic_error("Determinant = 0, calculation inpossible");
  }
  MyMatrix result = CalcComplements().Transpose() * (1 / Determinant());
  return result;
}

bool MyMatrix::operator==(const MyMatrix& other) const {
  return EqMatrix(other);
}

bool MyMatrix::operator!=(const MyMatrix& other) const {
  return !EqMatrix(other);
}

MyMatrix MyMatrix::operator+(const MyMatrix& other) {
  MyMatrix result = (*this);
  result.SumMatrix(other);
  return result;
}

MyMatrix MyMatrix::operator-(const MyMatrix& other) {
  MyMatrix result = (*this);
  result.SubMatrix(other);
  return result;
}

MyMatrix MyMatrix::operator*(const MyMatrix& other) {
  MyMatrix result = (*this);
  result.MulMatrix(other);
  return result;
}

MyMatrix operator*(const MyMatrix& other, const double other_double) {
  MyMatrix result(other);
  result.MulNumber(other_double);
  return result;
}

MyMatrix operator*(const double other_double, const MyMatrix& other) {
  MyMatrix result(other);
  result.MulNumber(other_double);
  return result;
}

MyMatrix& MyMatrix::operator=(const MyMatrix& other) {
  if (this != &other) {
    Clear();
    rows_ = other.rows_;
    cols_ = other.cols_;
    CreateMatrix();
  }
  for (int row = 0; row < rows_; row++) {
    for (int col = 0; col < cols_; col++) {
      matrix_[row][col] = other.matrix_[row][col];
    }
  }
  return *this;
}

MyMatrix& MyMatrix::operator+=(const MyMatrix& other) {
  SumMatrix(other);
  return *this;
}

MyMatrix& MyMatrix::operator-=(const MyMatrix& other) {
  SubMatrix(other);
  return *this;
}

MyMatrix& MyMatrix::operator*=(const MyMatrix& other) {
  MulMatrix(other);
  return *this;
}

MyMatrix& MyMatrix::operator*=(const double other) {
  MulNumber(other);
  return *this;
}

double& MyMatrix::operator()(int row, int col) {
  if (row > rows_ || col > cols_ || row <= 0 || col <= 0) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  return matrix_[row-1][col-1];
}

double MyMatrix::operator()(int row, int col) const {
  if (row > rows_ || col > cols_ || row <= 0 || col <= 0) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  return matrix_[row-1][col-1];
}

void MyMatrix::CreateMatrix() {
  matrix_ = new double*[rows_];
  for (auto row = 0; row < rows_; row++) {
    matrix_[row] = new double[cols_]{0};
  }
}

void MyMatrix::Clear() {
  for (auto row = 0; row < rows_; row++) {
    delete matrix_[row];
  }
  delete matrix_;
  matrix_ = nullptr;
}

MyMatrix MyMatrix::GetMinor(int row_ignored, int col_ignored) const {
  MyMatrix minor_matrix(rows_ - 1, cols_ - 1);
  int row_minor = 0;
  for (auto row = 0; row < rows_; row++) {
    if (row != row_ignored) {
      int col_minor = 0;
      for (auto col = 0; col < cols_; col++) {
        if (col != col_ignored) {
          minor_matrix.matrix_[row_minor][col_minor++] = matrix_[row][col];
        }
      }
      row_minor++;
    }
  }
  return minor_matrix;
}
