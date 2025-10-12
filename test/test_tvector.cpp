#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(10);
  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
  TDynamicVector<int> v(3);
  v[0] = 1; v[1] = 2; v[2] = 3;
  TDynamicVector<int> v1(v);
  EXPECT_EQ(v, v1);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
  TDynamicVector<int> v(3);
  v[0] = 1; v[1] = 2; v[2] = 3;
  TDynamicVector<int> v1(v);
  v1[0] = 123;
  EXPECT_NE(v[0], v1[0]);
  EXPECT_EQ(1, v[0]);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(23);
  EXPECT_EQ(23, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
  TDynamicVector<int> v(21);
  v[5] = 42;
  EXPECT_EQ(42, v[5]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
  TDynamicVector<int> v(31);
  EXPECT_THROW(v.at(-1), std::out_of_range);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
  TDynamicVector<int> v(2);
  EXPECT_THROW(v.at(33), std::out_of_range);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
  TDynamicVector<int> v(3);
  v[0] = 1; v[1] = 2; v[2] = 3;
  ASSERT_NO_THROW(v = v);
  EXPECT_EQ(1, v[0]);
  EXPECT_EQ(2, v[1]);
  EXPECT_EQ(3, v[2]);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
  TDynamicVector<int> v(3), vc(3);
  v[0] = 1; v[1] = 2; v[2] = 3;
  vc = v;
  EXPECT_EQ(v, vc);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
  TDynamicVector<int> v(3), vc(5);
  v[0] = 1; v[1] = 2; v[2] = 3;
  vc = v;
  EXPECT_EQ(3, vc.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
  TDynamicVector<int> v(3), vc(5);
  v[0] = 123; v[1] = 234; v[2] = 345;

  vc = v;
  EXPECT_EQ(3, vc.size());
  EXPECT_EQ(v, vc);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
  TDynamicVector<int> v(3), vc(3);
  v[0] = 1; v[1] = 2; v[2] = 3;
  vc[0] = 1; vc[1] = 2; vc[2] = 3;

  EXPECT_TRUE(v == vc);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
  TDynamicVector<int> v(2);
  v[0] = 42; v[1] = 21;

  EXPECT_TRUE(v == v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
  TDynamicVector<int> v1(3);
  TDynamicVector<int> v2(5);

  EXPECT_TRUE(v1 != v2);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
  TDynamicVector<int> v(3);
  v[0] = 1; v[1] = 2; v[2] = 3;

  TDynamicVector<int> res = v + 123;

  EXPECT_EQ(124, res[0]);
  EXPECT_EQ(125, res[1]);
  EXPECT_EQ(126, res[2]);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
  TDynamicVector<int> v(3);
  v[0] = 5; v[1] = 6; v[2] = 7;

  TDynamicVector<int> result = v - 2;

  EXPECT_EQ(3, result[0]);
  EXPECT_EQ(4, result[1]);
  EXPECT_EQ(5, result[2]);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
  TDynamicVector<float> v(3);
  v[0] = 1.0f; v[1] = 2.0f; v[2] = 3.0f;

  TDynamicVector<float> res = v * 3.0f;

  EXPECT_EQ(3.0, res[0]);
  EXPECT_EQ(6.0, res[1]);
  EXPECT_EQ(9.0, res[2]);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
  TDynamicVector<int> v1(3), v2(3);
  v1[0] = 1; v1[1] = 2; v1[2] = 3;
  v2[0] = 4; v2[1] = 5; v2[2] = 6;

  TDynamicVector<int> res = v1 + v2;

  EXPECT_EQ(5, res[0]);
  EXPECT_EQ(7, res[1]);
  EXPECT_EQ(9, res[2]);}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
  TDynamicVector<int> v1(3);
  TDynamicVector<int> v2(2);
  v1[0]=123, v1[1] = 412, v1[2] = 322;
  v2[0]=1, v2[1] = 3333;

  EXPECT_ANY_THROW(v1 + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
  TDynamicVector<int> v1(3), v2(3);
  v1[0] = 5; v1[1] = 7; v1[2] = 9;
  v2[0] = 1; v2[1] = 2; v2[2] = 3;

  TDynamicVector<int> res = v1 - v2;

  EXPECT_EQ(4, res[0]);
  EXPECT_EQ(5, res[1]);
  EXPECT_EQ(6, res[2]);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
  TDynamicVector<int> v1(3);
  TDynamicVector<int> v2(5);

  EXPECT_ANY_THROW(v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
  TDynamicVector<int> v1(3), v2(3);
  v1[0] = 1; v1[1] = 2; v1[2] = 3;
  v2[0] = 4; v2[1] = 5; v2[2] = 6;

  int res = v1 * v2;

  EXPECT_EQ(32, res);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
  TDynamicVector<int> v1(3), v2(5);

  EXPECT_ANY_THROW(v1 * v2);
}

TEST(TDynamicVector, move_constructor)
{
  TDynamicVector<int> from(3);
  from[0] = 3; from[1] = 2; from[2] = 1;
  TDynamicVector from_copy(from);
  TDynamicVector to(std::move(from));
  EXPECT_EQ(from_copy, to);
  EXPECT_EQ(0, from.size());
}

TEST(TDynamicVector, move_assignment)
{
  TDynamicVector<int> v(4), v1(2);
  v[0]=11; v[1]=12; v[2]=13; v[3]=14;
  v1[0]=1; v1[1]=2;
  v1 = std::move(v);
  EXPECT_EQ(4, v1.size());
  EXPECT_EQ(11, v1[0]);
  EXPECT_EQ(12, v1[1]);
  EXPECT_EQ(13, v1[2]);
  EXPECT_EQ(14, v1[3]);
  EXPECT_EQ(0, v.size());
}

TEST(TDynamicVector, swap_exchange_content)
{
  TDynamicVector<int> v1(2), v2(3);
  v1[0]=1; v1[1]=2;
  v2[0]=10; v2[1]=20; v2[2]=30;
  swap(v1, v2);
  EXPECT_EQ(3u, v1.size());
  EXPECT_EQ(2u, v2.size());
  EXPECT_EQ(10, v1[0]);
  EXPECT_EQ(20, v1[1]);
  EXPECT_EQ(30, v1[2]);
  EXPECT_EQ(1, v2[0]);
  EXPECT_EQ(2, v2[1]);
}

TEST(TDynamicVector, stream_input_output)
{
  TDynamicVector<int> v(3);
  v[0]=42; v[1]=43; v[2]=44;
  std::stringstream ss;
  ss << v;
  TDynamicVector<int> v1(3);
  ss >> v1;
  EXPECT_EQ(v, v1);
}

TEST(TDynamicVector, float_eq_no_eps)
{
  TDynamicVector<float> v(3), v1(3);
  v[0] = 1.00000; v[1] = 2.00000; v[2] = 3.00000;
  v1[0] = 1.000000004; v1[1] = 1.999999999; v1[2] = 3.00000005;
  EXPECT_TRUE(v == v1);
}

TEST(TDynamicVector, float_neq_w_eps)
{
  TDynamicVector<float> v1(2), v2(2);
  v1[0] = 1.0f; v1[1] = 2.0f;
  v2[0] = 1.0f + 1e-4f;
  v2[1] = 2.0f;
  EXPECT_FALSE(v1 == v2);
  EXPECT_TRUE(v1 != v2);
}

TEST(TDynamicVector, const_indexing)
{
  TDynamicVector<int> v(2);
  v[0] = 123; v[1] = 234;
  const TDynamicVector<int>& crv = v;
  EXPECT_EQ(123, crv[0]);
  EXPECT_EQ(234, crv[1]);
}

