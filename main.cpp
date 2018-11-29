#include <iostream>

template <typename Type>
class AVLTree {
  public:
    AVLTree();
    ~AVLTree();
		size_t size() const;
		void add(Type value);
		
  private:
    class Node {
      private:
        Type value_;
        size_t height_;
        size_t count_;
        Node* left_;
        Node* right_;
      public:
        Node(Type value);
        ~Node();
        Node* balance(Node* p);
        int balance_factor() const;
				size_t get_count() const;
        void set_height();
        void set_count();
        Node* left_little_rotate(Node* q);
        Node* right_little_rotate(Node* p);
        Node* insert(Node* p, Type value);
    };
    Node* root_;
};

template <typename Type>
AVLTree<Type>::AVLTree() : root_(nullptr) {}

template <typename Type>
AVLTree<Type>::Node::Node(Type value)
	: value_(value), height_(1), count_(1), left_(nullptr), right_(nullptr) {}

template <typename Type>
AVLTree<Type>::Node::~Node() {
	if(right_) delete right_;
	if(left_) delete left_;
}

template <typename Type>
AVLTree<Type>::~AVLTree() {
	if(root_) delete root_;
}

template <typename Type>
typename AVLTree<Type>::Node* AVLTree<Type>::Node::balance(Node* p) {
	p->set_height();
	p->set_count();
	switch(p->balance_factor()) {
		case 2:
			if(p->right_->balance_factor() < 0) {
				p->right_ = p->right_little_rotate(p->right_);
			}
			return p->left_little_rotate(p);
		case -2:
			if(p->left_->balance_factor() > 0) {
				p->left_ = p->left_little_rotate(p->left_);
			}
			return p->right_little_rotate(p);
		default: break;
	}
	return p;
}

template <typename Type>
int AVLTree<Type>::Node::balance_factor() const {
  return (right_ ? right_->height_ : 0) - (left_ ? left_->height_ : 0);
}

template <typename Type>
typename AVLTree<Type>::Node* 
AVLTree<Type>::Node::left_little_rotate(Node* q) {
  Node* p = q->right_;
  q->right_ = p->left_;
  p->left_ = q;
  q->set_height();
  p->set_height();
	return p;
}

template <typename Type>
typename AVLTree<Type>::Node*
AVLTree<Type>::Node::right_little_rotate(Node* p) {
  Node* q = p->left_;
  p->left_ = q->right_;
  q->right_ = p;
  p->set_height();
  q->set_height();
	return q;
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
size_t AVLTree<Type>::Node::get_count() const {
	return this->count_;
}

template <typename Type>
size_t AVLTree<Type>::size() const {
	return root_->get_count();
}

template <typename Type>
typename AVLTree<Type>::Node*
AVLTree<Type>::Node::insert(Node* p, Type value) {
	if(!p) {
		return new Node(value);
	}
	if(value < p->value_) {
		p->left_ = insert(p->left_, value);
	}
	else {
		p->right_ = insert(p->right_, value);
	}
	return this->balance(p);
}

template <typename Type>
void AVLTree<Type>::add(Type value) {
	root_ = root_->insert(root_, value);
}

int main(int argc, char** argv) {
  AVLTree<int> tree;
  tree.add(1);
  tree.add(6);
  tree.add(3);
  tree.add(0);
  tree.add(2);
  tree.add(4);
  tree.add(9);
	std::cout << tree.size() <<std::endl;
	return 0;
}
