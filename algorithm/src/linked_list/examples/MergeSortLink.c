// Problem: given two sorted singly-linked list, you need to merge
// them as one sorted linked list.
// the node count of two linked list is in [0, 50],
// the value of node is in [-100, 100]
/**
 * Definition for singly-linked list.
 */
struct ListNode
{
    int val;
    struct ListNode *next;
};
// It is quite easy to use iteration way, but here we will try
// the RECURSIVE way. Given two lists, named list1 and list2,
// if any of them is NULL, then you don't have to merge them;
// else, make a comparison of list1->val and list2->val, the smaller
// one would be the HEAD ListNode of answer, and then we can do that
// recursively!
struct ListNode *mergeTwoLists(struct ListNode *list1, struct ListNode *list2)
{
    if (!list1)
        return list2;
    if (!list2)
        return list1;
    if (list1->val < list2->val)
    {
        list1->next = mergeTwoLists(list1->next, list2);
        return list1;
    }
    else
    {
        list2->next = mergeTwoLists(list1, list2->next);
        return list2;
    }
}