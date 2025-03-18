#include <iostream>

struct node
{
    int data;
    node *next;
    node *prev;
    node(int val) : data(val), prev(nullptr), next(nullptr) {}
};

struct list
{
    node *next;
    node *prev;

    list() : next(nullptr), prev(nullptr) {}

    void push(int val)
    {
        node *newNode = new node(val);
        if (!next)
        {
            next = prev = newNode;
        }
        else
        {
            prev->next = newNode;
            newNode->prev = prev;
            prev = newNode;
        }
    }

    void erase(node *node)
    {
        if (!node) return;
        if (node == next) next = node->next;
        if (node == prev) prev = node->prev;
        if (node->prev) node->prev->next = node->next;
        if (node->next) node->next->prev = node->prev;
        delete node;
    }

    void print()
    {
        node *current = next;
        while (current)
        {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    ~list()
    {
        node *current = next;
        while (current)
        {
            node *next = current->next;
            delete current;
            current = next;
        }
    }
};

bool isPrime(int num)
{
    if (num < 2) return false;
    for (int i = 2; i * i <= num; i++)
    {
        if (num % i == 0) return false;
    }
    return true;
}

void shiftToFirstPrime(list &lst)
{
    if (!lst.next) return;

    node *current = lst.next;
    while (current && !isPrime(current->data))
    {
        current = current->next;
    }

    if (!current) return;

    // Move list beginning
    lst.prev->next = lst.next;
    lst.next->prev = lst.prev;
    lst.next = current;
    lst.prev = current->prev;
    current->prev = nullptr;
    if (lst.prev) lst.prev->next = nullptr;
}

void setList(list &lst)
{
    int n;
    std::cout << "Enter number of elements: ";
    std::cin >> n;

    // List filling
    std::cout << "Enter list elements separated by space: ";
    for (int i = 0; i < n; i++)
    {
        int x;
        std::cin >> x;
        lst.push(x);
    }
}

int main()
{
    list lst;

    setList(lst);

    shiftToFirstPrime(lst);

    std::cout << "List after shifting to first prime: ";
    lst.print();

    return 0;
}
