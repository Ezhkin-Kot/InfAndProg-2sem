#include <iostream>
#include <string>
#include <sstream>

struct Node {
    char data;
    Node* next;
    Node(char val) : data(val), next(nullptr) {}
};

class Stack {
private:
    Node* top;

public:
    Stack() : top(nullptr) {}

    // Add element to the top of the stack
    void push(char value) {
        Node* newNode = new Node(value);
        newNode->next = top;
        top = newNode;
    }

    // Get top element
    char peek() const {
        return top ? top->data : '\0';
    }

    // Remove and return top element
    char pop() {
        if (!top) return '\0';
        Node* temp = top;
        char value = temp->data;
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

    std::cout << "Enter letters separated by space:\n";
    std::getline(std::cin, input);
    std::stringstream ss(input);

    char ch;
    while (ss >> ch) {
        stack.push(ch);
    }

    return stack;
}

bool isVowel(char ch) {
    ch = std::tolower(ch);
    std::string s = "aeiouy";
    return s.find(ch) != std::string::npos;
}

void insertQuestionAfterFirstVowel(Stack& stack) {
    Stack temp;

    // Reverse stack
    while (!stack.isEmpty()) {
        temp.push(stack.pop());
    }

    bool isInserted = false;
    while (!temp.isEmpty()) {
        // Insert '?' after first vowel letter
        if (!isInserted && isVowel(stack.peek()))
        {
            stack.push('?');
            isInserted = true;
        }
        stack.push(temp.pop());
    }
}

int main() {
    Stack stack = setStack();

    std::cout << "Stack:\n";
    stack.print();

    insertQuestionAfterFirstVowel(stack);

    std::cout << "Stack after inserting '?' after first vowel:\n";
    stack.print();

    return 0;
}
