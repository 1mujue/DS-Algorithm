#include "tools/Timer.h"
#include "ADT/Heap.h"
#include <stdio.h>

int cmp(const void* e1, const void* e2)
{
    return *(int*)e1 < *(int*)e2;
}
int main(int argc, char *argv[], char* envp[]){
    int nn;
    scanf("%d", &nn);
    Heap* myHeap = newHeap(nn, sizeof(int), cmp);
    int t;
    for(int i = 0; i < nn; i++)
    {
        scanf("%d", &t);
        pushHeap(myHeap, &t);
    }
    for(int i = 0; i < nn; i++)
    {
        int* num = peekHeap(myHeap, 0);
        printf("%d ", *num);
        popHeap(myHeap);
    }
    free(myHeap);
    return 0;
}