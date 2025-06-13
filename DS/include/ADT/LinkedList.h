#pragma once
#include "tools/Number.h"

// first is linked list.
// usually, linked list has a HEADER or DUMMY NODE, which
// can solve the different behavior when trying to insert or delete
// the first node.

// the first kind is simple list.
// #define LIST_HEAD(name, type)                                                   \
//     struct name{                                                                \
//         struct type* lh_first;                                                  \
//     }

// #define LIST_HEAD_INITIALIZER(head)                                             \
// 	do         																	\
//     { (head)->lh_first = NULL; } while(0)

// /*
//  * Use this inside a structure "LIST_ENTRY(type) field" to use
//  * x as the list piece.
//  * *le_prev is the next elem of the elem which is the previous elem of elem.
//  */

// #define LIST_ENTRY(type)                                                        \
//     struct {                                                                    \
//         struct type* le_next;                                                   \
//         struct type** le_prev;                                                  \
//     }

// #define LIST_ENTRY_INIT(entry, field)													\
// do{																				\
// 	entry->field.le_next = NULL;														\
// 	entry->field.le_prev = NULL;														\
// }while(0)
// #define LSIT_EMPTY(head) ((head)->lh_first == NULL) 

// #define LIST_FIRST(head) ((head)->lh_first)

// // caution: the elem here is NOT a node of linked list, instead, it is a struct
// // which CONTAINS the node of linked list(field) !!
// #define LIST_NEXT(elem, field)    ((elem)->field.le_next)

// #define LIST_FOREACH(var, head, field)                                          \
//     for ((var) = LIST_FIRST((head)); (var); (var) = LIST_NEXT((var), field))    \

// #define LIST_INIT(head)                                                         \
//     do{                                                                         \
//         LIST_FIRST((head)) = NULL;                                              \
//     }while(0)

// #define LIST_REMOVE(elem, field)                                                \
//     do{                                                                         \
//         if(LIST_NEXT((elem), field) != NULL){                                   \
//             LIST_NEXT((elem), field)->field.le_prev = (elem)->field.le_prev;    \
//         }                                                                       \
//         *(elem)->field.le_prev = LIST_NEXT((elem) field);                       \
//     }while(0)                                                                   \

// /*
//  * Insert the element 'elm' *after* 'listelm' which is already in the list. The 'field'
//  * name is the link element as above.
//  */
// #define LIST_INSERT_AFTER(listelem, elem, field)                                    \
// 	do{											                                    \
// 		LIST_NEXT((elem),field) = LIST_NEXT((listelem),field);				        \
// 		if(LIST_NEXT((listelem),field) != NULL){						            \
// 			LIST_NEXT((listelem),field)->field.le_prev = &LIST_NEXT((elem),field);  \
// 		}										                                    \
// 		LIST_NEXT((listelem),field) = (elem);						                \
// 		(elem)->field.le_prev = &LIST_NEXT((listelem),field);				        \
// 	}while(0)

// /*
//  * Insert the element "elm" *before* the element "listelm" which is
//  * already in the list.  The "field" name is the link element
//  * as above.
//  */
// #define LIST_INSERT_BEFORE(listelem, elem, field)                               \
// 	do {                                                                        \
// 		(elem)->field.le_prev = (listelem)->field.le_prev;                      \
// 		LIST_NEXT((elem), field) = (listelem);                                  \
// 		*(listelem)->field.le_prev = (elem);                                    \
// 		(listelem)->field.le_prev = &LIST_NEXT((elem), field);                  \
// 	} while (0)

// /*
//  * Insert the element "elm" at the head of the list named "head".
//  * The "field" name is the link element as above.
//  */
// #define LIST_INSERT_HEAD(head, elem, field)                                     \
// 	do {                                                                        \
// 		if ((LIST_NEXT((elem), field) = LIST_FIRST((head))) != NULL)            \
// 			LIST_FIRST((head))->field.le_prev = &LIST_NEXT((elem), field);      \
// 		LIST_FIRST((head)) = (elem);                                            \
// 		(elem)->field.le_prev = &LIST_FIRST((head));                            \
// 	} while (0)

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


