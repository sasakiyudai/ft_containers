#ifndef MAP_HPP
#define MAP_HPP

#include <functional>
#include <iostream>
#include <memory>

#include "stack.hpp"
#include "util.hpp"

namespace ft {
template <class Key, class T, class value_compare, class key_compare>
class map_iterator;

template <class Key, class T, class value_compare, class key_compare>
class const_map_iterator;

template <class T>
struct tree_node;

template <class Key, class T, class Compare = std::less<Key>,
          class Alloc = std::allocator<std::pair<const Key, T> > >
class map {
 public:
  typedef Key key_type;
  typedef T mapped_type;
  typedef std::pair<const key_type, mapped_type> value_type;
  typedef Compare key_compare;
  class value_compare : std::binary_function<value_type, value_type, bool> {
    friend class map;

   public:
    Compare comp;
    value_compare(Compare c) : comp(c) {}
    typedef bool result_type;
    typedef value_type first_argument_type;
    typedef value_type second_argument_type;
    bool operator()(const value_type &x, const value_type &y) const {
      return comp(x.first, y.first);
    }
  };
  typedef Alloc allocator_type;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef map_iterator<key_type, value_type, value_compare, key_compare>
      iterator;
  typedef const_map_iterator<key_type, value_type, value_compare, key_compare>
      const_iterator;
  typedef reverse__iterator<iterator> reverse_iterator;
  typedef reverse__iterator<const_iterator> const_reverse_iterator;
  typedef ptrdiff_t difference_type;
  typedef size_t size_type;

 private:
  typedef tree_node<value_type> tree_node;

  tree_node *root;
  allocator_type allocator;
  key_compare comp;
  value_compare vcomp;

  void delete_node(tree_node *deleted, tree_node *parent) {
    if (deleted->left && deleted->right) {
      parent = deleted;
      tree_node *cur = deleted->right;
      while (cur->left) {
        parent = cur;
        cur = cur->left;
      }
      std::swap(deleted->value, cur->value);
      delete_node(cur, parent);
      return;
    } else if (deleted->left) {
      if (!parent)
        root = deleted->left;
      else if (deleted == parent->left)
        parent->left = deleted->left;
      else
        parent->right = deleted->left;
    } else {
      if (!parent)
        root = deleted->right;
      else if (deleted == parent->left)
        parent->left = deleted->right;
      else
        parent->right = deleted->right;
    }
    if (!deleted) return;
    if (deleted->value) delete deleted->value;
    delete deleted;
  }

  void all_delete(tree_node *root) {
    if (!root) return;
    all_delete(root->left);
    all_delete(root->right);
    if (root->value) delete root->value;
    delete root;
    root = NULL;
  }

  tree_node *search(const key_type &k, tree_node *node) const {
    if (!node)
      return NULL;
    else if (comp(k, node->value->first))
      return search(k, node->left);
    else if (comp(node->value->first, k))
      return search(k, node->right);
    return node;
  }

 public:
  explicit map(const key_compare &comp = key_compare(),
               const allocator_type &alloc = allocator_type())
      : allocator(alloc), comp(comp), vcomp(value_compare(comp)) {
    root = NULL;
  }

  template <class InputIterator>
  map(InputIterator first, InputIterator last,
      const key_compare &comp = key_compare(),
      const allocator_type &alloc = allocator_type())
      : allocator(alloc), comp(comp), vcomp(value_compare(comp)) {
    root = NULL;
    insert(first, last);
  }

  map(const map &x)
      : allocator(x.allocator), comp(x.comp), vcomp(value_compare(x.comp)) {
    root = NULL;
    insert(x.begin(), x.end());
  }

  ~map() { all_delete(root); }

  map &operator=(const map &x) {
    all_delete(root);
    comp = x.comp;
    vcomp = x.vcomp;
    allocator = x.allocator;
    root = NULL;

    insert(x.begin(), x.end());
    return *this;
  }

  iterator begin() {
    if (root == NULL)
      return iterator(static_cast<tree_node *>(NULL), root);
    else
      return iterator(root->begin(), root);
  }

  const_iterator begin() const {
    if (root == NULL)
      return const_iterator(static_cast<tree_node *>(NULL), root);
    else
      return const_iterator(root->begin(), root);
  }

  iterator end() { return iterator(static_cast<tree_node *>(NULL), root); }

  const_iterator end() const {
    return const_iterator(static_cast<tree_node *>(NULL), root);
  }

  reverse_iterator rbegin() { return reverse_iterator(end()); }

  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  }

  reverse_iterator rend() { return reverse_iterator(begin()); }

