/**
 * @file BST.h
 * @author Aubrey Nicoll (aubrey.nicoll@gmail.com)
 * @brief A binary search tree as seen in Cormen's Introduction to Algorithms.
 * @version 0.1
 * @date 2022-06-23
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <cstddef>
#include <functional>
#include <iterator>
#include <vector>

template <typename T, typename EQ = std::equal_to<T>,
          typename LT = std::less<T> >
class BST {
 private:
  /* Private Classes */
  class Node {
   public:
    T _val;
    Node *_parent;
    Node *_left;
    Node *_right;

    Node(const T &);
    ~Node();
  };

  /* Members */
  Node *_root;
  size_t _size;

 public:
  /* Typedefs */
  typedef T value_t;
  typedef size_t size_t;

  /* Operators */
  ostream &operator<<(ostream &, const BST &);

  /* Iterators */
  class Iterator {
    // todo
  };

  /* Constructors */
  BST();
  ~BST();

  /* Utilities */
  bool size();
  bool is_empty();

  /* Accessors */
  bool search(const T &);
  const T &min();
  const T &max();
  const T &predecessor(const T &);
  const T &successor(const T &);

  /* Mutators */
  void insert(const T &);
  void erase(const T &);

  /* Friends */
  friend ostream &operator<<(ostream &, const BST &);
};
