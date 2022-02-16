#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>  // debug
#include <limits>    // max
#include <memory>    // allocator

#include "util.hpp"

namespace ft {
template <class T>
struct list_node {
  list_node *prev;
  list_node *next;
  T value;

  list_node(list_node *prev, list_node *next)
      : prev(prev), next(next), value() {}
};

template <class T>
class list_iterator;

template <class T>
class const_list_iterator;

template <class T, class Allocator = std::allocator<T> >
class list {
 public:
  typedef T value_type;
  typedef Allocator allocator_type;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef list_iterator<T> iterator;
  typedef const_list_iterator<T> const_iterator;
  typedef reverse__iterator<iterator> reverse_iterator;
  typedef reverse__iterator<const_iterator> const_reverse_iterator;
  typedef typename allocator_type::difference_type difference_type;
  typedef typename allocator_type::size_type size_type;

 private:
  typedef list_node<T> list_node;

  list_node *head;
  list_node *tail;
  allocator_type allocator;
  size_type len;

 public:
  explicit list(const allocator_type &alloc = allocator_type()) : len(0) {
    head = tail = new list_node(NULL, NULL);
    allocator = alloc;
  }
  explicit list(size_type n, const value_type &val = value_type(),
                const allocator_type &alloc = allocator_type())
      : len(0) {
    head = tail = new list_node(NULL, NULL);
    allocator = alloc;
    assign(n, val);
  }
  template <class InputIterator>
  list(InputIterator first, InputIterator last,
       const allocator_type &alloc = allocator_type())
      : len(0) {
    head = tail = new list_node(NULL, NULL);
    allocator = alloc;
    assign(first, last);
  }
  list(const list &x) : len(0) {
    head = tail = new list_node(NULL, NULL);
    allocator = x.allocator;
    assign(x.begin(), x.end());
  }

  ~list() {
    erase(begin(), end());
    delete tail;
  }

  list &operator=(const list &x) {
    clear();
    assign(x.begin(), x.end());
    return *this;
  }

  iterator begin() { return iterator(head); }

  const_iterator begin() const { return const_iterator(head); }

  iterator end() { return iterator(tail); }

  const_iterator end() const { return const_iterator(tail); }

  reverse_iterator rbegin() { return reverse_iterator(end()); }

  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  }

  reverse_iterator rend() { return reverse_iterator(begin()); }

