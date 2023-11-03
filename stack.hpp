#ifndef STACK_HPP
#define STACK_HPP

#include <vector>

template <typename T>
class Stack {
public:
    Stack();
    bool empty() const;
    size_t size() const;
    void push(const T& value);
    void pop();
    T& top();
    const T& top() const;

private:
    std::vector<T> elements;
};

template <typename T>
Stack<T>::Stack() {}

template <typename T>
bool Stack<T>::empty() const {
    return elements.empty();
}

template <typename T>
size_t Stack<T>::size() const {
    return elements.size();
}

template <typename T>
void Stack<T>::push(const T& value) {
    elements.push_back(value);
}

template <typename T>
void Stack<T>::pop() {
    if (empty()) {
        throw std::runtime_error("Stack is empty.");
    }
    elements.pop_back();
}

template <typename T>
T& Stack<T>::top() {
    if (empty()) {
        throw std::runtime_error("Stack is empty.");
    }
    return elements.back();
}

template <typename T>
const T& Stack<T>::top() const {
    if (empty()) {
        throw std::runtime_error("Stack is empty.");
    }
    return elements.back();
}

#endif // STACK_HPP