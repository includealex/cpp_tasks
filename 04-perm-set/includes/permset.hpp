#ifndef INCLUDES_PERMSET_HPP_
#define INCLUDES_PERMSET_HPP_

#include <iostream>
#include <stack>
#include <vector>
#include <memory>

namespace custom {

template <typename T>
struct Node final{
    T data;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;

    Node(const T& value) : data(value), left(nullptr), right(nullptr) {}
};

template <typename T>
class PermSet final{
 public:
    PermSet();
    ~PermSet() = default;

    void insert(const T& value);
    bool contains(const T& value) const;
    void undo();
    void redo();

    std::vector<T> inorder() const;

 private:
    std::shared_ptr<Node<T>> _root;
    std::vector<std::shared_ptr<Node<T>>> _history;
    int _version;

    std::shared_ptr<Node<T>> insert(const std::shared_ptr<Node<T>>& node, const T& value);
    bool contains(const std::shared_ptr<Node<T>>& node, const T& value) const;
    void record();
};

} // namespace custom

#endif // INCLUDES_PERMSET_HPP_
