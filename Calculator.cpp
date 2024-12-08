#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

class Stack {
private:
    int maxSize;
    int top;
    double *stack;
public:
    Stack(int size) {
        maxSize = size;
        top = -1;
        stack = new double[maxSize];
    }

    void push(double value) {
        if (top == maxSize - 1) {
            throw overflow_error("Stack Overflow");
        }
        stack[++top] = value;
    }

    double pop() {
        if (top == -1) {
            throw underflow_error("Stack Underflow");
        }
        return stack[top--];
    }

    double peek() const {
        if (top == -1) {
            throw underflow_error("Stack is empty");
        }
        return stack[top];
    }

    bool isEmpty() const {
        return top == -1;
    }

    int size() const {
        return top + 1;
    }

    ~Stack() {
        delete[] stack;
    }
};

