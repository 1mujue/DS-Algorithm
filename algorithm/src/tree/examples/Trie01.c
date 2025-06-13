// https://www.luogu.com.cn/problem/P4551
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <math.h>

#define ll long long
#define ull unsigned long long
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define VOL 30

typedef struct TrieNode{
    int val;
    struct TrieNode* children[VOL];
}TrieNode;

TrieNode* newTNode(int val){
    TrieNode* obj = (TrieNode*)calloc(1, sizeof(TrieNode));
    obj->val = val;
    return obj;
}

TrieNode* getAndCreateChild(TrieNode* root, int val){
    if(!root->children[val]){
        root->children[val] = newTNode(val);
    }
    return root->children[val];
}

TrieNode* getChildDirectly(TrieNode* root, int val){
    return root->children[val];
}

void freeTNode(TrieNode* root){
    for(int i = 0; i < VOL; i++){
        if(root->children[i]){
            freeTNode(root->children[i]);
        }
    }
    free(root);
}

#define NODE_CNT 100004
#define EDGE_CNT 200007

int tot;
int head[NODE_CNT];
int vis[NODE_CNT];
int to[EDGE_CNT];
int weight[EDGE_CNT];
int next[EDGE_CNT];

void inEdge(int u, int v, int w){
    tot++;
    to[tot] = v;
    weight[tot] = w;
    next[tot] = head[u];
    head[u] = tot;
}

int queue[NODE_CNT][2];

// this is VERY IMPORTANT!! 0-1 Trie!!!
// To be easy, let's consider how to find the BIGGEST XOR
// value in a sub array of an array. The normal way is O(n^2). 

// Then let's change our idea. First, XOR is very beautiful,
// since it has this feature: if a = b ^ c, then a ^ b = b ^ c ^ b = c.
// Therefore, let prexor[i] represents XOR value in [0...i],
// then prexor[R] ^ prexor[L - 1] = XOR value in [L, R].

// Therefore, for a new index R, we want to find a L, that
// prexor[R] ^ prexor[L - 1] is max. Let prexor[R] be 6, for example,
// in binary, it is 110. Obviously, if there is a L satisfies that
// prexor[L - 1] == 001, then prexor[R] ^ prexor[L - 1] is max.

// However, we don't have to find L. Instead, we try to find 001 directly.
// How to get 001 from 110? For the high bit, if high bit is 0, then we want
// another high bit is 1, verse visa, since 0 ^ 1 == 1.
// Of course, 1000 > 0111, therefore, we will try to match HIGH BIT first.

// Now the quesion is HOW TO query a val like 001 in O(1) time.
// We can use Trie Tree to solve the problem!!!
// If val == k1k2k3 in binary, then we can build a tree like
// k1 -> k2 -> k3. This is INSERT a new val !!

// when query, let val == k1k2k3, then we will try to find 1 - k1 first
// (since (1 - k1) ^ k1 == 1), otherwise we can only find k1. Let 1 - k1 or k1 be k1'.
// Follow the rule, we can get a val' == k1'k2'k3', that val' XOR val is max.

int main(){
    int nn;
    scanf("%d", &nn);
    for(int i = 0; i < nn - 1; i++){
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        u--,v--;
        inEdge(u, v, w);
        inEdge(v, u, w);
    }

    TrieNode* root = newTNode(-1);

    // take 0 node as the root node.
    int slow = 0, fast = 0;
    queue[fast][0] = 0;
    queue[fast][1] = 0;
    vis[0] = 1;
    fast++;

    int ans = INT_MIN;

    while(slow != fast){
        int croot = queue[slow][0];
        int cxor = queue[slow][1];
        slow++;

        int bits[35];
        int txor = cxor;
        for(int i = 0; i < 32; i++){
            bits[i] = txor & 1;
            txor >>= 1;
        }

        TrieNode* curr = root;
        // create the val first to make sure when query,
        // we can STILL find an answer(val' == val).
        for(int i = 31; i >= 0; i--){
            curr = getAndCreateChild(curr, bits[i]);
        }

        // query then.
        int qxor = 0;
        curr = root;
        for(int i = 31; i >= 0; i--){
            int tar = 1 - bits[i];
            TrieNode* next = getChildDirectly(curr, tar);
            if(!next){
                next = getChildDirectly(curr, 1 - tar);
            }
            curr = next;
            qxor = qxor * 2 + next->val;
        }

        ans = fmax(ans, qxor ^ cxor);

        for(int eind = head[croot]; eind; eind = next[eind]){
            int nv = to[eind], nw = weight[eind];
            if(vis[nv]) continue;
            vis[nv] = 1;

            queue[fast][0] = nv;
            queue[fast][1] = cxor ^ nw;
            fast++;
        }
    }
    printf("%d\n", ans);
    return 0;
}