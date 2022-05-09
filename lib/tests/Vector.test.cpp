#include "../Vector.h"

#include <gtest/gtest.h>

TEST(VectorTest, BasicConstructor) {
  Vector<int> v;
  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.capacity(), 0);
}
