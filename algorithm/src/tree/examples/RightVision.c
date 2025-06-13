// Problem: given a BINARY tree, you need to return the right side view of it.
// The right side view is the set of nodes that can be seen from the right side.
// for example, if the tree is like this:
//     1
//    / \
//   2   3
//    \   \
//     5   4
// then the right side view is [1, 3, 4].

// the node count of the tree is in [0, 100].

/**
 * Definition for a binary tree node
 */
struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};
#define NODE_CNT 101


// the firs way is to use a recursive method to traverse the tree.(DFS).
// To be more exact, we just need to make sure we traverse left child first, right child second,
// and each time when we visit a node, we need to record the value of the node to the corresponding layer.
// That is, we will always visit the left child first, and then the right child,
// if we have right child, then we will UPDATE the value of the corresponding layer.
// If there is no right child, we the left child would be the rightmost node of the layer.
// The time complexity is O(n), and the space complexity is O(n).

// Attention: it doesn't matter if you use pre-order, inorder or suf-order traversal.

// ind is the index of the node in the array, and it is also the layer of the node.
// layer is the MAXIMUM layer of the tree.
void solute1(int *ans, int ind, int *layer, struct TreeNode *root)
{
    if (!root)
        return;
    ans[ind] = root->val;
    (*layer) = fmax(*layer, ind);
    solute1(ans, ind + 1, layer, root->left);
    solute1(ans, ind + 1, layer, root->right);
}
int *rightSideView1(struct TreeNode *root, int *returnSize)
{
    int t[NODE_CNT];
    int layer = -1;
    solute1(t, 0, &layer, root);
    *returnSize = layer + 1;
    int *ans = (int *)malloc(sizeof(int) * *returnSize);
    for (int i = 0; i < *returnSize; i++)
    {
        ans[i] = t[i];
    }
    return ans;
}

// the second way is BFS. This is much more simple, you only need to push the LAST NODE
// of a layer (which will be updated as BFS goes on) to the answer array.
// The time complexity is O(n), and the space complexity is O(n).
int* rightSideView2(struct TreeNode* root, int* returnSize) {
    int t[NODE_CNT];

    struct TreeNode* queue[NODE_CNT];
    int slow = 0, fast = 0;
    if(root) queue[fast++] = root;
    
    int layer = 0;
    while(slow != fast){
        int layerCnt = fast - slow;
        for(int i = 0; i < layerCnt; i++){
            struct TreeNode* node = queue[slow + i];
            if(node->left) queue[fast++] = node->left;
            if(node->right) queue[fast++] = node->right;
            if(i == layerCnt - 1) t[layer] = node->val;
        }
        slow += layerCnt;
        layer++;
    }
    int* ans = (int*)malloc(sizeof(int) * (layer));
    *returnSize = layer;
    for(int i = 0;i < layer; i++){
        ans[i] = t[i];
    }
    return ans;
}