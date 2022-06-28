/**
 * @file HashMapV1.h
 * @author Aubrey Nicoll (aubrey.nicoll@gmail.com)
 * @brief An implementation of a HashMap using chaining to resolve
 * collisions. Implements a universal hashing function as seen in Introduction
 * to Algorithms, 3rd ed.
 * @version 0.1
 * @date 2022-06-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <functional>
#include <random>
#include <stdexcept>

template <typename K, typename V, typename Hash = std::hash<K>,
          typename Pred = std::equal_to<K> >
class HashMap {
 private:
  /* Inner Classes */
  class Node {
   public:
    const K _key;
    V _val;
    Node *_next;

    Node(const K &, const V &);
    ~Node();
  };

  /* Static Members */
  static const size_t _max_capacity;
  static const size_t _large_prime_p;
  static std::random_device _generator;
  static std::uniform_int_distribution<size_t> _dist_a;
  static std::uniform_int_distribution<size_t> _dist_b;
  static const size_t _rand_a;
  static const size_t _rand_b;

  /* Members */
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

/**
 * @brief Construct a new Node used for chaining
 *
 * @tparam K
 * @tparam V
 * @tparam Hash
 * @tparam Pred
 * @param key
 * @param value
 */
template <typename K, typename V, typename Hash, typename Pred>
HashMap<K, V, Hash, Pred>::Node::Node(const K &key, const V &value)
    : _key(key), _val(value), _next(nullptr) {}

/**
 * @brief Destroy a Node object. Given the tight coupling between HashMap and
 * Node, it is not this destructor's responsibility to delete *_next
 *
 * @tparam K
 * @tparam V
 * @tparam Hash
 * @tparam Pred
 */
template <typename K, typename V, typename Hash, typename Pred>
HashMap<K, V, Hash, Pred>::Node::~Node() {}

/**
 * @brief Cormen[267] states that when designing universal hashing functions, it
 * can be useful to have a prime number larger than any possible hashed key.
 * Therefore, this implementation is arbitrarily limited to 2^32 buckets for the
 * sake of choosing a constant prime
 *
 * @tparam K
 * @tparam V
 * @tparam Hash
 * @tparam Pred
 */
template <typename K, typename V, typename Hash, typename Pred>
const size_t HashMap<K, V, Hash, Pred>::_max_capacity = 4294967296UL;

/**
 * @brief Cormen[267] states that when designing universal hashing functions, it
 * can be useful to have a prime number larger than any possible hashed key. The
 * buckets have been limited to 2^32, and this is the next prime over that value
 *
 * In the book, this is 'p'
 *
 * @tparam K
 * @tparam V
 * @tparam Hash
 * @tparam Pred
 */
template <typename K, typename V, typename Hash, typename Pred>
const size_t HashMap<K, V, Hash, Pred>::_large_prime_p = 4294967311UL;

/**
 * @brief Random number generator for internal use
 *
 * @tparam K
 * @tparam V
 * @tparam Hash
 * @tparam Pred
 */
template <typename K, typename V, typename Hash, typename Pred>
std::random_device HashMap<K, V, Hash, Pred>::_generator;

/**
 * @brief The random distribution of 'a' in Cormen[267], aka 'Z sub *p'
 *
 * @tparam K
 * @tparam V
 * @tparam Hash
 * @tparam Pred
 */
template <typename K, typename V, typename Hash, typename Pred>
std::uniform_int_distribution<size_t> HashMap<K, V, Hash, Pred>::_dist_a(
    1, _large_prime_p - 1);

/**
 * @brief The random distribution of 'b' in Cormen[267], aka 'Z sub p'
 *
 * @tparam K
 * @tparam V
 * @tparam Hash
 * @tparam Pred
 */
template <typename K, typename V, typename Hash, typename Pred>
std::uniform_int_distribution<size_t> HashMap<K, V, Hash, Pred>::_dist_b(
    0, _large_prime_p - 1);

/**
 * @brief The value of 'a' in Cormen[267]
 *
 * @tparam K
 * @tparam V
 * @tparam Hash
 * @tparam Pred
 */
template <typename K, typename V, typename Hash, typename Pred>
const size_t HashMap<K, V, Hash, Pred>::_rand_a = _dist_a(_generator);

/**
 * @brief The value of 'b' in Cormen[267]
 *
 * @tparam K
 * @tparam V
 * @tparam Hash
 * @tparam Pred
 */
template <typename K, typename V, typename Hash, typename Pred>
const size_t HashMap<K, V, Hash, Pred>::_rand_b = _dist_b(_generator);

/**
 * @brief The universal hash function from Cormen[267].
 *
 * @tparam K
 * @tparam V
 * @tparam Hash
 * @tparam Pred
 * @param key
 * @return size_t
 */
template <typename K, typename V, typename Hash, typename Pred>
size_t HashMap<K, V, Hash, Pred>::hash(const K &key) {
  size_t hashed_key = (_rand_a * Hash()(key) + _rand_b);
  hashed_key =
      hashed_key < _large_prime_p ? hashed_key : hashed_key % _large_prime_p;
  hashed_key = hashed_key < _capacity ? hashed_key : hashed_key % _capacity;
  return hashed_key;
}

/**
 * @brief Doubles the number of buckets, aka the capacity of the table
 *
 * @tparam K
 * @tparam V
 * @tparam Hash
 * @tparam Pred
 */
