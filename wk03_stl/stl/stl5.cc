#include <iterator>
#include <vector>
#include <algorithm>

#include "test.hh"

using namespace std;


/**
 * @brief Arrange vector in three subsequent sections:
 *        - those divisible by three (asc order)
 *        - those whose reminder is 1 (asc order)
 *        - those whose reminder is 2 (asc order)
 * @param v vector to be sorted
 * @return int EXIT_SUCCESS if everything went OK, EXIT_FAILURE otherwise
 */

int sortMod3(std::vector<int>& v)
{
    try {
        sort(v.begin(), v.end());

        std::vector<int> divisbleByThree;
        std::vector<int> remainderOne;
        std::vector<int> remainderTwo;

        for_each(v.begin(), v.end(), [&divisbleByThree, &remainderOne, &remainderTwo](int num){
            if(num % 3 == 0) {
                divisbleByThree.push_back(num);
            } else if(num % 3 == 1) {
                remainderOne.push_back(num);
            } else if(num % 3 == 2) {
                remainderTwo.push_back(num);
            }
        });

        v.clear();
        v.insert(v.end(), divisbleByThree.begin(), divisbleByThree.end());
        v.insert(v.end(), remainderOne.begin(), remainderOne.end());
        v.insert(v.end(), remainderTwo.begin(), remainderTwo.end());
    } catch (...) {
        return EXIT_FAILURE;
    }
}

