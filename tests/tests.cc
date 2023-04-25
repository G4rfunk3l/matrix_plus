#include <gtest/gtest.h>

#include "../src/my_matrix_oop.h"

TEST(testing_constructors, test_1) {
  MyMatrix matrix_initial;
  MyMatrix matrix_with_fields(2, 2);
  MyMatrix matrix_moved = std::move(matrix_with_fields);
  MyMatrix matrix_copied(matrix_moved);
  ASSERT_TRUE(matrix_copied == matrix_moved);
  EXPECT_THROW(MyMatrix matrix_wrong(-1, -1), std::logic_error);
  EXPECT_THROW(MyMatrix matrix_wrong(matrix_wrong), std::out_of_range);
}

TEST(testing_equals, test_2) {
  double data_res[4] = {1, 2, 3, 4};
  double data_not_res[4] = {0};
  double data_wrong[6] = {0};
  MyMatrix matrix_true(2, 2, data_res);
  MyMatrix matrix_copied = matrix_true;
  MyMatrix matrix_false(2, 2, data_not_res);
  MyMatrix matrix_result(2, 2, data_res);
  MyMatrix matrix_wrong_params(3, 2, data_wrong);
  ASSERT_TRUE(matrix_true == matrix_result);
  ASSERT_TRUE(matrix_copied.EqMatrix(matrix_result));
  ASSERT_TRUE(matrix_false != matrix_result);
  ASSERT_FALSE(matrix_wrong_params.EqMatrix(matrix_result));
}

TEST(testing_sum, test_3) {
  double data_first[4] = {1, 2, 3, 4};
  double data_second[4] = {5, 6, 7, 8};
  double data_result[4] = {6, 8, 10, 12};
  double data_wrong[6] = {0};
  MyMatrix matrix_first(2, 2, data_first);
  MyMatrix matrix_second(2, 2, data_second);
  MyMatrix matrix_result(2, 2, data_result);
  MyMatrix matrix_wrong(2, 3, data_wrong);
  MyMatrix matrix_sum_2 = matrix_first;
  MyMatrix matrix_sum_1 = matrix_first + matrix_second;
  matrix_sum_2 += matrix_second;
  matrix_first.SumMatrix(matrix_second);
  ASSERT_TRUE(matrix_sum_1 == matrix_result);
  ASSERT_TRUE(matrix_sum_2 == matrix_result);
  ASSERT_TRUE(matrix_first == matrix_result);
  EXPECT_THROW(matrix_wrong.SumMatrix(matrix_first), std::out_of_range);
}

TEST(testing_sub, test_4) {
  double data_first[4] = {5, 6, 7, 8};
  double data_second[4] = {1, 2, 3, 4};
  double data_result[4] = {4, 4, 4, 4};
  double data_wrong[6] = {0};
  MyMatrix matrix_first(2, 2, data_first);
  MyMatrix matrix_second(2, 2, data_second);
  MyMatrix matrix_result(2, 2, data_result);
  MyMatrix matrix_wrong(2, 3, data_wrong);
  MyMatrix matrix_sub_2 = matrix_first;
  MyMatrix matrix_sub_1 = matrix_first - matrix_second;
  matrix_sub_2 -= matrix_second;
  matrix_first.SubMatrix(matrix_second);
  ASSERT_TRUE(matrix_sub_1 == matrix_result);
  ASSERT_TRUE(matrix_sub_2 == matrix_result);
  ASSERT_TRUE(matrix_first == matrix_result);
  EXPECT_THROW(matrix_wrong.SubMatrix(matrix_first), std::out_of_range);
}

TEST(testing_mul_number, test_5) {
  double data_mul_nums[6] = {1, 2, 3, 4, 5, 6};
  double data_mul_nums_result[6] = {3, 6, 9, 12, 15, 18};
  MyMatrix matrix_first(2, 3, data_mul_nums);
  MyMatrix matrix_second = matrix_first;
  MyMatrix matrix_result(2, 3, data_mul_nums_result);
  MyMatrix matrix_third = 3 * matrix_first;
  ASSERT_TRUE(matrix_first * 3 == matrix_result);
  matrix_first *= 3;
  matrix_second.MulNumber(3);
  ASSERT_TRUE(matrix_first == matrix_result);
  ASSERT_TRUE(matrix_second == matrix_result);
  ASSERT_TRUE(matrix_third == matrix_result);
}

TEST(testing_mul_matrix, test_6) {
  double data_mul_matrix_1[6] = {1, 2, 3, 4, 5, 6};
  double data_mul_matrix_2[6] = {6, 5, 4, 3, 2, 1};
  double data_wrong[16] = {0};
  double data_mul_matrix_result[4] = {20, 14, 56, 41};
  MyMatrix matrix_first(2, 3, data_mul_matrix_1);
  MyMatrix matrix_second(3, 2, data_mul_matrix_2);
  MyMatrix matrix_third = matrix_first;
  MyMatrix matrix_wrong(4, 4, data_wrong);
  MyMatrix matrix_result(2, 2, data_mul_matrix_result);
  MyMatrix matrix_mul_matrix(2, 2);
  ASSERT_TRUE((matrix_first * matrix_second) == matrix_result);
  matrix_mul_matrix = matrix_first * matrix_second;
  matrix_first *= matrix_second;
  matrix_third.MulMatrix(matrix_second);
  ASSERT_TRUE(matrix_mul_matrix == matrix_result);
  ASSERT_TRUE(matrix_first == matrix_result);
  ASSERT_TRUE(matrix_third == matrix_result);
  EXPECT_THROW(matrix_wrong.MulMatrix(matrix_second), std::logic_error);
}

