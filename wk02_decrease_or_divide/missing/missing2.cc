#include <cstdlib>
#include <iostream>
#include "test.hh"

int searchSmallestMissing(int* A, int left, int right){
    //TODO: your code here
    //return missing value OR
    //return NO_VALUE_MISSING if no value is missing
    if (left > right) return NO_VALUE_MISSING;

    int mid = (left + right)/2;
    if (A[mid] == A[0] + mid){
        return searchSmallestMissing(A, mid + 1, right);
    }
    else {
        return searchSmallestMissing(A, left, mid - 1);
    }
    return NO_VALUE_MISSING;
}
