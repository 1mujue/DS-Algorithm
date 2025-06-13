// problem link: https://www.luogu.com.cn/problem/P1433
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <math.h>

#define ll long long
#define db double
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define LEN 16

db ans;
db getDis(db x1, db y1, db x2, db y2){
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

db nodes[LEN][2];

// we can use a binary number to represent the node WE HAVE passed through.
// For example, 0011001 means we have past the 1, 4, 5 nodes.
// dp[i][j] is that, when CURRENT node is i, and we HAVE passed j nodes,
// then the minimum answer to pass ALL left nodes.
db dp[LEN][(1 << LEN)];

db solute(int cur, int state, int size){
    if(dp[cur][state] != INT_MAX){
        return dp[cur][state];
    }
    for(int i = 0; i < size; i++){
        if((state & (1 << i)) == 0){
            state |= (1 << i);
            db res = solute(i + 1, state, size);
            state &= ~(1 << i);
            dp[cur][state] = fmin(dp[cur][state], res + getDis(nodes[cur][0], nodes[cur][1], nodes[i + 1][0], nodes[i + 1][1]));
        }
    }
    return dp[cur][state];
}


int main(){
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%lf%lf", &nodes[i][0], &nodes[i][1]);
    }

    ans = INT_MAX;
    
    int limit = (1 << n);
    for(int i = 0; i <= n; i++){
        for(int j = 0; j < limit; j++){
            dp[i][j] = INT_MAX;
        }
        dp[i][limit - 1] = 0;
    }

    db res = solute(0, 0, n);
    printf("%.2f", res);

    return 0;
}