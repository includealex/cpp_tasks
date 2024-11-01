#ifndef INCLUDES_PERMSET_HPP_
#define INCLUDES_PERMSET_HPP_

#include <iostream>
#include <stack>
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
    std::vector<T> inorder() const;

 private:
    Node<T>* _root;

    void clear(Node<T>* node);
    bool contains(Node<T>* node, const T& value) const;
};

} //namespace custom

#endif // INCLUDES_PERMSET_HPP_
