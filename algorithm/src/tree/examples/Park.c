// problem link: https://www.luogu.com.cn/problem/P4513
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

// this is the classic application of SEGMENT TREE to slove
// the problem related to sum of SUBARRAY!
// Basically, the problem will ask you to find some 
// value about a SUBARRAY, which means it is CONTINUOUS!!

// let's say the ith node in segment tree controls the range [l, r],
// Therefore, we can maintain to attribution in the segment tree:
// 1. the value of SUBARRAY whose start in the l;
// 2. the value of SUBARRAY whose end in the r;

// In this problem, we need to calculate the maximum sum of SUBARRAY,
// therefore, we also need to maintain the SUM of [l, r],
// and the maximum sum of SUBARRAY in [l, r].

// The details are in pushUp function.

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define ll long long
#define SIDE 500005

inline int getLC(int root){
    return root * 2 + 1;
}
inline int getRC(int root){
    return root * 2 + 2;
}

typedef struct SGTree{
    int l, r;
    ll maxleft, maxright, sum, ans;
}SGTree;

SGTree st[SIDE * 4];

// key to maintain the segment tree.
void pushUp(int root, int l, int r){
    int lc =getLC(root), rc = getRC(root);
    st[root].sum = st[lc].sum + st[rc].sum;
    st[root].maxleft = MAX(st[lc].maxleft, st[lc].sum + st[rc].maxleft);
    st[root].maxright = MAX(st[rc].maxright, st[rc].sum + st[lc].maxright);
    st[root].ans = MAX(MAX(st[lc].ans, st[rc].ans), st[lc].maxright + st[rc].maxleft);
}
void build(int root, int l, int r, int *arr){
    st[root].l = l, st[root].r = r;
    if(l == r){
        st[root].ans = st[root].maxleft = st[root].maxright = st[root].sum = arr[l];
        return;
    }
    int lc =getLC(root), rc = getRC(root);
    int m = (l + r) / 2;
    build(lc, l, m, arr);
    build(rc, m + 1, r, arr);

    pushUp(root, l, r);
}

SGTree query(int root, int l, int r, int ql, int qr){
    if(ql <= l && r <= qr){
        return st[root];
    }
    if(l > qr || r < ql){
        SGTree tmp;
        tmp.sum = 0;
        tmp.maxleft = tmp.maxright = tmp.ans = INT_MIN;
        return tmp;
    }

    int lc =getLC(root), rc = getRC(root);
    int m = (l + r) / 2;
    
    SGTree lq = query(lc, l, m, ql, qr);
    SGTree rq = query(rc, m + 1, r, ql, qr);

    SGTree t;

    t.sum = lq.sum + rq.sum;
    t.maxleft = MAX(lq.maxleft, lq.sum + rq.maxleft);
    t.maxright = MAX(rq.maxright, rq.sum + lq.maxright);
    t.ans = MAX(MAX(lq.ans, rq.ans), lq.maxright + rq.maxleft);
    return t;
}

void updateRange(int root, int l, int r, int ul, int ur, int val){
    if(l > ur || r < ul) return;
    if(l == r){
        st[root].ans = st[root].maxleft = st[root].maxright = st[root].sum = val;
        return;
    }
    int lc =getLC(root), rc = getRC(root);
    int m = (l + r) / 2;
    updateRange(lc, l, m, ul, ur, val);
    updateRange(rc, m + 1, r, ul, ur, val);
    pushUp(root, l, r);
}

int arr[SIDE];

int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++){
        scanf("%d", &arr[i]);   
    }
    build(0, 0, n - 1, arr);
    while(m--){
        int k, l, r;
        scanf("%d%d%d", &k, &l, &r);
        if(k == 1){
            int rl = MIN(l, r), rr = MAX(l, r);
            rl--, rr--;
            SGTree st = query(0, 0, n - 1, rl, rr);
            printf("%lld\n", st.ans);
        }
        else{
            updateRange(0, 0, n - 1, l - 1,l - 1, r);
        }
    }
    return 0;
}