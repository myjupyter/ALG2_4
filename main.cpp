#include <iostream>
#include <cassert>

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
        Node* balance(Node* node);
        int balance_factor() const;
        size_t get_height() const;
        size_t get_count(Node* node) const;
        size_t get_k() const;
				void set_height();
        void set_count();
				Type search_k_stat_(Node* node, size_t k);
        Node* left_little_rotate(Node* q);
        Node* right_little_rotate(Node* p);
        Node* insert(Node* node, Type value);
				Node* search_minimal(Node* node);
				Node* remove_minimal(Node* node, Type& value);
				Node* remove(Node* node, Type value);
    };
    Node* root_;
  public:
    AVLTree();
    ~AVLTree();
		size_t size() const;
		size_t height() const;
		void add(Type value);
		void erase(Type value);
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
AVLTree<Type>::Node::balance(Node* node) {
	switch(node->balance_factor()) {
		case 2:
			if(node->right_->balance_factor() < 0) {
				node->right_ = node->right_little_rotate(node->right_);
			}
			return node->left_little_rotate(node);
		case -2:
			if(node->left_->balance_factor() > 0) {
				node->left_ = node->left_little_rotate(node->left_);
			}
			return node->right_little_rotate(node);
		default:
			node->set_height();
			node->set_count();
			return node;
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
AVLTree<Type>::Node::insert(Node* node, Type value) {
	if(!node) {
		return new Node(value);
	}
	if(value < node->value_) {
		node->left_ = insert(node->left_, value);
	}
	else {
		node->right_ = insert(node->right_, value);
	}
	node->set_count();
	return this->balance(node);
}
        
template <typename Type>
typename AVLTree<Type>::Node*
AVLTree<Type>::Node::search_minimal(Node* node) {
	return node->left_ ? node->search_minimal(node->left_) : node;
}

template <typename Type>
typename AVLTree<Type>::Node*
AVLTree<Type>::Node::remove_minimal(Node* node, Type& value) {
	assert(node);
  if (node->left_) {
		node->left_ = node->remove_minimal(node->left_, value);
  } else {
		value = node->value_;
    Node* right = node->right_;
    node->right_ = nullptr;
    delete node;
    return right;
  }
	node->set_count();
  return node->balance(node);
}

template <typename Type>
typename AVLTree<Type>::Node* 
AVLTree<Type>::Node::remove(Node* node, Type value) {
	if (node == nullptr) {
		return nullptr;
  }
  if (value == node->value_) {
		if (node->right_ == nullptr) {
			Node* left = node->left_;
			node->left_ = nullptr;
      delete node;
      return left;
    }
    if (node->left_ == nullptr) {
			Node* right = node->right_;
      node->right_ = nullptr;
      delete node;
      return right;
    }
    node->right_ = node->right_->remove_minimal(node->right_, node->value_);
  }
	else if (value < node->value_) {
		node->left_ = node->left_->remove_minimal(node->left_, value);
  } 
	else {
    node->right_ = node->right_->remove_minimal(node->right_, value);
  }
	node->set_count();
	return node->balance(node);
}

template <typename Type>
void AVLTree<Type>::erase(Type value) {
	root_ = root_->remove(root_, value);
}

template <typename Type>
void AVLTree<Type>::add(Type value) {
	root_ = root_->insert(root_, value);
}
		

template <typename Type>
size_t AVLTree<Type>::Node::get_k() const {
	return this->get_count(left_);
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
	assert(k < root_->get_count(root_));
	return root_->search_k_stat_(root_, k);
}

int main(int argc, char** argv) {
  AVLTree<int> tree;
	int n = 0;
	int value = 0;
	unsigned int k = 0;
	std::cin >> n;
	for(int i = 0; i < n; ++i) {
		std::cin >> value >> k;
		if(value > 0) tree.add(value);
		else					tree.erase(-value);
		std::cout << tree.search_k_stat(k) << std::endl;
	}
	return 0;
}
