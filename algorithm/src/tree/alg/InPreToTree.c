#include <stdlib.h>
// Problem: Construct Binary Tree from Preorder and Inorder Traversal
// Given two integer arrays preorder and inorder where
// preorder is the preorder traversal of a binary tree and
// inorder is the inorder traversal of the same tree,
// construct and return the binary tree.

// The length of the inorder and preorder traversals are equal, which is in [1, 3000].
// -3000 <= inorder[i], preorder[i] <= 3000, and it is guaranteed that there is no
// duplicate value in either traversal.
/**
 * Definition for a binary tree node.
 */
struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// KEY: the first element of preorder is the ROOT of the tree! Therefore, we just
// need to find the root in inorder, then we can divide the inorder into two parts,
// the left part is the left subtree, and the right part is the right subtree.
// Then we can recursively build the left and right subtree.

// In realization, we can use a pointer to the first element of prerder, and pass it
// by reference to the recursive function. In this way, we can avoid the use of global
// variable.
struct TreeNode *solute(int *preorder, int *pind, int *inorder, int inLeft, int inRight)
{
    if (inLeft > inRight)
        return NULL;

    int rootVal = preorder[*pind];
    (*pind)++;
    struct TreeNode *ans = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    ans->val = rootVal;

    int mid;
    for (int i = inLeft; i <= inRight; i++)
    {
        if (inorder[i] == rootVal)
        {
            mid = i;
            break;
        }
    }

    ans->left = solute(preorder, pind, inorder, inLeft, mid - 1);
    ans->right = solute(preorder, pind, inorder, mid + 1, inRight);

    return ans;
}
struct TreeNode *buildTree(int *preorder, int preorderSize, int *inorder, int inorderSize)
{
    int pind = 0;
    return solute(preorder, &pind, inorder, 0, inorderSize - 1);
}