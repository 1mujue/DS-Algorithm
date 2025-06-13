// problem link: https://www.luogu.com.cn/problem/P7167
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#define ll long long
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define VOL 100010
#define LOGN 22

// ancestor[i][j]: the 2^j ancestor of i.
int ancestor[VOL][LOGN];
ll sum[VOL][LOGN];

int plate[VOL][2];
int len[VOL];
int stack[VOL];

int query(int index, int volume){
    if(plate[index][1] >= volume){
        return index;
    }
    volume -= plate[index][1];
    for(int i = LOGN - 1; i >= 0; i--){
        if(ancestor[index][i] && volume > sum[index][i]){
            volume -= sum[index][i];
            index = ancestor[index][i];
        }
    }
    return ancestor[index][0];
}

int main(){
    int nn, qq;
    scanf("%d%d", &nn, &qq);
    plate[0][0] = plate[nn + 1][0] = INT_MAX;
    plate[0][1] = plate[nn + 1][1] = 0;

    for(int i = 0; i < nn; i++){
        scanf("%d%d", &plate[i + 1][0], &plate[i + 1][1]);
    }

    int top = 0;
    for(int i = 0; i < nn + 2; i++){
        while(top && plate[i][0] > plate[stack[top - 1]][0]){
            ancestor[stack[top - 1]][0] = i;
            sum[stack[top - 1]][0] = plate[i][1];
            top--;
        }
        stack[top++] = i;
    }

    ancestor[0][0] = 0;
    ancestor[nn + 1][0] = 0;
    
    for(int i = 1; i < LOGN; i++){
        for(int j = 0; j < nn + 2; j++){
            ancestor[j][i] = ancestor[ancestor[j][i - 1]][i - 1];
            sum[j][i] = sum[j][i - 1] + sum[ancestor[j][i - 1]][i - 1];
        }
    }

    while(qq--){
        int rr, vv;
        scanf("%d%d", &rr, &vv);
        printf("%d\n", query(rr, vv));
    }

    return 0;
}