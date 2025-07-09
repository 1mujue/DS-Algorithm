#include "ADT/CursorList.h"

struct CursorNode{
    ElementType Element;
    CursorNodeP Next;
    int (*Compare)(const ElementType* a, const ElementType* b);
};

struct CursorNode CursorSpace[CURSOR_SPACE_SIZE];

void InitializeCursorSpace(void){
    for(int i = 0; i < CURSOR_SPACE_SIZE; i++){
        CursorSpace[i].Next = (i + 1) % CURSOR_SPACE_SIZE;
        CursorSpace[i].Compare = NULL;
    }
}

CursorNodeP CursorAlloc(void){
    CursorNodeP P = CursorSpace[0].Next;
    MY_RUNTIME_ASSERT(P != 0, "CursorSpace is full\n");
    CursorSpace[0].Next = CursorSpace[P].Next;
    return P;
}
void CursorFree(CursorNodeP P){
    CursorSpace[P].Next = CursorSpace[0].Next;
    CursorSpace[0].Next = P;
}

CursorHead newCursorList(int (*Compare)(const ElementType*, const ElementType*)){
    CursorHead H = (CursorHead)CursorAlloc();
    MY_RUNTIME_ASSERT(H != 0, "CursorSpace is full\n");
    MY_RUNTIME_ASSERT(Compare != NULL, "Comparison function cannot be NULL\n");
    CursorSpace[H].Next = 0;
    CursorSpace[H].Compare = Compare;
    return H;
}
CursorNodeP newCursorNode(ElementType X, CursorNodeP Next){
    CursorNodeP P = CursorAlloc();
    MY_RUNTIME_ASSERT(P != 0, "CursorSpace is full\n");
    CursorSpace[P].Element = X;
    CursorSpace[P].Next = Next;
    CursorSpace[P].Compare = NULL;
    return P;
}
CursorHead CursorMakeEmpty(CursorHead L){
    if(L == 0){
        return L;
    }
    CursorNodeP P = CursorSpace[L].Next;
    while(P != 0){
        CursorNodeP TempCell = CursorSpace[P].Next;
        CursorFree(P);
        P = TempCell;
    }
    CursorSpace[L].Next = 0;
    return L;
}
int CursorIsEmpty(CursorHead L){
    MY_RUNTIME_ASSERT(L != 0, "CursorList cannot be NULL\n");
    return CursorSpace[L].Next == 0;
}
int CursorIsLast(CursorNodeP P, CursorHead L){
    MY_RUNTIME_ASSERT(L != 0, "CursorList cannot be NULL\n");
    MY_RUNTIME_ASSERT(P != 0, "CursorNode cannot be NULL\n");
    return CursorSpace[P].Next == 0;
}
CursorNodeP CursorHeader(CursorHead L){
    return L;
}
CursorNodeP CursorFirst(CursorHead L){
    MY_RUNTIME_ASSERT(L != 0, "CursorList cannot be NULL\n");
    return CursorSpace[L].Next;
}
CursorNodeP CursorAdvance(CursorNodeP P){
    return P == 0 ? 0 : CursorSpace[P].Next;
}
ElementType CursorRetrieve(CursorNodeP P){
    MY_RUNTIME_ASSERT(P != 0, "CursorNode cannot be NULL\n");
    return CursorSpace[P].Element;
}
CursorNodeP CursorFind(ElementType X, CursorHead L){
    MY_RUNTIME_ASSERT(L != 0, "CursorList cannot be NULL\n");
    MY_RUNTIME_ASSERT(CursorSpace[L].Compare != NULL, "Comparison function cannot be NULL\n");
    CursorNodeP P = CursorSpace[L].Next;
    while(P != 0 && CursorSpace[L].Compare(&X, &CursorSpace[P].Element) != 0){
        P = CursorAdvance(P);
    }
    return P;
}
CursorNodeP CursorFindPrev(ElementType X, CursorHead L){
    MY_RUNTIME_ASSERT(L != 0, "CursorList cannot be NULL\n");
    MY_RUNTIME_ASSERT(CursorSpace[L].Compare != NULL, "Comparison function cannot be NULL\n");
    CursorNodeP P = L;
    while(P != 0 && CursorAdvance(P) != 0 && CursorSpace[L].Compare(&X, &CursorSpace[CursorAdvance(P)].Element) != 0){
        P = CursorAdvance(P);
    }
    if(P != 0 && CursorAdvance(P) != 0){
        return CursorSpace[L].Compare(&X, &CursorSpace[CursorAdvance(P)].Element) == 0 ? P : 0;
    }
}
void CursorInsert(ElementType X, CursorHead L, CursorNodeP P){
    MY_RUNTIME_ASSERT(L != 0, "CursorList cannot be NULL\n");
    MY_RUNTIME_ASSERT(P != 0, "CursorNode cannot be NULL\n");
    CursorNodeP TempCell = newCursorNode(X, CursorSpace[P].Next);
    CursorSpace[P].Next = TempCell;
}
void CursorDelete(ElementType X, CursorHead L){
    MY_RUNTIME_ASSERT(L != 0, "CursorList cannot be NULL\n");
    CursorNodeP P = CursorFindPrev(X, L);
    if(P != 0 && CursorAdvance(P) != 0){
        CursorNodeP TempCell = CursorAdvance(P);
        CursorSpace[P].Next = CursorSpace[TempCell].Next;
        CursorFree(TempCell);
    }
}
void CursorDeleteList(CursorHead L){
    CursorMakeEmpty(L);
    CursorFree(L);
}