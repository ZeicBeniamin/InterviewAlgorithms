#include <fstream>
#include <iostream>
#include <vector>

#define MAX_ELEMS 200002

std::ifstream f("heapuri.in");
std::ofstream g("heapuri.out");

class Heap {
   private:
    inline int parent(int node_idx) { return node_idx / 2; }
    inline int left(int node_idx) { return node_idx * 2; }
    inline int right(int node_idx) { return node_idx * 2 + 1; }
    int heap_size() { return k.size() - 1; }  // Return number of elements in heap

   public:
    std::vector<std::pair<int, int>> k;  // first = key, second = insertion time
    int time_idx_corresp[MAX_ELEMS];
    // int positions[MAX_ELEMS] = {0};
    // 0 - undefined - not in vector
    // positions[x] = y; - node added at time x
    Heap() {
        k.push_back(std::make_pair(0, 0));
    }

    void sift(int node_idx) {
        // Move down, either on left or right branch, until bottom reached
        // or all children smaller than current node_idx
        int left_idx = left(node_idx);
        int right_idx = right(node_idx);
        int largest_node_idx = 0;

        do {
            // Decide which of the left/right or parent is largest
            if (left_idx <= heap_size() &&
                k[left_idx].first < k[node_idx].first) {
                largest_node_idx = left_idx;
            } else {
                largest_node_idx = node_idx;
            }
            if (right_idx <= heap_size() &&
                k[right_idx].first < k[largest_node_idx].first) {
                largest_node_idx = right_idx;
            }

            if (largest_node_idx != node_idx) {
                // Swap the elements as well as the heap indexes from the
                // correspondence vectors
                std::swap(k[node_idx], k[largest_node_idx]);
                std::swap(time_idx_corresp[k[node_idx].second],
                          time_idx_corresp[k[largest_node_idx].second]);
                sift(largest_node_idx);
            }
        } while (largest_node_idx != node_idx);  // When largest == node_idx, we
                                                 // cannot move node_idx further
    }

    void percolate(int node_idx) {
        // Move up until parent greater than current node_idx
        int key = k[node_idx].first;
        int insertion_time = k[node_idx].second;

        while (node_idx > 1 && key < k[parent(node_idx)].first) {
            // Replace child node with parent. Note that the parent node's
            // values have been saved in the variables 'key' and
            // 'insertion_time', so they are still available
            k[node_idx] = k[parent(node_idx)];
            // Record that element added at time 'k[node_idx].second' has been
            // moved to node_idx in the heap
            time_idx_corresp[k[node_idx].second] = node_idx;

            node_idx = parent(node_idx);
        }

        k[node_idx].first = key;
        k[node_idx].second = insertion_time;
        // Record that element added at time 'insertion_time' has been moved to
        // node_idx in the heap
        time_idx_corresp[insertion_time] = node_idx;
    }

    void insert(int elem, int time) {
        // Add on last position, then percolate
        // ++length;  // We're adding a new element, so increase heap size
        // k[length].first = elem;
        // k[length].second = time;  // Record insertion time of element
        k.push_back(std::make_pair(elem, time));
        // Record that element added at time 'time' has been placed on position
        // 'length' in the heap vector
        time_idx_corresp[time] = heap_size();
        percolate(heap_size());
    }

    void remove(int insert_time) {
        // Get heap position of node inserted at time t
        int node_idx = time_idx_corresp[insert_time];
        k[node_idx] = k[heap_size()];
        // Delete the last element of the vector.
        // Note that the end() iterator actually points one element past the
        // last element of the array
        k.erase(k.end() - 1);
        // Record that element added at time 'k[node_idx].second' has been moved
        // to node_idx in the heap
        time_idx_corresp[k[node_idx].second] = node_idx;

        if ((node_idx > 1) && k[node_idx].first < k[parent(node_idx)].first) {
            percolate(node_idx);
        } else {
            sift(node_idx);
        }
    }

    void get_max() { g << k[1].first << "\n"; }
};

void solve() {
    Heap heap;

    int ops;
    int opcode;
    int elem;
    int insert_time;
    int time = 0;

    f >> ops;
    for (int i = 0; i < ops; ++i) {
        f >> opcode;
        switch (opcode) {
            case 1:
                f >> elem;
                heap.insert(elem, ++time);
                break;
            case 2:
                f >> insert_time;
                heap.remove(insert_time);
                break;
            case 3:
                heap.get_max();
                break;
            default:
                throw std::runtime_error("Unknown operation type");
                break;
        }
    }
}

int main() { solve(); }