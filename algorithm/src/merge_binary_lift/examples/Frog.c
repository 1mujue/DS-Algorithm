// problem link: https://www.luogu.com.cn/problem/P3509
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#define ll long long
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define VOL 1000005

ll stones[VOL];

int tnext[VOL];
int next[VOL];
int pos[VOL];

int main(){
    int n, k;
    ll m;
    scanf("%d%d%lld", &n, &k, &m);
    for(int i = 0; i < n; i++){
        scanf("%lld", stones + i);
    }

    int left = 0, right = k;

    for(int i = 0; i < n; i++){
        while(right + 1 < n && stones[right + 1] - stones[i] < stones[i] - stones[left]){
            right++;
            left++;
        }
        if(stones[right] - stones[i] > stones[i] - stones[left]) next[i] = right;
        else next[i] = left;
    }

    for(int i = 0; i < n; i++){
        pos[i] = i;
    }
    while(m){
        if(m & 1){
            for(int i = 0; i < n; i++){
                pos[i] = next[pos[i]];
            }
        }
        m >>= 1;
        memcpy(tnext, next, sizeof(ll) * n);
        for(int i = 0; i < n; i++){
            next[i] = tnext[tnext[i]];
        }
    }

    for(int i = 0; i < n; i++){
        printf("%d ", pos[i] + 1);
    }
    
    return 0;
}