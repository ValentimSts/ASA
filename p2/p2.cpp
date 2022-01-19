#include <iostream>
#include <vector>
#include <unordered_map>

void printGraph(std::vector<std::vector<int>> &graph, int size);
void computeInput();
std::vector<int> topologicalSort(std::vector<std::vector<int>> &graph);

int main() {
    computeInput();
    return 0;
}

/**
 * @brief 
 *      Sorts the given graph, topologically
 * 
 * @param graph
 * @return
 *      the sorted graph
 */
std::vector<int> topologicalSort(std::vector<std::vector<int>> &graph) {
    std::vector<int> sorted_graph;

    // do the stuffs brr

    return sorted_graph;
}

/**
 * @brief 
 *      Computes the input given, processing it for the
 *      actual algorithm
 * 
 *  v1, v2:
 *      Vertice identifiers.
 * 
 *  n_vertices:
 *      Number of vertices of the tree.
 *  n_edges:
 *      Number of edges.
 */
void computeInput() {
    int v1, v2, n_vertices, n_edges;

    if (scanf("%d %d", &v1, &v2) != 2) {
        std::cout << 0;
        return;
    }

    if (scanf("%d %d", &n_vertices, &n_edges) != 2) {
        std::cout << 0;
        return;
    }

    int u, v;

    // Graph used to represent the tree (adjacency list)
    std::vector<std::vector<int>> graph(n_vertices);
    // Vector used to know if a certain node has been visited or not
    std::vector<bool> visited(n_vertices, false);

    for (int i = 0; i < n_edges; i++) {
        if (scanf("%d %d", &u, &v) != 2) {
            std::cout << 0;
            return;   
        }

        // graph[u-1] because the identifiers go from 1 to n_vetices
        graph[u-1].push_back(v);
    }

    printGraph(graph, n_vertices);

    std::vector<int> sorted_graph = topologicalSort(graph);
}

void printGraph(std::vector<std::vector<int>> &graph, int size) {
    for (int i = 0; i < size; i++) {
        std::cout << i+1 << " ->";

        for (auto val: graph[i])
            std::cout << " " << val;
        
        std::cout << "\n";
    }  
}
