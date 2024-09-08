#include <cstdlib>
#include <iostream>
#include "test.hh"

int searchSmallestMissingRecursion(int* A, int left, int right){
    //TODO: your code here
    //return missing value OR
    //return NO_VALUE_MISSING if no value is missing
    if (left > right) return arr[0] + left;

    int mid = (left + right)/2;
    if (A[mid] == A[0] + mid){
        return searchSmallestMissing(A, mid + 1, right);
    }
    else {
        return searchSmallestMissing(A, left, mid - 1);
    }
}

int searchSmallestMissing(int* A, int left, int right){
    int n = right + 1;
    int result = searchSmallestMissingRecursion(arr, left , right);
    if (result > arr[n - 1]) {
        return NO_VALUE_MISSING;
    }
    else return result;
}