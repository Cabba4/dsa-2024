#include <iterator>
#include <vector>
#include <algorithm>
#include <iostream>
#include <numeric>


/**
 * @brief creates a vector of integers with ascending numbers from 0 - n-1
 *
 * @param n the size of the vector to be created
 * @return std::vector<int>
 */
std::vector<int> ascendingVector(int n){
    std::vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        v[i] = i;  // Assign values directly
    }
    return v;
}
