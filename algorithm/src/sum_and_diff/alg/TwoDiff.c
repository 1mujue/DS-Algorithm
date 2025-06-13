// problem link: https://www.luogu.com.cn/problem/P3397

#include <stdio.h>
#include <math.h>
#include <limits.h>

#define VOL 1003
#define ll long long 
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) > (b) ? (b) : (a))

int matrix[VOL][VOL];
int diff[VOL][VOL];

int main(){
    int n, m;
    scanf("%d%d", &n, &m);

    while(m--){
        int lx, ly, rx, ry;
        scanf("%d%d%d%d", &lx, &ly, &rx, &ry);
        // diff[i + 1][j + 1] = matrix[i + 1][j + 1] - matrix[i][j + 1] - matrix[i + 1][j] + matrix[i][j];
        diff[lx][ly]++;
        diff[rx + 1][ry + 1]++;
        diff[rx + 1][ly]--;
        diff[lx][ry + 1]--;
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            matrix[i + 1][j + 1] = matrix[i][j + 1] + matrix[i + 1][j] - matrix[i][j] + diff[i + 1][j + 1];
            printf("%d%c", matrix[i + 1][j + 1], " \n"[j == n - 1]);
        }
    }
    return 0;
}