  const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  }

  bool empty() const { return len == 0; }

  size_type size() const { return len; }

  size_type max_size() const {
    // return std::numeric_limits<difference_type>::max() / sizeof(T);
    return allocator.max_size();
  }

  reference front() { return head->value; }

  const_reference front() const { return head->value; }

  reference back() { return tail->prev->value; }

  const_reference back() const { return tail->prev->value; }

  template <class InputIterator>
  void assign(InputIterator first, InputIterator last) {
    clear();
    insert(begin(), first, last);
  }

  void assign(size_type n, const value_type &val) {
    clear();
    insert(begin(), n, val);
  }

  void push_front(const value_type &val) { insert(begin(), val); }

  void pop_front() { erase(begin()); }

  void push_back(const value_type &val) { insert(end(), val); }

  void pop_back() { erase(--end()); }

  iterator insert(iterator position, const value_type &val) {
    list_node *node =
        new list_node(position.get_node()->prev, position.get_node());

    node->value = val;
    if (node->prev)
      node->prev->next = node;
    else
      head = node;
    node->next->prev = node;
    len++;
    return iterator(node);
  }

  void insert(iterator position, size_type n, const value_type &val) {
    list_node *node1 = position.get_node()->prev;
    list_node *node2 = position.get_node();
    list_node *cnt = node1;

    while (n > 0) {
      list_node *node = new list_node(cnt, NULL);
      node->value = val;
      if (node->prev)
        node->prev->next = node;
      else
        head = node;
      cnt = node;
      len++;
      n--;
    }
    node2->prev = cnt;
    if (cnt) cnt->next = node2;
  }

  template <class InputIterator>
  typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type
  insert(iterator position, InputIterator first, InputIterator last) {
    list_node *node1 = position.get_node()->prev;
    list_node *node2 = position.get_node();
    list_node *cnt = node1;

    for (InputIterator ite = first; ite != last; ite++) {
      list_node *node = new list_node(cnt, NULL);
      node->value = *ite;
      if (node->prev)
        node->prev->next = node;
      else
        head = node;
      cnt = node;
      len++;
    }
    node2->prev = cnt;
    if (cnt) cnt->next = node2;
  }

  iterator erase(iterator first, iterator last) {
    list_node *node1 = first.get_node()->prev;
    list_node *node2 = last.get_node();
    iterator cnt = first;

    while (cnt != last) {
      iterator tmp(cnt);
      cnt++;
      len--;
      delete tmp.get_node();
    }
    if (node1)
      node1->next = node2;
    else
      head = node2;
    node2->prev = node1;
    return iterator(node2);
  }

  iterator erase(iterator position) {
    iterator last = position;

    last++;
    return erase(position, last);
  }

  void splice(iterator position, list &x) {
    splice(position, x, x.begin(), x.end());
  }

  void splice(iterator position, list &x, iterator i) {
    iterator tmp = i;

    tmp++;
    splice(position, x, i, tmp);
  }

  void splice(iterator position, list &x, iterator first, iterator last) {
    list_node *node1 = position.get_node()->prev;
    list_node *node2 = position.get_node();
    list_node *_node1 = first.get_node()->prev;
    list_node *_node2 = last.get_node();
    size_type splice_length = 0;

    while (first != last) {
      list_node *tmp = first.get_node();

      if (node1)
        node1->next = tmp;
      else
        head = tmp;
      tmp->prev = node1;
      node1 = tmp;
      first++;
      splice_length++;
    }
    node1->next = node2;
    node2->prev = node1;
    if (_node1)
      _node1->next = _node2;
    else
      x.head = _node2;
    _node2->prev = _node1;
    len += splice_length;
    x.len -= splice_length;
  }

  void clear() { erase(begin(), end()); }

  void resize(size_type n, value_type val = value_type()) {
    if (n < len) {
      iterator ite = begin();
      for (size_type i = 0; i < n; i++) ++ite;
      erase(ite, end());
    } else
      insert(end(), n - len, val);
  }

  void swap(list &x) {
    std::swap(head, x.head);
    std::swap(tail, x.tail);
    std::swap(len, x.len);
    std::swap(allocator, x.allocator);
  }

  void remove(const value_type &val) {
    iterator ite = begin();

    while (ite != end()) {
      if (*ite == val) erase(ite);
      ++ite;
    }
  }

  template <class Predicate>
  void remove_if(Predicate pred) {
    iterator ite = begin();

    while (ite != end()) {
      if (pred(*ite)) erase(ite);
      ++ite;
    }
  }

  void unique() {
    if (begin() == end()) return;
    iterator left = begin();
    iterator right = left;
    ++right;

    while (right != end()) {
      if (*left == *right)
        right = erase(right);
      else
        left = right++;
    }
  }

  template <class BinaryPredicate>
  void unique(BinaryPredicate binary_pred) {
    if (begin() == end()) return;
    iterator left = begin();
    iterator right = left;
    ++right;

    while (right != end()) {
      if (binary_pred(*left, *right))
        right = erase(right);
      else
        left = right++;
    }
  }

  void sort() {
    if (begin() == end()) return;
    for (size_type i = 0; i < len; i++) {
      iterator left = begin();
      iterator right = left;
      ++right;
      while (right != end()) {
        if (*left > *right) {
          splice(left, *this, right);
          right = left;
        } else
          left = right;
        right++;
      }
    }
  }

  template <class Compare>
  void sort(Compare comp) {
    if (begin() == end()) return;
    for (size_type i = 0; i < len; i++) {
      iterator left = begin();
      iterator right = left;
      ++right;
      while (right != end()) {
        if (!comp(*left, *right)) {
          splice(left, *this, right);
          right = left;
        } else
          left = right;
        right++;
      }
    }
  }

  void merge(list &x) {
    iterator ite1 = begin();
    iterator ite2 = x.begin();

    while (ite2 != x.end()) {
      while (ite1 != end() && *ite1 <= *ite2) ++ite1;
      list_node *node1 = ite1.get_node();
      list_node *node2 = ite2.get_node();
      ++ite2;

      if (node1->prev)
        node1->prev->next = node2;
      else
        head = node2;
      node2->prev = node1->prev;
      node1->prev = node2;
      node2->next = node1;
    }
    len += x.len;
    x.len = 0;
    x.head = x.tail;
    x.tail->prev = NULL;
  }

  template <class Compare>
  void merge(list &x, Compare comp) {
    iterator ite1 = begin();
    iterator ite2 = x.begin();

    while (ite2 != x.end()) {
      while (ite1 != end() && !comp(*ite2, *ite1)) ++ite1;
      list_node *node1 = ite1.get_node();
      list_node *node2 = ite2.get_node();
      ++ite2;

      if (node1->prev)
        node1->prev->next = node2;
      else
        head = node2;
      node2->prev = node1->prev;
      node1->prev = node2;
      node2->next = node1;
    }
    len += x.len;
    x.len = 0;
    x.head = x.tail;
    x.tail->prev = NULL;
  }

  void reverse() {
    iterator it = begin();
    iterator begin = it;
    while (1) {
      iterator tmp = it;
      it++;
      if (tmp.get_node()->next != tail)
        std::swap(tmp.get_node()->prev, tmp.get_node()->next);
      else {
        tmp.get_node()->next = tmp.get_node()->prev;
        tmp.get_node()->prev = NULL;
        head = tmp.get_node();
        tail->prev = begin.get_node();
        begin.get_node()->next = tail;
        break;
      }
    }
  }
};

