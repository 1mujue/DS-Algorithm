// problem link: https://leetcode.cn/problems/minimum-score-after-removals-on-a-tree/
// The key to solve this problem is HOW TO judge whether a node is a child of another node.
// Since we have to find the minimum score after removing two edges, 
// we can use DFS to get the in-time and out-time of each node.
// Then, if node n1 is the child node of node n2, then the in-time of n1 should be greater
// than the in-time of n2, and the out-time of n1 should be less than the out-time of n2.
// This is a very important problem that teaches you how to use DFS to solve tree problems.
#include <bits/stdc++.h>
using namespace std;
struct TNode{
    int inTime;
    int outTime;
    int xorVal;
};
class Solution {
public:
    vector<vector<int>> graph;
    vector<int> vis;
    vector<TNode> nodes;
    void dfs(vector<int>& nums, int val, int* ind){
        vis[val] = 1;
        nodes[val].inTime = *ind;
        nodes[val].xorVal = nums[val];
        (*ind)++;
        for(auto child: graph[val]){
            if(vis[child]) continue;
            dfs(nums, child, ind);
            nodes[val].xorVal ^= nodes[child].xorVal;
        }
        nodes[val].outTime = *ind;
        (*ind)++;
    }
    bool isFather(TNode& t1, TNode& t2){
        return t1.inTime < t2.inTime && t1.outTime > t2.outTime;
    }
    int getChild(int v1, int v2){
        if(isFather(nodes[v1], nodes[v2])) return v2;
        else if(isFather(nodes[v2], nodes[v1])) return v1;
        return -1;
    }
    int minimumScore(vector<int>& nums, vector<vector<int>>& edges) {
        int n = nums.size();
        vis.resize(n, 0);
        nodes.resize(n);
        graph.resize(n);
        for(int i = 0; i < n - 1; i ++){
            int u = edges[i][0], v = edges[i][1];
            graph[u].push_back(v), graph[v].push_back(u);
        }

        int ind = 0;
        dfs(nums, 0, &ind);  

        int ans = INT_MAX;
        int totXor = nodes[0].xorVal;
        for(int i = 0; i < n - 1; i ++){
            int u1 = edges[i][0], v1 = edges[i][1];
            int c1 = getChild(u1, v1);
            for(int j = i + 1; j < n - 1; j++){
                int u2 = edges[j][0], v2 = edges[j][1];
                int c2 = getChild(u2, v2);

                int xor0 = 0, xor1 = 0 , xor2 = 0;
                if(isFather(nodes[c1], nodes[c2])){
                    xor0 = totXor ^ nodes[c1].xorVal;
                    xor1 = nodes[c1].xorVal ^ nodes[c2].xorVal;
                    xor2 = nodes[c2].xorVal;
                }
                else if(isFather(nodes[c2], nodes[c1])){
                    xor0 = totXor ^ nodes[c2].xorVal;
                    xor1 = nodes[c2].xorVal ^ nodes[c1].xorVal;
                    xor2 = nodes[c1].xorVal;
                }
                else{
                    xor0 = totXor ^ nodes[c1].xorVal ^ nodes[c2].xorVal;
                    xor1 = nodes[c1].xorVal;
                    xor2 = nodes[c2].xorVal;
                }

                ans = min(max({xor0, xor1, xor2}) - min({xor0, xor1, xor2}), ans);
            }
        }
        return ans;
    }
};