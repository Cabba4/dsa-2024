#include <iterator>
#include <vector>
#include <algorithm>

#include "test.hh" // NOT_FOUND constant

using namespace std;


/**
 * @brief Find the median value of a given vector, whose elements are in random
 *        order. Return NOT_FOUND if the size of the vector is zero.
 *
 * @param v unsorted vector
 * @return int calculated median of parameter vector
 */
int findMedian(std::vector<int>& v)
{
    if ( !v.empty()) {
        sort(v.begin(), v.end());
        size_t n = v.size();
        if (n % 2 == 1) {
            auto mid = v.begin() + n / 2;
            return *mid;
        } else {
            auto mid1 = v.begin() + (n / 2) - 1;
            auto mid2 = v.begin() + (n / 2);
            return (*mid1 + *mid2) / 2;
        }
    } else {
        return NOT_FOUND;
    }

}

