// Copyright 2021 Your Name <your_email>

#include <gtest/gtest.h>

#include <sharedptrtests.hpp>
#include <stdexcept>

TEST(Example, EmptyTest) { EXPECT_THROW(example(), std::runtime_error); }

TEST(shared_pointer, initNull) {
  SharedPtr<int> ex;
  ASSERT_EQ(ex.use_count(), 0);
}

TEST(shared_pointer, reset) {
  int a = 1;
  SharedPtr<int> ex(&a);
  ex.reset();
  ASSERT_EQ(ex.use_count(), 0);
}

TEST(shares_pointer, initLink) {
  int a = 1;
  SharedPtr<int> ex(&a);
  ASSERT_EQ(ex.get(), &a);
}
//
TEST(shared_pointer, swap) {
  int a = 1;
  int b = 2;
  SharedPtr<int> ex_a(&a);
  SharedPtr<int> ex_b(&b);
  ex_a.swap(ex_b);
  ASSERT_EQ(ex_a.get(), &b);
}
