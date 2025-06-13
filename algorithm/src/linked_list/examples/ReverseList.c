// Problem: given a linked list, left and right, you should reverse the 
// nodes in [left, right]. Note that, left and right begin from 1 and end in
// n(the length of the linked list.)
// the node count is in [1, 500]
/**
 * Definition for singly-linked list.
 */
struct ListNode
{
    int val;
    struct ListNode *next;
};

struct ListNode *reverseBetween(struct ListNode *head, int left, int right)
{
    // use dummy node to prevent special operation when we need to reverse
    // the head(left == 1).
    struct ListNode dummy;
    dummy.next = head;

    struct ListNode *prev = &dummy, *curr = head;

    // you need to find where is left th node and the previous node of it.
    for (int i = 0; i < left - 1; i++)
    {
        prev = curr;
        curr = curr->next;
    }
    // curr now is the left.

    // 'start' here is the last node before reversion region. We record it since we need
    // to set 'start->next' equals to the "head node" after reversion.
    // 'end' here is set with 'curr', since after reversion, it will be the LAST node.
    struct ListNode *start = prev, *end = curr;

    for (int i = left; i <= right; i++)
    {
        struct ListNode *next = curr->next;
        // do reversion.
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    // now the 'prev' is the LAST node of reversion region, and 
    // the 'curr' is the FIRST node after reversion region.
    start->next = prev;
    end->next = curr;

    return dummy.next;
}