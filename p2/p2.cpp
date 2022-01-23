/**
 * @author
 *      al012: Valentim Santos (99343), Tiago Santos (99333)
 * @brief
 *      Finds the lowest common ancestor of two different nodes from a
 *      direct acyclic graph.
 */


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
void getLCA(int** graph, int n_vertices);
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

        // Cycle
        if (u == v) {
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

    getLCA(graph, n_vertices);
}


/**
 * @brief 
 *      Simple DFS algorithm, used to visit all the nodes we need. A node that
 *      has been visited once will be painted BLUE/YELLOW, a node that has been
 *      visited twice will be painted GREEN.
 * 
 * @param graph
 *      The graph we want to visit.
 * @param target_node
 *      The starting node.
 * @param color
 *      Color of the search (BLUE or YELLOW).
 */
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


/**
 * @brief
 *      Visits a node and colors it accordingly.
 * 
 * @param graph
 *      The node's graph.
 * @param target_node 
 *      The node we want to visit.
 * @param color
 *      The color we're currently using to visit the nodes.
 */
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


/**
 * @brief 
 *      Finds the lowest common ancestor of our 2 initial nodes, by
 *      analyzing the sub-graph created from the 2 DFSs.
 * 
 * @param graph
 *      Our main graph.
 * @param n_vertices 
 *      The number of vertices of the graph.
 */
void getLCA(int** graph, int n_vertices) {
    std::vector<int> lca;
    int size = 0;

    for (int i = 0; i < n_vertices; i++) {
        // If the node is GREEN its a common node
        // between the two sub-graphs.
        if (graph[i][visited] == GREEN) {
            lca.push_back(i);
            size++;
        }
    }

    if (size == 0) {
        std::cout << "-" << std::endl;
        return;
    }

    std::sort(lca.begin(), lca.end());

    for (int common_node: lca) {
        // We color all the parent nodes from the common sub-graph BLACK,
        // all the nodes that aren't colored black (after this operation) 
        // are the ones we are looking for.
        for (int i = 0; i < graph[common_node][n_parents]; i++) {
            int parent_id = graph[common_node][i] - 1;

            graph[parent_id][visited] = BLACK;
        }
    }

    for (int common_node: lca) {
        if (graph[common_node][visited] != BLACK) {
            std::cout << common_node+1 << " ";
        }
    }

    std::cout << std::endl;
}
