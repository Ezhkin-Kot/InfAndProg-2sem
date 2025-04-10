#include <iostream>
#include <vector>
#include <map>

class Queue
{
    private:
        struct Node
        {
            std::string value;
            Node *next;
            Node(std::string &val) : value(val), next(nullptr) {}
        };

        Node *frontNode = nullptr;
        Node *backNode = nullptr;

    public:
        void push(std::string &value)
        {
            Node *newNode = new Node(value);
            if (!backNode)
            {
                frontNode = backNode = newNode;
            }
            else
            {
                backNode->next = newNode;
                backNode = newNode;
            }
        }

        void pop()
        {
            if (!empty())
            {
                Node *temp = frontNode;
                frontNode = frontNode->next;
                delete temp;
                if (!frontNode)
                {
                    backNode = nullptr;
                }
            }
        }

        std::string front()
        {
            return frontNode->value;
        }

        bool empty()
        {
            return frontNode == nullptr;
        }

        ~Queue()
        {
            while (!empty())
            {
                pop();
            }
        }
};

class Graph
{
    private:
        std::map<std::string, std::vector<std::string> > adj;

    public:
        // Add an edge (undirected)
        void addEdge(std::string &u, std::string &v)
        {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // Set all possible moves
        void setHorseGraph()
        {
            std::vector<std::pair<int, int> > movesXY = {
                {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}
            };

            for (char x = 'A'; x <= 'H'; ++x)
            {
                for (int y = 1; y <= 8; ++y)
                {
                    std::string beginCell = std::string(1, x) + std::to_string(y);
                    for (int i = 0; i < 8; ++i)
                    {
                        char nx = x + movesXY[i].first;
                        int ny = y + movesXY[i].second;
                        if (nx >= 'A' && nx <= 'H' && ny >= 1 && ny <= 8)
                        {
                            std::string endCell = std::string(1, nx) + std::to_string(ny);
                            addEdge(beginCell, endCell);
                        }
                    }
                }
            }
        }

        // BFS to find minimal sequence of moves
        void shortestPath(std::string &start, std::string &end)
        {
            std::map<std::string, bool> visited;
            std::map<std::string, std::string> prev;
            Queue queue;

            visited[start] = true;
            queue.push(start);

            while (!queue.empty())
            {
                std::string current = queue.front();
                queue.pop();

                if (current == end) break;

                for (std::string &neighbor: adj[current])
                {
                    if (!visited[neighbor])
                    {
                        visited[neighbor] = true;
                        prev[neighbor] = current;
                        queue.push(neighbor);
                    }
                }
            }

            if (!visited[end])
            {
                std::cout << "Path not found." << std::endl;
                return;
            }

            std::vector<std::string> path;
            for (std::string at = end; at != start; at = prev[at])
            {
                path.push_back(at);
            }
            path.push_back(start);
            std::reverse(path.begin(), path.end());

            std::cout << "Shortest path: ";
            for (std::string &v: path)
            {
                std::cout << v << " ";
            }
            std::cout << std::endl;
        }
};

int main()
{
    Graph g;
    g.setHorseGraph();

    std::string u, v;
    std::cout << "Enter the initial and final cells (format: A2 E6): ";
    std::cin >> u >> v;
    g.shortestPath(u, v);

    return 0;
}

