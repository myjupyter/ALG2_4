#include <iostream>

template <typename Type>
class AVLTree {

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
        size_t get_height() const;
        size_t get_count(Node* node) const;
        size_t get_k() const;
				void set_height();
        void set_count();
				Type search_k_stat_(Node* node, size_t k);
        Node* left_little_rotate(Node* q);
        Node* right_little_rotate(Node* p);
        Node* insert(Node* p, Type value);
    };
    Node* root_;
  public:
    AVLTree();
    ~AVLTree();
		size_t size() const;
		size_t height() const;
		void add(Type value);
		Type search_k_stat(size_t k);
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
typename AVLTree<Type>::Node* 
AVLTree<Type>::Node::balance(Node* p) {
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
		default: return p;
	}
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
  q->set_count();
	p->set_height();
	p->set_count();
	return p;
}

template <typename Type>
typename AVLTree<Type>::Node*
AVLTree<Type>::Node::right_little_rotate(Node* p) {
  Node* q = p->left_;
  p->left_ = q->right_;
  q->right_ = p;
  p->set_height();
	p->set_count();
  q->set_height();
	q->set_count();
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
size_t AVLTree<Type>::Node::get_count(Node* node) const {
	return node ? node->count_ : 0;
}

template <typename Type>
size_t AVLTree<Type>::size() const {
	return root_->get_count(root_);
}

template <typename Type> 
size_t AVLTree<Type>::Node::get_height() const {
	return this->height_;
}

template <typename Type>
size_t AVLTree<Type>::height() const {
	return root_->get_height();
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
		

template <typename Type>
size_t AVLTree<Type>::Node::get_k() const {
	return this->get_count(this->left_);
}

template <typename Type>
Type AVLTree<Type>::Node::search_k_stat_(Node* node, size_t k) {
	if(node->get_k() == k) {
		return node->value_;
	}
	if(node->get_k() < k) {
		return this->search_k_stat_(node->right_, k - node->get_count(node->left_) - 1);
	}
	else {
		return this->search_k_stat_(node->left_, k);
	}
}

template <typename Type>
Type AVLTree<Type>::search_k_stat(size_t k) {
	return root_->search_k_stat_(root_, k);
}


int main(int argc, char** argv) {
  AVLTree<int> tree;
	int n = 0;
	int value = 0;
	std::cin >> n;
	for(int i = 0; i < n; ++i) {
		std::cin >> value;
		tree.add(value);
	}
	std::cin >> n;
	std::cout << tree.size() <<std::endl;
	std::cout << tree.height() <<std::endl;
	std::cout << tree.search_k_stat(n) << std::endl;
	return 0;
}
