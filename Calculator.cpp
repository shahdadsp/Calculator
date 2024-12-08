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

class InToPostConvertor {
public:

    int precedence(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        if (op == '^') return 3;
        return 0;
    }

    bool isOperator(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
    }


    string InToPost(const string &infix) {
        string postfix;
        Stack operatorStack(infix.length());

        for (size_t i = 0; i < infix.length(); ++i) {
            char c = infix[i];


            if (isalnum(c)) {
                postfix += c;
            } else if (c == '(') {
                operatorStack.push(c);
            } else if (c == ')') {
                while (!operatorStack.isEmpty() && operatorStack.peek() != '(') {
                    postfix += operatorStack.pop();
                }
                if (!operatorStack.isEmpty() && operatorStack.peek() == '(') {
                    operatorStack.pop();
                }
            } else if (isOperator(c)) {
                while (!operatorStack.isEmpty() &&
                       precedence(operatorStack.peek()) >= precedence(c)) {
                    postfix += operatorStack.pop();
                }
                operatorStack.push(c);
            }
        }


        while (!operatorStack.isEmpty()) {
            postfix += operatorStack.pop();
        }

        return postfix;
    }
};

class PostToInConvertor {
public:
    double evaluatePostfix(const string &postfix) {
        Stack evaluationStack(postfix.length());

        for (size_t i = 0; i < postfix.length(); ++i) {
            char c = postfix[i];


            if (isdigit(c)) {
                evaluationStack.push(c - '0');
            } else if (isOperator(c)) {
                if (evaluationStack.size() < 2) {
                    throw invalid_argument("Not enough operands");
                }

                double operand2 = evaluationStack.pop();
                double operand1 = evaluationStack.pop();
                double result = applyOperator(c, operand1, operand2);
                evaluationStack.push(result);
            }
        }

        if (evaluationStack.size() != 1) {
            throw invalid_argument("Remaining operands in stack");
        }

        return evaluationStack.pop();
    }

private:

    bool isOperator(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
    }


    double applyOperator(char op, double operand1, double operand2) {
        switch (op) {
            case '+':
                return operand1 + operand2;
            case '-':
                return operand1 - operand2;
            case '*':
                return operand1 * operand2;
            case '/':
                if (operand2 == 0) throw runtime_error("Division by zero error");
                return operand1 / operand2;
            case '^':
                return pow(operand1, operand2);
            default:
                throw invalid_argument("Unsupported operator");
        }
    }
};


