#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

class Graph
{
    private:
        std::map<int, std::vector<int> > adj;

        bool detectCycles(int v, int parent, std::map<int, bool> &visited, std::vector<int> &path,
                          std::vector<std::vector<int> > &cycles)
        {
            visited[v] = true;
            path.push_back(v);

            for (int neighbor: adj[v])
            {
                if (!visited[neighbor])
                {
                    if (detectCycles(neighbor, v, visited, path, cycles))
                    {
                        return true;
                    }
                }
                else if (neighbor != parent)
                {
                    // Cycle finding
                    std::vector<int> cycle;
                    auto it = std::find(path.begin(), path.end(), neighbor);
                    if (it != path.end())
                    {
                        cycle.insert(cycle.end(), it, path.end());
                        cycle.push_back(neighbor); // Close cycle
                        cycles.push_back(cycle);
                    }
                }
            }

            path.pop_back();
            return false;
        }

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

        void printCycles()
        {
            std::map<int, bool> visited;
            std::vector<std::vector<int> > cycles;
            std::vector<int> path;

            // DFS
            for (const auto &pair: adj)
            {
                int vertex = pair.first;
                detectCycles(vertex, -1, visited, path, cycles);
            }

            if (cycles.empty())
            {
                std::cout << "No cycles found." << std::endl;
            }
            else
            {
                std::cout << "Detected cycles:\n";
                for (const auto &cycle: cycles)
                {
                    for (int v: cycle)
                    {
                        std::cout << v << " ";
                    }
                    std::cout << std::endl;
                }
            }
        }
};

int main()
{
    Graph g;

    g.inputGraph();

    std::cout << "Graph:\n";
    g.printGraph();

    g.printCycles();

    return 0;
}

