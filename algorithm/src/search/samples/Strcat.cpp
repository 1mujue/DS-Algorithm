//#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <cmath>
#define N 22

using namespace std;

string strs[N];
int vis[N];
int ans;

void dfs(string temp, int curInd, int n){
    int tempSize = temp.size();

    string curStr = strs[curInd];
    int curSize = curStr.size();
    for(int i = 0; i < n; i++){
        if(vis[i] >= 2) continue;
        string otherStr = strs[i];
        int otherSize = otherStr.size();
        for(int j = fmin(curSize, otherSize) - 1; j > 0; j--){
            if(temp.substr(tempSize - j, j) == otherStr.substr(0, j)){
                vis[i]++;
                dfs(temp + otherStr.substr(j), i, n);
                vis[i]--;
            }
        }
    }
    ans = fmax(ans, tempSize);
}

int main(){
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> strs[i];
    }
    char ch;
    cin >> ch;
    for(int i = 0; i < n; i++){
        if(strs[i][0] == ch){
            vis[i] = 1;
            dfs(strs[i], i, n);
            vis[i] = 0;
        }
    }
    cout << ans;
    return 0;
}