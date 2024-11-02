#ifndef PERMSET_IMPL_HPP_
#define PERMSET_IMPL_HPP_

#include "permset.hpp"

namespace custom {

template<typename T>
PermSet<T>::PermSet() : _root(nullptr), _version(0) {
    _history.push_back(_root);
}

template <typename T>
void PermSet<T>::insert(const T& value) {
    _root = insert(_root, value);
    record();
}

template <typename T>
std::shared_ptr<Node<T>> PermSet<T>::insert(const std::shared_ptr<Node<T>>& node, const T& value) {
    if (!node) {
        return std::make_shared<Node<T>>(value);
    }

    if (value == node->data) {
        return node;
    }

    auto newNode = std::make_shared<Node<T>>(node->data);

    if (value < node->data) {
        newNode->left = insert(node->left, value);
        newNode->right = node->right;
    } 
    else {
        newNode->right = insert(node->right, value);
        newNode->left = node->left;
    }

    return newNode;
}

template<typename T>
bool PermSet<T>::contains(const T& value) const {
    return contains(_root, value);
}

template <typename T>
bool PermSet<T>::contains(const std::shared_ptr<Node<T>>& node, const T& value) const {
    auto cur = node;
    while (cur != nullptr) {
        if (value == cur->data) {
            return true;
        }

        if (value < cur->data) {
            cur = cur->left;
        } 
        else {
            cur = cur->right;
        }
    }
    return false;
}

template <typename T>
void PermSet<T>::record() {
    if (_version < static_cast<int>(_history.size()) - 1) {
        _history.resize(_version + 1);
    }
    _history.push_back(_root);
    _version++;
}

template <typename T>
void PermSet<T>::undo() {
    if (_version > 0) {
        _version--;
        _root = _history[_version];
    }
}

template <typename T>
void PermSet<T>::redo() {
    if (_version < static_cast<int>(_history.size()) - 1) {
        _version++;
        _root = _history[_version];
    }
}

template <typename T>
std::vector<T> PermSet<T>::inorder() const {
    std::vector<T> elements;
    std::stack<std::shared_ptr<Node<T>>> stack;
    auto cur = _root;

    while (cur != nullptr || !stack.empty()) {
        while (cur != nullptr) {
            stack.push(cur);
            cur = cur->left;
        }

        cur = stack.top();
        stack.pop();

        elements.push_back(cur->data);
        cur = cur->right;
    }

    return elements;
}

PermSet<std::string>::PermSet() : _root(nullptr), _version(0) {
    _history.push_back(_root);
}

void PermSet<std::string>::insert(const std::string& value) {
    auto twine_value = std::make_shared<string_twine>(value);
    _root = insert(_root, twine_value);
    record();
}

std::shared_ptr<Node<std::shared_ptr<string_twine>>>
PermSet<std::string>::insert(const std::shared_ptr<Node<std::shared_ptr<string_twine>>>& node,
                             const std::shared_ptr<string_twine>& value) {
    if (!node) {
        return std::make_shared<Node<std::shared_ptr<string_twine>>>(value);
    }

    if (value->str() == node->data->str()) {
        return node;
    }

    auto newNode = std::make_shared<Node<std::shared_ptr<string_twine>>>(node->data);

    if (value->str() < node->data->str()) {
        newNode->left = insert(node->left, value);
        newNode->right = node->right;
    } else {
        newNode->right = insert(node->right, value);
        newNode->left = node->left;
    }

    return newNode;
}

bool PermSet<std::string>::contains(const std::string& value) const {
    auto twine_value = std::make_shared<string_twine>(value);
    return contains(_root, twine_value);
}

bool PermSet<std::string>::contains(const std::shared_ptr<Node<std::shared_ptr<string_twine>>>& node,
                                    const std::shared_ptr<string_twine>& value) const {
    auto cur = node;
    auto str_val = value->str();
    while (cur != nullptr) {
        auto cur_val = cur->data->str();

        if (str_val == cur_val) {
            return true;
        }

        if (str_val < cur_val) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }
    return false;
}

void PermSet<std::string>::record() {
    if (_version < static_cast<int>(_history.size()) - 1) {
        _history.resize(_version + 1);
    }
    _history.push_back(_root);
    _version++;
}

void PermSet<std::string>::undo() {
    if (_version > 0) {
        _version--;
        _root = _history[_version];
    }
}

void PermSet<std::string>::redo() {
    if (_version < static_cast<int>(_history.size()) - 1) {
        _version++;
        _root = _history[_version];
    }
}

std::vector<std::string> PermSet<std::string>::inorder() const {
    std::vector<std::string> elements;
    std::stack<std::shared_ptr<Node<std::shared_ptr<string_twine>>>> stack;
    auto cur = _root;

    while (cur != nullptr || !stack.empty()) {
        while (cur != nullptr) {
            stack.push(cur);
            cur = cur->left;
        }

        cur = stack.top();
        stack.pop();

        elements.push_back(cur->data->str());
        cur = cur->right;
    }

    return elements;
}

} // namespace custom

#endif // PERMSET_IMPL_HPP_
