#include <cstdlib>
#include <iostream>
#include "test.hh"

int searchSmallestMissingIteration(int* arr, int size){
    //TODO: your code here
    //return missing value OR
    //return NO_VALUE_MISSING if no value is missing
    if (size == 0) return NO_VALUE_MISSING;

    for(int i=0; i< size; i++) {
        if( arr[i+1] - arr[i] > 1 ) {
            return arr[i] + 1;
        } 
    }
    return NO_VALUE_MISSING;
}