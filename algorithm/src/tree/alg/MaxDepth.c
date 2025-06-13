// Problem: get the max depth of a binary tree. The max depth is the number of nodes 
// along the longest path from the root node down to the farthest leaf node.
/**
 * Definition for a binary tree node.
 */
struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};
// we can do it recursively. If the root is NULL, then we return 0 (no depth).
// Else, the maxDepth of the root is the max of the maxDepth of left child and right child plus 1.
// The time complexity is O(n), and the space complexity is O(n).
int maxDepth(struct TreeNode *root)
{
    if (!root)
        return 0;
    int LDepth = maxDepth(root->left);
    int RDepth = maxDepth(root->right);
    return fmax(LDepth, RDepth) + 1;
}