#ifndef MY_MATRIXPLUS_MY_MATRIX_OOP_H__
#define MY_MATRIXPLUS_MY_MATRIX_OOP_H__

#include <cmath>
#include <iostream>

constexpr double EPS = 1e-7;

class MyMatrix {
 public:
  // конструктор по умолчанию, вызывается при создании объекта
  MyMatrix();
  // конструктор для создания матрицы заданных размеров
  MyMatrix(int rows, int cols);
  // конструктор копирования
  MyMatrix(const MyMatrix& other);
  // конструктор перемещения
  MyMatrix(MyMatrix&& other);
  /* конструктор для создания матрицы заданных размеров, заполненных заданными
   * значениями (для тестов) */
  MyMatrix(int rows, int cols, const double data[]);
  // деструктор
  ~MyMatrix();

  // метод возвращает количество строк
  int get_rows() const;
  // метод возвращает количество столбцов
  int get_cols() const;
  // метод устанавливает количество строк в матрице
  void set_row(int rows);
  // метод устанавливает количество столбцов в матрице
  void set_col(int cols);

  // метод сравнения матриц
  bool EqMatrix(const MyMatrix& other) const;
  // метод сложения матриц
  void SumMatrix(const MyMatrix& other);
  // метод вычитания матриц
  void SubMatrix(const MyMatrix& other);
  // метод умножения матрицы на число
  void MulNumber(const double num);
  // метод умножения матрицы на матрицу
  void MulMatrix(const MyMatrix& other);
  // метод транспонирования матрицы
  MyMatrix Transpose() const;
  // метод вычисления матрицы алгебраических дополнений текущей матрицы
  MyMatrix CalcComplements();
  // метод вычисления детерминанта текущей матрицы
  double Determinant();
  // метод вычисления обратной матрицы
  MyMatrix InverseMatrix();

  // перегрузка операторa ==
  bool operator==(const MyMatrix& other) const;
  // перегрузка операторa !=
  bool operator!=(const MyMatrix& other) const;
  // перегрузка операторa +
  MyMatrix operator+(const MyMatrix& other);
  // перегрузка операторa -
  MyMatrix operator-(const MyMatrix& other);
  // перегрузка операторa * (матрица на матрицу)
  MyMatrix operator*(const MyMatrix& other);
  // перегрузка операторa * (матрица на число)
  friend MyMatrix operator*(const MyMatrix& other, const double other_double);
  // перегрузка операторa * (число на матрицу)
  friend MyMatrix operator*(const double other_double, const MyMatrix& other);
  // перегрузка операторa =
  MyMatrix& operator=(const MyMatrix& other);
  // перегрузка операторa +=
  MyMatrix& operator+=(const MyMatrix& other);
  // перегрузка операторa -=
  MyMatrix& operator-=(const MyMatrix& other);
  // перегрузка операторa *= (на матрицу)
  MyMatrix& operator*=(const MyMatrix& other);
  // перегрузка операторa *= (на число)
  MyMatrix& operator*=(const double other);
  // перегрузка операторa () (не const, можно поменять значение внутри ячейки)
  double& operator()(int row, int col);
  // перегрузка операторa () (const, нельзя поменять значение внутри ячейки)
  double operator()(int row, int col) const;

 private:
  // параметры матрицы
  int rows_, cols_;
  double** matrix_;

  // служебный метод создания матрицы
  void CreateMatrix();
  // служебный метод удаления матрицы
  void Clear();
  // служебный метод нахождения минора матрицы
  MyMatrix GetMinor(int rows, int cols) const;
};

#endif  // MY_MATRIXPLUS_MY_MATRIX_OOP_H__