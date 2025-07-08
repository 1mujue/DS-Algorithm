#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

#include "Common.h"

struct ListNode;
typedef struct ListNode* ListHead;
typedef struct ListNode* ListNodeP;

ListHead newLinkedList(int (*Compare)(const ElementType*, const ElementType*));
ListNodeP newListNode(ElementType X, ListNodeP Next);
ListHead ListMakeEmpty(ListHead L);
ListNodeP ListHeader(ListHead L);
ListNodeP ListFirst(ListHead L);
int ListIsEmpty(ListHead L);
int ListIsLast(ListNodeP P, ListHead L);
ListNodeP ListAdvance(ListNodeP P);
ElementType ListRetrieve(ListNodeP P);
ListNodeP ListFind(ElementType X, ListHead L);
ListNodeP ListFindPrev(ElementType X, ListHead L);
void ListInsert(ElementType X, ListHead L, ListNodeP P);
void ListDelete(ElementType X, ListHead L);
void ListDeleteList(ListHead L);
#endif