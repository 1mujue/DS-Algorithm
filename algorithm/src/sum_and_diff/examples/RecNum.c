// problem link: https://www.luogu.com.cn/problem/P1950
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#define ll long long
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define SIDE 1005

int presum[SIDE][SIDE];
int matrix[SIDE][SIDE];

int main(){
    char buf[SIDE];
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++){
        scanf(" %s", buf);
        for(int j = 0; j < m; j++){
            matrix[i][j] = buf[j] == '.';
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(matrix[i][j]){
                presum[i + 1][j + 1] = presum[i][j + 1] + 1;
            }
            else{
                presum[i + 1][j + 1] = 0;
            }
        }
    }

    int stack[SIDE];
    int top = 0;
    ll ans = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j <= m + 1; j++){
            while(top && presum[i + 1][stack[top - 1]] >= presum[i + 1][j]){
                ll l = stack[top - 1] - stack[top - 2];
                ll r = j - stack[top - 1];
                ll h = presum[i + 1][stack[top - 1]];
                ans += l * r * h;
                top--;
            }
            stack[top++] = j;
        }
    }
    printf("%lld\n", ans);
    return 0;
}