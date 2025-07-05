// problem link: https://www.luogu.com.cn/problem/P2419
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

const int NODE_CNT = 102;

vector<vector<int>> graph(NODE_CNT, vector<int>(NODE_CNT, 0));

// this problem is not complicated, but the solution is VERY tricky.
// If the rank of a cow can be defined, then the relationship between 
// this cow and all other cows are DEFINED.
// let graph[i][j] = 1 means cow i can win cow j, then we need to check
// whether for j != i, graph[i][j] | graph[j][i] == 1, that is, we need 
// to check whether cow i can win cow j or cow j can win cow i.

int main(){
    int nn, mm;
    cin >> nn >> mm;

    while(mm--){
        int aa, bb;
        cin >> aa >> bb;
        aa--, bb--;
        graph[aa][bb] = 1;
    }
    
    for(int k = 0; k < nn; k++){
        for(int i = 0; i < nn; i++){
            for(int j = 0; j < nn; j++){
                graph[i][j] = graph[i][j] | graph[i][k] & graph[k][j];
            }
        }
    }

    int ans = 0;
    for(int i = 0; i < nn; i++){
        int isOk = 1;
        for(int j = 0; j < nn; j++){
            if(i == j) continue;
            isOk &= graph[i][j] | graph[j][i];
        }
        ans += isOk;
    }
    cout << ans;

    return 0;
}