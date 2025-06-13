#include <stdio.h>
#include <malloc.h>

#define N 100001
#define SIGK 300001
#define NATION 100001

typedef struct Ship{
    int t;
    int startInd;
    int endInd;
}Ship;

Ship ships[N];
int cus[SIGK];
int x[NATION];

int main(){
    int cusInd = 0;
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        int ti, ki;
        scanf("%d%d", &ti, &ki);
        ships[i].t = ti;
        ships[i].startInd = cusInd;
        ships[i].endInd = cusInd + ki;
        for(int j = 0; j < ki; j++){
            scanf("%d", &cus[cusInd + j]);
        }
        cusInd += ki;
    }

    int countryCnt = 0;
    int left = 0, right = 0;
    while(right < n){
        int startInd = ships[right].startInd;
        int endInd = ships[right].endInd;
        int endT = ships[right].t;
        right++;
        for(int i = startInd; i < endInd; i++){
            if(!x[cus[i]]++){
                countryCnt++;
            }
        }
        while(ships[left].t <= endT - 86400){
            for(int i = ships[left].startInd; i < ships[left].endInd; i++){
                if(!--x[cus[i]]){
                    countryCnt--;
                }
            }
            left++;
        }
        printf("%d\n", countryCnt);
    }
    return 0;
}