  const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  }

  bool empty() const { return root == NULL; }

  size_type size() const {
    if (root == NULL)
      return 0;
    else
      return static_cast<size_type>(root->size());
  }

  size_type max_size() const { return allocator.max_size(); }

  mapped_type &operator[](const key_type &k) {
    return (*((this->insert(std::make_pair(k, mapped_type()))).first)).second;
  }

  std::pair<iterator, bool> insert(const value_type &val) {
    tree_node *cur = root;
    tree_node *new_node;

    while (1) {
      if (cur == NULL) {
        root = new tree_node(NULL, NULL, new value_type(val));
        new_node = root;
        break;
      }
      if (!vcomp(*cur->value, val) && !vcomp(val, *cur->value))
        return make_pair(iterator(cur, root), false);
      if (vcomp(val, *cur->value)) {
        if (cur->left)
          cur = cur->left;
        else {
          new_node = new tree_node(NULL, NULL, new value_type(val));
          cur->left = new_node;
          break;
        }
      } else {
        if (cur->right)
          cur = cur->right;
        else {
          new_node = new tree_node(NULL, NULL, new value_type(val));
          cur->right = new_node;
          break;
        }
      }
    }
    root->rebalance();
    return make_pair(iterator(new_node, root), true);
  }

  iterator insert(iterator position, const value_type &val) {
    (void)position;
    tree_node *cur = root;
    tree_node *new_node;

    while (1) {
      if (cur == NULL) {
        root = new tree_node(NULL, NULL, new value_type(val));
        new_node = root;
        break;
      }
      if (!vcomp(*cur->value, val) && !vcomp(val, *cur->value))
        return iterator(cur, root);
      if (vcomp(val, *cur->value)) {
        if (cur->left)
          cur = cur->left;
        else {
          new_node = new tree_node(NULL, NULL, new value_type(val));
          cur->left = new_node;
          break;
        }
      } else {
        if (cur->right)
          cur = cur->right;
        else {
          new_node = new tree_node(NULL, NULL, new value_type(val));
          cur->right = new_node;
          break;
        }
      }
    }
    root->rebalance();
    return iterator(new_node, root);
  }

  template <class InputIterator>
  typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type
  insert(InputIterator first, InputIterator last) {
    for (; first != last; ++first) insert(*first);
  }

  void erase(iterator position) {
    if (position.node == root)
      delete_node(position.node, NULL);
    else
      delete_node(position.node, position.q.top());
    if (root) root->rebalance();
  }

  size_type erase(const key_type &k) {
    iterator node_iter = find(k);

    if (node_iter == end()) return 0;
    erase(node_iter);
    return 1;
  }

  void erase(iterator first, iterator last) {
    stack<key_type> tmp;

    for (iterator iter = first; iter != last; ++iter)
      tmp.push(iter.node->value->first);
    while (!tmp.empty()) {
      erase(tmp.top());
      tmp.pop();
    }
  }

  void swap(map &x) { std::swap(root, x.root); }

  void clear() {
    all_delete(root);
    root = NULL;
  }

  key_compare key_comp() const { return comp; }

  value_compare value_comp() const { return vcomp; }

  iterator find(const key_type &k) { return iterator(k, root); }

  const_iterator find(const key_type &k) const {
    return const_iterator(k, root);
  }

  size_type count(const key_type &k) const {
    if (search(k, root))
      return 1;
    else
      return 0;
  }

  iterator lower_bound(const key_type &k) {
    for (iterator iter = begin(); iter != end(); iter++)
      if (!comp(iter->first, k)) return iter;
    return end();
  }

  const_iterator lower_bound(const key_type &k) const {
    for (const_iterator iter = begin(); iter != end(); iter++)
      if (!comp(iter->first, k)) return iter;
    return end();
  }

  iterator upper_bound(const key_type &k) {
    for (iterator iter = begin(); iter != end(); iter++)
      if (comp(k, iter->first)) return iter;
    return end();
  }

  const_iterator upper_bound(const key_type &k) const {
    for (const_iterator iter = begin(); iter != end(); iter++)
      if (comp(k, iter->first)) return iter;
    return end();
  }

  std::pair<const_iterator, const_iterator> equal_range(
      const key_type &k) const {
    return std::pair<const_iterator, const_iterator>(lower_bound(k),
                                                     upper_bound(k));
  }

  std::pair<iterator, iterator> equal_range(const key_type &k) {
    return std::pair<iterator, iterator>(lower_bound(k), upper_bound(k));
  }
};

template <class T>
struct tree_node {
  tree_node *left;
  tree_node *right;
  T *value;
  long height;

  tree_node(tree_node *left = NULL, tree_node *right = NULL, T *value = NULL)
      : left(left), right(right), value(value) {
    set_height();
  }

