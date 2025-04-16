#include <iostream>
#include <map>
#include <vector>
#include <set>

class Queue
{
private:
    struct Node
    {
        int data;
        Node* next;
        Node(int val) : data(val), next(nullptr) {}
    };

    Node* front;
    Node* rear;

public:
    Queue() : front(nullptr), rear(nullptr) {}

    void push(int value)
    {
        Node* newNode = new Node(value);
        if (rear == nullptr)
        {
            front = rear = newNode;
        }
        else
        {
            rear->next = newNode;
            rear = newNode;
        }
    }

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

    bool isEmpty()
    {
        return front == nullptr;
    }

    ~Queue()
    {
        while (!isEmpty()) pop();
    }
};

class Stack
{
private:
    struct Node
    {
        int data;
        Node* next;
        Node(int val, Node* nxt = nullptr) : data(val), next(nxt) {}
    };

    Node* topNode;

public:
    Stack() : topNode(nullptr) {}

    void push(int value)
    {
        topNode = new Node(value, topNode);
    }

    int pop()
    {
        if (isEmpty())
        {
            throw std::out_of_range("Stack is empty");
        }
        Node* temp = topNode;
        int val = temp->data;
        topNode = topNode->next;
        delete temp;
        return val;
    }

    bool isEmpty()
    {
        return topNode == nullptr;
    }

    ~Stack()
    {
        while (!isEmpty()) pop();
    }
};

class Graph
{
private:
    std::map<int, std::vector<int>> adj;

public:
    // Add undirected edge
    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void inputGraph()
    {
        int edges;
        std::cout << "Enter the number of edges: ";
        std::cin >> edges;

        std::cout << "Enter the edges (format: u v):\n";
        for (int i = 0; i < edges; ++i)
        {
            int u, v;
            std::cin >> u >> v;
            addEdge(u, v);
        }
    }

    void printGraph()
    {
        std::cout << "Graph adjacency list:\n";
        for (const auto& pair : adj)
        {
            std::cout << pair.first << " -> ";
            for (int v : pair.second)
            {
                std::cout << v << " ";
            }
            std::cout << std::endl;
        }
    }

    std::vector<int> getAdjVertices(int v)
    {
        static const std::vector<int> empty;
        auto it = adj.find(v);
        return it != adj.end() ? it->second : empty;
    }

    void bfs(int start)
    {
        std::set<int> visited;
        Queue q;
        q.push(start);
        visited.insert(start);

        std::cout << "BFS: ";
        while (!q.isEmpty())
        {
            int v = q.pop();
            std::cout << v << " ";

            for (int neighbor : getAdjVertices(v))
            {
                if (visited.find(neighbor) == visited.end())
                {
                    q.push(neighbor);
                    visited.insert(neighbor);
                }
            }
        }
        std::cout << std::endl;
    }

    void dfs(int start)
    {
        std::set<int> visited;
        Stack s;
        s.push(start);

        std::cout << "DFS: ";
        while (!s.isEmpty())
        {
            int v = s.pop();

            if (visited.find(v) == visited.end())
            {
                std::cout << v << " ";
                visited.insert(v);

                const auto& neighbors = getAdjVertices(v);
                for (auto it = neighbors.rbegin(); it != neighbors.rend(); ++it)
                {
                    if (visited.find(*it) == visited.end())
                    {
                        s.push(*it);
                    }
                }
            }
        }
        std::cout << std::endl;
    }
};

int main()
{
    Graph g;
    g.inputGraph();
    g.printGraph();

    int start;
    std::cout << "Enter start vertex: ";
    std::cin >> start;

    g.bfs(start);
    g.dfs(start);

    return 0;
}

