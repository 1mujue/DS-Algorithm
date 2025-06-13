// problem link:  https://leetcode.cn/problems/painting-a-grid-with-three-different-colors/
#include <stdbool.h>
#define ROW 1003
#define COL (3 * 3 * 3 * 3 * 3 + 5)
#define MOD 1000000007
#define ll long long

// this is an example of dp with status compression. Since m is in [1, 5], and there
// are 3 colors, we have totally 3^m  different status, and we can use a 
// number in [0, 3^m - 1] to represent the status UNIQUELY. 

// For example, if m = 3, and the status is 23, 
// after 3 div and mod, we have 23 % 3 = 2, 23 / 3 = 7;
// 7 % 3 = 1, 7 / 3 = 2; 2 % 3 = 2, 2 / 3 = 0. Therefore, the color is (2, 1, 2) !!

// So we just need to check whether the status itself is valid, and whether the two
// adjacent statuses are conflict. That is, the same number cannot be adjacent 
// (one status validation) and in the same place(two statuses conflict).

// Additionally, we can use FAST POW OF MATRIX to solve this problem, but I don't
// write the code here.
bool isOK(int v, int m){
    int prev = -1;
    while(m--){
        if(prev == v % 3) return false;
        prev = v % 3;
        v /= 3;
    }
    return true;
}
bool isConflict(int j, int k, int m){
    if(!isOK(j, m) || !isOK(k, m)) return true;
    while(m){
        if(j % 3 == k % 3) return true;
        j /= 3;
        k /= 3;
        m--;
    }
    return false;
}
int colorTheGrid(int m, int n) {
    ll dp[ROW][COL] = {0};
    int col = 1;
    for(int i = 0; i < m; i++){
        col *= 3;
    }
    for(int i = 0; i < col; i++){
        if(isOK(i, m)) dp[0][i] = 1;
    }
    for(int i = 1; i < n; i++){
        for(int j = 0; j < col; j++){
            for(int k = 0; k < col; k++){
                if(!isConflict(j, k, m)){
                    dp[i][j] = (dp[i][j] + dp[i - 1][k]) % MOD;
                }
            }
        }
    }
    ll ans = 0;
    for(int i = 0; i < col; i++){
        ans = (ans + dp[n - 1][i]) % MOD;
    }
    return ans;
}