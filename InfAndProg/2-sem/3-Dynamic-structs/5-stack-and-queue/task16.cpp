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

std::pair<int, int> findMinMaxElems(std::stack<int> stack)
{
    std::pair<int, int> result; // first - min, second - max
    result.first = result.second = stack.top();
    while (!stack.empty()) {
        int temp = stack.top();
        stack.pop();
        if (temp < result.first) result.first = temp;
        if (temp > result.second) result.second = temp;
    }
    return result;
}

void insertMaxAfterMin(std::stack<int>& stack) {
    const auto [minElem, maxElem] = findMinMaxElems(stack);
    bool firstInserted = false, lastInserted = false;

    std::stack<int> tempStack;
    while (!stack.empty()) {
        int elem = stack.top();
        stack.pop();
        tempStack.push(elem);

        // Put max element after first min
        if (!firstInserted && elem == minElem) {
            tempStack.push(maxElem);
            firstInserted = true;
        }
    }

    // Go through reversed stack and find last min element
    std::stack<int> finalStack;
    while (!tempStack.empty()) {
        int elem = tempStack.top();
        tempStack.pop();

        // Put max element after last min
        if (!lastInserted && elem == minElem) {
            finalStack.push(maxElem);
            lastInserted = true;
        }
        finalStack.push(elem);
    }

    stack = finalStack;
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

    insertMaxAfterMin(stack);

    printStack(stack);

    return 0;
}