  void set_height() {
    if (value == NULL)
      height = 0;
    else {
      long left_height = left ? left->height + 1 : 1;
      long right_height = right ? right->height + 1 : 1;
      height = std::max(left_height, right_height);
    }
  }

  long size() const {
    long left_size;
    long right_size;

    if (left)
      left_size = left->size();
    else
      left_size = 0;
    if (right)
      right_size = right->size();
    else
      right_size = 0;
    return left_size + right_size + 1;
  }

  tree_node *begin() {
    if (left == NULL) return this;
    return left->begin();
  }

  void left_rotate() {
    if (right == NULL) return;
    std::swap(value, right->value);
    tree_node *tmp = left;
    left = right;
    right = left->right;
    left->right = left->left;
    left->left = tmp;
    left->set_height();
    set_height();
  }

  void right_rotate() {
    if (left == NULL) return;
    std::swap(value, left->value);
    tree_node *tmp = right;
    right = left;
    left = right->left;
    right->left = right->right;
    right->right = tmp;
    right->set_height();
    set_height();
  }

  long calc_co() {
    long left_height;
    long right_height;

    if (left)
      left_height = left->height;
    else
      left_height = 0;
    if (right)
      right_height = right->height;
    else
      right_height = 0;
    return left_height - right_height;
  }

  void balancing() {
    set_height();
    long co = calc_co();

    if (co > 1) {
      if (left->calc_co() < 0) left->left_rotate();
      right_rotate();
    } else if (co < -1) {
      if (right->calc_co() > 0) right->right_rotate();
      left_rotate();
    }
  }

  void rebalance() {
    if (left) left->rebalance();
    if (right) right->rebalance();
    balancing();
  }
};

template <class Key, class T, class value_compare, class key_compare>
class map_iterator {
 public:
  typedef bidirectional_iterator_tag iterator_category;
  typedef Key key_type;
  typedef T value_type;
  typedef std::ptrdiff_t difference_type;
  typedef value_type *pointer;
  typedef value_type &reference;
  typedef tree_node<value_type> tree_node;

 public:
  tree_node *node;
  stack<tree_node *> q;
  value_compare vcomp;
  key_compare comp;

 private:
  void go_first() {
    if (node == NULL || node->left == NULL) return;
    q.push(node);
    node = node->left;
    go_first();
  }

  void go_next() {
    tree_node *child;

    if (node == NULL) {
      node = q.top();
      go_first();
      return;
    }
    if (node->right) {
      q.push(node);
      node = node->right;
      go_first();
      return;
    }
    while (!q.empty()) {
      child = node;
      node = q.top();
      q.pop();
      if (node->left == child) return;
    }
    q.push(node);
    node = NULL;
  }

  void go_last() {
    if (node == NULL || node->right == NULL) return;
    q.push(node);
    node = node->right;
    go_last();
  }

  void go_prev() {
    tree_node *child;

    if (node == NULL) {
      node = q.top();
      go_last();
      return;
    }
    if (node->left) {
      q.push(node);
      node = node->left;
      go_last();
      return;
    }
    while (!q.empty()) {
      child = node;
      node = q.top();
      q.pop();
      if (node->right == child) return;
    }
    q.push(node);
    node = NULL;
  }

 public:
  map_iterator()
      : node(NULL), vcomp(value_compare(key_compare())), comp(key_compare()) {}

  map_iterator(tree_node *node, tree_node *root)
      : node(node), vcomp(value_compare(key_compare())), comp(key_compare()) {
    if (node == NULL)
      q.push(root);
    else {
      tree_node *cur = root;
      while (cur != node) {
        q.push(cur);
        if (vcomp(*node->value, *cur->value))
          cur = cur->left;
        else
          cur = cur->right;
      }
    }
  }

  map_iterator(const key_type &k, tree_node *root)
      : node(root), vcomp(value_compare(key_compare())), comp(key_compare()) {
    while (node != NULL) {
      if (comp(k, node->value->first)) {
        q.push(node);
        node = node->left;
      } else if (comp(node->value->first, k)) {
        q.push(node);
        node = node->right;
      } else
        return;
    }
    long len = q.size();
    while (len > 1) {
      q.pop();
      --len;
    }
  }

  map_iterator(const map_iterator &other)
      : node(other.node),
        q(other.q),
        vcomp(value_compare(key_compare())),
        comp(key_compare()) {}

  ~map_iterator() {}

  map_iterator &operator=(const map_iterator &other) {
    node = other.node;
    q = other.q;
    vcomp = other.vcomp;
    comp = other.comp;
    return *this;
  }

  reference operator*() const { return *node->value; }

  pointer operator->() const { return node->value; }

