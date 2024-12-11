#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <algorithm>

std::ifstream f("day1.txt");

struct CustomCompare {
    bool operator()(const int &a, const int &b ) const {
        return a < b;
    }
};

// CustomCompare just for the fun of it
std::vector<int> listA;
std::vector<int> listB;

void see(std::vector<int> &kijkvector) {
    for (auto it = kijkvector.begin(); it != kijkvector.end(); ++it) {
        std::cout << "Number " << *it << "\n";
    }
}

void read() {
    int a;
    int b;

    while (!f.eof()) {
        f >> a >> b;

        listA.push_back(a);
        listB.push_back(b);
    }

    std::sort(listA.begin(), listA.end());
    std::sort(listB.begin(), listB.end());

    see(listA);

    std::cout << listA.size() << "\n";
    std::cout << listB.size() << "\n";
}

int solve() {
    long long sum = 0;
    auto itA = listA.begin();
    auto itB = listB.begin();

    while (itA != listA.end() && itB != listB.end()) {
        sum += std::abs(*itA - *itB);
        ++itA;
        ++itB;
    }

    return sum;
}

int main() {
    read();
    std::cout << "Sum " << solve() << "\n";
}