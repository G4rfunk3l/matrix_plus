# my_matrix_oop.h
My own realization of matrix data type (used by C++ language, OOP methodology) for Mac and Linux.
Here are my attempts to understand operator overloading and OOP programming methodology.
For build static library do make all, for tests do make test.
Usage of library like in tests.c.
A matrix is a collection of numbers arranged into a fixed number of rows and columns.
## Realized methods
### Constructors and destructors
- Default constructor (MyMatrix())
- Parameterized constructor (MyMatrix(int rows, int cols))
- Copy constructor (MyMatrix(const MyMatrix& other))
- Move constructor (MyMatrix(MyMatrix&& other))
- Constructor for creating a matrix of given sizes filled with given values (for tests) (MyMatrix(int rows, int cols, const double data[]))
- Destructor (~MyMatrix())
### Getters
- Method returning the number of rows (int get_rows() const)
- Method returning the number of columns (int get_cols() const)
### Setters
- Method to set the number of rows (int set_rows() const)
- Method to set the number of columns (int set_cols() const)
### Comparision
- Method for comparing two matrices (bool EqMatrix(const MyMatrix& other) const)
- 0 - FAILURE
- 1 - SUCCESS
### Algebraic operations
- Method for adding two matrices (void SumMatrix(const MyMatrix& other))
- Method for subtract two matrices (void SubMatrix(const MyMatrix& other))
- Method for multiplying matrix by scalar (void MulNumber(const double num))
- Method for multiplying two matrices (void MulMatrix(const MyMatrix& other))
- Method for transposing matrix (MyMatrix Transpose() const)
- Method for calculation algebraic complements (MyMatrix CalcComplements())
- Method for calculation determinant of matrix (double Determinant())
- Method for inverse matrix (MyMatrix InverseMatrix())
### Operators overloads
- ==(equal)
- !=(not equal)
- +(addition)
- -(substraction)
- *(multiplication)
- =(value assignment)
- +=(addition assignments)
- -=(substraction assignments)
- *=(multiplication assignment)
- ()(interaction with the value inside the cell)
### Private methods
- Calculation of matrix of minors (MyMatrix GetMinor(int rows, int cols) const)
- Utility method of matrix cleaning (void Clear())
- Utility method of matrix creating (void CreateMatrix())