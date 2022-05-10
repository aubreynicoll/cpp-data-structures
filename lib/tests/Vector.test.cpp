#include "../Vector.h"

#include <gtest/gtest.h>

TEST(VectorTest, BasicConstructor) {
  Vector<int> v;

  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.capacity(), 0);
  EXPECT_TRUE(v.is_empty());
}

TEST(VectorTest, SizedConstructor) {
  Vector<int> v(10);

  EXPECT_EQ(v.size(), 10);
  EXPECT_EQ(v.capacity(), 10);
  EXPECT_FALSE(v.is_empty());

  int *p = v.data();
  for (size_t i = 0; i < v.size(); i++) {
    EXPECT_EQ(*(p + i), 0);
  }
}

TEST(VectorTest, FillConstructor) {
  Vector<int> v(10, 99);

  EXPECT_EQ(v.size(), 10);
  EXPECT_EQ(v.capacity(), 10);
  EXPECT_FALSE(v.is_empty());

  int *p = v.data();
  for (size_t i = 0; i < v.size(); i++) {
    EXPECT_EQ(*(p + i), 99);
  }
}

TEST(VectorTest, Clear) {
  Vector<int> v(3, 0);

  v.clear();

  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.capacity(), 0);
  EXPECT_TRUE(v.data() == NULL);
}

TEST(VectorTest, Resize) {
  Vector<int> v;
  int *p;

  // trigger storage reallocation
  v.resize(10);
  EXPECT_EQ(v.size(), 10);
  EXPECT_EQ(v.capacity(), 10);

  p = v.data();
  for (size_t i = 0; i < v.size(); i++) {
    EXPECT_EQ(*(p + i), 0);
    *(p + i) = 1;  // should be erased when resizing up
  }

  // downsize shouldn't change capacity
  v.resize(0);
  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.capacity(), 10);

  // upsize less than capacity will only trigger zero-initialization
  v.resize(5);
  EXPECT_EQ(v.size(), 5);
  EXPECT_EQ(v.capacity(), 10);

  for (size_t i = 0; i < v.size(); i++) {
    EXPECT_EQ(*(p + i), 0);  // 1's turned into 0's
  }
}

TEST(VectorTest, FillResize) {
  Vector<int> v;
  int *p;

  // trigger storage reallocation
  v.resize(10, 99);
  EXPECT_EQ(v.size(), 10);
  EXPECT_EQ(v.capacity(), 10);

  p = v.data();
  for (size_t i = 0; i < v.size(); i++) {
    EXPECT_EQ(*(p + i), 99);
    *(p + i) = 1;  // should be erased when resizing up
  }

  // downsize shouldn't change capacity
  v.resize(0);
  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.capacity(), 10);

  // upsize less than capacity will only trigger value-initialization
  v.resize(5, 22);
  EXPECT_EQ(v.size(), 5);
  EXPECT_EQ(v.capacity(), 10);

  for (size_t i = 0; i < v.size(); i++) {
    EXPECT_EQ(*(p + i), 22);
  }
}

TEST(VectorTest, Reserve) {
  Vector<int> v;

  v.reserve(100);

  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.capacity(), 100);

  v.reserve(50);

  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.capacity(), 100);
}

TEST(VectorTest, At) {
  Vector<int> v(5, 99);
  EXPECT_EQ(v.at(0), 99);
  EXPECT_EQ(v.at(v.size() - 1), 99);

  // expect out-of-bounds errors
  EXPECT_ANY_THROW(v.at(-1));
  EXPECT_ANY_THROW(v.at(v.size()));
}

TEST(VectorTest, Assign) {
  Vector<int> v(2);
  int *p;

  v.assign(0, 99);
  v.assign(1, 5);

  p = v.data();

  EXPECT_EQ(*p, 99);
  EXPECT_EQ(*(p + 1), 5);

  // expect out-of-bounds errors
  EXPECT_ANY_THROW(v.assign(-1, 1));
  EXPECT_ANY_THROW(v.assign(v.size(), 1));
}

TEST(VectorTest, Insert) {
  Vector<int> v(3, 99);

  EXPECT_EQ(v.capacity(), 3);

  v.insert(v.size(), 101);
  v.insert(0, 1234);

  // Triggers reallocation if capacity is too little
  EXPECT_EQ(v.capacity(), 6);

  int *p = v.data();
  EXPECT_EQ(*(p + 0), 1234);
  EXPECT_EQ(*(p + 1), 99);
  EXPECT_EQ(*(p + 2), 99);
  EXPECT_EQ(*(p + 3), 99);
  EXPECT_EQ(*(p + 4), 101);

  // Expect out-of-bounds errors
  EXPECT_ANY_THROW(v.insert(-1, 1));
  EXPECT_ANY_THROW(v.insert(v.size() + 1, 1));
}

TEST(VectorTest, Remove) {
  Vector<int> v(3);
  int *p = v.data();

  for (size_t i = 0; i < v.size(); i++) {
    *(p + i) = i;
  }

  int a = v.remove(0);
  int b = v.remove(v.size() - 1);

  EXPECT_EQ(v.size(), 1);
  EXPECT_EQ(v.capacity(), 3);
  EXPECT_EQ(*p, 1);

  // check that values are valid after memory is freed
  v.clear();
  EXPECT_EQ(a, 0);
  EXPECT_EQ(b, 2);
}

TEST(VectorTest, Push) {
  Vector<int> v;
  for (size_t i = 0; i < 3; i++) {
    v.push(i);
  }

  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v.capacity(), 4);

  int *p = v.data();
  for (size_t i = 0; i < 3; i++) {
    EXPECT_EQ(*(p + i), i);
  }
}

TEST(VectorTest, Pop) {
  Vector<int> v(2, 99);

  EXPECT_EQ(v.pop(), 99);
  EXPECT_EQ(v.pop(), 99);

  EXPECT_ANY_THROW(v.pop());

  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.capacity(), 2);
}

TEST(VectorTest, IndexOf) {
  Vector<int> v(100);
  int *p = v.data();
  for (size_t i = 0; i < v.size(); i++) {
    *(p + i) = i;
  }

  EXPECT_EQ(v.index_of([](int n) -> bool { return n == 5; }), 5);

  EXPECT_EQ(v.index_of([](int n) -> bool { return n == -5; }), -1);
}

TEST(VectorTest, Reverse) {
  Vector<int> v(100);
  int *p;

  p = v.data();
  for (size_t i = 0; i < 100; i++) {
    *(p + i) = i;
  }

  v.reverse();

  for (size_t i = 0; i < 100; i++) {
    EXPECT_EQ(*(p + i), 99 - i);
  }
}

TEST(VectorTest, Swap) {
  Vector<int> v1(5, 100);
  Vector<int> v2(6, 20);
  int *p;

  v1.swap(v2);

  EXPECT_EQ(v1.size(), 6);
  EXPECT_EQ(v1.capacity(), 6);
  p = v1.data();
  for (size_t i = 0; i < v1.size(); i++) {
    EXPECT_EQ(*(p + i), 20);
  }

  EXPECT_EQ(v2.size(), 5);
  EXPECT_EQ(v2.capacity(), 5);
  p = v2.data();
  for (size_t i = 0; i < v2.size(); i++) {
    EXPECT_EQ(*(p + i), 100);
  }
}
