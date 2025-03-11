#include <iostream>
#include <queue>

std::queue<int> setQueue()
{
    int n;
    std::queue<int> queue;

    std::cout << "Enter number of elements: ";
    std::cin >> n;

    // Queue filling
    std::cout << "Enter queue elements separated by space: ";
    for (int i = 0; i < n; i++)
    {
        int x;
        std::cin >> x;
        queue.push(x);
    }

    return queue;
}

void removeDuplicates(std::queue<int>& queue)
{
    std::queue<int> result;
    int prev = queue.front();
    result.push(prev);
    queue.pop();

    while (!queue.empty())
    {
        int current = queue.front();
        queue.pop();
        if (current != prev) // Filter same elements
        {
            result.push(current);
            prev = current;
        }
    }

    queue = result;
}

void printQueue(std::queue<int> queue)
{
    while (!queue.empty())
    {
        std::cout << queue.front() << " ";
        queue.pop();
    }
    std::cout << std::endl;
}

int main()
{
    std::queue<int> queue = setQueue();

    removeDuplicates(queue);

    printQueue(queue);

    return 0;
}
