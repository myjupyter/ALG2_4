#include <iostream>

template <typename Type>
class AVLTree {
  public:
    struct Node {
      Type value;
      int height;
      Node* left;
      Node* right;
      Node(Type value_) : value(value_),
                          height(0),
                          left(nullptr),
                          right(nullptr) {}
    };
    AVLTree();
    ~AVLTree();
  private:
    Node* root_;
};

template <typename Type>
AVLTree<Type>::AVLTree() : root_(nullptr) {}

template <typename Type>
AVLTree<Type>::~AVLTree() {}

int main(int argc, char** argv) {
  AVLTree<int> tree;
  tree.~AVLTree();
  return 0;
}
