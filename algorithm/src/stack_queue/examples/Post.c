// problem link: https://www.luogu.com.cn/problem/P3467
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#define ll long long
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define VOL 250003

ll arr[VOL];
ll stack[VOL];
int top;

int main(){
    int n;
    scanf("%d", &n);
    int ans = 0;
    for(int i = 0; i < n; i++){
        ll di;
        scanf("%lld%lld", &di, &arr[i]);
    }
    arr[n] = LLONG_MIN;

    for(int i = 0; i <= n; i++){
        ll wi = arr[i];
        int cur = top - 1;
        while(cur >= 0 && stack[cur] > wi){
            cur--;
        }
        ll cw = wi;
        for(int j = cur + 1; j < top; j++){
            if(stack[j] > cw){
                ans++;
            }
            cw = stack[j];
        }
        top = cur + 1;
        stack[top++] = wi;
    }

    printf("%d", ans);
    return 0;
}