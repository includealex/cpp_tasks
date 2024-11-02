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

class string_twine {
 public:
    string_twine(const std::string& value) : _left(nullptr), _right(nullptr), _value(value) {}
    string_twine(std::shared_ptr<string_twine> left, std::shared_ptr<string_twine> right)
        : _left(left), _right(right), _value("") {}

    std::string str() const {
        if (!_value.empty()) {
            return _value;
        }

        std::string res;
        if (_left) {
            res += _left->str();
        }

        if (_right) { 
            res += _right->str();
        }

        return res;
    }

 private:
    std::shared_ptr<string_twine> _left;
    std::shared_ptr<string_twine> _right;
    std::string _value;
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

template <>
class PermSet<std::string> final {
 public:
    PermSet();
    ~PermSet() = default;

    void insert(const std::string& value);
    bool contains(const std::string& value) const;
    void undo();
    void redo();
    std::vector<std::string> inorder() const;

 private:
    std::shared_ptr<Node<std::shared_ptr<string_twine>>> _root;
    std::vector<std::shared_ptr<Node<std::shared_ptr<string_twine>>>> _history;
    int _version;

    std::shared_ptr<Node<std::shared_ptr<string_twine>>>
    insert(const std::shared_ptr<Node<std::shared_ptr<string_twine>>>& node, 
           const std::shared_ptr<string_twine>& value);
    bool contains(const std::shared_ptr<Node<std::shared_ptr<string_twine>>>& node,
                  const std::shared_ptr<string_twine>& value) const;
    void record();
};

} // namespace custom

#endif // INCLUDES_PERMSET_HPP_
