#include "ADT/Heap.h"
#include <string.h>

Heap *newHeap(size_t capacity, size_t elementSize, int (*cmp)(const void *a, const void *b))
{
    Heap *ans = (Heap *)malloc(sizeof(Heap));
    ans->capacity = capacity;
    ans->elementSize = elementSize;
    ans->currentSize = 0;
    ans->cmp = cmp;
    ans->data = malloc(elementSize * capacity);
    return ans;
}
void freeHeap(Heap *heap)
{
    free(heap->data);
    free(heap);
}

void pushHeap(Heap *heap, const void *value)
{
    size_t index = heap->currentSize++;
    memcpy(heap->data + index * heap->elementSize, value, heap->elementSize);
    upHeap(heap, index);
}
void popHeap(Heap *heap)
{
    heap->currentSize--;
    memcpy(heap->data, heap->data + heap->currentSize * heap->elementSize, heap->elementSize);
    downHeap(heap, 0);
}
void *peekHeap(Heap *heap, size_t index)
{
    return heap->data + index * heap->elementSize;
}
void upHeap(Heap *heap, size_t index)
{
    void *value = malloc(heap->elementSize);
    const size_t elementSize = heap->elementSize;
    memcpy(value, heap->data + index * elementSize, elementSize);

    while (index && heap->cmp(heap->data + (index - 1) / 2 * elementSize, value) > 0)
    {
        memcpy(heap->data + index * elementSize, heap->data + (index - 1) / 2 * elementSize, elementSize);
        index = (index - 1) / 2;
    }
    memcpy(heap->data + index * elementSize, value, elementSize);
    free(value);
}
void downHeap(struct Heap *heap, size_t index)
{
    const size_t elementSize = heap->elementSize;
    void* value = malloc(elementSize);
    while(1)
    {
        int biggest = index;
        int t = biggest * 2 + 1;
        if(t < heap->currentSize && heap->cmp(heap->data + biggest * elementSize, heap->data + t * elementSize) > 0){
            biggest = t;
        }
        t++;
        if(t < heap->currentSize && heap->cmp(heap->data + biggest * elementSize, heap->data + t * elementSize) > 0){
            biggest = t;
        }
        if(biggest != index)
        {
            memcpy(value, heap->data + biggest * elementSize, elementSize);
            memcpy(heap->data + biggest * elementSize, heap->data + index * elementSize, elementSize);
            memcpy(heap->data + index * elementSize, value, elementSize);
            index = biggest;
        }
        else
        {
            break;
        }
    }
    free(value);
}