template <typename K, typename V, typename Hash, typename Pred>
void HashMap<K, V, Hash, Pred>::increase_capacity() {
  size_t old_capacity = _capacity;
  Node **old_table = _table;

  _capacity = _capacity ? _capacity * 2 : 1;
  _table = new Node *[_capacity] {};

  for (size_t i = 0; i < old_capacity; i++) {
    Node *node_to_move = old_table[i];
    while (node_to_move) {
      size_t hashed_key = hash(node_to_move->_key);

      if (!_table[hashed_key]) {
        _table[hashed_key] = node_to_move;
      } else {
        Node *curr_node = _table[hashed_key];
        while (curr_node->_next) curr_node = curr_node->_next;
        curr_node->_next = node_to_move;
      }

      Node *next_node = node_to_move->_next;
      node_to_move->_next = nullptr;
      node_to_move = next_node;
    }
  }

  delete[] old_table;
}

/**
 * @brief Construct a new Hash Map< K,  V,  Hash,  Pred>:: Hash Map object
 *
 * @tparam K
 * @tparam V
 * @tparam Hash
 * @tparam Pred
 */
template <typename K, typename V, typename Hash, typename Pred>
HashMap<K, V, Hash, Pred>::HashMap()
    : _size(0), _capacity(0), _table(nullptr) {}

/**
 * @brief Destroy the Hash Map< K,  V,  Hash,  Pred>:: Hash Map object
 *
 * @tparam K
 * @tparam V
 * @tparam Hash
 * @tparam Pred
 */
template <typename K, typename V, typename Hash, typename Pred>
HashMap<K, V, Hash, Pred>::~HashMap() {
  for (size_t i = 0; i < _capacity; i++) {
    Node *curr_node = _table[i];
    while (curr_node) {
      Node *next_node = curr_node->_next;
      delete curr_node;
      curr_node = next_node;
    }
  }
  delete[] _table;
}

/**
 * @brief Returns true if HashMap is empty
 *
 * @tparam K
 * @tparam V
 * @tparam Hash
 * @tparam Pred
 * @return boolean
 */
template <typename K, typename V, typename Hash, typename Pred>
bool HashMap<K, V, Hash, Pred>::is_empty() {
  return !_size;
}

/**
 * @brief Returns the number of nodes stored in the HashMap
 *
 * @tparam K
 * @tparam V
 * @tparam Hash
 * @tparam Pred
 * @return size_t
 */
template <typename K, typename V, typename Hash, typename Pred>
size_t HashMap<K, V, Hash, Pred>::size() {
  return _size;
}

/**
 * @brief Returns the current number of buckets, which is also the number of
 * nodes that can be stored before the HashMap must resize
 *
 * @tparam K
 * @tparam V
 * @tparam Hash
 * @tparam Pred
 * @return size_t
 */
template <typename K, typename V, typename Hash, typename Pred>
size_t HashMap<K, V, Hash, Pred>::capacity() {
  return _capacity;
}

/**
 * @brief Returns the ratio of size / capacity
 *
 * @tparam K
 * @tparam V
 * @tparam Hash
 * @tparam Pred
 * @return double
 */
template <typename K, typename V, typename Hash, typename Pred>
double HashMap<K, V, Hash, Pred>::load_factor() {
  return double(_size) / double(_capacity);
}

/**
 * @brief Returns true if HashMap contains the provided key
 *
 * @tparam K
 * @tparam V
 * @tparam Hash
 * @tparam Pred
 * @param key
 * @return boolean
 */
template <typename K, typename V, typename Hash, typename Pred>
bool HashMap<K, V, Hash, Pred>::has(const K &key) {
  if (!_size) return false;

  Node *curr_node = _table[hash(key)];

  while (curr_node) {
    if (curr_node->_key == key) return true;
    curr_node = curr_node->_next;
  }

  return false;
}

/**
 * @brief Returns the value associated with the provided key
 *
 * @tparam K
 * @tparam V
 * @tparam Hash
 * @tparam Pred
 * @param key
 * @return V&
 */
template <typename K, typename V, typename Hash, typename Pred>
V &HashMap<K, V, Hash, Pred>::get(const K &key) {
  if (!_size) throw std::out_of_range("key not found");

  Node *curr_node = _table[hash(key)];

  while (curr_node) {
    if (curr_node->_key == key) return curr_node->_val;
    curr_node = curr_node->_next;
  }

  throw std::out_of_range("key not found");
}

/**
 * @brief Insert or overwrite a key/value pair.
 *
 * @tparam K
 * @tparam V
 * @tparam Hash
 * @tparam Pred
 * @param key
 * @param value
 */
template <typename K, typename V, typename Hash, typename Pred>
void HashMap<K, V, Hash, Pred>::insert(const K &key, const V &value) {
  if (_size == _capacity) increase_capacity();

  size_t hashed_key = hash(key);

  if (!_table[hashed_key]) {
    _table[hashed_key] = new Node(key, value);
    _size++;
  } else {
    Node *curr_node = _table[hashed_key];

    while (curr_node->_key != key && curr_node->_next)
      curr_node = curr_node->_next;

    if (curr_node->_key == key) {
      curr_node->_val = value;
    } else {
      curr_node->_next = new Node(key, value);
      _size++;
    }
  }
}

/**
 * @brief Delete a key/value pair
 *
 * @tparam K
 * @tparam V
 * @tparam Hash
 * @tparam Pred
 * @param key
 */
template <typename K, typename V, typename Hash, typename Pred>
void HashMap<K, V, Hash, Pred>::erase(const K &key) {
  if (!_size) return;

  size_t hashed_key = hash(key);
  Node *curr_node = _table[hashed_key];
  Node *prev_node = nullptr;

  while (curr_node && curr_node->_key != key) {
    prev_node = curr_node;
    curr_node = curr_node->_next;
  }

  if (curr_node) {
    if (!prev_node) {
      _table[hashed_key] = curr_node->_next;
    } else {
      prev_node->_next = curr_node->_next;
    }

    delete curr_node;
    _size--;
  }
}
