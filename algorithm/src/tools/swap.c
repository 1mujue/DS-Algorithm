#include "include/tools/swap.h"

void swapInt(int* e1, int *e2){
    int tmp = *e1;
    *e1 = *e2;
    *e2 = tmp;
    // if e1 not equals to e2, you can use:
    // *e1 = *e1 ^ *e2;
    // *e2 = *e1 ^ *e2;
    // *e1 = *e1 ^ *e2;
}