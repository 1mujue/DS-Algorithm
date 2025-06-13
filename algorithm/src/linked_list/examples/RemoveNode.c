#include <stdlib.h>
// Problem: given a linked list and a val, you should remove those 
// nodes whose value equals to val.
// the node count is in [0, 10^4]
/**
 * Definition for singly-linked list.
 */
struct ListNode
{
    int val;
    struct ListNode *next;
};

// The iteration way is quite easy, but here we will introduce 
// the RECURSIVE way. For a ListNode* head, if its value equals to 
// val, then we need to remove it; since it is the head, after removing
// it, the next node of it becomes the new head.
// Otherwise, we will not remove the head, but the rest of the linked list
// might still contains nodes whose value equals to val, so we have to
// do that recursively.
struct ListNode *removeElements(struct ListNode *head, int val)
{
    if (!head)
        return NULL;
    if (head->val == val)
    {
        return removeElements(head->next, val);
    }
    else
    {
        head->next = removeElements(head->next, val);
    }
    return head;
}