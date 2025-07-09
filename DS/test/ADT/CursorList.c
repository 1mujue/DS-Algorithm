#include "ADT/CursorList.h"

// 比较函数：按整数值比较
int CursorListIntCompare(const ElementType* a, const ElementType* b) {
    return *((int*)(*a)) - *((int*)(*b));
}

// 打印链表元素（整数）
void PrintIntCursorList(CursorHead L) {
    CursorNodeP P = CursorFirst(L);
    while (P != 0) {
        int* val = (int*)CursorRetrieve(P);
        printf("%d -> ", *val);
        P = CursorAdvance(P);
    }
    printf("NULL\n");
}

// 封装为测试函数
void TestCursorList(void) {
    printf("=== CursorList Test Begin ===\n");

    InitializeCursorSpace();

    CursorHead L = newCursorList(CursorListIntCompare);

    // 准备元素（注意作用域必须保持有效）
    int a = 10, b = 20, c = 30, d = 40;

    // 插入 10, 20, 30 到头部之后（顺序为 30 -> 20 -> 10）
    CursorInsert(&a, L, L);
    CursorInsert(&b, L, L);
    CursorInsert(&c, L, L);

    printf("Initial list:\n");
    PrintIntCursorList(L);

    // 查找 20
    int key = 20;
    CursorNodeP found = CursorFind(&key, L);
    printf("Searching for %d: ", key);
    if (found)
        printf("Found %d\n", *(int*)CursorRetrieve(found));
    else
        printf("Not found\n");

    // 删除 20
    CursorDelete(&key, L);
    printf("List after deleting %d:\n", key);
    PrintIntCursorList(L);

    // 插入 40
    CursorInsert(&d, L, L);
    printf("List after inserting %d:\n", d);
    PrintIntCursorList(L);

    // 清理
    CursorDeleteList(L);
    printf("List deleted.\n");

    printf("=== CursorList Test End ===\n\n");
}