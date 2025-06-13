// problem link: https://leetcode.cn/problems/find-the-maximum-sum-of-node-values/description/

#include <limits.h>
#define ll long long
#define LEN 20003

// the first solution: tree dp.
int tot;
int head[2 * LEN];
int to[2 * LEN];
int next[2 * LEN];

void inEdge(int u, int v){
    tot++;
    to[tot] = v;
    next[tot] = head[u];
    head[u] = tot;
}

// dp[i][0]: after operation even times, the max value sum of tree whose root is i EXCEPT i.
// dp[i][1]: even -> odd.
ll dp[LEN][2];

void solute(int root, int* nums, int nsize, int * vis, int k){
    for(int eind = head[root]; eind; eind = next[eind]){
        int child = to[eind];
        if(vis[child]) continue;

        // the tree has no ring, so we can do DFS.
        vis[child] = 1;
        solute(child, nums, nsize, vis, k);
        
        // caution: dp[i][0] didn't count nums[i], and dp[i][1] didn't count nums[i] ^ k.
        // r0: when not operate on root and child, the max value of subtree child.
        // r1: when operate on root and child, the max value of subtree child.

        // in r0 case, dp[root][0] = dp[root][0] + r0, dp[root][1] = dp[root][1] + r0.
        // in r1 case, dp[root][0] = dp[root][1] + r1, dp[root][1] = dp[root][0] + r1.
        ll r0 = fmaxl(dp[child][0] + nums[child], dp[child][1] + (nums[child] ^ k));
        ll r1 = fmaxl(dp[child][1] + nums[child], dp[child][0] + (nums[child] ^ k));

        ll ori_dp0 = dp[root][0], ori_dp1 = dp[root][1];
        dp[root][0] = fmaxl(ori_dp0 + r0, ori_dp1 + r1);
        dp[root][1] = fmaxl(ori_dp1 + r0, ori_dp0 + r1);
    }
}
long long maximumValueSum(int* nums, int numsSize, int k, int** edges, int edgesSize, int* edgesColSize) {
    tot = 0;
    memset(head, 0, sizeof(int) * 2 * LEN);
    memset(next, 0, sizeof(int) * 2 * LEN);
    for(int i = 0; i < numsSize; i++){
        dp[i][0] = 0;
        dp[i][1] = LLONG_MIN;
    }
    for(int i = 0; i < edgesSize; i++){
        int u = edges[i][0], v = edges[i][1];
        inEdge(u, v);
        inEdge(v, u);
    }

    int vis[LEN] = {0};
    vis[0] = 1;
    solute(0, nums, numsSize, vis, k);
    return fmaxl(dp[0][0] + nums[0], dp[0][1] + (nums[0] ^ k));
}

// second solution: state machine dp.
// the first solution is slow, so we need to optimize it.

// KEY thought: tree is CONNECTED graph -> for ANY node u and v, there MUST exist
// one path (u -> a1 -> ... -> ak -> v)!!
// Moreover, if we do operation on the path, EVERY ai has do TWICE xor, and ai = ai ^ k ^ k = ai,
// therefore, ONLY u = u ^ k, v = v ^ k !! That is, we can update all PAIRS in nums !!
// Finally, the quesion becomes, if we do EVEN time xor operations on nums, what is the maximum sum?
long long maximumValueSum(int* nums, int numsSize, int k, int** edges, int edgesSize, int* edgesColSize) {
    // dp[i][0]: for num in nums[0, i - 1], the most value if we do even time operations.
    // dp[i][1]: even -> odd.

    // then, dp[i + 1][0] = MAX(dp[i][0] + nums[i], dp[i][1] + (nums[i] ^ k)).
    // dp[i + 1][1] = MAX(dp[i][1] + nums[i], dp[i][0] + (nums[i] ^ k)).
    // ll dp[LEN][2];
    // dp[0][0] = 0;
    // dp[0][1] = LLONG_MIN;

    // Clearly, we can do ROLL ARRAY to compress the space !!

    ll dp1 = 0, dp2 = LLONG_MIN;

    for(int i = 0; i < numsSize; i++){
        ll ndp1 = fmaxl(dp1 + nums[i], dp2 + (nums[i] ^ k));
        ll ndp2 = fmaxl(dp2 + nums[i], dp1 + (nums[i] ^ k));
        dp1 = ndp1;
        dp2 = ndp2;
    }
    return dp1;
}