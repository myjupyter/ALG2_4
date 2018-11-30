#include <iostream>
///////////////////////////////
// Node ///////////////////////
///////////////////////////////
template <typename Type>
struct Node {
	Type value;
	int height;
	int size;
	Node* left;
	Node* right;

	Node() = delete;
	Node(Type val);
	~Node();
};

	template <typename Type>
Node<Type>::Node(Type val)
	: value(val),
		height(1),
		size(1),
		left(nullptr),
		right(nullptr) {
}

template <typename Type>
Node<Type>::~Node() {}

///////////////////////////////
// AVLTRee ////////////////////
///////////////////////////////
template <typename Type>
class AVLTree {
		using NodeT = Node<Type>;
	private:
		Node<Type>* root_;

		int height_(NodeT* node) const;
		void update_height_(NodeT* node);
		int size_(NodeT* node) const;
		void update_size_(NodeT* node);
		int balance_factor_(NodeT* node) const;
		int get_k_(NodeT* node) const;
		Type search_k_stat_(NodeT* node, int k);
		NodeT* balance_(NodeT* node);
		NodeT* left_rotate_(NodeT* q);
		NodeT* right_rotate_(NodeT* p);
		NodeT* insert_(NodeT* node, Type value);
		NodeT* get_minimal_(NodeT* node);
		NodeT* remove_minimal_(NodeT* root, NodeT* node);
		NodeT* remove_(NodeT* node, Type value);
		void delete_function_(NodeT* node);
	public:
		AVLTree();
		~AVLTree();
		void add(Type value);
		void erase(Type value);
		Type search_k_stat(int k);
};

template <typename Type>
AVLTree<Type>::AVLTree() : root_(nullptr) {}


template <typename Type>
void AVLTree<Type>::delete_function_(NodeT* node) {
	if(node) {
		delete_function_(node->left);
		delete_function_(node->right);
		delete node;
	}
}

template <typename Type>
AVLTree<Type>::~AVLTree() {
	delete_function_(root_);
}

template <typename Type>
int AVLTree<Type>::height_(NodeT* node) const {
	return node ? node->height : 0;
}

template <typename Type>
void AVLTree<Type>::update_height_(NodeT* node) {
	node->height = std::max(height_(node->left), height_(node->right)) + 1;
}

template <typename Type>
int AVLTree<Type>::size_(NodeT* node) const {
	return node ? node->size : 0;
}

template <typename Type>
void AVLTree<Type>::update_size_(NodeT* node) {
	node->size = size_(node->left) + size_(node->right) + 1; 
}

template <typename Type>
int AVLTree<Type>::balance_factor_(NodeT* node) const {
	return node ? height_(node->right) - height_(node->left) : 0;
}

template <typename Type>
typename AVLTree<Type>::NodeT*
AVLTree<Type>::left_rotate_(NodeT* q) {
	NodeT* p = q->right;
	q->right = p->left;
	p->left = q;
	update_size_(q);
	update_height_(q);
	update_size_(p);
	update_height_(p);
	return p;
}

template <typename Type>
typename AVLTree<Type>::NodeT* 
AVLTree<Type>::right_rotate_(NodeT* p) {
	NodeT* q = p->left;
	p->left = q->right;
	q->right = p;
	update_size_(p);
	update_height_(p);
	update_size_(q);
	update_height_(q);
	return q;
}

template <typename Type>
typename AVLTree<Type>::NodeT*
AVLTree<Type>::balance_(NodeT* node) {
	update_height_(node);
	update_size_(node);
	if(balance_factor_(node) == 2) {
		if(balance_factor_(node->right) < 0) {
			node->right = right_rotate_(node->right);
		}
		return left_rotate_(node);
	}
	if(balance_factor_(node) == -2) {
		if(balance_factor_(node->left) > 0) {
			node->left = left_rotate_(node->left);
		}
		return right_rotate_(node);
	}
	return node;
}

template <typename Type>
typename AVLTree<Type>::NodeT*
AVLTree<Type>::insert_(NodeT* node, Type value) {
	if(!node) {
		return new NodeT(value);
	}
	if(value >= node->value) {
		node->right = insert_(node->right, value);
	}
	else {
		node->left = insert_(node->left, value);
	}
	update_size_(node);
	return balance_(node);
}

template <typename Type>
typename AVLTree<Type>::NodeT*
AVLTree<Type>::get_minimal_(NodeT* node) {
	return node->left ? get_minimal_(node->left) : node;
}

template <typename Type>
typename AVLTree<Type>::NodeT*
AVLTree<Type>::remove_minimal_(NodeT* root, NodeT* node) {
	if(!node->left) {
		root->value = node->value;
		NodeT* right_node = node->right;
		delete node;
		return right_node;
	}
	node->left = remove_minimal_(root, node->left);
	return balance_(node);
}

template <typename Type>
typename AVLTree<Type>::NodeT*
AVLTree<Type>::remove_(NodeT* node, Type value) {
	if(!node) {
		return nullptr;
	}
	if(value < node->value) {
		node->left = remove_(node->left, value);
	}
	else if( value > node->value) {
		node->right = remove_(node->right, value);
	}
	else {
		if(!node->right) {
			return node->left;
		}
		node->right = remove_minimal_(node, node->right);
	}
	return balance_(node);
}

template <typename Type>
int AVLTree<Type>::get_k_(NodeT* node) const {
	return size_(node->left);
}

template <typename Type>
Type AVLTree<Type>::search_k_stat_(NodeT* node, int k) {
	if(get_k_(node) == k) {
		return node->value;
	}
	if(get_k_(node) < k) {
		return search_k_stat_(node->right, k - size_(node->left) - 1);
	}
	else {
		return search_k_stat_(node->left, k);
	}
}

template <typename Type>
void AVLTree<Type>::add(Type value) {
	root_ = insert_(root_, value);
}

template <typename Type>
void AVLTree<Type>::erase(Type value) {
	root_ = remove_(root_, value);
}

template <typename Type>
Type AVLTree<Type>::search_k_stat(int k) {
	return search_k_stat_(root_, k);
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
		std::cout <<  tree.search_k_stat(k) << std::endl;
	}
	return 0;
}
