#include "../LinkedList.h"

#include <gtest/gtest.h>

TEST(LinkedListTest, BasicConstructor) {
  EXPECT_NO_FATAL_FAILURE(LinkedList<int> list);
}

TEST(LinkedListTest, Insert) {
  LinkedList<int> list;
  EXPECT_EQ(list.size(), 0);

  list.insert(0, 99);
  EXPECT_EQ(list.at(0), 99);
  EXPECT_EQ(list.size(), 1);

  list.insert(0, 101);
  EXPECT_EQ(list.at(0), 101);
  EXPECT_EQ(list.at(1), 99);
  EXPECT_EQ(list.size(), 2);

  list.insert(2, 1);
  EXPECT_EQ(list.at(0), 101);
  EXPECT_EQ(list.at(1), 99);
  EXPECT_EQ(list.at(2), 1);
  EXPECT_EQ(list.size(), 3);

  list.insert(1, 13);
  EXPECT_EQ(list.at(0), 101);
  EXPECT_EQ(list.at(1), 13);
  EXPECT_EQ(list.at(2), 99);
  EXPECT_EQ(list.at(3), 1);
  EXPECT_EQ(list.size(), 4);
}

TEST(LinkedListTest, Erase) {
  LinkedList<int> list;

  for (int i = 0; i < 10; i++) {
    list.insert(list.size(), i);
  }

  list.erase(0);
  EXPECT_EQ(list.front(), 1);

  list.erase(4);
  EXPECT_EQ(list.at(4), 6);

  list.erase(7);
  EXPECT_EQ(list.back(), 8);

  EXPECT_EQ(list.size(), 7);

  while (list.size()) {
    EXPECT_NO_THROW(list.erase(0));
  }

  EXPECT_EQ(list.size(), 0);
  EXPECT_ANY_THROW(list.erase(0));
}

TEST(LinkedListTest, Accessors) {
  LinkedList<int> list;

  list.insert(0, 1);
  list.insert(0, 2);
  list.insert(0, 3);

  EXPECT_EQ(list.front(), 3);
  EXPECT_EQ(list.at(1), 2);
  EXPECT_EQ(list.back(), 1);

  LinkedList<int> empty_list;

  EXPECT_ANY_THROW(empty_list.front());
  EXPECT_ANY_THROW(empty_list.at(0));
  EXPECT_ANY_THROW(empty_list.back());
}

TEST(LinkedListTest, PushPopFront) {
  LinkedList<int> list;

  for (int i = 0; i < 10; i++) {
    list.push_front(i);
    EXPECT_EQ(list.front(), i);
    EXPECT_EQ(list.size(), i + 1);
  }

  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(list.at(i), 9 - i);
  }

  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(list.front(), 9 - i);
    list.pop_front();
    EXPECT_EQ(list.size(), 9 - i);
  }
}

TEST(LinkedListTest, PushPopBack) {
  LinkedList<int> list;

  for (int i = 0; i < 10; i++) {
    list.push_back(i);
    EXPECT_EQ(list.back(), i);
    EXPECT_EQ(list.size(), i + 1);
  }

  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(list.at(i), i);
  }

  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(list.back(), 9 - i);
    list.pop_back();
    EXPECT_EQ(list.size(), 9 - i);
  }
}

TEST(LinkedListTest, Clear) {
  LinkedList<int> list;

  for (size_t i = 0; i < 10; i++) {
    list.push_back(i);
  }

  EXPECT_EQ(list.size(), 10);
  list.clear();
  EXPECT_EQ(list.size(), 0);
}

TEST(LinkedListTest, Reverse) {
  LinkedList<int> list;

  for (size_t i = 0; i < 3; i++) {
    list.push_back(i);
  }

  EXPECT_EQ(list.at(0), 0);
  EXPECT_EQ(list.at(1), 1);
  EXPECT_EQ(list.at(2), 2);

  list.reverse();

  EXPECT_EQ(list.at(0), 2);
  EXPECT_EQ(list.at(1), 1);
  EXPECT_EQ(list.at(2), 0);

  list.push_front(3);
  list.reverse();

  EXPECT_EQ(list.at(0), 0);
  EXPECT_EQ(list.at(1), 1);
  EXPECT_EQ(list.at(2), 2);
  EXPECT_EQ(list.at(3), 3);
}

TEST(LinkedListTest, RotateLeft) {
  LinkedList<int> list;

  for (size_t i = 0; i < 10; i++) {
    list.push_back(i);
  }

  EXPECT_EQ(list.front(), 0);
  list.rotate_left(0);
  EXPECT_EQ(list.front(), 0);

  for (size_t i = 0; i < list.size(); i++) {
    list.rotate_left(1);
    EXPECT_EQ(list.front(), (i + 1) % 10);
  }

  for (size_t i = 0; i < list.size(); i++) {
    list.rotate_left(list.size() - 1);
    EXPECT_EQ(list.front(), 9 - i);
  }

  list.rotate_left(5);
  EXPECT_EQ(list.front(), 5);
}

TEST(LinkedListTest, RotateRight) {
  LinkedList<int> list;

  for (size_t i = 0; i < 10; i++) {
    list.push_back(i);
  }

  EXPECT_EQ(list.front(), 0);
  list.rotate_right(0);
  EXPECT_EQ(list.front(), 0);

  for (size_t i = 0; i < list.size(); i++) {
    list.rotate_right(1);
    EXPECT_EQ(list.front(), 9 - i);
  }

  for (size_t i = 0; i < list.size(); i++) {
    list.rotate_right(list.size() - 1);
    EXPECT_EQ(list.front(), (i + 1) % 10);
  }

  list.rotate_right(5);
  EXPECT_EQ(list.front(), 5);
}

TEST(LinkedListTest, Swap) {
  LinkedList<int> listA, listB;

  listA.push_back(0);
  listA.push_back(1);
  listA.push_back(2);

  listB.push_back(3);
  listB.push_back(4);
  listB.push_back(5);

  listA.swap(listB);

  EXPECT_EQ(listA.front(), 3);
  EXPECT_EQ(listB.front(), 0);
}
