/**
 * @file BST.h
 * @author Aubrey Nicoll (aubrey.nicoll@gmail.com)
 * @brief A binary search tree as seen in Cormen's Introduction to Algorithms.
 * I've made an effort to provide an interface in the style of the STL as best I
 * can, although I am still learning. Therefore, operator guarantees made for
 * the generic type should be injected into the std:: namespace.
 *
 * This data structure is also going to contain my first iterator. The main goal
 * here is to make it compatible with range-for loops to get an in-order
 * traversal of the tree.
 *
 * @version 0.1
 * @date 2022-06-23
 *
 * @copyright Copyright (c) 2022
 *
 */

// TODO Create an iterator class
// TODO Overload operator==

#pragma once

#include <cstddef>
#include <functional>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <vector>

using namespace std;

template <typename T, typename EQ = std::equal_to<T>,
          typename LT = std::less<T> >
class BST {
 public:
  /* Constructors */
  BST();
  ~BST();

  /* Utilities */
  size_t size();
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

  /* Nice to Haves */
  void clear();
  void swap(BST &);

  /* Operators */
  friend std::ostream &operator<<(std::ostream &stream, const BST &bst) {
    vector<Node *> stack;
    Node *curr_node = bst._root;

    stream << "[";

    while (curr_node || stack.size()) {
      while (curr_node) {
        stack.push_back(curr_node);
        curr_node = curr_node->_left;
      }

      curr_node = stack.back();
      stack.pop_back();

      stream << *curr_node;

      curr_node = curr_node->_right;

      if (curr_node || stack.size()) stream << ", ";
    }

    stream << "]";
    return stream;
  };

 private:
  /* Private Classes */
  class Node {
   public:
    /* BST::Node Constructors */
    Node(const T &);
    ~Node();

    /* BST::Node Operators */
    friend std::ostream &operator<<(std::ostream &stream, const Node &node) {
      stream << node._val;
      return stream;
    };

    /* BST::Node Member Data */
    T _val;
    Node *_parent;
    Node *_left;
    Node *_right;
  };

  /* Helpers */
  void transplant(Node *, Node *);

  /* Member Data */
  Node *_root;
  size_t _size;
};

template <typename T, typename EQ, typename LT>
BST<T, EQ, LT>::Node::Node(const T &val)
    : _val(val), _parent(nullptr), _left(nullptr), _right(nullptr) {}

template <typename T, typename EQ, typename LT>
BST<T, EQ, LT>::Node::~Node() {}

template <typename T, typename EQ, typename LT>
BST<T, EQ, LT>::BST() : _root(nullptr), _size(0) {}

template <typename T, typename EQ, typename LT>
BST<T, EQ, LT>::~BST() {
  clear();
}

template <typename T, typename EQ, typename LT>
size_t BST<T, EQ, LT>::size() {
  return _size;
}

template <typename T, typename EQ, typename LT>
bool BST<T, EQ, LT>::is_empty() {
  return !_size;
}

template <typename T, typename EQ, typename LT>
bool BST<T, EQ, LT>::search(const T &val) {
  Node *curr_node = _root;
  while (curr_node) {
    if (EQ()(val, curr_node->_val)) return true;

    if (LT()(val, curr_node->_val)) {
      curr_node = curr_node->_left;
    } else {
      curr_node = curr_node->_right;
    }
  }
  return false;
}

template <typename T, typename EQ, typename LT>
const T &BST<T, EQ, LT>::min() {
  if (is_empty())
    throw std::out_of_range("Empty tree error: min is out of bounds");
  Node *curr_node = _root;
  while (curr_node->_left) curr_node = curr_node->_left;
  return curr_node->_val;
}

template <typename T, typename EQ, typename LT>
const T &BST<T, EQ, LT>::max() {
  if (is_empty())
    throw std::out_of_range("Empty tree error: max is out of bounds");
  Node *curr_node = _root;
  while (curr_node->_right) curr_node = curr_node->_right;
  return curr_node->_val;
}

