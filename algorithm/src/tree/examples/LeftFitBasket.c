// problem link: https://leetcode.cn/problems/fruits-into-baskets-iii/
#include <limits.h>
#define VOL 100007

// This problem gives another sight into Segment Tree.
// We can take fruits as a QUERY sequence, and baskets as a Segment Tree.
// For each query, we need to find the MOST LEFT basket that can hold the fruit.
// Therefore, we can use a Segment Tree to maintain the MAX VALUE of a range.
// if sgt[root] < val, then there is not basket in this range that can hold the fruit;
// if sgt[root] >= val, then at LEAST sgt[lc] >= val or sgt[rc] >= val.
// If sgt[lc] >= val, we can query the left; otherwise, we query the right.
// NOTE: the query here returns the MOST LEFT INDEX of fit basket, which is 
// quite different from the common Segment Tree query that returns the sum or max value.

int sgt[4 * VOL];
inline int getLC(int root){
    return root * 2 + 1;
}
inline int getRC(int root){
    return root * 2 + 2;
}
void build(int root, int l, int r, int* arr){
    if(l == r){
        sgt[root] = arr[l];
        return;
    }
    int lc = getLC(root), rc = getRC(root);
    int m = (l + r) / 2;
    build(lc, l, m, arr);
    build(rc, m + 1, r, arr);
    sgt[root] = fmax(sgt[lc], sgt[rc]);
}
void update(int root, int l, int r, int ind, int val){
    if(l > ind || r < ind) return;
    if(l == ind && r == ind){
        sgt[root] = val;
        return;
    }
    int lc = getLC(root), rc = getRC(root);
    int m = (l + r) / 2;
    if(ind >= l && ind <= m){
        update(lc, l, m, ind, val);
    }
    else{
        update(rc, m + 1, r, ind, val);
    }
    sgt[root] = fmax(sgt[lc], sgt[rc]);
}

int query(int root, int l, int r, int val){
    if(sgt[root] < val) return -1;
    if(l == r){
        if(sgt[root] >= val){
            return l;
        }
        else{
            return -1;
        }
    }
    int lc = getLC(root), rc = getRC(root);
    int m = (l + r) / 2;
    if(sgt[lc] >= val){
        return query(lc, l, m, val);
    }
    if(sgt[rc] >= val){
        return query(rc, m + 1, r, val);
    }
    return -1;
}
int numOfUnplacedFruits(int* fruits, int fruitsSize, int* baskets, int basketsSize) {
    int n = fruitsSize;
    int ans = 0;
    build(0, 0, n - 1, baskets);
    for(int i = 0; i < n; i++){
        int ind = query(0, 0, n - 1, fruits[i]);
        ans += ind != -1;
        if(ind != -1) update(0, 0, n - 1, ind, INT_MIN);
    }
    return n - ans;
}