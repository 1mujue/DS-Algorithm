// #include "ADT/Cursor.h"
// #include "tools/Error.h"

// #define CURSOR_SPACE_SIZE 1007

// extern struct ElementType;
// // {
// //     int val;
// // };
// struct Node
// {
//     struct ElementType* element;
//     Position next;
// };

// struct Node cursorSpace[CURSOR_SPACE_SIZE];

// // this function is for comparation between two struct ElementType.
// // since we are using C, we can't write `boolean operator==(const struct ElementType&)`
// // in C++.
// int elementCompare(const void *e1, const void *e2);
// // {
// //     struct ElementType *re1 = (struct ElementType *)e1;
// //     struct ElementType *re2 = (struct ElementType *)e2;
// //     if (re1->val < re2->val)
// //         return -1;
// //     else if (re1->val > re2->val)
// //         return 1;
// //     else
// //         return 0;
// // }

// // caution: cursorSpace[0] will NOT be used, and next == 0
// // is something like next = NULL.
// void cursorListInit(void)
// {
//     for (int i = 0; i < CURSOR_SPACE_SIZE; i++)
//     {
//         if (i != CURSOR_SPACE_SIZE - 1)
//             cursorSpace[i].next = i + 1;
//         else
//             cursorSpace[i].next = 0;
//     }
// }
// // caution: cursorSpace is like a FREE LIST which contains ALL
// // available nodes now, therefore, if you want to alloc a node,
// // then the cursorSpace[0].next would be the node's index,
// // and it will be removed (logically)
// Position cursorListAlloc(void)
// {
//     Position P;
//     // delete from cursor space.
//     P = cursorSpace[0].next;
//     cursorSpace[0].next = cursorSpace[P].next;
//     return P;
// }
// void cursorListFree(Position P)
// {
//     // add into cursor space.
//     cursorSpace[P].next = cursorSpace[0].next;
//     cursorSpace[0].next = P;
// }

// int cursorListIsLegalPosition(Position P)
// {
//     return P != 0;
// }

// List cursorListMakeEmpty(List L)
// {
//     cursorSpace[L].next = 0;
// }
// int cursorListIsEmpty(const List L)
// {
//     return cursorSpace[L].next = 0;
// }
// int cursorListIsLast(const Position P, const List L)
// {
//     return cursorSpace[P].next = 0;
// }
// Position cursorListFind(struct ElementType* elem, const List L)
// {
//     Position P = cursorSpace[L].next;
//     while(!elementCompare(elem, &cursorSpace[P].element) && !cursorListIsLast(P, L))
//         P = cursorSpace[P].next;
//     return P;
// }
// Position cursorListFindPrevious(struct ElementType elem, const List L)
// {
//     Position P = L;
//     Position nxt = cursorSpace[P].next;
//     while(!elementCompare(&elem, &cursorSpace[nxt].element) && !cursorListIsLast(P, L)){
//         P = cursorSpace[P].next;
//         nxt = cursorSpace[P].next;
//     }
//     return P;
// }
// void cursorListInsert(struct ElementType elem, List L, Position P)
// {
//     Position cell = cursorListAlloc();
//     if(!cursorListIsLegalPosition(cell))
//         fatalError("Error: cursor list out of space\n");
//     cursorSpace[cell].element = elem;
//     cursorSpace[cell].next = cursorSpace[P].next;
//     cursorSpace[P].next = cell;
// }
// void cursorListDeleteElem(struct ElementType elem, List L)
// {
//     Position prev, temp;
//     prev = cursorListFindPrevious(elem, L);
//     if(!cursorListIsLast(prev, L))
//     {
//         temp = cursorSpace[prev].next;
//         cursorSpace[prev].next = cursorSpace[temp].next;
//         cursorListFree(temp);
//     }
// }
// void cursorListDeleteList(List L)
// {
//     Position dele, temp;
//     dele = L;
//     temp = cursorSpace[dele].next;  
//     while(!cursorListIsLast(dele, L))
//     {
//         cursorListFree(dele);
//         dele = temp;
//         temp = cursorSpace[dele].next;
//     }
// }
// Position cursorListGetHead(const List L)
// {
//     return L;
// }
// Position cursorListGetFirst(const List L)
// {
//     return cursorSpace[L].next;
// }
// Position cursorListAdvance(const Position P)
// {

// }
// struct ElementType cursorListRetrieve(const Position P)
// {
//     if(!cursorListIsLegalPosition(P))
//         fatalError("Error: illegal cursor list position\n");
//     return cursorSpace[P].element;
// }
