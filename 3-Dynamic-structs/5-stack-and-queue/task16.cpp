#include <iostream>
#include <string>
#include <sstream>

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class Stack {
private:
    Node* top;

public:
    Stack() : top(nullptr) {}

    // Add element to the top of the stack
    void push(int value) {
        Node* newNode = new Node(value);
        newNode->next = top;
        top = newNode;
    }

    // Get top element
    int peek() const {
        return top->data;
    }

    // Remove and return top element
    int pop() {
        if (!top) return 0;
        Node* temp = top;
        int value = temp->data;
        top = top->next;
        delete temp;
        return value;
    }

    void print() const {
        Node* current = top;
        Stack tempStack;
        while (current) {
            tempStack.push(current->data);
            current = current->next;
        }
        while (!tempStack.isEmpty()) {
            std::cout << tempStack.pop() << ' ';
        }
        std::cout << std::endl;
    }

    bool isEmpty() const {
        return top == nullptr;
    }

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }
};

Stack setStack() {
    Stack stack;
    std::string input;

    std::cout << "Enter integers separated by space:\n";
    std::getline(std::cin, input);
    std::stringstream ss(input);

    int x;
    while (ss >> x) {
        stack.push(x);
    }

    return stack;
}

// first - min, second - max
std::pair<int, int> findMinMaxElems(Stack& stack)
{
    std::pair<int, int> result;
    result.first = result.second = stack.peek();

    Stack tempStack;

    while (!stack.isEmpty()) {
        int temp = stack.pop();
        tempStack.push(temp);
        if (temp < result.first) result.first = temp;
        if (temp > result.second) result.second = temp;
    }

    while (!tempStack.isEmpty())
    {
        stack.push(tempStack.pop());
    }

    return result;
}

void insertMinAfterMax(Stack& stack) {
    const auto [minElem, maxElem] = findMinMaxElems(stack);
    bool firstInserted = false, lastInserted = false;

    Stack tempStack;

    // Insert min after last max element and put the stack into the tempStack
    while (!stack.isEmpty())
    {
        int temp = stack.pop();
        if (!lastInserted && temp == maxElem)
        {
            tempStack.push(minElem);
            lastInserted = true;
        }
        tempStack.push(temp);
    }

    // Insert min after first max element and restore the stack from reversed tempStack
    while (!tempStack.isEmpty())
    {
        int temp = tempStack.pop();
        stack.push(temp);
        if (!firstInserted && temp == maxElem)
        {
            stack.push(minElem);
            firstInserted = true;
        }
    }
}

int main() {
    Stack stack = setStack();

    std::cout << "Stack:\n";
    stack.print();

    insertMinAfterMax(stack);

    std::cout << "Stack after inserting min element after first and last max:\n";
    stack.print();

    return 0;
}

