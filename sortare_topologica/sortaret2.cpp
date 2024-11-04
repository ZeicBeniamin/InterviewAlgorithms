#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;

ifstream fin("sortaret.in");
ofstream gout("sortaret.out");

/** Classes **************************** */

class Node;
class Node;

class Node {
private:
    int weight;
    Node *node;
public:
    Node(Node *) : weight(0) {}
    Node & operator=(const Node&) = delete;
    Node (const Node&) = delete;
};

class Node {
private:
    int id;
    vector<Node*> edges;
public:
    Node(int id) : id(id) {};
    // Delete copy and copy-assignment constructors
    Node & operator=(const Node&) = delete;
    Node (const Node&) = delete;

    void add_edge(Node *e) {
        edges.push_back(e);
    }
};

/** Variables **************************** */

int n_nodes;
int m_edges;

int in_deg[50001];

unordered_map<int, Node*> nodes_dict;
vector<Node *> topological_sort;

/** Functions **************************** */

void read_graph() {
    Node *src;
    Node *dst;
    
    int node_1_id;
    int node_2_id;

    fin >> n_nodes >> m_edges;

    for (int i = 0; i < m_edges; ++i) {
        fin >> node_1_id >> node_2_id;
        
        // Create nodes
        if (!nodes_dict.contains(node_1_id)) {
            src = new Node(node_1_id);
            nodes_dict[node_1_id] = src;
            cout << "Creating node " << node_1_id << "\n";
        }
        if (!nodes_dict.contains(node_2_id)) {
            dst = new Node(node_2_id);
            nodes_dict[node_2_id] = dst;
            cout << "Creating node " << node_2_id << "\n";
        }
        // Link nodes
        Node *edge = new Node(nodes_dict[node_2_id]);
        nodes_dict[node_1_id] -> add_edge(edge);

        ++in_deg[node_2_id];
    }
}

void topological_sort() {
    // Add all zero-deg nodes to qeue

    // Add rest of nodes to queue
}

void deallocate() {
    for (auto it = nodes_dict.begin(); it != nodes_dict.end(); ++it) {
        auto key = it -> first;
        auto *node = nodes_dict[key];
        cout << "Deleting node " << key << "\n";
        delete node; // Problematic - edges stay in memory
    }
}

int main() {
    read_graph();
    topological_sort();
    deallocate();
    return 0;
}