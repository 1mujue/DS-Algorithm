#include "include/tools/random.h"
#include "include/tools/swap.h"
// Quick Sort: the most prevalent sort algorithm.
// The key thought of Quick Sort:
// 1. find an element as the pivot.
// 2. make all elment smaller than the pivot at the 
// left of it, and all element larger than the pivot
// at the right of it.
// 3. do the same thing recursively on the left side
// and right side.
// * the "smaller" and "larger" can be defined by yourself,
// and the element doesn't have to be a number.

void quickSort(int* arr, int start, int end){
    if(start >= end) return;
    // take arr[start] as pivot.
    int pivot = arr[start];

    int smallerInd = start; // smallerInd - 1 is the last elment smaller than pivot
    int biggerInd = end; // biggerInd + 1 is the first element larger than pivot
    int ind = start + 1;
    
    // for it >= biggerInd, arr[biggerInd] > pivot, so there is no need to traverse.
    while(ind <= biggerInd){
        if(arr[ind] > pivot){
            swapInt(arr + ind, arr + biggerInd);
            // after swap, arr[biggerInd](origin is arr[ind]) must be larger than pivot 
            // however, arr[ind](origin is arr[biggerInd]) might still 
            // be larger than pivot, so ind CAN'T plus 1.
            biggerInd--;
        }
        else if(arr[ind] < pivot){
            swapInt(arr + ind, arr + smallerInd);
            // after swap, arr[smallerInd](origin is arr[ind]) must be smaller than pivot,
            // but arr[ind](origin is arr[smallerInd]) might be larger than pivot.
            // However, because ind is always larger than smallerInd, therefore, before swap,
            // arr[smallerInd] must have been traversed by ind. If arr[smallerInd] is larger
            // than pivot, then it should be swapped to the right side of pivot, if
            // arr[smallerInd] is smaller than pivot, then it should be swapped to the left side
            // before. Therefore, arr[smallInd] can only equals to pivot.
            smallerInd++;
            ind++;
        }
         else{
            // euqual area.
            ind++;
        }
    }

    quickSort(arr, start, smallerInd - 1);
    quickSort(arr, biggerInd + 1, end);
}