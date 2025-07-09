#include "ADT/LinkedList.h"

// 比较函数：按整数值比较
int LinkedListIntCompare(const ElementType* a, const ElementType* b) {
    return *((int*)(*a)) - *((int*)(*b));
}

// 打印 int 元素（LinkedList 专用）
void Linked_PrintElement(ElementType x) {
    printf("%d ", *(int*)x);
}

// 打印整个链表
void Linked_PrintList(ListHead L) {
    ListNodeP p = ListFirst(L);
    while (p != NULL) {
        Linked_PrintElement(ListRetrieve(p));
        p = ListAdvance(p);
    }
    printf("\n");
}

// 释放整型元素（仅在 DeleteList 中可用）
void Linked_FreeListElements(ListHead L) {
    ListNodeP p = ListFirst(L);
    while (p != NULL) {
        free(ListRetrieve(p));  // 释放 int*
        p = ListAdvance(p);
    }
}

// 主测试函数
void TestLinkedList(void) {
    printf("=== LinkedList Test Begin ===\n");

    ListHead L = newLinkedList(LinkedListIntCompare);
    printf("List is empty: %d (Expect 1)\n", ListIsEmpty(L));

    // 插入元素（头插法）
    for (int i = 1; i <= 5; ++i) {
        int* p = malloc(sizeof(int));
        *p = i * 10;
        ListInsert(p, L, ListHeader(L));
    }

    printf("List after inserts: ");
    Linked_PrintList(L); // 50 40 30 20 10

    // 查找元素
    int val = 30;
    ElementType key = &val;
    ListNodeP found = ListFind(key, L);
    printf("Searching for 30: ");
    if (found != NULL)
        Linked_PrintElement(ListRetrieve(found));
    else
        printf("Not found");
    printf("\n");

    // 删除元素
    ListDelete(key, L);
    printf("List after deleting 30: ");
    Linked_PrintList(L); // 50 40 20 10

    // 删除头部
    val = 50;
    ListDelete(&val, L);
    printf("List after deleting 50 (head): ");
    Linked_PrintList(L); // 40 20 10

    // 删除不存在元素
    val = 999;
    ListDelete(&val, L); // no effect
    printf("List after deleting non-existent 999: ");
    Linked_PrintList(L);

    // 清空链表（保留头节点）
    Linked_FreeListElements(L);  // 先释放存储的 int*
    ListMakeEmpty(L);           // 再清空结构
    printf("List after make empty: ");
    Linked_PrintList(L);

    // 再次插入测试
    int* a = malloc(sizeof(int)); *a = 100;
    int* b = malloc(sizeof(int)); *b = 200;
    ListInsert(a, L, ListHeader(L));
    ListInsert(b, L, ListHeader(L));
    printf("List after reinserting: ");
    Linked_PrintList(L);  // 200 100

    // 删除链表本体（结构 + 元素）
    Linked_FreeListElements(L);
    ListDeleteList(L);
    printf("List deleted.\n");

    printf("=== LinkedList Test End ===\n\n");
}