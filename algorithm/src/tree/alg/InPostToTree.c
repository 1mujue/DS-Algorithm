#include <stdlib.h>

// Problem: Construct Binary Tree from Inorder and Postorder Traversal
// Given two integer arrays inorder and postorder where 
// inorder is the inorder traversal of a binary tree and 
// postorder is the postorder traversal of the same tree, 
// construct and return the binary tree.

// The length of the inorder and postorder traversals are equal, which is in [1, 3000].
// -3000 <= inorder[i], postorder[i] <= 3000, and it is guaranteed that there is no
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

// KEY: the last element of postorder is the ROOT of the tree! Therefore, we just
// need to find the root in inorder, then we can divide the inorder into two parts,
// the left part is the left subtree, and the right part is the right subtree.
// Then we can recursively build the left and right subtree.

// In realization, we can use a pointer to the last element of postorder, and pass it
// by reference to the recursive function. In this way, we can avoid the use of global
// variable.
struct TreeNode *solute(int *inorder, int inLeft, int inRight, int *postorder, int *pind)
{
    if (inLeft > inRight)
        return NULL;

    int rootVal = postorder[*pind];
    (*pind)--;
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

    ans->right = solute(inorder, mid + 1, inRight, postorder, pind);
    ans->left = solute(inorder, inLeft, mid - 1, postorder, pind);

    return ans;
}
struct TreeNode *buildTree(int *inorder, int inorderSize, int *postorder, int postorderSize)
{
    int pind = postorderSize - 1;
    return solute(inorder, 0, inorderSize - 1, postorder, &pind);
}