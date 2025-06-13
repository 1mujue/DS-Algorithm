#include <limits.h>
// Problem: given a BINARY tree, you need to return the maximum path sum.
// The path may start and end at any node in the tree, BUT it must contains at least one node.
// The path DON'T have to go down down the tree, and leftChild -> root -> rightChild is also a path.
// for example, if the tree is like this:
//     1
//    / \
//   2   3
// then the maximum path sum is 6, which is 2 -> 1 -> 3.
//
// the node count of the tree is in [0, 3 * 10^4], and the value of each node is in [-1000, 1000].

/**
 * Definition for a binary tree node.
 */
struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};
// this function would return the MAXIMUM path START from 'node' and go ALWAYS downside.
// However, we will update 'ans' by the MAXIMUM path that may NOT start from node and go upside.
int solute(int *ans, struct TreeNode *node)
{
    if (!node)
        return 0;
    int leftSum = solute(ans, node->left);
    int rightSum = solute(ans, node->right);
    *ans = fmax(*ans, fmax(leftSum, 0) + fmax(rightSum, 0) + node->val);
    return fmax(fmax(leftSum, 0), fmax(rightSum, 0)) + node->val;
}
int maxPathSum(struct TreeNode *root)
{
    int ans = INT_MIN;
    solute(&ans, root);
    return ans;
}