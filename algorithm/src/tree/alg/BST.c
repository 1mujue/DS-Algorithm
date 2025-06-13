#include <stdio.h>
#include <limits.h>
#include <malloc.h>
#include <math.h>
#include <string.h>

#define PRE_ERROR (INT_MIN + 1)
#define SUF_ERROR (INT_MAX)
#define RANK_ERROR (INT_MIN)

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define VOL 10001

typedef struct BSTNode
{
    int val;
    int cnt;
    int treeSize;
    int prev, left, right;
} BSTNode;

BSTNode nodes[VOL];
int nodeCnt;

void newBSTNode(int val, int cnt, int treeSize, int prev, int left, int right)
{
    nodeCnt++;
    nodes[nodeCnt].val = val;
    nodes[nodeCnt].cnt = cnt;
    nodes[nodeCnt].treeSize = treeSize;
    nodes[nodeCnt].prev = prev;
    nodes[nodeCnt].left = left;
    nodes[nodeCnt].right = right;
}

void insert(int val, int curNodeInd)
{
    BSTNode *curNodes = &nodes[curNodeInd];
    if (val == curNodes->val)
    {
        curNodes->cnt++;
        curNodes->treeSize++;
        return;
    }
    if (val < curNodes->val)
    {
        // treeSize ONLY records the left part.
        curNodes->treeSize++;
        if (curNodes->left)
        {
            insert(val, curNodes->left);
        }
        else
        {
            newBSTNode(val, 1, 1, curNodeInd, 0, 0);
            curNodes->left = nodeCnt;
        }
    }
    else
    {
        if (curNodes->right)
        {
            insert(val, curNodes->right);
        }
        else
        {
            newBSTNode(val, 1, 1, curNodeInd, 0, 0);
            curNodes->right = nodeCnt;
        }
    }
}

int findPre(int val, int curNodeInd)
{
    BSTNode *curNodes = &nodes[curNodeInd];
    int ans = PRE_ERROR;
    if (curNodes->val < val)
    {
        ans = curNodes->val;
        if (curNodes->right)
        {
            int ret = findPre(val, curNodes->right);
            if (ret != PRE_ERROR)
                ans = ret;
        }
    }
    else
    {
        if (curNodes->left)
        {
            int ret = findPre(val, curNodes->left);
            if (ret != PRE_ERROR)
                ans = ret;
        }
    }
    return ans;
}

int findSuf(int val, int curNodeInd)
{
    BSTNode *curNodes = &nodes[curNodeInd];
    int ans = SUF_ERROR;
    if (curNodes->val > val)
    {
        ans = curNodes->val;
        if (curNodes->left)
        {
            int ret = findSuf(val, curNodes->left);
            if (ret != SUF_ERROR)
                ans = ret;
        }
    }
    else
    {
        if (curNodes->right)
        {
            int ret = findSuf(val, curNodes->right);
            if (ret != SUF_ERROR)
                ans = ret;
        }
    }
    return ans;
}

int findRank(int val, int curNodeInd)
{
    if (!curNodeInd)
        return 0;

    BSTNode *curNodes = &nodes[curNodeInd];
    if (curNodes->val == val)
    {
        return curNodes->treeSize - curNodes->cnt;
    }
    else if (curNodes->val < val)
    {
        return findRank(val, curNodes->right) + curNodes->treeSize;
    }
    else
    {
        return findRank(val, curNodes->left);
    }
}

int queryRank(int rank, int curNodeInd, int curRank)
{
    if (!curNodeInd)
        return RANK_ERROR;

    BSTNode *curNodes = &nodes[curNodeInd];
    int delta = curNodes->treeSize - curNodes->cnt;
    curRank += delta;
    if (curRank == rank)
    {
        return curNodes->val;
    }
    else if (curRank > rank)
    {
        return queryRank(rank, curNodes->left, curRank - delta);
    }
    else
    {
        return queryRank(rank, curNodes->right, curRank + curNodes->cnt);
    }
}