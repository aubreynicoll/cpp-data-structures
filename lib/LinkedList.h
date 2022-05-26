/**
 * @file LinkedList.h
 * @author Aubrey Nicoll (aubrey.nicoll@gmail.com)
 * @brief A doubly-linked list implementation
 * @version 0.1
 * @date 2022-05-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <stdexcept>

#include "IList.h"
#include "IQueue.h"
#include "ListNode.h"

template <typename T>
class Listnode;

template <typename T>
class LinkedList : public virtual IList<T, LinkedList<T>>,
                   public virtual IQueue<T, LinkedList<T>> {
  ListNode<T> *_head;
  ListNode<T> *_tail;
  size_t _size;

 public:
  /* Constructors */
  LinkedList();
  ~LinkedList();

  /* Utility */
  size_t size() const override;
  bool is_empty() const override;
  bool is_full() const override;

  /* Accessors */
  T &at(size_t) override;
  T &front() override;
  T &back() override;

  /* Mutators */
  void insert(size_t, const T &) override;
  void erase(size_t) override;
  void push_front(const T &) override;
  void pop_front() override;
  void push_back(const T &) override;
  void pop_back() override;

  /* Nice to Haves */
  void clear() override;
  void reverse() override;
  void rotate_left(size_t) override;
  void rotate_right(size_t) override;
  void swap(LinkedList<T> &) override;
};

/**
 * @brief Default Constructor: Create an empty list
 *
 * @tparam T
 */
template <typename T>
LinkedList<T>::LinkedList() {
  _head = nullptr;
  _tail = nullptr;
  _size = 0;
}

/**
 * @brief Destroy the Linked List< T>:: Linked List object
 *
 * @tparam T
 */
template <typename T>
LinkedList<T>::~LinkedList() {
  clear();
}

/**
 * @brief Get the number of nodes in the list.
 *
 * @tparam T
 * @return size_t
 */
template <typename T>
inline size_t LinkedList<T>::size() const {
  return _size;
}

/**
 * @brief Returns true if list is empty
 *
 * @tparam T
 * @return bool
 */
template <typename T>
inline bool LinkedList<T>::is_empty() const {
  return !_size;
}

/**
 * @brief Always returns false because LinkedList is dynamically sized. Part
 * of the IQueue interface, since it will be used on other implementations.
 *
 * @tparam T
 * @return bool
 */
template <typename T>
inline bool LinkedList<T>::is_full() const {
  return false;
}

/**
 * @brief Get a reference to the value at the given index.
 *
 * @tparam T
 * @param index
 * @return T&
 */
template <typename T>
T &LinkedList<T>::at(size_t index) {
  if (index >= _size) throw std::invalid_argument("index out of bounds");

  ListNode<T> *index_node;

  size_t mid_point = _size / 2;
  if (index < mid_point) {
    index_node = _head;

    for (size_t i = 0; i < index; i++) {
      index_node = index_node->_next;
    }
  } else {
    index_node = _tail;

    for (size_t i = _size - 1; i > index; i--) {
      index_node = index_node->_prev;
    }
  }

  return index_node->_value;
}

/**
 * @brief Get a reference to the value at the lowest index.
 *
 * @tparam T
 * @return T&
 */
template <typename T>
inline T &LinkedList<T>::front() {
  return at(0);
}

/**
 * @brief Get a reference to the value at the highest index.
 *
 * @tparam T
 * @return T&
 */
template <typename T>
inline T &LinkedList<T>::back() {
  return at(_size - 1);
}

/**
 * @brief Insert a new node at index, pushing the node previously at index (and
 * every node thereafter) to the right.
 *
 * @tparam T
 * @param index 0 <= index <= size of list
 * @param value The value to be inserted
 */
template <typename T>
void LinkedList<T>::insert(size_t index, const T &value) {
  if (index > _size) throw std::invalid_argument("index out of bounds");

  ListNode<T> *new_node = new ListNode<T>(value);
  ListNode<T> *prev_node, *index_node;
  prev_node = index_node = nullptr;

  size_t mid_point = _size / 2;
  if (index < mid_point) {
    index_node = _head;

    for (size_t i = 0; i < index; i++) {
      prev_node = index_node;
      index_node = index_node->_next;
    }
  } else {
    prev_node = _tail;

    for (size_t i = _size; i > index; i--) {
      index_node = prev_node;
      prev_node = prev_node->_prev;
    }
  }

  new_node->_prev = prev_node;
  new_node->_next = index_node;

  if (prev_node == nullptr) {
    _head = new_node;
  } else {
    prev_node->_next = new_node;
  }

  if (index_node == nullptr) {
    _tail = new_node;
  } else {
    index_node->_prev = new_node;
  }

  _size++;
}

