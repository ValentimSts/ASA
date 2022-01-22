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
    // parent(s) id, aswell as some extra information (explained bellow).
    int** graph = new int*[n_vertices];

    for (int i = 0; i < n_edges; i++) {
        if (scanf("%d %d", &u, &v) != 2) {
            std::cout << 0;
            return;   
        }

        
        // v-1 because the node ids go from 1 to n
        if (graph[v-1] == NULL) {
            // If the node hasn't been initialized, we initialize it with
            // 4 positions:
            // ----------------------------------------------------------
            //   index 0: first parent node
            //   index 1: second parent node (if needed)
            //   index 2: number of parents
            //   index 3: weight of the node (to be found after the DFS)
            graph[v-1] = new int[4];

            graph[v-1][0] = -1;
            graph[v-1][1] = -1;
            graph[v-1][2] = 0;
            graph[v-1][3] = 0;
        }

        int parent_pos = graph[v-1][2];

        // If the node has more than 2 parents, the tree is invalid.
        if (parent_pos == 2) {
            std::cout << "-" << std::endl;
            return;
        }

        graph[v-1][parent_pos] = u;

        // Increments the number of parents of the node
        graph[v-1][2]++;
    }

    printGraph(graph, n_vertices);
}

void 

void printGraph(int** graph, int size) {
    for (int i = 0; i < size; i++) {
        if (graph[i] != NULL)
            std::cout << i+1 << " <- " << graph[i][0] << " " << graph[i][1] << std::endl;
    }  
}
