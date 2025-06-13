#include "demo/RadixSort.h"
#include <stdio.h>
#include <stdlib.h>

void radixSortEntryPoint(int argc, char* argv[]){
    printf("start radix sort test...\n");

    struct Node{
        LIST_ENTRY(Node) Entry;
        int val;
    };

    typedef LIST_HEAD(head, Node) head;
    head buckets[10];
    for(int i = 0;i < 10; i++){
        LIST_HEAD_INITIALIZER(buckets + i);
    }

    int nn;
    int val;
    scanf("%d", nn);
    for(int i = 0;i < nn;i++){
        scanf("%d", &val);
        int left = val % 10;
        struct Node* node = (struct Node*)malloc(sizeof(struct Node));
        LIST_ENTRY_INIT(node, Entry);

        struct Node* p = NULL;
        LIST_FOREACH(p, buckets + left, Entry){
            if(p->val > left){
                break;
            }
        }
        if(p == NULL){
            LIST_INSERT_HEAD(buckets + left, node, Entry);
        }
        else{
            LIST_INSERT_BEFORE(p, node, Entry);
        }
    }

    int isFinished = 0;
    int curBit = 10;
    while(!isFinished){
        isFinished = 1;
        for(int i = 0;i < 10;i++){
            ;
        }
    }
    
    printf("end radix sort test...\n");
}