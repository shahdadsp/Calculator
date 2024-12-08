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

class Queue {
    int front;
    int rear;
    int count;
    int maxSize;
    double *queue;
public:

    Queue(int size) {
        maxSize = size;
        front = 0;
        rear = -1;
        count = 0;
        queue = new double[maxSize];
    }

    void enqueue(double value) {
        if (count == maxSize) {
            throw overflow_error("Queue Overflow!");
        }
        rear = (rear + 1) % maxSize;
        queue[rear] = value;
        count++;
    }

    double dequeue() {
        if (count == 0) {
            throw underflow_error("Queue Underflow!");
        }
        double value = queue[front];
        front = (front + 1) % maxSize;
        count--;
        return value;
    }

    double peek() const {
        if (count == 0) {
            throw underflow_error("Queue is empty");
        }
        return queue[front];

    }

    bool isEmpty() const {
        return count == 0;
    }

    int size() const {
        return count;
    }

    ~Queue() {
        delete[] queue;
    }
};

