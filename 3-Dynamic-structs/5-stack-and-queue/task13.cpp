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

    // Cyclic shift of the queue
    void rotateToFirstEven() {
        if (!front) return;

        Node* current = front;
        Node* prev = nullptr;
        while (current && current->data % 2 != 0) {
            prev = current;
            current = current->next;
        }

        if (!current || current == front) return;

        // Queue circular
        rear->next = front;

        // Update front and rear
        front = current;
        rear = prev;
        rear->next = nullptr;
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

    std::cout << "Queue before cyclic shift:\n";
    queue.print();

    queue.rotateToFirstEven();

    std::cout << "Queue after cyclic shift to first even element:\n";
    queue.print();

    return 0;
}
