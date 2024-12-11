#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#define INITIALIZE 2

std::ifstream f("day2.txt");


inline int signum(int a) {
    return (a > 0) - (a < 0);
}

void read() {
    /*
        This is somewhat similar to taking a second derivative.

        You have the difference of two succesive numbers (that's really the first derivative)
        Then you have the sign of the last two differences (that would be the second derivative)

        The thing is that the differences we get are 1 less than the number of elements..
        E. g.: for 6 elements you would have 5 succesive differences. But then, when comparing
        the signs of two succesive differences, you get only 4 comparisons, because you compare
        5 successive differences.

        Thus, we can only check the difference in signedness after we've read 3 elements (that means
        we've calculated 2 differences). We could solve this either by having a supplementary while
        loop and some extra logic, or by signaling when we've read 3 elements. I chose the latter.

    */
    std::string line;

    bool valid = true;
    bool diffInitialized = false;
    int correctReports = 0;
    int currentDiff;
    int previousDiff;

    int currentNum;
    int previousNum;

    while (std::getline(f, line)) {
        valid = true;
        diffInitialized = false;
        std::istringstream lineStream(line);

        lineStream >> previousNum;
        std::cout << previousNum << " ";
        while (lineStream >> currentNum) {
            std::cout << currentNum << " ";
            currentDiff = currentNum - previousNum;
            if (std::abs(currentDiff) > 3 || currentDiff == 0) {
                valid = false;
                break;
            }
            if (diffInitialized && (signum(currentDiff) != signum(previousDiff))) {
                valid = false;
                break;
            }
            previousDiff = currentDiff;
            previousNum = currentNum;
            diffInitialized = true;
        }
        if (valid) {
            std::cout << "; valid\n";
            ++correctReports;
        } else {
            std::cout << "; invalid\n";
        }
    }

    std::cout << correctReports;
}

int main() {
    read();
}