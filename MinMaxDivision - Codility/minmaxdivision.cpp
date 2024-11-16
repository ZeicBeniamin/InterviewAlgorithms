#include <vector>
#include <limits.h>

using namespace std;

int maximum(vector<int> &A) {
    int max_a = A[0];
    for (auto it = A.begin(); it != A.end(); ++it) {
        max_a = std::max(*it, max_a);
    }

    return max_a;
}

int sum(vector<int> &A, int begin, int end) {
    int sum = 0;

    for (int i = begin; i < end; ++i) {
        sum += A[i];
    }

    return sum;
}

bool check(int K, int desired_sum, vector<int> &A) {
    int block_count = 1;
    int block_sum = 0;

    for (int i = 0; i < A.size(); ++i) {
        if (block_sum + A[i] > desired_sum) {
            // If the block sum goes past the deisred sum, create a new block.
            ++block_count;
            block_sum = A[i];
        } else {
            block_sum += A[i];
        }

        // Efficiency: exit early if number of blocks already larger than desired
        if (block_count > K) { return false; }
    }

    // If loop has terminated, the desired block sum has been achieved with at most K blocks.
    return true; 
}

int binary_search(int K, int M, vector<int> &A) {
    int vec_size = A.size();
    int lowest_sum = sum(A, 0, A.size());
    int beg = M;
    int end = lowest_sum;
    int mid = 0;

    while (beg <= end) {
        // Recalculate mid
        mid = (beg + end) / 2;
        // cout << "beg: " << beg << ", end: " << end << ", mid: " << mid << "\n";
        // If current sum is feasible with at most K blocks, lower the bar
        if (check(K, mid, A)) {
            end = mid -1;
            lowest_sum = mid;
        } else {
            beg = mid + 1;
        }
        // cout << lowest_sum << "\n";
        // cout << "beg: " << beg << ", end: " << end << "\n";
    }
    return lowest_sum;
}

int solution(int K, int M, vector<int> &A) {
    // Recalculate M, to obtain the lowest value of an array element
    M = maximum(A);
    if (K == 1) {
        // Obvious
        return sum(A, 0, A.size());
    } else {
        return binary_search(K, M, A);
    }
}