/**
 * @brief Remove node at index from the list. Permanently.
 *
 * @tparam T
 * @param index
 */
template <typename T>
void LinkedList<T>::erase(size_t index) {
  if (index >= _size) throw std::invalid_argument("index out of bounds");

  ListNode<T> *prev_node, *index_node, *next_node;
  prev_node = index_node = next_node = nullptr;

  size_t mid_point = _size / 2;
  if (index < mid_point) {
    index_node = _head;
    for (size_t i = 0; i < index; i++) {
      index_node = index_node->_next;
    }
  } else {
    index_node = _tail;
    for (size_t i = _size - 1; i > index; i--) {
      index_node = index_node->_prev;
    }
  }

  prev_node = index_node->_prev;
  next_node = index_node->_next;

  if (prev_node == nullptr) {
    _head = next_node;
  } else {
    prev_node->_next = next_node;
  }

  if (next_node == nullptr) {
    _tail = prev_node;
  } else {
    next_node->_prev = prev_node;
  }

  delete index_node;
  _size--;
}

/**
 * @brief Prepend a new node at the front of the list.
 *
 * @tparam T
 * @param value
 */
template <typename T>
inline void LinkedList<T>::push_front(const T &value) {
  insert(0, value);
}

/**
 * @brief Remove the node at the front of the list.
 *
 * @tparam T
 */
template <typename T>
inline void LinkedList<T>::pop_front() {
  erase(0);
}

/**
 * @brief Append a new node at the back of the list.
 *
 * @tparam T
 * @param value
 */
template <typename T>
inline void LinkedList<T>::push_back(const T &value) {
  insert(_size, value);
}

/**
 * @brief Remove the node at the back of the list.
 *
 * @tparam T
 */
template <typename T>
inline void LinkedList<T>::pop_back() {
  erase(_size - 1);
}

/**
 * @brief Delete every node from the list.
 *
 * @tparam T
 */
template <typename T>
void LinkedList<T>::clear() {
  while (_size) {
    pop_front();
  }
}

/**
 * @brief Reverse the contents of the list in-place.
 *
 * @tparam T
 */
template <typename T>
void LinkedList<T>::reverse() {
  ListNode<T> *left = _head;
  ListNode<T> *right = _tail;

  while (left != right && left->_prev != right) {
    T temp = left->_value;
    left->_value = right->_value;
    right->_value = temp;

    left = left->_next;
    right = right->_prev;
  }
}

/**
 * @brief Rotate the content of the list in-place by k places to the left.
 *
 * @tparam T
 * @param k must be < size of list
 */
template <typename T>
void LinkedList<T>::rotate_left(size_t k) {
  k = k >= _size ? k % _size : k;
  if (!k) return;

  ListNode<T> *k_node;

  size_t mid_point = _size / 2;
  if (k < mid_point) {
    k_node = _head;

    for (size_t i = 0; i < k; i++) {
      k_node = k_node->_next;
    }
  } else {
    k_node = _tail;

    for (size_t i = _size - 1; i > k; i--) {
      k_node = k_node->_prev;
    }
  }

  _head->_prev = _tail;
  _tail->_next = _head;
  _tail = k_node->_prev;
  _head = k_node;
  _tail->_next = nullptr;
  _head->_prev = nullptr;
}

/**
 * @brief Rotate the content of the list in-place by k places to the right.
 *
 * @tparam T
 * @param k
 */
template <typename T>
inline void LinkedList<T>::rotate_right(size_t k) {
  k = k >= _size ? k % _size : k;
  rotate_left(_size - k);
}

/**
 * @brief Swap contents with another list
 *
 * @tparam T
 * @param other
 */
template <typename T>
inline void LinkedList<T>::swap(LinkedList<T> &other) {
  ListNode<T> *temp_head = other._head;
  other._head = _head;
  _head = temp_head;

  ListNode<T> *temp_tail = other._tail;
  other._tail = _tail;
  _tail = temp_tail;

  size_t temp_size = other._size;
  other._size = _size;
  _size = temp_size;
}
