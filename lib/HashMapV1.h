/**
 * @file HashMapV1.h
 * @author Aubrey Nicoll (aubrey.nicoll@gmail.com)
 * @brief An implementation of a HashMap using chaining to resolve
 * collisions. Implements a universal hashing function.
 * @version 0.1
 * @date 2022-06-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <cstddef>
#include <cstdlib>
#include <functional>

template <typename K, typename V, typename Hash = std::hash<K>,
          typename Pred = std::equal_to<K> >
class HashMap {
 private:
  /* Inner Classes */
  class Node {
   public:
    K _key;
    V _val;
    Node *_next;

    Node(const K &, const V &);
    ~Node();
  };

  /* Static Members */
  static const size_t _max_capacity;
  static const size_t _large_prime_p;

  /* Members */
  const size_t _rand_a;
  const size_t _rand_b;
  size_t _size;
  size_t _capacity;
  Node **_table;

  /* Helpers */
  size_t hash(const K &);
  void increase_capacity();

 public:
  /* Constructors */
  HashMap();
  ~HashMap();

  /* Util */
  bool is_empty();
  size_t size();
  size_t capacity();
  double load_factor();
  bool has(const K &);

  /* Accessors */
  V &get(const K &);

  /* Mutators */
  void insert(const K &, const V &);
  void erase(const K &);
};

template <typename K, typename V, typename Hash, typename Pred>
HashMap<K, V, Hash, Pred>::Node::Node(const K &key, const V &value)
    : _key(key), _val(value), _next(nullptr) {}

template <typename K, typename V, typename Hash, typename Pred>
HashMap<K, V, Hash, Pred>::Node::~Node() {}

template <typename K, typename V, typename Hash, typename Pred>
const size_t HashMap<K, V, Hash, Pred>::_max_capacity = 4294967296;

template <typename K, typename V, typename Hash, typename Pred>
const size_t HashMap<K, V, Hash, Pred>::_large_prime_p = 4294967311;

template <typename K, typename V, typename Hash, typename Pred>
size_t HashMap<K, V, Hash, Pred>::hash(const K &key) {
  size_t hashed_key = (_rand_a * Hash()(key) + _rand_b);
  hashed_key =
      hashed_key < _large_prime_p ? hashed_key : hashed_key % _large_prime_p;
  hashed_key = hashed_key < _capacity ? hashed_key : hashed_key % _capacity;
  return hashed_key;
}

template <typename K, typename V, typename Hash, typename Pred>
void HashMap<K, V, Hash, Pred>::increase_capacity() {}

template <typename K, typename V, typename Hash, typename Pred>
HashMap<K, V, Hash, Pred>::HashMap()
    : _rand_a((rand() + 1) % _large_prime_p),
      _rand_b(rand() % _large_prime_p),
      _size(0),
      _capacity(0),
      _table(nullptr) {}

template <typename K, typename V, typename Hash, typename Pred>
HashMap<K, V, Hash, Pred>::~HashMap() {
  if (_table != nullptr) {
    for (size_t i = 0; i < _capacity; i++) {
      Node *curr_ptr = _table[i];
      while (curr_ptr != nullptr) {
        Node *next_ptr = curr_ptr->_next;
        delete curr_ptr;
        curr_ptr = next_ptr;
      }
    }
    delete[] _table;
  }
}

template <typename K, typename V, typename Hash, typename Pred>
bool HashMap<K, V, Hash, Pred>::is_empty() {
  return !_size;
}

template <typename K, typename V, typename Hash, typename Pred>
size_t HashMap<K, V, Hash, Pred>::size() {
  return _size;
}

template <typename K, typename V, typename Hash, typename Pred>
size_t HashMap<K, V, Hash, Pred>::capacity() {
  return _capacity;
}

template <typename K, typename V, typename Hash, typename Pred>
double HashMap<K, V, Hash, Pred>::load_factor() {
  return double(_size) / double(_capacity);
}

template <typename K, typename V, typename Hash, typename Pred>
bool HashMap<K, V, Hash, Pred>::has(const K &key) {}

template <typename K, typename V, typename Hash, typename Pred>
V &HashMap<K, V, Hash, Pred>::get(const K &key) {}

template <typename K, typename V, typename Hash, typename Pred>
void HashMap<K, V, Hash, Pred>::insert(const K &key, const V &value) {}

template <typename K, typename V, typename Hash, typename Pred>
void HashMap<K, V, Hash, Pred>::erase(const K &key) {}
