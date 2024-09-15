/**
 * iteration3.cc
 *
 * Print beginning half of a list
 */

/**
 * DO NOT ADD ANY INCLUDES!!
 */

#include "iteration3.hh"
using namespace std;


void printHalf(const list<int>& lst)
{
    // ADD YOUR CODE HERE
    auto it = lst.begin();
    auto mid = next(lst.begin(), lst.size() / 2);
    while(it != mid) {
        std::cout<<*it<<" ";
        ++it;
    }
    std::cout<<endl;
}
