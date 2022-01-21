#include <iostream>
#include <vector>
#include <algorithm>

typedef enum {
    WHITE, YELLOW, RED
} visit_color;


/**
 * @brief 
 *      Struct node, used to describe each node of
 *      the graph.
 * 
 *  - std::vector<int> parents:
 *      vector containing all the parents of the node.
 *  - n_parents:
 *      number od parents the node has.
 * 
 *  - std::vector<int> children:
 *      vector containing all the children of the node.
 *  - n_children:
 *      number of children the node has. 
 */
typedef struct Node {
    int id;

    std::vector<int> parents;
    int n_parents = 0;

    std::vector<int> children;
    int n_children = 0;

    int weight = 0;
    visit_color color = WHITE;
} node;


void printGraph(std::vector<node> &graph, int size);
void computeInput();
std::vector<int> topologicalSort(std::vector<node> &graph, int graph_size, std::vector<bool> &visited);
void LCA(std::vector<node> &graph, int v1, int v2);
void visitParents(std::vector<node> &graph, node v, std::vector<int> &aux);


int main() {
    computeInput();
    return 0;
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
    std::vector<node> graph(n_vertices);

    for (int i = 0; i < n_edges; i++) {
        if (scanf("%d %d", &u, &v) != 2) {
            std::cout << 0;
            return;   
        }
        
        // "u-1" and "v-1" because the identifiers go from 1 to n_vetices
        graph[u-1].id = u;
        graph[u-1].children.push_back(v);
        graph[u-1].n_children++;

        graph[v-1].id = v;
        graph[v-1].parents.push_back(u);
        graph[v-1].n_parents++;
    }

    // Vector used to know if a certain node has been visited or not
    std::vector<bool> visited(n_vertices, false);

    printGraph(graph, n_vertices);

    std::vector<int> sorted_graph = topologicalSort(graph, n_vertices, visited);

    for (int val: sorted_graph) {
        std::cout << val << std::endl;
    }

    std::cout << std::endl;

    LCA(graph, v1, v2);
}


/**
 * @brief 
 *      Sorts the given graph, topologically
 * 
 * @param graph
 *      graph to be sorted
 * @return
 *      the sorted graph
 */
std::vector<int> topologicalSort(std::vector<node> &graph, int size, std::vector<bool> &visited) {
    std::vector<int> sorted_graph;

    for (int i = 0; i < size; i++) {

        for (auto val: graph[i].children) {
            // If that node hasn't been visited, we visit it
            if (!visited[val-1]) {
                visited[val-1] = true;
                sorted_graph.push_back(val);
            }
        }

        if (!visited[i]) {
            visited[i] = true;
            sorted_graph.push_back(i + 1);
        }

    }

    // Reverses the current vector because it has the values in the opposite order
    std::reverse(sorted_graph.begin(), sorted_graph.end());

    return sorted_graph;
}


void printGraph(std::vector<node> &graph, int size) {
    for (int i = 0; i < size; i++) {
        std::cout << i+1 << " ->";

        for (auto val: graph[i].children)
            std::cout << " " << val;
        
        std::cout << "\n";
    }  
}

/**
 * @brief 
 *      Lowest common ancestor
 * 
 * @param graph 
 * @param visited 
 */
void LCA(std::vector<node> &graph, int v1, int v2) {
    std::vector<int> aux;

    node n1 = graph[v1-1];
    node n2 = graph[v2-1];

    visitParents(graph, n1, aux);
    visitParents(graph, n2, aux);

    for (auto i: aux) {
        std::cout << i << " " << std::endl;
    }
}


void visitParents(std::vector<node> &graph, node v, std::vector<int> &aux) {
    switch(v.color) {
        case WHITE:
            v.color = YELLOW;
        case YELLOW:
            v.color = RED;
            aux.push_back(v.id);
    }

    if (v.n_parents > 0) {
        for (auto i: v.parents) {
            visitParents(graph, graph[i-1], aux);
        }
    } 
}
