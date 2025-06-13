#pragma once
#include <stdlib.h>

typedef struct Heap{
    size_t elementSize;
    size_t currentSize;
    size_t capacity;
    void* data;
    int (*cmp)(const void* e1, const void* e2);
} Heap;


extern int cmp(const void* a, const void* b);

Heap* newHeap(size_t capacity, size_t elementSize, int (*cmp)(const void* a, const void* b));
void freeHeap(Heap* heap);

void pushHeap(struct Heap* heap, const void* value);
void popHeap(struct Heap* heap);
void* peekHeap(struct Heap* heap, size_t index);
void upHeap(struct Heap* heap, size_t index);
void downHeap(struct Heap* heap, size_t index);