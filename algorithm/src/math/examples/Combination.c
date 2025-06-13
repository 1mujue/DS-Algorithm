// problem link: https://www.luogu.com.cn/problem/P2822

// this is a VERY IMPORTANT example about combination problem. It also involves
// two-dimension previous sum!!!

#include <stdio.h>
#include <math.h>
#define VOL 2005

int combination[VOL][VOL];
int presum[VOL + 1][VOL + 1];

void preHandle(int val, int k){
    combination[0][0] = 1;
    for(int i = 1; i <= val + 1; i++){
        for(int j = 1; j <= i; j++){
            combination[i][j] = (combination[i - 1][j - 1] + combination[i - 1][j]) % k;
            presum[i][j] = presum[i - 1][j] + presum[i][j - 1] - presum[i - 1][j - 1] + (combination[i][j] == 0);
        }
        presum[i][i + 1] = presum[i][i];
    }
}


int main(){
    int t, k;
    scanf("%d%d", &t, &k);
    preHandle(2000, k);
    while(t--){
        int n, m;
        scanf("%d%d", &n, &m);
        m = fmin(n, m);
        printf("%d\n", presum[n + 1][m + 1]);
    }
    return 0;
}