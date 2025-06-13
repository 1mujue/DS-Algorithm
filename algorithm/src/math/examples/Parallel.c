// problem link: https://www.luogu.com.cn/problem/P2789

#include <stdio.h>
#define N 30

int main(){
    int rec[N][N * N] = {0};
    rec[0][0] = rec[1][0] = 1;
    int nn;
    scanf("%d", &nn);
    for(int i = 2; i <= nn; i++){
        for(int j = i; j >= 2; j--){
            int para = j, upara = i - j;
            for(int k = 0; k <= upara * (upara - 1) / 2; k++){
                if(rec[upara][k]){
                    int val = para * upara + k;
                    rec[i][val]++;
                }
            }
        }
        rec[i][i * (i - 1) / 2] = 1;
    }
    int ans = 0;
    for(int i = 0; i <= nn * (nn - 1) / 2; i++){
        ans += rec[nn][i] != 0;
    }
    printf("%d", ans);
    return 0;
}