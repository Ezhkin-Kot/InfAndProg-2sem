#include <iostream>
#include <string>
#include <sstream>

struct Node 
{
    int data;
    Node* next;
    Node(int value) : data(value), next(nullptr) {}
};

class Queue 
{
private:
    Node* front;
    Node* rear;

public:
    Queue() : front(nullptr), rear(nullptr) {}

    // Add an element to the end of the queue
    void push(int value)
    {
        Node* newNode = new Node(value);
        if (!rear)
        {
            front = rear = newNode;
        }
        else
        {
            rear->next = newNode;
            rear = newNode;
        }
    }

    // Remove and return an element from the front
    int pop()
    {
        if (isEmpty())
        {
            throw std::out_of_range("Queue is empty");
        }
        Node* temp = front;
        int val = temp->data;
        front = front->next;
        if (front == nullptr)
        {
            rear = nullptr;
        }
        delete temp;
        return val;
    }

    // Get front element
    int peek()
    {
        return front->data;
    }

    bool isEmpty()
    {
        return front == nullptr;
    }

    ~Queue() 
    {
        while (front) 
        {
            Node* temp = front;
            front = front->next;
            delete temp;
        }
    }
};

Queue setQueue()
{
    Queue q;
    std::string input;

    std::cout << "Enter elements of the queue separated by space:\n";
    std::getline(std::cin, input);
    std::stringstream ss(input);

    int x;
    while (ss >> x) 
    {
        q.push(x);
    }

    return q;
}

void printQueue(Queue& q)
{
    Queue tempQueue;
    int temp;

    while (!q.isEmpty())
    {
        temp = q.pop();
        tempQueue.push(temp);
        std::cout << temp << ' ';
    }

    while (!tempQueue.isEmpty())
    {
        q.push(tempQueue.pop());
    }
    std::cout << std::endl;
}

// Cyclic shift of the queue
void rotateQueueToFirstEven(Queue& q)
{
    Queue tempQueue;

    while (!q.isEmpty() && q.peek() % 2 != 0)
    {
        tempQueue.push(q.pop());
    }

    while (!tempQueue.isEmpty())
    {
        q.push(tempQueue.pop());
    }
}

int main() {
    Queue queue = setQueue();

    std::cout << "Queue before cyclic shift:\n";
    printQueue(queue);

    rotateQueueToFirstEven(queue);

    std::cout << "Queue after cyclic shift to first even element:\n";
    printQueue(queue);

    return 0;
}

