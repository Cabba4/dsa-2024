#include <iterator>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


/**
 * @brief Erases every second item from the vector. Example: {1, 2, 3, 4} -> {1, 3}
 *
 * @param vec vector where every second item is erased.
 */
void eraseEverySecond(std::vector<int>& vec) {
    for (auto i = vec.begin() + 1; i != vec.end(); ) {
        i = vec.erase(i); // Erase the current element and get the next iterator
        if (i != vec.end()) {
            ++i; // Move to the next element
        }
    }
}

