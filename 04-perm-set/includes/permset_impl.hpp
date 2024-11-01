#ifndef PERMSET_IMPL_HPP_
#define PERMSET_IMPL_HPP_

#include "permset.hpp"

namespace custom {

template<typename T>
PermanentSet<T>::PermanentSet() : _root(nullptr) {}

template<typename T>
PermanentSet<T>::~PermanentSet() {
    clear(_root);
}

template <typename T>
void PermanentSet<T>::clear(Node<T>* node) {
    if (node == nullptr) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

template<typename T>
void PermanentSet<T>::insert(const T& value) {
    if (_root == nullptr) {
        _root = new Node<T>(value);
        return;
    }

    Node<T>* current = _root;
    Node<T>* parent = nullptr;

    while (current != nullptr) {
        parent = current;
        if (value < current->data) {
            current = current->left;
        } else if (value > current->data) {
            current = current->right;
        } else {
            return;
        }
    }

    if (value < parent->data) {
        parent->left = new Node<T>(value);
    } else {
        parent->right = new Node<T>(value);
    }
}

template<typename T>
bool PermanentSet<T>::contains(const T& value) const {
    return contains(_root, value);
}

template<typename T>
bool PermanentSet<T>::contains(Node<T>* node, const T& value) const {
    while (node != nullptr) {
        if (value == node->data) {
            return true;
        } else if (value < node->data) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    return false;
}

template <typename T>
std::vector<T> PermanentSet<T>::inorder() const {
    std::vector<T> elements;
    std::stack<Node<T>*> stack;
    Node<T>* current = _root;

    while (current != nullptr || !stack.empty()) {
        while (current != nullptr) {
            stack.push(current);
            current = current->left;
        }

        current = stack.top();
        stack.pop();

        elements.push_back(current->data);

        current = current->right;
    }

    return elements;
}

} // namespace custom

#endif //PERMSET_IMPL_HPP_

