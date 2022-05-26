/**
 * @file CircularBuffer.h
 * @author Aubrey Nicoll (aubrey.nicoll@gmail.com)
 * @brief A Circular Buffer which uses contiguous memory.
 * @version 0.1
 * @date 2022-05-26
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "IQueue.h"

template <typename T>
class CircularBuffer : public virtual IQueue<T, CircularBuffer<T>> {
  size_t _capacity;
  size_t _size;
  size_t _readoffset;
  size_t _writeoffset;
  T *_data;

 public:
  /* Constructors */
  CircularBuffer(size_t);
  ~CircularBuffer();

  /* Utility */
  bool is_empty() const override;
  bool is_full() const override;
  size_t size() const override;
  size_t capacity() const;

  /* Accessors */
  T &front() override;
  T &back() override;

  /* Mutators */
  void push_back(const T &) override;
  void pop_front() override;

  /* Nice to Haves */
  void clear() override;
  void swap(CircularBuffer<T> &) override;
};

/**
 * @brief Size Constructor: Get a buffer with maximum capacity n
 *
 * @tparam T
 * @param n
 */
template <typename T>
CircularBuffer<T>::CircularBuffer(size_t n) {
  _capacity = n;
  _size = _readoffset = _writeoffset = 0;
  _data = new T[n];
}

/**
 * @brief Destroy the Circular Buffer< T>:: Circular Buffer object
 *
 * @tparam T
 */
template <typename T>
CircularBuffer<T>::~CircularBuffer() {
  delete[] _data;
}

/**
 * @brief Returns true if the buffer is empty, e.g. size == 0
 *
 * @tparam T
 * @return bool
 */
template <typename T>
inline bool CircularBuffer<T>::is_empty() const {
  return !_size;
}

/**
 * @brief Returns true if the buffer is full, e.g. size == capacity
 *
 * @tparam T
 * @return bool
 */
template <typename T>
inline bool CircularBuffer<T>::is_full() const {
  return _size == _capacity;
}

/**
 * @brief Returns the current size of the buffer
 *
 * @tparam T
 * @return size_t
 */
template <typename T>
inline size_t CircularBuffer<T>::size() const {
  return _size;
}

/**
 * @brief Returns the maximum capacity of the buffer
 *
 * @tparam T
 * @return size_t
 */
template <typename T>
inline size_t CircularBuffer<T>::capacity() const {
  return _capacity;
}

/**
 * @brief Returns a reference to the next value in the buffer
 *
 * @tparam T
 * @return T&
 */
template <typename T>
inline T &CircularBuffer<T>::front() {
  if (is_empty()) throw "Buffer is empty";
  return _data[_readoffset];
}

/**
 * @brief Returns a reference to the last value in the buffer
 *
 * @tparam T
 * @return T&
 */
template <typename T>
inline T &CircularBuffer<T>::back() {
  if (is_empty()) throw "Buffer is empty";
  return _data[_writeoffset];
}

/**
 * @brief Pushes a new value into the buffer
 *
 * @tparam T
 * @param value
 */
template <typename T>
inline void CircularBuffer<T>::push_back(const T &value) {
  if (is_full()) throw "Buffer is full";
  if (!is_empty()) {
    _writeoffset = _writeoffset == _capacity - 1 ? 0 : _writeoffset + 1;
  }
  _data[_writeoffset] = value;
  _size++;
}

/**
 * @brief Erases the next value from the buffer
 *
 * @tparam T
 */
template <typename T>
inline void CircularBuffer<T>::pop_front() {
  if (is_empty()) throw "Buffer is empty";
  if (_size != 1) {
    _readoffset = _readoffset == _capacity - 1 ? 0 : _readoffset + 1;
  }
  _size--;
}

/**
 * @brief Empty the buffer
 *
 * @tparam T
 */
template <typename T>
inline void CircularBuffer<T>::clear() {
  _size = _readoffset = _writeoffset = 0;
}

/**
 * @brief Swap data with another buffer
 *
 * @tparam T
 * @param other
 */
template <typename T>
inline void CircularBuffer<T>::swap(CircularBuffer<T> &other) {
  size_t temp_size = other._size;
  other._size = _size;
  _size = temp_size;

  size_t temp_capacity = other._capacity;
  other._capacity = _capacity;
  _capacity = temp_capacity;

  size_t temp_readoffset = other._readoffset;
  other._readoffset = _readoffset;
  _readoffset = temp_readoffset;

  size_t temp_writeoffset = other._writeoffset;
  other._writeoffset = _writeoffset;
  _writeoffset = temp_writeoffset;

  T *temp_data = other._data;
  other._data = _data;
  _data = temp_data;
}