template <typename T, typename EQ, typename LT>
const T &BST<T, EQ, LT>::predecessor(const T &val) {
  Node *predecessor = nullptr;
  Node *curr_node = _root;

  while (curr_node) {
    if (!LT()(curr_node->_val, val)) {
      curr_node = curr_node->_left;
    } else {
      if (!predecessor || curr_node->_val > predecessor->_val) {
        predecessor = curr_node;
      }
      curr_node = curr_node->_right;
    }
  }

  if (!predecessor) throw std::out_of_range("predecessor out of bounds");
  return predecessor->_val;
}

template <typename T, typename EQ, typename LT>
const T &BST<T, EQ, LT>::successor(const T &val) {
  Node *successor = nullptr;
  Node *curr_node = _root;

  while (curr_node) {
    if (!LT()(val, curr_node->_val)) {
      curr_node = curr_node->_right;
    } else {
      if (!successor || curr_node->_val < successor->_val) {
        successor = curr_node;
      }
      curr_node = curr_node->_left;
    }
  }

  if (!successor) throw std::out_of_range("successor out of bounds");
  return successor->_val;
}

template <typename T, typename EQ, typename LT>
void BST<T, EQ, LT>::insert(const T &val) {
  Node *curr_node = _root;
  Node *prev_node = nullptr;

  while (curr_node) {
    if (EQ()(val, curr_node->_val)) {
      return;
    }

    prev_node = curr_node;
    if (LT()(val, curr_node->_val)) {
      curr_node = curr_node->_left;
    } else {
      curr_node = curr_node->_right;
    }
  }

  Node *new_node = new Node(val);
  new_node->_parent = prev_node;

  if (!prev_node) {
    _root = new_node;
  } else if (LT()(val, prev_node->_val)) {
    prev_node->_left = new_node;
  } else {
    prev_node->_right = new_node;
  }

  _size++;
}

template <typename T, typename EQ, typename LT>
void BST<T, EQ, LT>::erase(const T &val) {
  Node *node_to_delete = _root;

  while (node_to_delete && node_to_delete->_val != val) {
    if (LT()(val, node_to_delete->_val)) {
      node_to_delete = node_to_delete->_left;
    } else {
      node_to_delete = node_to_delete->_right;
    }
  }

  if (!node_to_delete) return;

  if (!node_to_delete->_left) {
    transplant(node_to_delete, node_to_delete->_right);
  } else if (!node_to_delete->_right) {
    transplant(node_to_delete, node_to_delete->_left);
  } else {
    Node *successor = node_to_delete->_right;
    while (successor->_left) successor = successor->_left;

    if (successor->_parent != node_to_delete) {
      transplant(successor, successor->_right);
      successor->_right = node_to_delete->_right;
      successor->_right->_parent = successor;
    }

    transplant(node_to_delete, successor);
    successor->_left = node_to_delete->_left;
    successor->_left->_parent = successor;
  }

  delete node_to_delete;
  _size--;
}

template <typename T, typename EQ, typename LT>
void BST<T, EQ, LT>::clear() {
  vector<Node *> stack;
  Node *curr_node = _root;

  while (curr_node || stack.size()) {
    while (curr_node) {
      stack.push_back(curr_node);
      curr_node = curr_node->_left;
    }

    Node *node_to_delete = stack.back();
    stack.pop_back();

    curr_node = node_to_delete->_right;

    delete node_to_delete;
  }

  _root = nullptr;
  _size = 0;
}

template <typename T, typename EQ, typename LT>
void BST<T, EQ, LT>::swap(BST &other) {
  size_t temp_size = _size;
  _size = other._size;
  other._size = temp_size;

  Node *temp_root = _root;
  _root = other._root;
  other._root = temp_root;
}

template <typename T, typename EQ, typename LT>
void BST<T, EQ, LT>::transplant(Node *a, Node *b) {
  if (!a->_parent) {
    _root = b;
  } else if (a == a->_parent->_left) {
    a->_parent->_left = b;
  } else {
    a->_parent->_right = b;
  }

  if (b) {
    b->_parent = a->_parent;
  }
}
