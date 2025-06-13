#include "include/tools/swap.h"
#include <assert.h>
// Heap: usually it is a binary tree. Max Heap or Min Heap
// are widely used. Max Heap or Min Heap mean that the value
// of parent node is larger or smaller than its child nodes
// (in binary tree case, left node and right node). We will 
// take Max Heap as example.

void insertHeap(int* heap, int* heapSize, int num);
void buildHeap(int* heap, int heapSize);
void keepHeap(int* heap, int heapSize, int ind);
int getHeapEle(int* heap, int heapSize, int ind);
void deleteHeapEle(int* heap, int* heapSize, int ind);

// create a heap gradually.
void insertHeap(int* heap, int* heapSize, int num){
    (*heapSize)++;
    int ind = *heapSize - 1;
    // heap[(ind - 1) / 2] is the father node of 
    // heap[ind].
    while(ind > 0 && heap[(ind - 1) / 2] < num) {
        heap[ind] = heap[(ind - 1) / 2];
    }
    heap[ind] = num;
}
// create a heap based on the current one.
void buildHeap(int* heap, int heapSize){
    // the last index of leaf node is heapSize - 1,
    // so the last index of non-leaf node is 
    // (heapSize - 1 - 1) / 2 = heapSize / 2 - 1.
    for(int i = heapSize / 2 - 1; i >= 0; i--){
        keepHeap(heap, heapSize, i);
    }
}
void keepHeap(int* heap, int heapSize, int ind){
    int left = 2 * ind + 1;
    int right = 2 * ind + 2;
    int largest = ind;
    if(left < heapSize && heap[left] > heap[largest]) largest = left;
    if(right < heapSize && heap[right] > heap[largest]) largest = right;
    if(largest != ind){
        swapInt(heap + ind, heap + largest);
        keepHeap(heap, heapSize, largest);
    }
}
int getHeapEle(int* heap, int heapSize, int ind){
    assert(heapSize > ind && ind >= 0);
    return heap[ind];
}
void deleteHeapEle(int* heap, int* heapSize, int ind){
    heap[ind] = heap[--(*heapSize)];
    keepHeap(heap, *heapSize, ind);
}