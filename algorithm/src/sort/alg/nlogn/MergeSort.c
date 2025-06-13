#include <stdio.h>
#include <stdlib.h>
// Merge Sort: the merge sort would sort the left 
// and the right part of an array, and then merge
// them together. How to sort the left and the right
// part? Call this procedure again (recursively) until
// the array only contains 1 element.

void mergeSort(int* ori, int start, int end, int* res){
    if(start >= end) return;
    int mid = (end - start) / 2 + start;
    mergeSort(ori, start, mid, res);
    mergeSort(ori, mid + 1, end, res);
    merge(ori, start, end, res);
}

void merge(int* ori, int start, int end, int* res){
    int mid = (end - start) / 2 + start;
    int indOfRes = start, indOfLef = start, indOfRht = mid + 1;
    while(indOfLef <= mid && indOfRht <= end){
        if(ori[indOfLef] <= ori[indOfRht]) res[indOfRes++] = ori[indOfLef++];
        else res[indOfRes++] = ori[indOfRht++];
    }
    while(indOfLef <= mid) res[indOfRes++] = ori[indOfLef++];
    while(indOfRht <= end) res[indOfRes++] = ori[indOfRht++];
    while(indOfRes--) ori[indOfRes] = res[indOfRes];
}

// first optimization: can we DON'T allocate (on heap or stack) 
// additional memory to finish Merge Sort? -> In-Place Merge Sort?
// the truth is, if we do that, then we have to move the element constantly
// to not lose the information. The result is, Merge Sort becomes
// Insert Sort, and it it really low effective.
void mergeSortInPlace(int* arr, int start, int end){
    if(start >= end) return;
    int mid = (end - start) / 2 + start;
    mergeSortInPlace(arr, start, mid);
    mergeSortInPlace(arr, mid + 1, end);
    mergeInPlace(arr, start, end);
}

void mergeInPlace(int* arr, int start, int end){
    int mid = (end - start) / 2 + start;
    int indOfLef = start, indOfRht = mid + 1;
    while(indOfLef <= mid && indOfRht <= end){
        if(arr[indOfLef] <= arr[indOfRht]) indOfLef++;
        else{
            int value = arr[indOfRht];
            int ind = indOfRht;
            while(ind > indOfLef){
                arr[ind] = arr[ind - 1];
                ind--;
            }
            arr[ind] = value;
            indOfLef++;
        }
    }
}