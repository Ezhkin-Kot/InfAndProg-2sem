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

int maxQueueElem(std::queue<int> queue)
{
    int maxElem = INT_MIN;
    while (!queue.empty())
    {
        int temp = queue.front();
        if (temp > maxElem)
        {
            maxElem = temp;
        }
        queue.pop();
    }
    return maxElem;
}

std::queue<int> transformQueue(std::queue<int> queue)
{
    int firstElem = queue.front();
    int maxElem = maxQueueElem(queue);
    std::queue<int> result;
    while (!queue.empty())
    {
        int temp = queue.front();
        if (temp == firstElem)
        {
            // Add max elem after equal to first elem
            result.push(temp);
            result.push(maxElem);
        }
        else
        {
            result.push(temp);
        }
        queue.pop();
    }
    return result;
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

    queue = transformQueue(queue);

    printQueue(queue);

    return 0;
}
