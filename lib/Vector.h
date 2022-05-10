#pragma once

#include <stddef.h>
#include <string.h>

#include <cstdlib>
#include <stdexcept>

/**
 * @brief A basic Vector class. I've made an effort to remain faithful to the
 * standard C++ Vector, but decided to scrap some things (e.g. push_front &
 * pop_front, as array-style storage is not conducive to these operations)
 *
 * @tparam T
 */
template <class T>
class Vector {
  T* _data;
  size_t _size;
  size_t _capacity;

  /**
   * @brief Get new memory allocation, copy data, free previous memory
   * allocation
   */
  void reallocate_storage(size_t);

  /**
   * @brief Doubles the vector's capacity and handles memory reallocation
   */
  void increase_capacity();

  /**
   * @brief Halves the vector's capacity and handles memory reallocation
   */
  void decrease_capacity();

 public:
  /**
   * @brief Default Constructor: get Vector of size 0, capacity 0
   */
  Vector();

  /**
   * @brief Sized Constructor: get Vector  of size k, capacity k
   *
   * @param k size_t - sets size & capacity
   */
  Vector(size_t);

  /**
   * @brief Fill Constructor: get Vector of size k, capacity k, filled with
   * value
   *
   * @param k size_t - sets size & capacity
   * @param val T - fill the array with val
   */
  Vector(size_t, T);

  /**
   * @brief Destroy the Vector object
   */
  ~Vector();

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

  /**
   * @brief Resizes the vector to k elements. If k is less than size, any
   * element of index >= k will be deleted. If k is greater than size, then new
   * elements will be 0 initialized (as by calloc). If k is also greater than
   * capacity, then capacity will be k.
   *
   * @param k size_t - The desired size
   */
  void resize(size_t);

  /**
   * @brief Resizes the vector to k elements. If k is less than size, any
   * element of index >= k will be deleted. If k is greater than size, then new
   * elements will be initialized to val. If k is also greater than
   * capacity, then capacity will be k.
   *
   * @param k size_t - The desired size
   * @param val T - New elements initialized to val
   */
  void resize(size_t, T);

  /**
   * @brief Increase the capacity of the vector to k. If k < capacity, this does
   * nothing.
   *
   * @param k size_t - The new capacity, if k > capacity
   */
  void reserve(size_t);

  /**
   * @brief Shrink capacity to equal size
   */
  void shrink_to_fit();

  /**
   * @brief Returns true if the vector has 0 elements
   *
   * @return bool
   */
  bool is_empty();

  /**
   * @brief Get value at index
   *
   * @param index size_t
   *
   * @return T
   * @throws out-of-bounds if index < 0 or index >= size
   */
  T at(size_t);

  /**
   * @brief Returns a pointer to the vector's internal storage. Beware that if
   * storage is reallocated, this pointer is pointing to garbage.
   *
   * @return T*
   */
  T* data();

  /**
   * @brief Store value at index, overwriting previous element
   *
   * @param index size_t
   * @param value T
   *
   * @throws out-of-bounds if index < 0 or index >= size
   */
  void assign(size_t, T);

  /**
   * @brief Insert value at index. All elements to the right of index (and
   * including index) are shifted right by one.
   *
   * @param index size_t
   * @param value T
   *
   * @throws out-of-bounds if index < 0 or index > size
   */
  void insert(size_t, T);

  /**
   * @brief Remove value at index. All elements to the right of index are
   * shifted left by one.
   *
   * @param index size_t
   *
   * @return T
   *
   * @throws out-of-bounds if index < 0 or index >= size
   */
  T remove(size_t);

  /**
   * @brief Push a value into storage, inserting it at the end of the vector
   *
   * @param value T
   */
  void push(T);

  /**
   * @brief Pop a value from storage, removing it from the end of the vector
   *
   * @return T
   *
   * @throws out-of-bounds if size == 0
   */
  T pop();

  /**
   * @brief Returns the index of the first matching value as defined by the
   * predicate f. Returns -1 if no matching value is found.
   *
   * @param f a function that consumes a single param of type T, and which
   * returns a bool
   * @return size_t
   */
  size_t index_of(bool (*f)(T));

  /**
   * @brief Reverses the vector's internal storage in place
   */
  void reverse();

  /**
   * @brief Swap data with another Vector<T>
   *
   * @param v Vector<T>
   */
  void swap(Vector<T>&);

