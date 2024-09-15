/**
 * iteration2.cc
 *
 * Print every second item of a list starting from the first item
 */

/**
 * DO NOT ADD ANY INCLUDES!!
 */

#include "iteration2.hh"
using namespace std;


void printEverySecond(const list<int>& lst)
{
    // ADD YOUR CODE HERE
    for (auto it = lst.begin(); it != lst.end(); std::advance(it, 2)) {
        std::cout << *it << " ";
        auto next_it = it;
        std::advance(next_it, 1);  // Check if advancing will go past the end
        if (next_it == lst.end())  // If so, stop the loop
            break;
    }
    std::cout << std::endl;
}
