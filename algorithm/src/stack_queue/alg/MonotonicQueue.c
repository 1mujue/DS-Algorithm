// problem link: https://www.luogu.com.cn/problem/P1886
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#define ll long long
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define VOL 1000002

int arr[VOL];
int minQueue[VOL];
int maxQueue[VOL];
int minAns[VOL];
int maxAns[VOL];

int main(){
    int n, k;
    scanf("%d%d", &n ,&k);
    for(int i = 0; i < n; i++){
        scanf("%d",  &arr[i]);
    }

    int ind = 0;
    int mnleft = 0, mnright = 0, mxleft = 0, mxright = 0;

    while(ind != n){
        int val = arr[ind];
        while(mnleft != mnright && ind - minQueue[mnleft] + 1 > k){
            mnleft++;
        }
        while(mxleft != mxright && ind - maxQueue[mxleft] + 1 > k){
            mxleft++;
        }
        while(mnleft != mnright && arr[minQueue[mnright - 1]] > val){
            mnright--;
        }
        while(mxleft != mxright && arr[maxQueue[mxright - 1]] < val){
            mxright--;
        }
        minQueue[mnright++] = ind;
        maxQueue[mxright++] = ind;
        if(ind >= k - 1){
            minAns[ind - k + 1] = arr[minQueue[mnleft]];
            maxAns[ind - k + 1] = arr[maxQueue[mxleft]];
        }

        ind++;
    }
    for(int i = 0; i < n - k + 1; i++){
        printf("%d ", minAns[i]);
    }
    printf("\n");
    for(int i = 0; i < n - k + 1; i++){
        printf("%d ", maxAns[i]);
    }
    return 0;
}