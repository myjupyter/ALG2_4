#include <iostream>

template <typename Type>
class AVLTree {
  public:
    class Node {
      private:
      Type value_;
      size_t height_;
      size_t count_;
      Node* left_;
      Node* right_;
      public:
      Node(Type value) : value_(value),
                          height_(0),
                          count_(0),
                          left_(nullptr),
                          right_(nullptr) {}

      int balance_factor() const;
      void set_height();
      void set_count();
      void left_little_rotate();
      void right_little_rotate();
      void insert(Type value);
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


template <typename Type>
int AVLTree<Type>::Node::balance_factor() const {
  return (left_ ? left_->height_ : 0) - (right_ ? right_->height_ : 0);
}

template <typename Type>
void AVLTree<Type>::Node::left_little_rotate() {
  Node* temp = this->left_;
  this->left_ = temp->right_;
  temp->right_ = this;
  this = temp;
  this->set_height();
  this->right_->set_height();
}

template <typename Type>
void AVLTree<Type>::Node::right_little_rotate() {
  Node* temp = this->right_;
  this->right_ = temp->left_;
  temp->left_ = this;
  this = temp;
  this->set_height();
  this->left_->set_height();
}

template <typename Type>
void AVLTree<Type>::Node::set_height() {
  size_t left_height = left_ ? left_->height_ : 0;
  size_t right_height = right_ ? right_->height_ : 0;
  height_ = left_height < right_height ? right_height + 1 : left_height + 1;
}

template <typename Type>
void AVLTree<Type>::Node::set_count() {
  count_ = (left_ ? left_->count_ : 0) + (right_ ? right_->count_ : 0) + 1;
}

template <typename Type>
void AVLTree<Type>::Node::insert(Type value) {
  if(!this) {
     this = new Node(key);
     return;
  }
	if( value < this->value ) {
		this->left->insert(value);
  }
	else {
		this->right->insert(value);
  }
	this->balance();
}

int main(int argc, char** argv) {
  AVLTree<int> tree;
  tree.~AVLTree();
  return 0;
}
