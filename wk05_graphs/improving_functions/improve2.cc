#include <iterator>
#include <vector>
#include <algorithm>
#include <limits>

/**
 * @brief Gets the smallest value from the vector passed as a parameter.
 *
 * @param vec vector which is searched for the smallest value.
 * @return int - the smallest value or 0 (zero) if vector is empty.
 */
int minValue(std::vector<int> vec){
    if ( vec.empty() ) { return 0; }
    int minVal = std::numeric_limits<int>::max();
    for (int num: vec) {
        if (num < minVal) {
            minVal = num;
        }
    }
    return minVal;
}
