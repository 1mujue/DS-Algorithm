// problem link: https://www.luogu.com.cn/problem/P4147
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#define ll long long
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define SIDE 1006

int grid[SIDE][SIDE];
int fcnt[SIDE][SIDE];

int main(){
    char buf[SIDE];
    int nn, mm;
    scanf("%d%d", &nn, &mm);
    
    for(int i = 0; i < nn; i++){
        scanf(" %[^\n]", buf);
        for(int j = 0; j < mm; j++){
            if(buf[2 * j] == 'R'){
                grid[i][j] = 0;
            }
            else{
                grid[i][j] = 1;
            }
        }
    }

    for(int i = 0; i < mm; i++){
        int curfcnt = 0;
        for(int j = 0; j < nn; j++){
            curfcnt = grid[j][i] ? curfcnt + 1 : 0;
            fcnt[j][i + 1] = curfcnt;
        }
    }

    for(int j = 0; j < nn; j++){
        fcnt[j][0] = fcnt[j][mm + 1] = 0;
    }

    int queue[SIDE];
    int ans = 0;
    for(int i = 0; i < nn; i++){
        int top = 0;
        for(int j = 0; j < mm + 2; j++){
            while(top && fcnt[i][j] < fcnt[i][queue[top - 1]]){
                ans = MAX(ans, (j - queue[top - 2] - 1) * fcnt[i][queue[top - 1]]);
                top--;
            }   
            queue[top++] = j;
        }
    }
    printf("%d", ans * 3);
    return 0;
}