TEST(testing_transpose, test_7) {
  double data_initial[6] = {1, 2, 3, 4, 5, 6};
  double data_result[6] = {1, 4, 2, 5, 3, 6};
  MyMatrix matrix_initial(2, 3, data_initial);
  MyMatrix matrix_result(3, 2, data_result);
  MyMatrix matrix_transposed = matrix_initial.Transpose();
  ASSERT_TRUE(matrix_transposed == matrix_result);
}

TEST(testing_complements, test_8) {
  double data_initial[9] = {1, 2, 4, 4, 8, 6, 11, 8, 9};
  double data_unit[1] = {56};
  double data_wrong[6] = {0};
  double data_result[9] = {24, 30, -56, 14, -35, 14, -20, 10, 0};
  double data_result_unit[1] = {1};
  MyMatrix matrix_initial(3, 3, data_initial);
  MyMatrix matrix_unit(1, 1, data_unit);
  MyMatrix matrix_wrong(2, 3, data_wrong);
  MyMatrix matrix_result(3, 3, data_result);
  MyMatrix matrix_result_unit(1, 1, data_result_unit);
  MyMatrix matrix_complemented = matrix_initial.CalcComplements();
  ASSERT_TRUE(matrix_complemented == matrix_result);
  ASSERT_TRUE(matrix_unit.CalcComplements() == matrix_result_unit);
  EXPECT_THROW(matrix_wrong.CalcComplements(), std::logic_error);
}

TEST(testing_determinant, test_9) {
  double data_initial[9] = {1, 2, 4, 4, 8, 6, 11, 8, 9};
  double data_unit[1] = {56};
  double data_wrong[6] = {0};
  MyMatrix matrix_initial(3, 3, data_initial);
  MyMatrix matrix_unit(1, 1, data_unit);
  MyMatrix matrix_wrong(2, 3, data_wrong);
  double result = -140.0;
  double result_unit = 56.0;
  ASSERT_TRUE(matrix_initial.Determinant() == result);
  ASSERT_TRUE(matrix_unit.Determinant() == result_unit);
  EXPECT_THROW(matrix_wrong.Determinant(), std::logic_error);
}

TEST(testing_inverse, test_10) {
  double data_initial[9] = {1, 2, 4, 4, 8, 6, 11, 8, 9};
  double data_zero_determinant[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double data_wrong[6] = {0};
  double data_result[9] = {-0.1714286, -0.1, 0.1428571, -0.2142857, 0.25,
                           -0.0714286, 0.4,  -0.1,      0};
  MyMatrix matrix_initial(3, 3, data_initial);
  MyMatrix matrix_zero_determinant(3, 3, data_zero_determinant);
  MyMatrix matrix_wrong(2, 3, data_wrong);
  MyMatrix matrix_result(3, 3, data_result);
  MyMatrix matrix_inversed = matrix_initial.InverseMatrix();
  ASSERT_TRUE(matrix_inversed == matrix_result);
  EXPECT_THROW(matrix_wrong.InverseMatrix(), std::logic_error);
  EXPECT_THROW(matrix_zero_determinant.InverseMatrix(), std::logic_error);
}

TEST(testing_getters_and_setters, test_11) {
  double data[9] = {1, 2, 4, 4, 8, 6, 11, 8, 9};
  MyMatrix matrix(3, 3, data);
  int getted_row = matrix.get_rows();
  int getted_col = matrix.get_cols();
  ASSERT_TRUE(getted_row == 3);
  ASSERT_TRUE(getted_col == 3);
  matrix.set_col(4);
  matrix.set_row(5);
  ASSERT_TRUE(matrix.get_rows() == 5);
  ASSERT_TRUE(matrix.get_cols() == 4);
  matrix.set_col(3);
  matrix.set_row(3);
  ASSERT_TRUE(matrix.get_rows() == 3);
  ASSERT_TRUE(matrix.get_cols() == 3);
}

TEST(testing_brackets_operators, test_12) {
  double data[9] = {1, 2, 4, 4, 8, 6, 11, 8, 9};
  MyMatrix matrix(3, 3, data);
  const MyMatrix matrix_const(3, 3, data);
  matrix(1, 1) = 8;
  double elem = matrix(1, 1);
  double elem_const = matrix_const(1, 1);
  ASSERT_TRUE(elem == 8);
  ASSERT_TRUE(elem_const == 1);
  EXPECT_THROW(matrix(4, 4), std::out_of_range);
  EXPECT_THROW(matrix(0, 1), std::out_of_range);
  EXPECT_THROW(matrix_const(4, 4), std::out_of_range);
  EXPECT_THROW(matrix_const(0, 1), std::out_of_range);
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}