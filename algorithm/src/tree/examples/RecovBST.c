// Problem: we will provide a Binary Search Tree whose two nodes 
// are EXCHANGED. You need to recover the BST.
// The node count is in [2, 1000], the value of the node
// is in [-2^31, 2^31 - 1].
#include <limits.h>
// Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};
#define LEN 1002
// tarverse the BST in inorder and fill the val in 
// an array.
void getSeq(struct TreeNode* root, int* seq, int* ind){
    if(!root) return;
    getSeq(root->left, seq, ind);
    seq[(*ind)++] = root->val;
    getSeq(root->right, seq, ind);
}
void recov(struct TreeNode* root, int mis1, int mis2){
    if(!root) return;
    if(root->val == mis1){
        root->val = mis2;
    }
    else if(root->val == mis2){
        root->val = mis1;
    }
    recov(root->left, mis1, mis2);
    recov(root->right, mis1, mis2);
}
void recoverTree(struct TreeNode* root) {
    // It is obviously that, if you traverse a BST
    // in inorder and record the value of the node,
    // the array would be a non-decreasing array.
    // Therefore, if there exist some elements that
    // doesn't fit the requirement, then we find the error
    // nodes, and we just need to recover it.

    // step 1: get the result of inorder traverse.
    int seq[LEN];
    seq[0] = INT_MIN;
    int ind = 1;
    getSeq(root, seq, &ind);
    seq[ind++] = INT_MAX;
    // step 2: find the error node.

    // the bigger one will appear first. Let its index be
    // i, apparently, seq[i + 1] < seq[i].
    // However, since a smaller node is switched with the bigger
    // node, the smaller node would still be less then its
    // previous element. Therefore, if we find another seq[i + 1] < seq[i],
    // then the wrong node should be i + 1 instead of i.

    // mis1 records the smaller index, mis2 record the bigger index.
    int mis1 = -1, mis2 = -1;
    for(int i = 1; i < ind - 1; i++){
        if(seq[i + 1] < seq[i]){
            mis2 = i + 1;
            if(mis1 == -1) mis1 = i;
            else break;
        }
    }
    recov(root, seq[mis1], seq[mis2]);
}