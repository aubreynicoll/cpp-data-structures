#include "../HashMapV1.h"

#include <gtest/gtest.h>

TEST(HashMapTest, EmptyInitialization) {
  HashMap<char, int> map;
  EXPECT_EQ(map.size(), 0);
  EXPECT_EQ(map.capacity(), 0);
}

TEST(HashMapTest, HandlesAlphabet) {
  HashMap<char, int> map;
  EXPECT_EQ(map.size(), 0);
  EXPECT_EQ(map.capacity(), 0);

  for (int i = 0; i < 26; i++) {
    EXPECT_FALSE(map.has('a' + i));
    EXPECT_ANY_THROW(map.get('a' + i));
  }

  for (int i = 0; i < 26; i++) {
    map.insert('a' + i, i);
  }

  EXPECT_EQ(map.size(), 26);
  EXPECT_EQ(map.capacity(), 32);

  for (int i = 0; i < 26; i++) {
    EXPECT_TRUE(map.has('a' + i));
    EXPECT_EQ(map.get('a' + i), i);
  }

  for (int i = 0; i < 26; i++) {
    map.erase('a' + i);
  }

  EXPECT_EQ(map.size(), 0);
  EXPECT_EQ(map.capacity(), 32);

  for (int i = 0; i < 26; i++) {
    EXPECT_FALSE(map.has('a' + i));
    EXPECT_ANY_THROW(map.get('a' + i));
  }
}

TEST(HashMapTest, NoDuplicateKeys) {
  HashMap<int, int> map;
  map.insert(0, 0);
  map.insert(0, 1);

  EXPECT_EQ(map.size(), 1);
  EXPECT_EQ(map.get(0), 1);
}
