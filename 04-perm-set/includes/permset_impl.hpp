#include "permset.hpp"

namespace custom {

template<typename T>
PermanentSet<T>::PermanentSet() : _root(nullptr) {}

template<typename T>
PermanentSet<T>::~PermanentSet() {
    clear(_root);
}

template<typename T>
void PermanentSet<T>::insert(const T& value) {
    _root = insert(_root, value);
}

template<typename T>
bool PermanentSet<T>::contains(const T& value) const {
    return contains(_root, value);
}

template<typename T>
bool PermanentSet<T>::contains(Node<T>* node, const T& value) const {
    if (node == nullptr) {
        return false;
    }
    if (value == node->data) {
        return true;
    } else if (value < node->data) {
        return contains(node->left, value);
    } else {
        return contains(node->right, value);
    }
}

template <typename T>
void PermanentSet<T>::printInOrder() const {
    inOrder(_root);
    std::cout << std::endl;
}

template <typename T>
Node<T>* PermanentSet<T>::insert(Node<T>* node, const T& value) {
    if (node == nullptr) {
        return new Node(value);
    }
    if (value < node->data) {
        node->left = insert(node->left, value);
    } else if (value > node->data) {
        node->right = insert(node->right, value);
    }

    return node;
}

template <typename T>
void PermanentSet<T>::inOrder(Node<T>* node) const {
    if (node == nullptr) return;
    inOrder(node->left);
    std::cout << node->data << " ";
    inOrder(node->right);
}

template <typename T>
void PermanentSet<T>::clear(Node<T>* node) {
    if (node == nullptr) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

template <typename T>
std::vector<T> PermanentSet<T>::inOrderTraversal() const {
    std::vector<T> elements;
    inOrderTraversalHelper(_root, elements);
    return elements;
}

template <typename T>
void PermanentSet<T>::inOrderTraversalHelper(Node<T>* node, std::vector<T>& elements) const {
    if (node == nullptr) return;
    inOrderTraversalHelper(node->left, elements);
    elements.push_back(node->data);
    inOrderTraversalHelper(node->right, elements);
}

} // namespace custom
