#ifndef _CURSOR_H
#define _CURSOR_H

#include "Common.h"

#define CURSOR_SPACE_SIZE 100007

struct CursorNode;
// caution: we use int as index to represent the cursor head and position.
typedef int CursorHead;
typedef int CursorNodeP;

void InitializeCursorSpace(void);

CursorNodeP CursorAlloc(void);
void CursorFree(CursorNodeP P);

CursorHead newCursorList(int (*Compare)(const ElementType*, const ElementType*));
CursorNodeP newCursorNode(ElementType X, CursorNodeP Next);
CursorHead CursorMakeEmpty(CursorHead L);
CursorNodeP CursorHeader(CursorHead L);
CursorNodeP CursorFirst(CursorHead L);
int CursorIsEmpty(CursorHead L);
int CursorIsLast(CursorNodeP P, CursorHead L);
CursorNodeP CursorAdvance(CursorNodeP P);
ElementType CursorRetrieve(CursorNodeP P);
CursorNodeP CursorFind(ElementType X, CursorHead L);
CursorNodeP CursorFindPrev(ElementType X, CursorHead L);
void CursorInsert(ElementType X, CursorHead L, CursorNodeP P);
void CursorDelete(ElementType X, CursorHead L);
void CursorDeleteList(CursorHead L);

#endif 