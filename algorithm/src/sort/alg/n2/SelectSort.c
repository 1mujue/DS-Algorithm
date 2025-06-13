#include "include/tools/swap.h"
// it is quite similar with bubble sort:
// find the min or max number of CURRENT ARRAY,
// and then put it at the beginning. However,
// Select Sort would record index first and then
// swap the number, and that makes sorting more
// effective.
void selectSortO0(int* arr, int len){
    for(int i = 0;i < len - 1; i++){
        int indOfMin = i;
        for(int j = i + 1; j < len; j++){
            if(arr[j] < arr[indOfMin]) indOfMin = j;
        }
        swapInt(arr + i, arr + indOfMin);
    }
}

// first optimization: we can find min and max 
// AT THE SAME TIME, and that would be more effective.
void selectSortO1(int* arr, int len){
    for(int i = 0;i < len / 2; i++){
        int indOfMin = i;
        int indOfMax = i;
        for(int j = i + 1; j < len - i; j++){
            if(arr[indOfMin] > arr[j]) indOfMin = j;
            if(arr[indOfMax] < arr[j]) indOfMax = j;
        }
        // in this case, i == indOfMin == indOfMax,
        // and all numbers after i are same, so the 
        // arr is sorted.
        if(indOfMin == indOfMax) break;
        swapInt(arr + i, arr + indOfMin);
        
        // since arr[i] and arr[indOfMin] have been
        // swapped, the indOfMax should now be indOfMin.
        if(indOfMax == i) indOfMax = indOfMin;
        int indLast = len - 1 - i;
        swapInt(arr + indLast, arr + indOfMax);
    }
}