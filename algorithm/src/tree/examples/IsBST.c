#include <stdbool.h>
#include <limits.h>
// Problem: given a BINARY tree, you need to determine if it is a valid binary search tree (BST).
// A valid BST is defined as follows:
// 1. The left subtree of a node contains only nodes with keys less than the node's key.
// 2. The right subtree of a node contains only nodes with keys greater than the node's key.
// 3. Both the left and right subtrees must also be binary search trees.

// the node count is in [1, 10^4], and the value of each node is in [-2^31, 2^31 - 1].
/**
 * Definition for a binary tree node.
 */
struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// since the value of node is in [-2^31, 2^31 - 1], we can use long long to store the value.
// That is, we need to initialize min as LLONG_MAX and max as LLONG_MIN. If we initialize them
// with INT_MAX and INT_MIN, then the test case [-2147483648] would fail.
typedef struct
{
    long long min;
    long long max;
    bool isBST;
} BSTRet;
BSTRet solute(struct TreeNode *root)
{
    BSTRet ret;
    ret.min = LLONG_MAX;
    ret.max = LLONG_MIN;
    ret.isBST = true;
    if (!root)
        return ret;

    BSTRet LRet = solute(root->left);
    BSTRet RRet = solute(root->right);

    ret.min = fmin(fmin(LRet.min, RRet.min), root->val);
    ret.max = fmax(fmax(LRet.max, RRet.max), root->val);
    // Only if left and right subtrees are BST and the max of left subtree is less than root->val
    // and the min of right subtree is greater than root->val, then the tree is a BST.
    ret.isBST = LRet.isBST && RRet.isBST && LRet.max < root->val && RRet.min > root->val;
    return ret;
}
bool isValidBST(struct TreeNode *root)
{
    BSTRet ret = solute(root);
    return ret.isBST;
}