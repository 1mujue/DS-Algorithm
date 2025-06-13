#include <stdlib.h>
// Problem: given a SORTED array, you need to convert it to a height BALANCED BST.
// the length of array is in [1, 10^4], and the value of each element is in [-10^4, 10^4].
/**
 * Definition for a binary tree node.
 */
struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// The key is about to find the root of the tree(To make sure it is balanced).
// There is one important thing to know: when you do inorder traversal of a BST, the result
// is a sorted array. 

// Therefore, we can use the middle element of the array as the root of the tree,
// and left part of the array would be the left child tree, and the right part of the array would 
// be the right child tree. Since we take the middle element as the root, the left child tree and right
// child tree would be balanced. Therefore, the tree would be balanced.
// Then we can recursively build the left child and right child of the root.
struct TreeNode *solute(int *nums, int left, int right)
{
    if (left > right)
        return NULL;
    int mid = (left + right) / 2;
    struct TreeNode *ans = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    ans->val = nums[mid];
    ans->left = solute(nums, left, mid - 1);
    ans->right = solute(nums, mid + 1, right);
    return ans;
}
struct TreeNode *sortedArrayToBST(int *nums, int numsSize)
{
    return solute(nums, 0, numsSize - 1);
}