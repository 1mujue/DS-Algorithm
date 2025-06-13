#include "include/tools/swap.h"
// basic thought: each time, make the largest number
// to the end of CURRENT ARRAY, and then the length
// of current array minus 1.
void bubbleSortO0(int* arr, int len){
    // i represents the count of numbers that has been
    // moved to the end. (sorted)
    for(int i = 0;i < len - 1; i++){
        for(int j = 0;j < len - 1 - i; j++){
            if(arr[j] > arr[j + 1]) {
                swapInt(arr + j, arr + j + 1);
            }
        }
    }
}

// first optimization: if there is no swap happened,
// meaning the arr has been sorted, then we can break.
void bubbleSortO1(int* arr, int len){
    int isSorted;
    for(int i = 0;i < len - 1; i++){
        isSorted = 1;
        for(int j = 0;j < len - 1 - i; j++){
            if(arr[j] > arr[j + 1]) {
                swapInt(arr + j, arr + j + 1);
                isSorted = 0;
            }
        }
        if(isSorted) break;
    }
}

// second optimization: we only need to traverse
// those elements before the location where the last
// swap happened. For example:
// 3 2 1 4 5 6, and the location should be 1 (arr[1] == 2)
// and then the arr is 3 1 2 4 5 6, clearly, arr[i] (i >= location)
// have all been sorted !!
void bubbleSortO2(int* arr, int len){
    int isSorted = 0;
    // the index of last UNSORTED element.
    int indOfLastUnsortedEle = len - 1;
    // the index of last SWAPPED.
    int indOfLastSwap = -1;
    while(!isSorted){
        isSorted = 1;
        for(int i = 0;i < indOfLastUnsortedEle; i++){
            if(arr[i] > arr[i + 1]){
                swapInt(arr + i, arr + i + 1);
                isSorted = 0;
                indOfLastSwap = i;
            }
        }
        indOfLastUnsortedEle = indOfLastSwap;
    }
}