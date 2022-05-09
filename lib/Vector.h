#pragma once

#include <stddef.h>

#include <cstdlib>

template <class T>
class Vector {
  T* _data;
  size_t _size;
  size_t _capacity;

  void reallocate_storage(size_t);
  void increase_capacity();
  void decrease_capacity();

 public:
  /**
   * @brief Construct a new Vector object
   * Default: size 0, capacity 0
   */
  Vector();
  Vector(size_t);
  Vector(size_t, T);
  ~Vector();

  /* Capacity */
  /**
   * @brief Returns the current size of the Vector, which is equal
   * to the number of elements stored within.
   *
   * @return size_t
   */
  size_t size();

  /**
   * @brief Returns the current capacity of the Vector, which is the maximum
   * number of elements that can be stored before the Vector must reallocate its
   * storage.
   *
   * @return size_t
   */
  size_t capacity();
  void resize();
  void reserve();
  void shrink_to_fit();
  bool empty();

  /* Access */
  T at(size_t);
  T* data();

  /* Modifiers */
  void assign(size_t, T);
  void insert(size_t, T);
  T remove(size_t);
  void push(T);
  T pop();

  /* Nice to haves */
  size_t index_of(T);
  void reverse();
  void swap(Vector<T>);
  void clear();
};

template <class T>
Vector<T>::Vector() {
  _size = 0;
  _capacity = 0;
  _data = NULL;
}

template <class T>
Vector<T>::~Vector() {
  free(_data);
}

template <class T>
size_t Vector<T>::size() {
  return _size;
}

template <class T>
size_t Vector<T>::capacity() {
  return _capacity;
}
