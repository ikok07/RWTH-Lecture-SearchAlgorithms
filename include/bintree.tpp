#include "bintree.hpp"

template <typename T>
BTree<T>::BTree(T *item)
    : data(item), parent(nullptr), left(nullptr), right(nullptr) {}

template <typename T>
BTree<T>::BTree(T *item, BTree<T> *parent)
    : data(item), parent(parent), left(nullptr), right(nullptr) {}

template <typename T>
void BTree<T>::explore(std::function<bool(BTree<T> *)> cb) {
  if (!cb(this))
    return;

  if (this->left)
    this->left->explore(cb);
  if (this->right)
    this->right->explore(cb);
}

template <typename T>
T *BTree<T>::search(std::function<int(T *)> compare) {
  const int result = compare(this->data);
  if (result == 0) return this->data;

  if (result < 0 && this->left) return this->left->search(compare);
  else if (result > 0 && this->right) return this->right->search(compare);
  return nullptr;
}

template <typename T> void BTree<T>::insert(T *item) {
  if (*item < *(this->data)) {
    if (this->left != nullptr) {
      this->left->insert(item);
    } else {
      this->left = new BTree(item, this);
    }
  } else if (*item > *(this->data)) {
    if (this->right != nullptr) {
      this->right->insert(item);
    } else {
      this->right = new BTree(item, this);
    }
  }
}

template <typename T> T *BTree<T>::remove(std::function<int(T *)> compare) {
  int result = compare(this->data);
  if (result == 0) {
    // Node found
    bool leftAvail = this->left != nullptr;
    bool rightAvail = this->right != nullptr;
    auto parent_child = this->parent ?
                                                this->parent->left == this ? &(this->parent->left) :
                                                &(this->parent->right)
                                    : nullptr;

    T *curr_data = this->data;
    if (!leftAvail && !rightAvail) {
      // Leaf node. Just delete it
      if (parent_child) {
        // It's not the root
        *parent_child = nullptr;
        delete this;
      } else {
        this->data = nullptr;
      }
      return curr_data;
    }

    if (((leftAvail && !rightAvail) || (!leftAvail && rightAvail)) && parent_child) {
      // One child node only and it is not the root.
      BTree<T> *child = leftAvail ? this->left : this->right;
      *parent_child = child;
      child->parent = this->parent;

      this->left = nullptr;
      this->right = nullptr;
      delete this;
      return curr_data;
    }

    // Two child nodes or this is the root node
    BTree<T> *replace_node = this->find_successor();
    if (!replace_node) replace_node = this->find_predecessor();
    if (!replace_node) return nullptr;

    this->data = replace_node->data;
    BTree<T> *replacement_child = replace_node->left ? replace_node->left : replace_node->right;
    if (replace_node->parent->left == replace_node) replace_node->parent->left = replacement_child;
    else replace_node->parent->right = replacement_child;

    if (replacement_child) replacement_child->parent = replace_node->parent;

    replace_node->left = nullptr;
    replace_node->right = nullptr;

    delete replace_node;
    return curr_data;
  }

  // Continue to search for target node
  if (result < 0) {
    if (this->left == nullptr) return nullptr;
    return this->left->remove(compare);
  }

  if (this->right == nullptr) return nullptr;
  return this->right->remove(compare);
}

template <typename T> BTree<T> *BTree<T>::find_successor() {
  BTree<T> *node = this->right;
  if (!node) return nullptr;

  while (node->left) {
    node = node->left;
  }

  return node;
}

template <typename T> BTree<T> *BTree<T>::find_predecessor() {
  BTree<T> *node = this->left;
  if (!node) return nullptr;

  while (node->right) {
    node = node->right;
  }

  return node;
}