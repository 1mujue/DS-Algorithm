// problem link: https://www.luogu.com.cn/problem/P1099

#include <bits/stdc++.h>
using namespace std; 
typedef long long ll;

#define N 50005

vector<vector<int>> graph(N);

vector<int> treeSize;
vector<int> vis;

int n;

// a VERY GOOD example of tree-shape DP.
// Let's say a node 'root' and its child node 'child', if the distance for 
// 'root' to reach ALL others node is dp[root], how will the distance CHNAGES
// if we switch to 'child'? Clearly, in 'child' node, those nodes which can be reached
// ONLY IF you pass 'root' is further, and those nodes which can be reached ONLY IF
// you pass 'child' is shorter.

// This solution can be easily understood if the tree is directed. Now that the tree
// is undirected, we can set a 'root' node, and the direction of 'root' node and 'child' node
// is from 'root' to 'child'. The size of the subtree whose ROOT node is 'root' is the
// SUM of the subtree whose ROOT node is the 'child' node of 'root' node, therefore, we 
// can calculate the treeSize whose ROOT node is 'root' by DFS.

int calcTreeSize(int root){
    vis[root] = 1;
    for(const int& child : graph[root]){
        if(vis[child]) continue;
        vis[child] = 1;
        treeSize[root] += calcTreeSize(child);
    }
    treeSize[root] += 1;
    return treeSize[root];
}

int minDis = INT_MAX;
int minNode = -1;

int calcDis(int root){
    vis[root] = 1;
    int dis = 0;
    for(const int& child : graph[root]){
        if(vis[child]) continue;
        vis[child] = 1;
        dis += calcDis(child) + treeSize[child];
    }
    return dis;
}

vector<int> dp;

void solute(int curr){
    for(const int& child : graph[curr]){
        if(dp[child] == -1){
            dp[child] = dp[curr] + n - 2 * treeSize[child];
            if(dp[child] < minDis || dp[child] == minDis && child < minNode){
                minDis = dp[child];
                minNode = child;
            }
            solute(child);
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    
    cin >> n;
    for(int i = 0; i < n - 1; i++){
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    vis.resize(n + 1, 0);
    treeSize.resize(n + 1, 0);

    calcTreeSize(1);

    vis.assign(n + 1, 0);
    dp.resize(n + 1, -1);
    dp[1] = calcDis(1);

    solute(1);

    cout << minNode << ' ' << minDis;
    return 0;
}