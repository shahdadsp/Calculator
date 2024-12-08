#include <iostream>
#include <stdexcept>
#include <string>
#include <cmath>

using namespace std;

//Stack implementation
class MyStack {
private:
    int capacity;
    int topIndex;
    double *elements;

public:
    MyStack(int maxSize) {
        capacity = maxSize;
        topIndex = -1;
        elements = new double[capacity];
    }

    void push(double value) {
        if (topIndex == capacity - 1) {
            throw overflow_error("Stack is full");
        }
        elements[++topIndex] = value;
    }

    double pop() {
        if (topIndex == -1) {
            throw underflow_error("Stack is empty");
        }
        return elements[topIndex--];
    }

    double top() const {
        if (topIndex == -1) {
            throw underflow_error("Stack is empty");
        }
        return elements[topIndex];
    }

    bool isEmpty() const {
        return topIndex == -1;
    }

    int size() const {
        return topIndex + 1;
    }

    ~MyStack() {
        delete[] elements;
    }
};


//a function for converting an infix notation to a postfix for the calculator
class NotationConverter {
public:
    string toPostfix(const string &infix) {
        string postfix;
        MyStack operators(infix.length());

        for (char ch: infix) {
            if (isalnum(ch)) {
                postfix = postfix + ch;
            } else if (ch == '(') {
                operators.push(ch);
            } else if (ch == ')') {
                while (!operators.isEmpty() && operators.top() != '(') {
                    postfix += operators.pop();
                }
                if (!operators.isEmpty()) {
                    operators.pop();
                }
            } else if (isOperator(ch)) {
                while (!operators.isEmpty() && precedence(operators.top()) >= precedence(ch)) {
                    postfix += operators.pop();
                }
                operators.push(ch);
            }
        }

        while (!operators.isEmpty()) {
            postfix += operators.pop();
        }

        return postfix;
    }

private:
    bool isOperator(char op) {
        return op == '+' || op == '-' || op == '*' || op == '/' || op == '^';
    }

    int precedence(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        if (op == '^') return 3;
        return 0;
    }
};

// this function solves the converted version of the infix notation as a postfix one.
class PostfixSolver {
public:
    double solve(const string &postfix) {
        MyStack stack(postfix.length());
        for (char ch: postfix) {
            if (isdigit(ch)) {
                stack.push(ch - '0');
            } else if (isOperator(ch)) {
                if (stack.size() < 2) {
                    throw invalid_argument("Invalid expression: not enough operands");
                }
                double b = stack.pop();
                double a = stack.pop();
                stack.push(apply(ch, a, b));
            } else if (isAdvancedFunction(ch)) {
                double operand = stack.pop();
                stack.push(applyAdvancedFunction(ch, operand));
            }
        }

        if (stack.size() != 1) {
            throw invalid_argument("Invalid expression: too many operands");
        }

        return stack.pop();
    }

private:
    bool isOperator(char op) {
        return op == '+' || op == '-' || op == '*' || op == '/' || op == '^';
    }

    bool isAdvancedFunction(char op) {
        return op == 's' || op == 'c' || op == 't' || op == 'l' || op == 'e';
    }

    double apply(char op, double a, double b) {
        switch (op) {
            case '+':
                return a + b;
            case '-':
                return a - b;
            case '*':
                return a * b;
            case '/':
                if (b == 0) throw runtime_error("Division by zero");
                return a / b;
            case '^':
                return pow(a, b);
            default:
                throw invalid_argument("Unknown operator");
        }
    }

    // for showing the history of calculations
    void showHistory() const {
        for (const string& entry : history) {
            cout << entry << endl;
        }
    }
// for using more advanced functions as a calculator
    double applyAdvancedFunction(char op, double operand) {
        switch (op) {
            case 's':
                return sin(operand);
            case 'c':
                return cos(operand);
            case 't':
                return tan(operand);
            case 'l':
                return log(operand);
            case 'e':
                return exp(operand);
            default:
                throw invalid_argument;
        }
    }
};


struct Node {
    string variable;
    double value;
    string equation;
    Node *next;

    Node(string var, string eqn) : variable(var), equation(eqn), value(0), next(nullptr) {}
};


class EquationSolver {
private:
    Node *head;

public:
    EquationSolver() : head(nullptr) {}

    void addEquation(const string &var, const string &expr) {
        Node *newNode = new Node(var, expr);
        newNode->next = head;
        head = newNode;
    }


    void solveAll() {
        Node *current = head;
        while (current != nullptr) {
            solveVariable(current);
            current = current->next;
        }
    }


    double getValue(const string &var) {
        Node *current = head;
        while (current != nullptr) {
            if (current->variable == var) {
                return current->value;
            }
            current = current->next;
        }
        throw invalid_argument("Variable not found: " + var);
    }

private:

    void solveVariable(Node *node) {
        NotationConverter converter;
        PostfixSolver solver;

        string postfix = converter.toPostfix(node->equation);

        node->value = solver.solve(postfix);
    }
};
