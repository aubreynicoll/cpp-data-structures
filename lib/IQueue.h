/**
 * @file IQueue.h
 * @author Aubrey Nicoll (aubrey.nicoll@gmail.com)
 * @brief An abstract Queue interface
 *
 * @version 0.1
 * @date 2022-05-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

template <typename T, typename Container>
class IQueue {
 public:
  /* Typedefs */
  typedef T value_t;
  typedef Container container_t;

  /* Utility */
  virtual bool is_empty() const = 0;
  virtual bool is_full() const = 0;
  virtual size_t size() const = 0;

  /* Accessors */
  virtual T &front() = 0;
  virtual T &back() = 0;

  /* Mutators */
  virtual void push_back(const T &) = 0;
  virtual void pop_front() = 0;

  /* Nice to Haves */
  virtual void clear() = 0;
  virtual void swap(Container &) = 0;
};
