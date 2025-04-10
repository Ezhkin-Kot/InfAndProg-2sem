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

        std::vector<int> getAdjVertices(int v)
        {
            static const std::vector<int> empty;
            auto it = adj.find(v);
            return it != adj.end() ? it->second : empty;
        }
};

int main()
{
    Graph g;

    g.inputGraph();

    std::cout << "Graph:\n";
    g.printGraph();

    int vertex;
    std::cout << "Enter vertex: ";
    std::cin >> vertex;
    std::cout << "Number of adjacent vertices: " << g.getAdjVertices(vertex).size() << std::endl;

    return 0;
}

/* 
5
1 2
1 3
2 4
3 4
4 5
*/

