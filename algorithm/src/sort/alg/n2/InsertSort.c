#include "include/tools/swap.h"
// the basic version of Insert Sort is quite similar
// with Bubble Sort. However, the Bubble Sort would make 
// sure that the end area of the arr is SORTED, while
// Insert Sort would change the begin area of the arr 
// constantly. In short, Bubble Sort's sorted area would NEVER
// change, while Insert Sort's sorted area would change.
void insertSortO0(int* arr, int len){
    // the i is the index of the number SHOULD BE INSERTED
    // into the sorted area.
    for(int i = 1;i < len; i++){
        int j = i;
        while(j >= 1 && arr[j] < arr[j - 1]){
            swapInt(arr + j, arr + j - 1);
            j--;
        }
    }
}

// first optimization: we DON'T have to SWAP all the time,
// we just need to FIND the correct location of the number 
// SHOULD BE INSERTED. For example, 1 3 4 2 5 6, now if we 
// want insert 2 into 1, 3, 4, we just need to find the location
// of 2, and move numbers behind the location.
// Here is the difference of O0 and O1:
// O0: 1 3 4 2 5 6 -> 1 3 2 4 5 6 -> 1 2 3 4 5 6
// O1: 1 3 4 2 5 6 -> 1 3 4 " " 5 6, 2 -> 1 3 " " 4 5 6, 2
// 1 " " 3 4 5 6, 2 -> 1 2 3 4 5 6
void insertSortO1(int* arr, int len){
    for(int i = 1;i < len; i++){
        int curNum = arr[i];
        int j = i - 1;
        while(j >= 0 && arr[j] > curNum){
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = curNum;
    }
}