  map_iterator &operator++() {
    go_next();
    return *this;
  }

  map_iterator operator++(int) {
    map_iterator ret(*this);
    go_next();
    return ret;
  }

  map_iterator &operator--() {
    go_prev();
    return *this;
  }

  map_iterator operator--(int) {
    map_iterator ret(*this);
    go_prev();
    return ret;
  }

  friend void swap(const map_iterator &a, const map_iterator &b) {
    map_iterator tmp(a);
    a = b;
    b = tmp;
  }

  friend bool operator==(const map_iterator &lhs, const map_iterator &rhs) {
    return lhs.node == rhs.node;
  }

  friend bool operator!=(const map_iterator &lhs, const map_iterator &rhs) {
    return !(lhs.node == rhs.node);
  }
};

template <class Key, class T, class value_compare, class key_compare>
class const_map_iterator {
 public:
  typedef bidirectional_iterator_tag iterator_category;
  typedef Key key_type;
  typedef T value_type;
  typedef std::ptrdiff_t difference_type;
  typedef const value_type *pointer;
  typedef const value_type &reference;
  typedef tree_node<value_type> tree_node;

 public:
  tree_node *node;
  stack<tree_node *> q;
  value_compare vcomp;
  key_compare comp;

 private:
  void go_first() {
    if (node == NULL || node->left == NULL) return;
    q.push(node);
    node = node->left;
    go_first();
  }

  void go_next() {
    tree_node *child;

    if (node == NULL) {
      node = q.top();
      go_first();
      return;
    }
    if (node->right) {
      q.push(node);
      node = node->right;
      go_first();
      return;
    }
    while (!q.empty()) {
      child = node;
      node = q.top();
      q.pop();
      if (node->left == child) return;
    }
    q.push(node);
    node = NULL;
  }

  void go_last() {
    if (node == NULL || node->right == NULL) return;
    q.push(node);
    node = node->right;
    go_last();
  }

  void go_prev() {
    tree_node *child;

    if (node == NULL) {
      node = q.top();
      go_last();
      return;
    }
    if (node->left) {
      q.push(node);
      node = node->left;
      go_last();
      return;
    }
    while (!q.empty()) {
      child = node;
      node = q.top();
      q.pop();
      if (node->right == child) return;
    }
    q.push(node);
    node = NULL;
  }

 public:
  const_map_iterator()
      : node(NULL), vcomp(value_compare(key_compare())), comp(key_compare()) {}

  const_map_iterator(tree_node *node, tree_node *root)
      : node(node), vcomp(value_compare(key_compare())), comp(key_compare()) {
    if (node == NULL)
      q.push(root);
    else {
      tree_node *cur = root;
      while (cur != node) {
        q.push(cur);
        if (vcomp(*node->value, *cur->value))
          cur = cur->left;
        else
          cur = cur->right;
      }
    }
  }

  const_map_iterator(const key_type &k, tree_node *root)
      : node(root), comp(key_compare()), vcomp(value_compare(key_compare())) {
    while (node != NULL) {
      if (comp(k, node->value->first)) {
        q.push(node);
        node = node->left;
      } else if (comp(node->value->first, k)) {
        q.push(node);
        node = node->right;
      } else
        return;
    }
    long len = q.size();
    while (len > 1) {
      q.pop();
      --len;
    }
  }

  const_map_iterator(const const_map_iterator &other)
      : node(other.node),
        q(other.q),
        vcomp(value_compare(key_compare())),
        comp(key_compare()) {}

  ~const_map_iterator() {}

  const_map_iterator &operator=(const const_map_iterator &other) {
    node = other.node;
    q = other.q;
    vcomp = other.vcomp;
    comp = other.comp;
    return *this;
  }

  reference operator*() const { return *node->value; }

  pointer operator->() const { return node->value; }

  const_map_iterator &operator++() {
    go_next();
    return *this;
  }

  const_map_iterator operator++(int) {
    const_map_iterator ret(*this);
    go_next();
    return ret;
  }

  const_map_iterator &operator--() {
    go_prev();
    return *this;
  }

  const_map_iterator operator--(int) {
    const_map_iterator ret(*this);
    go_prev();
    return ret;
  }

  friend void swap(const const_map_iterator &a, const const_map_iterator &b) {
    const_map_iterator tmp(a);
    a = b;
    b = tmp;
  }

  friend bool operator==(const const_map_iterator &lhs,
                         const const_map_iterator &rhs) {
    return lhs.node == rhs.node;
  }

  friend bool operator!=(const const_map_iterator &lhs,
                         const const_map_iterator &rhs) {
    return !(lhs.node == rhs.node);
  }
};

}  // namespace ft

#endif
