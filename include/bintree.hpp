#ifndef INCLUDE_BINTREE
#define INCLUDE_BINTREE

#include <functional>

template <typename T> class BTree {
private:
  T *data;
  BTree *parent;
  BTree *left;
  BTree *right;

  BTree *find_successor();
  BTree *find_predecessor();

public:
  BTree(T *item);
  BTree(T *item, BTree<T> *parent);

  T *get_data() { return this->data; }

  void explore(std::function<bool(BTree<T> *)> cb);
  T *search(std::function<int(T *)> compare);
  void insert(T *item);
  T *remove(std::function<int(T *)> compare);
};

#include "bintree.tpp"

#endif /* INCLUDE_BINTREE */
