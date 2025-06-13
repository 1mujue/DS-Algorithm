// Problem: given a linked list, you need to swap 2 nodes pair by pair.
// That is, if the linked list is 1->2->3->4, then the ans should be
// 2->1->4->3.
// the node count is in [0, 100]
/**
 * Definition for singly-linked list.
 */
struct ListNode
{
    int val;
    struct ListNode *next;
};

// Here is the RECURSIVE way. If the current linked list(start with head)
// contains at least 2 nodes, then we have to swap them. Then, we 'move' these
// 2 nodes 'to' the ans, and do that recursively for the rest linked list.
struct ListNode *swapPairs(struct ListNode *head)
{
    if (!head || !head->next)
        return head;
    struct ListNode *first = head, *second = first->next, *next = second->next;
    second->next = first;
    first->next = swapPairs(next);
    return second;
}