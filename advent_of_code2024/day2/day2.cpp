#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#define INITIALIZE 2

std::ifstream f("day2.txt");

inline int signum(int a) { return (a > 0) - (a < 0); }


inline bool recheck(int nums[], int difs[], bool sign[], int idx) {
    int diff = nums[idx + 1] - nums[idx - 1];
    int sig = difs[idx + 1] - difs[idx - 1];
    if (std::abs(diff) > 3 || diff == 0) {
        return false;
    } else {
        difs[idx + 1] = diff;
        if (idx > 1 && sig != 0) {
            return false;
        }
        sign[idx + 1] = sig;
    }
}

void read() {
    /*
        This is somewhat similar to taking a second derivative.

        You have the difference of two succesive numbers (that's really the
       first derivative) Then you have the sign of the last two differences
       (that would be the second derivative)

        The thing is that the differences we get are 1 less than the number of
       elements.. E. g.: for 6 elements you would have 5 succesive differences.
       But then, when comparing the signs of two succesive differences, you get
       only 4 comparisons, because you compare 5 successive differences.

        Thus, we can only check the difference in signedness after we've read 3
       elements (that means we've calculated 2 differences). We could solve this
       either by having a supplementary while loop and some extra logic, or by
       signaling when we've read 3 elements. I chose the latter.

    */
    std::string line;

    int invalidLevels = 0;
    int elems = 0;
    int correctReports = 0;

    int nums[1005];
    int difs[1005];
    bool sign[1005];

    int* nums_p = nums;

    while (std::getline(f, line)) {
        invalidLevels = 0;
        elems = 0;
        std::istringstream lineStream(line);

        difs[0] = difs[1] = 0;
        sign[0] = sign[1] = 0;

        
        while(lineStream >> nums[elems]) {
            if (elems > 0) {
                difs[elems] = nums[elems] - nums[elems - 1];
            } 
            if (elems > 1) {
                sign[elems] = (signum(difs[elems]) != signum(difs[elems - 1]));
            }
            std::cout << nums[elems] << " ";
            ++elems;
        }

        for (int i = 1; i < elems && invalidLevels < 2; ++i) {
            // Check for one error.
            // If found, recheck after replacement; if errs again, exit, invalid
            if (difs[i] == 0 || std::abs(difs[i]) > 3) {
                ++invalidLevels;
                if (!recheck(nums, difs, sign, i - 1)) { // If error happened at pos. i, remove i-1
                    ++invalidLevels;
                }
            }
            if (i > 1) {
                if (sign[i]) {
                    ++invalidLevels;
                    if (!recheck(nums, difs, sign, i - 1)) {
                        ++invalidLevels;
                    }
                }
            }
            
        }

        if (invalidLevels < 2) {
            std::cout << "; valid\n";
            ++correctReports;
        } else {
            std::cout << "; invalid\n";
        }
    }

    std::cout << correctReports;
}


int main() { read(); }