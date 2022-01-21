#include <iostream>
#include <algorithm>

typedef enum {
    WHITE, YELLOW, RED
} visit_color;

void computeInput();
void printGraph(int** graph, int size);

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
    // Graph used to represent the tree (transpose graph). Where each
    // index is used as the identifier of the node, and contains its
    // parent id. (Ex: 1 -> 2, graph[1 (2-1)] = 1).
    int** graph = new int*[n_vertices];

    // Array used to store the number of parents eah node has, if the
    // node with id = 2 has 2 parents, n_parents[1 (2-1)] = 2. 
    int** n_parents = new int*[n_vertices];

    // Initializes the array with 0, as in the beggining we don't know
    // how many parents each node has.
    int init_val = 0;
    for (int i = 0; i < n_vertices; i++) {
        n_parents[i] = &init_val;
    }

    for (int i = 0; i < n_edges; i++) {
        if (scanf("%d %d", &u, &v) != 2) {
            std::cout << 0;
            return;   
        }

        std::cout << u << " " << v << std::endl;
        
        graph[v-1] = &u;
        std::cout << "joao?" << std::endl;

        // Increment the number of parents the node with id v-1 has.
        n_parents[v-1] += 1;
        std::cout << "joao2?" << std::endl;

        // If the node has more than 2 parents, the tree is invalid.
        if (*n_parents[v-1] > 2) {
            std::cout << "-";
            return;
        }
    }

    std::cout << "hmmmmm" << std::endl;

    printGraph(graph, n_vertices);
}


void printGraph(int** graph, int size) {
    for (int i = 0; i < size; i++) {
        std::cout << i+1 << " <- " << *graph[i] << std::endl;
    }  
}
