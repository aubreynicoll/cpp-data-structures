#include "../CircularBuffer.h"

#include <gtest/gtest.h>

TEST(CircularBufferTest, SizeConstructor) {
  EXPECT_NO_FATAL_FAILURE(CircularBuffer<int> buf(4));
}

TEST(CircularBufferTest, Mutators) {
  CircularBuffer<int> buf(2);
  buf.push_back(1);
  buf.push_back(2);
  EXPECT_ANY_THROW(buf.push_back(3));  // Too full
  buf.pop_front();
  buf.pop_front();
  EXPECT_ANY_THROW(buf.pop_front());  // Empty
}

TEST(CircularBufferTest, Accessors) {
  CircularBuffer<int> buf(2);
  EXPECT_ANY_THROW(buf.front());  // Empty
  EXPECT_ANY_THROW(buf.back());   // Empty

  buf.push_back(1);
  EXPECT_EQ(buf.front(), 1);
  EXPECT_EQ(buf.back(), 1);

  buf.push_back(2);
  EXPECT_EQ(buf.front(), 1);
  EXPECT_EQ(buf.back(), 2);

  buf.pop_front();
  EXPECT_EQ(buf.front(), 2);
  EXPECT_EQ(buf.back(), 2);

  buf.pop_front();
  EXPECT_ANY_THROW(buf.front());  // Empty
  EXPECT_ANY_THROW(buf.back());   // Empty
}

TEST(CircularBufferTest, Utilities) {
  CircularBuffer<int> buf(2);
  EXPECT_EQ(buf.size(), 0);
  EXPECT_EQ(buf.capacity(), 2);
  EXPECT_TRUE(buf.is_empty());
  EXPECT_FALSE(buf.is_full());

  buf.push_back(1);
  EXPECT_EQ(buf.size(), 1);
  EXPECT_EQ(buf.capacity(), 2);
  EXPECT_FALSE(buf.is_empty());
  EXPECT_FALSE(buf.is_full());

  buf.push_back(1);
  EXPECT_EQ(buf.size(), 2);
  EXPECT_EQ(buf.capacity(), 2);
  EXPECT_FALSE(buf.is_empty());
  EXPECT_TRUE(buf.is_full());

  buf.pop_front();
  EXPECT_EQ(buf.size(), 1);
  EXPECT_EQ(buf.capacity(), 2);
  EXPECT_FALSE(buf.is_empty());
  EXPECT_FALSE(buf.is_full());

  buf.pop_front();
  EXPECT_EQ(buf.size(), 0);
  EXPECT_EQ(buf.capacity(), 2);
  EXPECT_TRUE(buf.is_empty());
  EXPECT_FALSE(buf.is_full());
}

TEST(CircularBufferTest, Clear) {
  CircularBuffer<int> buf(2);
  buf.push_back(1);
  buf.push_back(2);
  buf.clear();

  EXPECT_EQ(buf.size(), 0);
  EXPECT_EQ(buf.capacity(), 2);
  EXPECT_TRUE(buf.is_empty());
  EXPECT_FALSE(buf.is_full());
}

TEST(CircularBufferTest, Swap) {
  CircularBuffer<int> bufA(2);
  CircularBuffer<int> bufB(4);

  bufA.push_back(1);
  bufA.push_back(2);

  bufB.push_back(9);

  bufA.swap(bufB);

  EXPECT_EQ(bufA.front(), 9);
  EXPECT_EQ(bufA.back(), 9);
  EXPECT_EQ(bufA.size(), 1);
  EXPECT_EQ(bufA.capacity(), 4);

  EXPECT_EQ(bufB.front(), 1);
  EXPECT_EQ(bufB.back(), 2);
  EXPECT_EQ(bufB.size(), 2);
  EXPECT_EQ(bufB.capacity(), 2);
}
