#include <iostream>
#include <string>
#include <sstream>

struct Node {
    int data;
    Node* next;
    Node(int value) : data(value), next(nullptr) {}
};

class Queue {
private:
    Node* front;
    Node* rear;

public:
    Queue() : front(nullptr), rear(nullptr) {}

    // Add an element to the end of the queue
    void push(int value) {
        Node* newNode = new Node(value);
        if (!rear) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    void print() {
        Node* temp = front;
        while (temp) {
            std::cout << temp->data << ' ';
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    void insertLastOddAfterMax() {
        if (!front) return;

        // Find max and last odd
        int maxVal = front->data;
        Node* lastOddNode = nullptr;
        Node* temp = front;
        while (temp) {
            if (temp->data > maxVal) maxVal = temp->data;
            if (temp->data % 2 != 0) lastOddNode = temp;
            temp = temp->next;
        }

        if (!lastOddNode) return;

        int lastOdd = lastOddNode->data;

        // Insert lastOdd after all nodes equals to maxVal
        temp = front;
        while (temp) {
            if (temp->data == maxVal) {
                Node* newNode = new Node(lastOdd);
                newNode->next = temp->next;
                temp->next = newNode;
                if (temp == rear) rear = newNode;
                temp = newNode; // Skip over inserted node
            }
            temp = temp->next;
        }
    }

    ~Queue() {
        while (front) {
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
    while (ss >> x) {
        q.push(x);
    }

    return q;
}

int main() {
    Queue queue = setQueue();

    std::cout << "Queue:\n";
    queue.print();

    queue.insertLastOddAfterMax();

    std::cout << "Queue after inserting last odd after max elements:\n";
    queue.print();

    return 0;
}
