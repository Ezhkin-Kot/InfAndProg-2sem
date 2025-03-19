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
        // Change pointers
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

    // List destructor
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

void removeFirstAndLastOdd(list &lst)
{
    if (!lst.next) return;

    node *firstOdd = nullptr;
    node *lastOdd = nullptr;
    node *current = lst.next;

    while (current)
    {
        if (current->data % 2 != 0)
        {
            if (!firstOdd) firstOdd = current;
            lastOdd = current;
        }
        current = current->next;
    }

    if (firstOdd) lst.erase(firstOdd);
    if (lastOdd && lastOdd != firstOdd) lst.erase(lastOdd);
}

int main()
{
    list lst;

    setList(lst);

    removeFirstAndLastOdd(lst);

    std::cout << "Elements after removing: ";
    lst.print();

    return 0;
}
