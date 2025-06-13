// problem link: https://www.luogu.com.cn/problem/P3369
// this is THE TEMPLATE OF AVL TREE.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) > (b) ? (b) : (a))

typedef struct AVLTreeNode
{
    // basic info.
    int key;
    struct AVLTreeNode *left;
    struct AVLTreeNode *right;

    // other info.
    // size: the size of sub tree whose root node is this.
    int size;
    // count: how many times current node repeats.
    int count;
    // height: the height of current node.
    int height;

} AVLTreeNode;

AVLTreeNode *newAVLTreeNode(int value)
{
    AVLTreeNode *obj = (AVLTreeNode *)malloc(sizeof(AVLTreeNode));
    obj->key = value;
    obj->height = 1;
    obj->size = 1;
    obj->count = 1;
    obj->left = obj->right = NULL;
    return obj;
}

void delTreeNode(AVLTreeNode *root)
{
    if (root->left)
        delTreeNode(root->left);
    if (root->right)
        delTreeNode(root->right);
    free(root);
}

int getKey(AVLTreeNode *root)
{
    if (!root)
        return 0;
    return root->key;
}

int getHeight(AVLTreeNode *root)
{
    if (!root)
        return 0;
    return root->height;
}

void updateHeight(AVLTreeNode *root)
{
    if (!root)
        return;
    root->height = 1 + MAX(getHeight(root->left), getHeight(root->right));
}

int getBalance(AVLTreeNode *root)
{
    if (!root)
        return 0;
    return getHeight(root->left) - getHeight(root->right);
}

int getSize(AVLTreeNode *root)
{
    if (!root)
        return 0;
    return root->size;
}

void updateSize(AVLTreeNode *root)
{
    if (!root)
        return;
    root->size = getSize(root->left) + getSize(root->right) + root->count;
}

AVLTreeNode *LLRotate(AVLTreeNode *root)
{
    AVLTreeNode *newRoot = root->left;
    root->left = newRoot->right;
    newRoot->right = root;

    updateHeight(root);
    updateHeight(newRoot);
    updateSize(root);
    updateSize(newRoot);

    return newRoot;
}

AVLTreeNode *RRRotate(AVLTreeNode *root)
{
    AVLTreeNode *newRoot = root->right;
    root->right = newRoot->left;
    newRoot->left = root;

    updateHeight(root);
    updateHeight(newRoot);
    updateSize(root);
    updateSize(newRoot);

    return newRoot;
}

AVLTreeNode *LRRotate(AVLTreeNode *root)
{
    root->left = RRRotate(root->left);
    return LLRotate(root);
}

AVLTreeNode *RLRotate(AVLTreeNode *root)
{
    root->right = LLRotate(root->right);
    return RRRotate(root);
}

int findMin(AVLTreeNode *root)
{
    if (!root)
        return INT_MAX;
    while (root->left)
    {
        root = root->left;
    }
    return root->key;
}

AVLTreeNode *findMinNode(AVLTreeNode *root)
{
    if (!root)
        return NULL;
    while (root->left)
    {
        root = root->left;
    }
    return root;
}

int findMax(AVLTreeNode *root)
{
    if (!root)
        return INT_MIN;
    while (root->right)
    {
        root = root->right;
    }
    return root->key;
}

AVLTreeNode *findMaxNode(AVLTreeNode *root)
{
    if (!root)
        return NULL;
    while (root->right)
    {
        root = root->right;
    }
    return root;
}

AVLTreeNode *insertVal(AVLTreeNode *root, int value)
{
    if (!root)
        return newAVLTreeNode(value);
    if (value == root->key)
    {
        root->count++;
    }
    else if (value < root->key)
    {
        root->left = insertVal(root->left, value);
    }
    else
    {
        root->right = insertVal(root->right, value);
    }

    updateHeight(root);
    updateSize(root);

    int bal = getBalance(root);

    // LL
    if (bal > 1 && getBalance(root->left) >= 0)
        root = LLRotate(root);
    // LR
    else if (bal > 1 && getBalance(root->left) < 0)
        root = LRRotate(root);
    // RR
    else if (bal < -1 && getBalance(root->right) <= 0)
        root = RRRotate(root);
    // RL
    else if (bal < -1 && getBalance(root->right) > 0)
        root = RLRotate(root);

    return root;
}

