#include "ADT/LinkedList.h"

typedef void* LinkNodePtr;
typedef LinkNodePtr ListHead;
typedef LinkNodePtr Position;

typedef struct LinkedList{
	ListHead head;
	Compare cmp;
} LinkedList;

ListHead LLMakeEmpty(LinkedList* L);
int LLIsEmpty(LinkedList* L);
int LLIsLast(Position P, LinkedList* L);
Position LLFind(LinkedList* L, const void* value);
void LLDelElement(LinkedList* L, const void* value);
Position LLFindPrev(LinkedList* L, const void* value);
void LLInsert(LinkedList* L, const void* value, Position P);
void LLDelList(LinkedList* L);
Position LLHeader(LinkedList* L);
Position LLFirst(LinkedList* L);
Position LLAdvance(Position P);
void* LLRetrive(Position P);