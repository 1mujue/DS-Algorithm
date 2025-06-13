// #pragma once

// extern struct ElementType;

// // sometimes you CAN'T use pointer, so we have to
// // use CURSOR. In this case, this "pointer" is an integer
// // which represents the index of array.

// typedef int PtrToCursorNode;
// typedef PtrToCursorNode List;
// typedef PtrToCursorNode Position;

// void cursorListInit(void);
// Position cursorListAlloc(void);
// void cursorListFree(Position P);

// int cursorListIsLegalPosition(Position P);
// List cursorListMakeEmpty(List L);
// int cursorListIsEmpty(const List L);
// int cursorListIsLast(const Position P, const List L);

// Position cursorListFind(struct ElementType* elem, const List L);
// Position cursorListFindPrevious(struct ElementType* elem, const List L);

// // here, it represents insert after Position P.
// void cursorListInsert(struct ElementType* elem, List L, Position P);
// void cursorListDeleteElem(struct ElementType* elem, List L);
// void cursorListDeleteList(List L);

// Position cursorListGetHead(const List L);
// Position cursorListGetFirst(const List L);
// Position cursorListAdvance(const Position P);
// struct ElementType* cursorListRetrieve(const Position P);
