#include <iostream>
#include <algorithm>
#include <vector>

#define parent1 0
#define parent2 1
#define n_parents 2
#define visited 3

typedef enum {
    WHITE, BLUE, YELLOW, GREEN, BLACK
} visit_type;

void computeInput();
void DFS(int** graph, int target_node, visit_type color);
void visitNode(int** graph, int target_node, visit_type color);
void getLCA(int** graph, int n_vertices, int n_edges);
void DFS_aux(int** graph, int target_node);

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
        std::cout << 0 << std::endl;
        return;
    }

    if (scanf("%d %d", &n_vertices, &n_edges) != 2) {
        std::cout << 0 << std::endl;
        return;
    }

    int u, v;
    // Graph used to represent the tree (transpose graph). Where each
    // index is used as the identifier of the node, and contains its
    // parent(s) id, aswell as some extra information (explained bellow).
    int** graph = new int*[n_vertices];
    for (int i = 0; i < n_vertices; i++) {
        // We initialize all the nodes with an array of 4 posiztion:
        // ----------------------------------------------------------
        //   index 0 (parent1): first parent node
        //   index 1 (parent2): second parent node (if needed)
        //   index 2 (n_paents): number of parents
        //   index 3 (weight): weight of the node (to be found after the DFS)
        //   index 4 (visited): number of times the node has been visited (DFS)
        graph[i] = new int[4];

        graph[i][parent1] = -1;
        graph[i][parent2] = -1;
        graph[i][n_parents] = 0;
        graph[i][visited] = WHITE;
    }

    for (int i = 0; i < n_edges; i++) {
        if (scanf("%d %d", &u, &v) != 2) {
            std::cout << 0 << std::endl;
            return;   
        }

        int parent_pos = graph[v-1][n_parents];

        // If the node has more than 2 parents, the tree is invalid.
        if (parent_pos == 2) {
            std::cout << 0 << std::endl;
            return;
        }

        graph[v-1][parent_pos] = u;

        // Increments the number of parents of the node
        graph[v-1][n_parents]++;
    }

    DFS(graph, v1, BLUE);
    DFS(graph, v2, YELLOW);

    getLCA(graph, n_vertices, n_edges);
}


void DFS(int** graph, int target_node, visit_type color) {
    // We decrement the targe_node because, once again, the node
    // ids go from 1 to n, and we want them to go from 0 to n-1.
    target_node--;

    if (graph[target_node][n_parents] == 0) {
        // Node has no parents and so we end the algorithm
        visitNode(graph, target_node, color);
        return;
    }

    visitNode(graph, target_node, color);

    for (int i = 0; i < graph[target_node][n_parents]; i++) {
        DFS(graph, graph[target_node][i], color);
    }
}


void visitNode(int** graph, int target_node, visit_type color) {
    // If the node hasn't yet been visited, we visit it with the current
    // color we're using.
    if (graph[target_node][visited] == WHITE) {
        graph[target_node][visited] = color;
    }
    // If the node was already BLUE and our current color is YELLOW it means
    // that node is a common node between both sub-graphs, and so we color it
    // GREEN.
    else if (graph[target_node][visited] == BLUE && color == YELLOW) {
        graph[target_node][visited] = GREEN;
    }
}


void getLCA(int** graph, int n_vertices, int n_edges) {
    std::vector<int> lca;
    int n_lca = 0;


    for (int i = 0; i < n_vertices; i++) {
        // If the node id GREEN its a common node
        // between the two sub-graphs.
        if (graph[i][visited] == GREEN) {
            lca.push_back(i);
            n_lca++;
        }
    }

    if (n_lca == 0) {
        std::cout << "-" << std::endl;
        return;
    }

    std::sort(lca.begin(), lca.end());

    for (int common_node: lca) {
        DFS_aux(graph, common_node);
    }

    for (int common_node: lca) {
        if (graph[common_node][visited] != BLACK) {
            std::cout << common_node+1 << " ";
        }
    }

    std::cout << std::endl;
}

void DFS_aux(int** graph, int target_node) {

    for (int i = 0; i < graph[target_node][n_parents]; i++) {
        int parent_id = graph[target_node][i];
        graph[parent_id-1][visited] = BLACK;
    }
}
