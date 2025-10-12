#include "tmatrix.h"
#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
  TDynamicMatrix<int> m(2);
  m[0][0] = 1, m[0][1] = 2, m[1][0] = 3, m[1][1] = 4;
  TDynamicMatrix m1(m);
  EXPECT_EQ(m, m1);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
  TDynamicMatrix<int> m(2);
  m[0][0] = 1, m[0][1] = 2, m[1][0] = 3, m[1][1] = 4;
  TDynamicMatrix m1(m);
  m1[0][0] = 1010;
  EXPECT_NE(m[0][0], m1[0][0]);
}

TEST(TDynamicMatrix, can_get_size)
{
  TDynamicMatrix<int> m(4);
  EXPECT_EQ(4, m[0].size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
  TDynamicMatrix<int> m(2);
  m[0][0] = 5;
  EXPECT_EQ(5, m[0][0]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
  TDynamicMatrix<int> m(2);
  EXPECT_THROW(m[0].at(-1), std::out_of_range);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
  TDynamicMatrix<int> m(3);
  EXPECT_THROW(m[0].at(3), std::out_of_range);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
  TDynamicMatrix<int> m(2);
  m[0][0] = 1, m[0][1] = 2, m[1][0] = 3, m[1][1] = 4;
  ASSERT_NO_THROW(m = m);
  EXPECT_EQ(2, m.size());
  EXPECT_EQ(1, m[0][0]);
  EXPECT_EQ(2, m[0][1]);
  EXPECT_EQ(3, m[1][0]);
  EXPECT_EQ(4, m[1][1]);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
  TDynamicMatrix<int> m1(2), m2(2);
  m1[0][0]=1, m1[0][1]=2, m1[1][0]=3, m1[1][1]=4;
  m2 = m1;
  EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
  TDynamicMatrix<int> m1(2), m2(3);
  m1[0][0] = 7, m1[0][1] = 8,  m1[1][0] = 9, m1[1][1] = 10;
  m2 = m1;
  EXPECT_EQ(2, m2.size());
  EXPECT_EQ(7, m1[0][0]);
  EXPECT_EQ(10, m1[1][1]);
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
  TDynamicMatrix<int> a(2), b(4);
  a[0][0] = 1, a[0][1] = 2, a[1][0] = 3, a[1][1] = 4;
  ASSERT_NO_THROW(b = a);
  EXPECT_EQ(a, b);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
  TDynamicMatrix<int> a(2), b(2);
  a[0][0]=1, a[0][1]=2, a[1][0]=3, a[1][1]=4;
  b[0][0]=1, b[0][1]=2, b[1][0]=3, b[1][1]=4;
  EXPECT_TRUE(a == b);
  EXPECT_FALSE(a != b);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
  TDynamicMatrix<int> a(2);
  a[0][0] = 1, a[0][1] = 2, a[1][0] = 3, a[1][1] = 4;
  EXPECT_TRUE(a == a);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
  TDynamicMatrix<int> a(2), b(3);
  EXPECT_FALSE(a == b);
  EXPECT_TRUE(a != b);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
  TDynamicMatrix<int> a(2), b(2);
  a[0][0]=1, a[0][1]=2, a[1][0]=3, a[1][1]=4;
  b[0][0]=1, b[0][1]=2, b[1][0]=3, b[1][1]=4;
  TDynamicMatrix<int> c = a + b;
  EXPECT_EQ(2, c[0][0]);
  EXPECT_EQ(4, c[0][1]);
  EXPECT_EQ(6, c[1][0]);
  EXPECT_EQ(8, c[1][1]);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
  TDynamicMatrix<int> a(2), b(3);
  EXPECT_ANY_THROW(a + b);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
  TDynamicMatrix<int> a(2), b(2);
  a[0][0]=1, a[0][1]=2, a[1][0]=3, a[1][1]=4;
  b[0][0]=5, b[0][1]=6, b[1][0]=7, b[1][1]=8;
  TDynamicMatrix<int> c = a - b;
  EXPECT_EQ(-4, c[0][0]);
  EXPECT_EQ(-4, c[0][1]);
  EXPECT_EQ(-4, c[1][0]);
  EXPECT_EQ(-4, c[1][1]);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
  TDynamicMatrix<int> a(2), b(4);
  EXPECT_ANY_THROW(a - b);
}

TEST(TDynamicMatrix, can_multiply_matrix_by_scalar)
{
  TDynamicMatrix<int> a(2);
  a[0][0] = 1, a[0][1] = 2, a[1][0] = 3, a[1][1] = 4;
  TDynamicMatrix<int> b = a * 2;
  EXPECT_EQ(2, b[0][0]);
  EXPECT_EQ(4, b[0][1]);
  EXPECT_EQ(6, b[1][0]);
  EXPECT_EQ(8, b[1][1]);
}

TEST(TDynamicMatrix, can_multiply_matrix_by_vector)
{
  TDynamicMatrix<int> a(2);
  a[0][0] = 1, a[0][1] = 2, a[1][0] = 3, a[1][1] = 4;
  TDynamicVector<int> b(2);
  b[0] = 5, b[1] = 6;
  TDynamicVector<int> c = a * b;
  EXPECT_EQ(17, c[0]);
  EXPECT_EQ(39, c[1]);
}

TEST(TDynamicMatrix, can_multiply_matrices_with_equal_size)
{
  TDynamicMatrix<int> a(2), b(2);
  a[0][0]=1, a[0][1]=2, a[1][0]=3, a[1][1]=4;
  b[0][0]=5, b[0][1]=6, b[1][0]=7, b[1][1]=8;
  TDynamicMatrix<int> c = a * b;
  EXPECT_EQ(19, c[0][0]);
  EXPECT_EQ(22, c[0][1]);
  EXPECT_EQ(43, c[1][0]);
  EXPECT_EQ(50, c[1][1]);
}

TEST(TDynamicMatrix, stream_input_output_roundtrip)
{
  TDynamicMatrix<int> out(2);
  out[0][0]=1, out[0][1]=2, out[1][0]=3, out[1][1]=4;
  std::stringstream ss;
  ss << out;
  TDynamicMatrix<int> in(2);
  ss >> in;
  EXPECT_EQ(out, in);
}

