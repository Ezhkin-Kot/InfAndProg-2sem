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

void setList(list &lst)
{
    int n;
    std::cout << "Enter number of elements: ";
    std::cin >> n;

    std::cout << "Enter list elements separated by space: ";
    for (int i = 0; i < n; i++)
    {
        int x;
        std::cin >> x;
        lst.push(x);
    }
}

void bubbleSort(list &lst)
{
    if (!lst.next) return;
    bool isSwapped;
    do
    {
        isSwapped = false;
        node *current = lst.next;
        while (current->next)
        {
            if (current->data > current->next->data)
            {
                node *temp = current->next;
                current->next = temp->next;
                if (temp->next) temp->next->prev = current;
                temp->prev = current->prev;
                temp->next = current;
                if (current->prev) current->prev->next = temp;
                current->prev = temp;
                if (current == lst.next) lst.next = temp;
                isSwapped = true;
            }
            else
            {
                current = current->next;
            }
        }
    } while (isSwapped);
}

int main()
{
    list lst;
    setList(lst);
    bubbleSort(lst);
    std::cout << "Sorted list: ";
    lst.print();
    return 0;
}