template <class T, class Alloc>
bool operator==(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs) {
  if (lhs.size() == rhs.size())
    return equal(lhs.begin(), lhs.end(), rhs.begin());
  return false;
}

template <class T, class Alloc>
bool operator!=(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs) {
  return !(lhs == rhs);
}

template <class T, class Alloc>
bool operator<(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs) {
  return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                 rhs.end());
}

template <class T, class Alloc>
bool operator<=(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs) {
  return !(lhs > rhs);
}

template <class T, class Alloc>
bool operator>(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs) {
  return rhs < lhs;
}

template <class T, class Alloc>
bool operator>=(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs) {
  return !(lhs < rhs);
}

template <class T, class Alloc>
void swap(list<T, Alloc> &x, list<T, Alloc> &y) {
  x.swap(y);
}

template <class T>
class list_iterator {
 public:
  typedef bidirectional_iterator_tag iterator_category;
  typedef T value_type;
  typedef std::ptrdiff_t difference_type;
  typedef T *pointer;
  typedef T &reference;
  typedef list_node<T> list_node;

 private:
  list_node *node;

 public:
  list_iterator() : node(NULL) {}
  list_iterator(list_node *node) : node(node) {}
  list_iterator(const list_iterator &other) : node(other.node) {}

  ~list_iterator() {}

  list_node *get_node() { return node; }

  list_iterator<T> &operator=(const list_iterator<T> &other) {
    node = other.node;
    return *this;
  }

  list_iterator<T> &operator++() {
    node = node->next;
    return *this;
  }

  list_iterator<T> operator++(int) {
    list_iterator<T> ret = *this;
    ++*this;
    return ret;
  }

  list_iterator<T> &operator--() {
    node = node->prev;
    return *this;
  }

  list_iterator<T> operator--(int) {
    list_iterator<T> ret = *this;
    --*this;
    return ret;
  }

  reference operator*() const { return node->value; }

  pointer operator->() const { return &node->value; }

  friend void swap(const list_iterator &a, const list_iterator &b) {
    list_iterator tmp(a);
    a = b;
    b = tmp;
  }

  friend bool operator==(const list_iterator &lhs, const list_iterator &rhs) {
    return lhs.node == rhs.node;
  }

  friend bool operator!=(const list_iterator &lhs, const list_iterator &rhs) {
    return !(lhs.node == rhs.node);
  }
};

template <class T>
class const_list_iterator {
 public:
  typedef bidirectional_iterator_tag iterator_category;
  typedef T value_type;
  typedef std::ptrdiff_t difference_type;
  typedef const T *pointer;
  typedef const T &reference;
  typedef list_node<T> list_node;
  typedef list_iterator<T> iterator;

 private:
  const list_node *node;

 public:
  const_list_iterator() : node(NULL) {}
  const_list_iterator(const list_node *node) : node(node) {}
  const_list_iterator(const const_list_iterator &other) : node(other.node) {}

  ~const_list_iterator() {}

  list_node *get_node() { return node; }

  const_list_iterator<T> &operator=(const const_list_iterator<T> &other) {
    node = other.node;
    return *this;
  }

  const_list_iterator<T> &operator++() {
    node = node->next;
    return *this;
  }

  const_list_iterator<T> operator++(int) {
    const_list_iterator<T> ret = *this;
    ++*this;
    return ret;
  }

  const_list_iterator<T> &operator--() {
    node = node->prev;
    return *this;
  }

  const_list_iterator<T> operator--(int) {
    const_list_iterator<T> ret = *this;
    --*this;
    return ret;
  }

  reference operator*() const { return node->value; }

  pointer operator->() const { return &node->value; }

  friend void swap(const const_list_iterator &a, const const_list_iterator &b) {
    const_list_iterator tmp(a);
    a = b;
    b = tmp;
  }

  friend bool operator==(const const_list_iterator &lhs,
                         const const_list_iterator &rhs) {
    return lhs.node == rhs.node;
  }

  friend bool operator!=(const const_list_iterator &lhs,
                         const const_list_iterator &rhs) {
    return !(lhs.node == rhs.node);
  }
};
}  // namespace ft

#endif