  /**
   * @brief set size & capacity of Vector to 0 and free all allocated storage
   */
  void clear();
};

template <class T>
void Vector<T>::reallocate_storage(size_t k) {
  if (k == 0) {
    _size = 0;
    _capacity = 0;

    free(_data);
    _data = NULL;
  } else {
    if (k < _size) {
      _size = k;
    }
    _capacity = k;

    T* new_data = (T*)malloc(_capacity * sizeof(T));
    memcpy(new_data, _data, _size * sizeof(T));

    free(_data);
    _data = new_data;
  }
}

template <class T>
void Vector<T>::increase_capacity() {
  size_t new_capacity = _capacity == 0 ? 1 : _capacity * 2;
  reallocate_storage(new_capacity);
}

template <class T>
void Vector<T>::decrease_capacity() {
  if (_capacity == 0) return;
  size_t new_capacity = _capacity / 2;
  reallocate_storage(new_capacity);
}

template <class T>
Vector<T>::Vector() {
  _size = 0;
  _capacity = 0;
  _data = NULL;
}

template <class T>
Vector<T>::Vector(size_t k) {
  _size = k;
  _capacity = k;
  _data = (T*)calloc(k, sizeof(T));
}

template <class T>
Vector<T>::Vector(size_t k, T val) {
  _size = k;
  _capacity = k;
  _data = (T*)malloc(_capacity * sizeof(T));

  for (size_t i = 0; i < _size; i++) {
    *(_data + i) = val;
  }
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

template <class T>
void Vector<T>::resize(size_t k) {
  if (k > _capacity) {
    reallocate_storage(k);
  }

  if (k > _size) {
    memset(_data + _size, 0, (k - _size) * sizeof(T));
  }

  _size = k;
}

template <class T>
void Vector<T>::resize(size_t k, T val) {
  if (k > _capacity) {
    reallocate_storage(k);
  }

  if (k > _size) {
    for (size_t i = _size; i < k; i++) {
      *(_data + i) = val;
    }
  }

  _size = k;
}

template <class T>
void Vector<T>::reserve(size_t k) {
  if (k > _capacity) reallocate_storage(k);
}

template <class T>
void Vector<T>::shrink_to_fit() {
  if (_capacity > _size) reallocate_storage(_size);
}

template <class T>
bool Vector<T>::is_empty() {
  return _size == 0;
}

template <class T>
T Vector<T>::at(size_t i) {
  if (i >= _size) throw std::invalid_argument("index out of bounds");
  return *(_data + i);
}

template <class T>
T* Vector<T>::data() {
  return _data;
}

template <class T>
void Vector<T>::assign(size_t i, T val) {
  if (i >= _size) throw std::invalid_argument("index out of bounds");
  *(_data + i) = val;
}

template <class T>
void Vector<T>::insert(size_t i, T val) {
  if (i > _size) throw std::invalid_argument("index out of bounds");

  if (_size == _capacity) increase_capacity();

  memmove(_data + i + 1, _data + i, (_size - i) * sizeof(T));
  *(_data + i) = val;
  _size++;
}

template <class T>
T Vector<T>::remove(size_t i) {
  if (i >= _size) throw std::invalid_argument("index out of bounds");

  T val = *(_data + i);
  memmove(_data + i, _data + i + 1, (_size - i - 1) * sizeof(T));
  _size--;

  return val;
}

template <class T>
void Vector<T>::push(T val) {
  insert(_size, val);
}

template <class T>
T Vector<T>::pop() {
  return remove(_size - 1);
}

template <class T>
size_t Vector<T>::index_of(bool (*f)(T)) {
  for (size_t i = 0; i < _size; i++) {
    if ((*f)(*(_data + i))) {
      return i;
    }
  }
  return -1;
}

template <class T>
void Vector<T>::reverse() {
  int *i, *j, temp;
  i = _data;
  j = _data + _size - 1;

  while (i < j) {
    temp = *i;
    *i = *j;
    *j = temp;

    i++;
    j--;
  }
}

template <class T>
void Vector<T>::swap(Vector<T>& v) {
  size_t temp_size = _size;
  _size = v._size;
  v._size = temp_size;

  size_t temp_capacity = _capacity;
  _capacity = v._capacity;
  v._capacity = temp_capacity;

  T* temp_data = _data;
  _data = v._data;
  v._data = temp_data;
}

template <class T>
void Vector<T>::clear() {
  reallocate_storage(0);
}
