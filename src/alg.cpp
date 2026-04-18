// Copyright 2025 NNTU-CS
#include <string>
#include <cctype>
#include <stdexcept>
#include "../include/tstack.h"

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int getPriority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

std::string infx2pstfx(const std::string& inf) {
    TStack<char, 100> stack;
    std::string result;

    for (size_t i = 0; i < inf.length(); ++i) {
        char c = inf[i];

        if (c == ' ') continue;

        if (std::isdigit(c)) {
            while (i < inf.length() && std::isdigit(inf[i])) {
                result += inf[i++];
            }
            result += ' '; 
            --i; 
        }

        else if (c == '(') {
            stack.push(c);
        }

        else if (c == ')') {
            while (!stack.isEmpty() && stack.peek() != '(') {
                result += stack.pop();
                result += ' ';
            }
            if (!stack.isEmpty()) {
                stack.pop(); 
            }
        }

        else if (isOperator(c)) {
            while (!stack.isEmpty() &&
                   stack.peek() != '(' &&
                   getPriority(stack.peek()) >= getPriority(c)) {
                result += stack.pop();
                result += ' ';
            }
            stack.push(c);
        }
    }

    while (!stack.isEmpty()) {
        result += stack.pop();
        result += ' ';
    }

    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }

    return result;
}

int eval(const std::string& post) {
    TStack<int, 100> stack;

    for (size_t i = 0; i < post.length(); ++i) {
        char c = post[i];

        if (c == ' ') continue;

        if (std::isdigit(c)) {
            int num = 0;
            while (i < post.length() && std::isdigit(post[i])) {
                num = num * 10 + (post[i++] - '0');
            }
            --i; 
            stack.push(num);
        }

        else if (isOperator(c)) {
            if (stack.isEmpty()) throw std::runtime_error("Invalid expression");
            int b = stack.pop();
            if (stack.isEmpty()) throw std::runtime_error("Invalid expression");
            int a = stack.pop();

            switch (c) {
                case '+':
                    stack.push(a + b);
                    break;
                case '-':
                    stack.push(a - b);
                    break;
                case '*':
                    stack.push(a * b);
                    break;
                case '/':
                    if (b == 0) throw std::runtime_error("Division by zero");
                    stack.push(a / b);
                    break;
            }
        }
    }

    if (stack.isEmpty()) throw std::runtime_error("Empty result");
    return stack.pop();
}

