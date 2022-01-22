#include <iostream>
#include <vector>

#define parent1 0
#define parent2 1
#define n_parents 2
#define weight 3
#define visited 4

void computeInput();
void DFS(int** graph, int target_node, int curr_weight);
void getLCA(int** graph, int n_vertices, int n_edges);

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
    for (int i = 0; i < n_vertices; i++) {
        // We initialize all the nodes with an array of 4 posiztion:
        // ----------------------------------------------------------
        //   index 0 (parent1): first parent node
        //   index 1 (parent2): second parent node (if needed)
        //   index 2 (n_paents): number of parents
        //   index 3 (weight): weight of the node (to be found after the DFS)
        //   index 4 (visited): number of times the node has been visited (DFS)
        graph[i] = new int[5];

        graph[i][parent1] = -1;
        graph[i][parent2] = -1;
        graph[i][n_parents] = 0;
        graph[i][weight] = n_edges;
        graph[i][visited] = 0;
    }

    for (int i = 0; i < n_edges; i++) {
        if (scanf("%d %d", &u, &v) != 2) {
            std::cout << 0;
            return;   
        }

        int parent_pos = graph[v-1][n_parents];

        // If the node has more than 2 parents, the tree is invalid.
        if (parent_pos == 2) {
            std::cout << "-" << std::endl;
            return;
        }

        graph[v-1][parent_pos] = u;

        // Increments the number of parents of the node
        graph[v-1][n_parents]++;
    }

    DFS(graph, v1, 0);
    DFS(graph, v2, 0);

    getLCA(graph, n_vertices, n_edges);
}


void DFS(int** graph, int target_node, int curr_weight) {
    // We decrement the targe_node because, once again, the node
    // ids go from 1 to n, and we want them to go from 0 to n-1.
    target_node--;

    if (graph[target_node][n_parents] == 0) {
        // Node has no parents and so we end the algorithm
        if (graph[target_node][weight] > curr_weight) {
            graph[target_node][weight] = curr_weight;
        }
        graph[target_node][visited]++;
        return;
    }

    // We only want to keep the lowest cost to get to a certain node (weight),
    // whether its from node v1 or v2, we only want the lowest one.
    if (graph[target_node][weight] > curr_weight) {
        graph[target_node][weight] = curr_weight;
    }
    graph[target_node][visited]++;

    for (int i = 0; i < graph[target_node][n_parents]; i++) {
        DFS(graph, graph[target_node][i], curr_weight+1);
    }
}


void getLCA(int** graph, int n_vertices, int n_edges) {
    std::vector<int> common_nodes;
    int min = n_edges, n_lca = 0;


    for (int i = 0; i < n_vertices; i++) {
        // If the node has been visited atleast 2 times its a common node
        // between the two DFS.
        if (graph[i][visited] >= 2) {
            common_nodes.push_back(i);

            if (graph[i][weight] < min) {
                min = graph[i][weight];
                n_lca = 0;
            }
            n_lca++;
        }
    }

    for (auto node_id: common_nodes) {
        if (graph[node_id][weight] == min) {
            if (n_lca >  1) {
                std::cout << node_id+1 << " ";
            }
            else {
                std::cout << node_id+1;
            }
        }
    }

    std::cout << std::endl;
}
