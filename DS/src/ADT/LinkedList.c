#include "ADT/LinkedList.h"
#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    ElementType Element;
    ListNodeP Next;
    int (*Compare) (const ElementType*, const ElementType*) ;
};


ListHead newLinkedList(int (*Compare)(const ElementType*, const ElementType*)){
    printf("Creating a new LinkedList...\n");
    ListHead H = (ListHead)malloc(sizeof(struct ListNode));
    MY_RUNTIME_ASSERT(H != NULL, "Memory allocation failed for LinkedList\n");
    MY_RUNTIME_ASSERT(Compare != NULL, "Comparison function cannot be NULL\n");
    H->Next = NULL;
    H->Compare = Compare;
    return H;
}

ListNodeP newListNode(ElementType X, ListNodeP Next){
    ListNodeP P = (ListNodeP)malloc(sizeof(struct ListNode));
    MY_RUNTIME_ASSERT(P != NULL, "Memory allocation failed for ListNode\n");
    P->Element = X;
    P->Next = Next;
    P->Compare = NULL;
    return P;
}

ListHead ListMakeEmpty(ListHead L){
    if(L == NULL){
        return L;
    }
    ListNodeP P = L->Next;
    while(P != NULL){
        ListNodeP TempCell = P->Next;
        free(P);
        P = TempCell;
    }
    L->Next = NULL;
    return L;
}
int ListIsEmpty(ListHead L){
    MY_RUNTIME_ASSERT(L != NULL, "LinkedList cannot be NULL\n");
    return L->Next == NULL;
}
int ListIsLast(ListNodeP P, ListHead L){
    MY_RUNTIME_ASSERT(L != NULL, "LinkedList cannot be NULL\n");
    MY_RUNTIME_ASSERT(P != NULL, "ListNode cannot be NULL\n");
    return P->Next == NULL;
}
ListNodeP ListHeader(ListHead L){
    return L;
}
ListNodeP ListFirst(ListHead L){
    MY_RUNTIME_ASSERT(L != NULL, "LinkedList cannot be NULL\n");
    return L->Next;
}
ListNodeP ListAdvance(ListNodeP P){
    return P != NULL ? P->Next : NULL;
}
ElementType ListRetrieve(ListNodeP P){
    MY_RUNTIME_ASSERT(P != NULL, "ListNode cannot be NULL\n");
    return P->Element;
}
ListNodeP ListFind(ElementType X, ListHead L){
    MY_RUNTIME_ASSERT(L != NULL, "LinkedList cannot be NULL");
    MY_RUNTIME_ASSERT(L->Compare != NULL, "Comparison function cannot be NULL");
    ListNodeP P = L->Next;
    while(P != NULL && L->Compare(&X, &P->Element) != 0){
        P = ListAdvance(P);
    }
    if(P != NULL && L->Compare(&X, &P->Element) != 0) P = NULL;
    return P;
}
ListNodeP ListFindPrev(ElementType X, ListHead L){
    MY_RUNTIME_ASSERT(L != NULL, "LinkedList cannot be NULL");
    MY_RUNTIME_ASSERT(L->Compare != NULL, "Comparison function cannot be NULL");
    ListNodeP P = L;
    while(P != NULL && ListAdvance(P) != NULL && L->Compare(&ListAdvance(P)->Element, &X) != 0){
        P = ListAdvance(P);
    }
    if(P != NULL && ListAdvance(P) != NULL){
        L->Compare(&ListAdvance(P)->Element, &X) != 0 ? P = NULL : P;
    }
    return P;
}
void ListInsert(ElementType X, ListHead L, ListNodeP P){
    MY_RUNTIME_ASSERT(L != NULL, "LinkedList cannot be NULL");
    MY_RUNTIME_ASSERT(P != NULL, "ListNode cannot be NULL");
    ListNodeP TempCell = newListNode(X, P->Next);
    P->Next = TempCell;
}
void ListDelete(ElementType X, ListHead L){
    MY_RUNTIME_ASSERT(L != NULL, "LinkedList cannot be NULL");
    ListNodeP P = ListFindPrev(X, L);
    if(P != NULL && ListAdvance(P) != NULL){
        ListNodeP TempCell = ListAdvance(P);
        P->Next = ListAdvance(TempCell);
        free(TempCell);
    }
}

void ListDeleteList(ListHead L){
    ListMakeEmpty(L);
    free(L);
}