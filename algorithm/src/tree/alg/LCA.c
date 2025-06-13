// Problem: given a binary tree, find the lowest common ancestor of the deepest leaves.
// the node count is in [1, 1000].

/**
 * Definition for a binary tree node.
 */
struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

typedef struct TInfo
{
    int depth;
    struct TreeNode *lca;
} TInfo;

// Solution: we solve it recursively. Since we want to find the DEEPEST leaves(may be more than 1) 
// and their lowest common ancestor, we need to record the depth first. Then, the deepest leaves would
// be in the left subtree or the right subtree or both. In both situation, clearly, the LCA would be 
// the CURRENT NODE. Otherwise, the answer would be the deepest node in the left subtree or the right subtree.
TInfo solute(struct TreeNode *root, int depth)
{
    TInfo ret;
    // leaf node.
    if (!root->left && !root->right)
    {
        ret.depth = depth;
        ret.lca = root;
        return ret;
    }
    TInfo left, right;
    left.depth = right.depth = 0;
    if (root->left)
        left = solute(root->left, depth + 1);
    if (root->right)
        right = solute(root->right, depth + 1);
    if (left.depth > right.depth)
        ret = left;
    else if (left.depth < right.depth)
        ret = right;
    else
    {
        ret.lca = root;
        ret.depth = left.depth;
    }
    return ret;
}

struct TreeNode *lcaDeepestLeaves(struct TreeNode *root)
{
    return solute(root, 0).lca;
}