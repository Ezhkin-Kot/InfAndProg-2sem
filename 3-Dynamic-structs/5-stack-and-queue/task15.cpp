#include <iostream>
#include <stack>

std::stack<int> setStack()
{
    int n;
    std::stack<int> stack;
    std::stack<int> tempStack;

    std::cout << "Enter number of elements: ";
    std::cin >> n;

    // Stack filling
    std::cout << "Enter stack elements separated by space: ";
    for (int i = 0; i < n; i++)
    {
        int x;
        std::cin >> x;
        tempStack.push(x);
    }
    while (!tempStack.empty()) {
        stack.push(tempStack.top());
        tempStack.pop();
    }

    return stack;
}

void insertAfterFirstEven(std::stack<int>& stack) {
    std::stack<int> tempStack;

    int newElem = 0;
    std::cout << "Enter element to be inserted: ";
    std::cin >> newElem;

    // Put odd elements into tempStack until get to even
    while (!stack.empty()) {
        int topElement = stack.top();
        stack.pop();
        tempStack.push(topElement);

        // Add newElem after first even element
        if (topElement % 2 == 0) {
            stack.push(newElem);
            break;
        }
    }

    // Put even elements in stack again
    while (!tempStack.empty()) {
        stack.push(tempStack.top());
        tempStack.pop();
    }
}

void printStack(std::stack<int> stack)
{
    while (!stack.empty())
    {
        std::cout << stack.top() << " ";
        stack.pop();
    }
    std::cout << std::endl;
}

int main() {
    std::stack<int> stack = setStack();

    insertAfterFirstEven(stack);

    printStack(stack);

    return 0;
}
