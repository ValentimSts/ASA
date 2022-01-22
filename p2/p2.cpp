#include <iostream>
#include <vector>

#define parent1 0
#define parent2 1
#define n_parents 2
#define weight 3
#define visited 4

void computeInput();
void printGraph(int** graph, int size);
void DFS(int** graph, int target_node, int curr_weight);
void getLCA(int** graph, int size);

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
            //   index 4: number of times the node has been visited (DFS)
            graph[v-1] = new int[5];

            graph[v-1][parent1] = -1;
            graph[v-1][parent2] = -1;
            graph[v-1][n_parents] = 0;
            graph[v-1][weight] = 0;
            graph[v-1][visited] = 0;
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

    printGraph(graph, n_vertices);

    DFS(graph, v1, 0);
    DFS(graph, v2, 0);

    getLCA(graph, n_vertices);
}


void DFS(int** graph, int target_node, int curr_weight) {
    // node has no parents 
    if (graph[target_node] == NULL) {
        graph[target_node] = new int[5];

        graph[target_node][weight] = curr_weight;
        graph[target_node][visited]++;

        return;
    }

    graph[target_node][weight] = curr_weight++;
    graph[target_node][visited]++;

    for (int i = 0; i < graph[target_node][n_parents]; i++) {
        DFS(graph, graph[target_node][i], curr_weight);
    }
}


void getLCA(int** graph, int size) {
    std::vector<int> common_nodes;
    std::vector<int> res;
    bool first_common = true;
    int min;

    for (int i = 0; i < size; i++) {
        if (graph[i][visited] == 2) {
            if (first_common) {
                first_common = false;
                min = graph[i][weight];
            }

            common_nodes.push_back(i);

            if (graph[i][weight] < min) {
                min = graph[i][weight];
            }
        }
    }

    for (auto val: common_nodes) {
        if (graph[val][weight] == min)
            res.push_back(val);
    }

    for (auto val: res) {
        std::cout << val << " ";
    }

    std::cout << std::endl;
}


void printGraph(int** graph, int size) {
    for (int i = 0; i < size; i++) {
        if (graph[i] != NULL)
            std::cout << i+1 << " <- " << graph[i][parent1] << " " << graph[i][parent2] << std::endl;
    }  
}
