#ifndef STACK_H
#define STACK_H

#include <vector>
#include <stdexcept>

// Use inheritance from std::vector (choose public/private) as appropriate
template <typename T>
class Stack 
{
public:
    // Default constructor for the Stack
    Stack() {}

    // Return current Stack size
    size_t size() const {
        return data.size();
    }

    // Check if Stack is empty
    bool empty() const {
        return data.empty();
    }

    // Pushes an item onto the top of the Stack
    void push(const T& item) {
        data.push_back(item);
    }

    // Pops the top item from the Stack
    // Throws an underflow_error if the Stack is empty
    void pop() {
        if (!empty()) {
            data.pop_back();
        } else {
            throw std::underflow_error("Stack is empty");
        }
    }

    // Returns a reference to the top item of the Stack
    // Throws an underflow_error if the Stack is empty
    const T& top() const {
        if (!empty()) {
            return data.back();
        } else {
            throw std::underflow_error("Stack is empty");
        }
    }

private:
    // Private member variable to store the elements of the Stack
    std::vector<T> data;
};


#endif