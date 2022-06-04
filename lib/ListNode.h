#pragma once

#include "LinkedList.h"

template <typename T>
class LinkedList;

template <typename T>
class ListNode {
 private:
  T _value;
  ListNode<T> *_prev;
  ListNode<T> *_next;

  /* Constructors */
  ListNode(const T &value);
  ~ListNode();

  friend class LinkedList<T>;
};

template <typename T>
ListNode<T>::ListNode(const T &value) {
  _value = value;
  _prev = nullptr;
  _next = nullptr;
}

template <typename T>
ListNode<T>::~ListNode() {}
