#include "../BST.h"

#include <gtest/gtest.h>

#include <iostream>
#include <vector>

using namespace std;

TEST(BSTTest, BasicConstructor) { BST<int> bst; }

TEST(BSTTest, Utilities) {
  BST<int> bst;

  EXPECT_EQ(bst.size(), 0);
  EXPECT_TRUE(bst.is_empty());

  bst.insert(10);

  EXPECT_EQ(bst.size(), 1);
  EXPECT_FALSE(bst.is_empty());

  bst.insert(9);

  EXPECT_EQ(bst.size(), 2);
  EXPECT_FALSE(bst.is_empty());

  bst.insert(11);

  EXPECT_EQ(bst.size(), 3);
  EXPECT_FALSE(bst.is_empty());
}

TEST(BSTTest, InsertAndSearch) {
  BST<int> bst;
  vector<int> nums{55, 45, 78, 99, 101, 1, 15, 66, 34, 3};

  for (auto &num : nums) {
    EXPECT_FALSE(bst.search(num));
  }

  for (auto &num : nums) {
    bst.insert(num);
  }

  for (auto &num : nums) {
    EXPECT_TRUE(bst.search(num));
  }
}

TEST(BSTTest, Accessors) {
  BST<int> bst;
  vector<int> nums{55, 45, 78, 99, 101, 1, 15, 66, 34, 3};

  for (auto &num : nums) {
    EXPECT_FALSE(bst.search(num));
  }

  EXPECT_ANY_THROW(bst.min());
  EXPECT_ANY_THROW(bst.max());

  for (auto &num : nums) {
    bst.insert(num);
  }

  EXPECT_EQ(bst.min(), 1);
  EXPECT_EQ(bst.max(), 101);

  EXPECT_EQ(bst.predecessor(3), 1);
  EXPECT_EQ(bst.predecessor(101), 99);
  EXPECT_EQ(bst.predecessor(82), 78);
  EXPECT_EQ(bst.predecessor(1000), 101);
  EXPECT_ANY_THROW(bst.predecessor(1));

  EXPECT_EQ(bst.successor(1), 3);
  EXPECT_EQ(bst.successor(-1), 1);
  EXPECT_EQ(bst.successor(21), 34);
  EXPECT_EQ(bst.successor(78), 99);
  EXPECT_ANY_THROW(bst.successor(101));
}

TEST(BSTTest, Swap) {
  BST<int> a, b;
  a.insert(11);
  a.insert(3);
  a.insert(77);
  a.insert(8);

  b.insert(88);
  b.insert(-1);
  b.insert(1000000);

  a.swap(b);

  EXPECT_EQ(a.min(), -1);
  EXPECT_EQ(a.max(), 1000000);
  EXPECT_EQ(a.size(), 3);

  EXPECT_EQ(b.min(), 3);
  EXPECT_EQ(b.max(), 77);
  EXPECT_EQ(b.size(), 4);
}

TEST(BSTTest, Erase) {
  BST<int> bst;
  vector<int> nums{55, 45, 78, 99, 101, 1, 15, 66, 34, 3};

  for (auto &num : nums) {
    bst.insert(num);
  }

  EXPECT_EQ(bst.size(), nums.size());

  bst.erase(55);
  bst.erase(bst.min());
  bst.erase(bst.max());

  EXPECT_EQ(bst.size(), nums.size() - 3);

  EXPECT_FALSE(bst.search(55));
  EXPECT_FALSE(bst.search(1));
  EXPECT_FALSE(bst.search(101));
}
