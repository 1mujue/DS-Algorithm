// This is the template of SEGMENT TREE!!

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <limits.h>

// the default value can change.
#define LAZY_DEFAULT INT_MAX

typedef struct SegmentTreeNode{
    int data;
    int lazy;
} STNode;

inline int getLeftChild(int root){
    // 2 * root + 1
    return ((root << 1) | 1);
}

inline int getRightChild(int root){
    // 2 * root + 2
    return ((root + 1) << 1);
}

// NOTE: lazyUpdate and pushUp is NOT invariable. 

// KEY: if you want to update a RANGE of element and want to keep the time complexity
// in O(logn), you have to use LAZY UPDATE. Otherwise, the time complexity would be O(nlogn).
void lazyUpdate(STNode* segmentTree, int root, int left, int right, int value){
    segmentTree[root].lazy = value;
    segmentTree[root].data = value * (right - left + 1);
}

// the pushUp operation must satisfy Commutative law. For example, sum, max, min,
// xor, multiple are ALL qualified.
int pushUp(int leftVal, int rightVal){
    return leftVal + rightVal;
}

// the pushDown operation is Derivative of LAZY UPDATE.
void pushDown(STNode* segmentTree, int root, int left, int right){
    int mid = left + ((right - left) >> 1);
    int leftChild = getLeftChild(root), rightChild = getRightChild(root);

    int lazyValue = segmentTree[root].lazy;
    // caution: the push down operation will ONLY happen if the 
    // lazy is not LAZY_DEFAULT. 
    if(lazyValue == LAZY_DEFAULT) return;

    lazyUpdate(segmentTree, leftChild, left, mid, lazyValue);
    lazyUpdate(segmentTree, rightChild, mid + 1, right, lazyValue);

    segmentTree[root].lazy = LAZY_DEFAULT;
}

void build(const int* data, STNode* segmentTree, int root, int left, int right){
    segmentTree[root].lazy = LAZY_DEFAULT;

    if(left == right){
        segmentTree[root].data = data[left];
        return;
    }

    int mid = left + ((right - left) >> 1);
    int leftChild = getLeftChild(root), rightChild = getRightChild(root);

    build(data, segmentTree, leftChild, left, mid);
    build(data, segmentTree, rightChild, mid + 1, right);

    segmentTree[root].data = pushUp(segmentTree[leftChild].data, segmentTree[rightChild].data);
}

int query(STNode* segmentTree, int root, int left, int right, int queryLeft, int queryRight){
    // there is NO intersection between query area and the node's area.
    if(queryLeft > right || queryRight < left){
        return 0;
    }
    if(queryLeft <= left && queryRight >= right){
        return segmentTree[root].data;
    }
    int mid = left + ((right - left) >> 1);

    // caution: since we are using LAZY UPDATE, if you want to query, you MUST update forcely,
    // otherwise the answer is undefined. This is similar with CACHE and MEMORY.
    pushDown(segmentTree, root, left, right);

    int leftChild = 2 * root + 1, rightChild = 2 * root + 2;
    int leftValue = query(segmentTree, leftChild, left, mid, queryLeft, queryRight);
    int rightValue = query(segmentTree, rightChild, mid + 1, right, queryLeft, queryRight);

    return pushUp(leftValue, rightValue);
}

// update one node is a SPECIAL situation of update a range of node
// when updateLeft == updateRight. Therefore, we will focus on range update.
void updateRange(STNode* segmentTree, int root, int left, int right, int updateLeft, int updateRight, int value){
    if(updateLeft > right || updateRight < left){
        return;
    }
    if(updateLeft <= left && updateRight >= right){
        lazyUpdate(segmentTree, root, left, right, value);
        return;
    }
    pushDown(segmentTree, root, left, right);

    int mid = left + ((right - left) >> 1);
    int leftChild = getLeftChild(root), rightChild = getRightChild(root);

    updateRange(segmentTree, leftChild, left, mid, updateLeft, updateRight, value);
    updateRange(segmentTree, rightChild, mid + 1, right, updateLeft, updateRight, value);

    segmentTree[root].data = pushUp(segmentTree[leftChild].data, segmentTree[rightChild].data);
}