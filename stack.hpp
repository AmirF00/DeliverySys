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
    T pop();
    T top() const;

private:
    std::vector<T> data;
};

// Implementation of the template class should be in the header file.
// The method definitions are included in the header file.

template <typename T>
Stack<T>::Stack() {}

template <typename T>
bool Stack<T>::empty() const {
    return data.empty();
}

template <typename T>
size_t Stack<T>::size() const {
    return data.size();
}

template <typename T>
void Stack<T>::push(const T& value) {
    data.push_back(value);
}

template <typename T>
T Stack<T>::pop() {
    if (empty()) {
        throw std::runtime_error("Stack is empty.");
    }
    T top = data.back();
    data.pop_back();
    return top;
}

template <typename T>
T Stack<T>::top() const {
    if (empty()) {
        throw std::runtime_error("Stack is empty.");
    }
    return data.back();
}

#endif // STACK_HPP
