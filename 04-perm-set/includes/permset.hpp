#ifndef INCLUDES_PERMSET_HPP_
#define INCLUDES_PERMSET_HPP_

#include <iostream>
#include <vector>

namespace custom {

template <typename T>
struct Node {
    T data;
    Node* left;
    Node* right;

    Node(const T& value) : data(value), left(nullptr), right(nullptr) {}
};

template <typename T>
class PermanentSet {
 public:
    PermanentSet();
    ~PermanentSet();

    void insert(const T& value);
    bool contains(const T& value) const;
    std::vector<T> inOrderTraversal() const;

    void printInOrder() const;
 private:
    Node<T>* _root;
    void clear(Node<T>* node);

    Node<T>* insert(Node<T>* node, const T& value);
    bool contains(Node<T>* node, const T& value) const;

    void inOrderTraversalHelper(Node<T>* node, std::vector<T>& elements) const;
    void inOrder(Node<T>* node) const;
};

} //namespace custom

#endif // INCLUDES_PERMSET_HPP_