// return the new ROOT after removing a value.
AVLTreeNode *removeVal(AVLTreeNode *root, int value)
{
    if (!root)
    {
        return root;
    }
    if (value < root->key)
    {
        root->left = removeVal(root->left, value);
    }
    else if (value > root->key)
    {
        root->right = removeVal(root->right, value);
    }
    else
    {
        if (root->count > 1)
        {
            root->count--;
        }
        else
        {
            if (!root->left)
            {
                AVLTreeNode *temp = root->right;
                root->right = NULL;
                delTreeNode(root);
                return temp;
            }
            else if (!root->right)
            {
                AVLTreeNode *temp = root->left;
                root->left = NULL;
                delTreeNode(root);
                return temp;
            }
            else
            {
                AVLTreeNode *successor = findMinNode(root->right);
                root->key = successor->key;
                root->count = successor->count;
                // Remember, we DIDN'T delete successor here,
                // therefore, we have to do that.
                successor->count = 1;
                root->right = removeVal(root->right, successor->key);
            }
        }
    }

    updateHeight(root);
    updateSize(root);

    int bal = getBalance(root);

    // LL
    if (bal > 1 && getBalance(root->left) >= 0)
        root = LLRotate(root);
    // LR
    else if (bal > 1 && getBalance(root->left) < 0)
        root = LRRotate(root);
    // RR
    else if (bal < -1 && getBalance(root->right) <= 0)
        root = RRRotate(root);
    // RL
    else if (bal < -1 && getBalance(root->right) > 0)
        root = RLRotate(root);

    return root;
}

void inTraversal(AVLTreeNode *root)
{
    if (!root)
        return;
    inTraversal(root->left);
    printf("%d ", root->key);
    inTraversal(root->right);
}

AVLTreeNode *findVal(AVLTreeNode *root, int value)
{
    if (!root)
        return NULL;
    if (value == root->key)
        return root;
    if (value < root->key)
        return findVal(root->left, value);
    else
        return findVal(root->right, value);
}

int findNextVal(AVLTreeNode* root, int value){
    if(!root) return INT_MAX;
    if(value == root->key){
        return findMin(root->right);
    }
    else if(value > root->key){
        return findNextVal(root->right, value);
    }
    else{
        return MIN(findNextVal(root->left, value), root->key);
    }
}

int findPrevVal(AVLTreeNode* root, int value){
    if(!root) return INT_MIN;
    if(value == root->key){
        return findMax(root->left);
    }
    else if(value < root->key){
        return findPrevVal(root->left, value);
    }
    else{
        return MAX(findPrevVal(root->right, value), root->key);
    }
}

int findRank(AVLTreeNode *root, int value)
{
    if (!root)
        return 1;
    int rank;
    if (value == root->key)
        rank = getSize(root->left) + 1;
    else if (value < root->key)
        rank = findRank(root->left, value);
    else
        rank = findRank(root->right, value) + getSize(root->left) + root->count;
    return rank;
}

int findKTH(AVLTreeNode *root, int k)
{
    if (!root)
        return -1;
    if (root->left)
    {
        if (root->left->size >= k)
            return findKTH(root->left, k);
        if (root->left->size + root->count >= k)
            return root->key;
    }
    else
    {
        if (k <= root->count)
            return root->key;
    }
    return findKTH(root->right, k - getSize(root->left) - root->count);
}

int main(){
    int n;
    scanf("%d", &n);

    AVLTreeNode* root = newAVLTreeNode(INT_MIN);

    while(n--){
        int op, x;
        scanf("%d%d", &op, &x);

        if(op == 1){
            root = insertVal(root, x);
            // inorderTraversal(root);
            // printf("\n");
        }
        else if(op == 2){
            root = removeVal(root, x);
        }
        else if(op == 3){
            // the root's val is INT_MIN, which is NOT EXIST actually.
            printf("%d\n", findRank(root, x) - 1);
        }
        else if(op == 4){
            printf("%d\n", findKTH(root, x + 1));
        }
        else if(op == 5){
            printf("%d\n", findPrevVal(root, x));
        }
        else if(op == 6){
            printf("%d\n", findNextVal(root, x));
        }
    }
    delTreeNode(root);
    return 0;
}