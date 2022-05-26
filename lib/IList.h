/**
 * @file IList.h
 * @author Aubrey Nicoll (aubrey.nicoll@gmail.com)
 * @brief An abstract List class
 * @version 0.1
 * @date 2022-05-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <cstddef>

template <typename T, typename Container>
class IList {
 public:
  /* Typedefs */
  typedef T value_t;
  typedef Container container_t;

  /* Utility */
  virtual size_t size() const = 0;
  virtual bool is_empty() const = 0;

  /* Accessors */
  virtual T &at(size_t) = 0;
  virtual T &front() = 0;
  virtual T &back() = 0;

  /* Mutators */
  virtual void insert(size_t, const T &) = 0;
  virtual void erase(size_t) = 0;
  virtual void push_front(const T &) = 0;
  virtual void pop_front() = 0;
  virtual void push_back(const T &) = 0;
  virtual void pop_back() = 0;

  /* Nice to Haves */
  virtual void clear() = 0;
  virtual void reverse() = 0;
  virtual void rotate_left(size_t) = 0;
  virtual void rotate_right(size_t) = 0;
  virtual void swap(Container &) = 0;
};
