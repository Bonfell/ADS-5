// Copyright 2021 NNTU-CS
#ifndef TSTACK_H
#define TSTACK_H

#include <stdexcept>

template<typename T, size_t Capacity>
class TStack {
private:
    T data[Capacity];
    size_t topIndex;

public:
    TStack() : topIndex(0) {}

    bool isEmpty() const {
        return topIndex == 0;
    }

    bool isFull() const {
        return topIndex >= Capacity;
    }

    void push(const T& value) {
        if (!isFull()) {
            data[topIndex++] = value;
        } else {
            throw std::overflow_error("Stack overflow");
        }
    }

    T pop() {
        if (!isEmpty()) {
            return data[--topIndex];
        } else {
            throw std::underflow_error("Stack underflow");
        }
    }

    T peek() const {
        if (!isEmpty()) {
            return data[topIndex - 1];
        } else {
            throw std::underflow_error("Stack is empty");
        }
    }
};
#endif  // INCLUDE_TSTACK_H_
