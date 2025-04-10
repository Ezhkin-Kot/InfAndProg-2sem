#include <iostream>
#include <map>
#include <vector>

class Graph
{
    private:
        std::map<int, std::vector<int> > adj;

    public:
        // Add an edge (undirected)
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
            for (const auto &pair: adj)
            {
                std::cout << pair.first << " -> ";
                for (int v: pair.second)
                {
                    std::cout << v << " ";
                }
                std::cout << std::endl;
            }
        }

        void shortestPath(int start, int end)
        {
            std::map<int, bool> visited;
            std::map<int, int> prev;
            std::vector<int> queue;

            visited[start] = true;
            queue.push_back(start);

            // BFS
            while (!queue.empty())
            {
                int current = queue.front();
                queue.erase(queue.begin());

                if (current == end) break;

                for (int neighbor: adj[current])
                {
                    if (!visited[neighbor])
                    {
                        visited[neighbor] = true;
                        prev[neighbor] = current;
                        queue.push_back(neighbor);
                    }
                }
            }

            if (!visited[end])
            {
                std::cout << "Path not found." << std::endl;
                return;
            }

            std::vector<int> path;
            for (int at = end; at != start; at = prev[at])
            {
                path.push_back(at);
            }
            path.push_back(start);
            std::reverse(path.begin(), path.end());

            std::cout << "Shortest path: ";
            for (int v: path)
            {
                std::cout << v << " ";
            }
            std::cout << std::endl;
        }
};

int main()
{
    Graph g;

    g.inputGraph();

    std::cout << "Graph:\n";
    g.printGraph();

    int u, v;
    std::cout << "Enter vertices (format: u v): ";
    std::cin >> u >> v;
    g.shortestPath(u, v);

    return 0;
}

