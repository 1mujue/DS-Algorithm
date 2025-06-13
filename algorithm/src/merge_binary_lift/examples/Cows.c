// problem link: https://www.luogu.com.cn/problem/P2345
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

#define ll long long
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define LEN 20003

typedef struct Cow{
    ll v, x;
} Cow;

int cmp(const void* e1, const void* e2){
    Cow* a1 = (Cow*)e1;
    Cow* a2 = (Cow*)e2;
    return a1->v > a2->v;
}

Cow cows[LEN];

inline int getLowBit(int x){
    return x & (-x);
}
ll presum[LEN];
int cnt[LEN];

void add(int val, int index, int limit){
    while (index <= limit)
    {
        presum[index] += val;
        cnt[index]++;
        index += getLowBit(index);
    }
}

void query(int index, ll* s, int* c){
    while(index){
        (*s) += presum[index];
        (*c) += cnt[index];
        index -= getLowBit(index);
    }
}

int main(){
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d%d", &cows[i].v, &cows[i].x);
    }
    qsort(cows, n, sizeof(Cow), cmp);

    ll ans = 0;
    ll asum = 0, tsum;
    int acnt = 0, tcnt;

    for(int i = 0; i < n; i++){
        tsum = tcnt = 0;
        ll x = cows[i].x;
        ll v = cows[i].v;
        query(x, &tsum, &tcnt);
        ans += (tcnt * x - tsum) * v;
        ans += (asum - tsum - (acnt - tcnt) * x) * v;
        add(x, x, LEN - 1);
        asum += x;
        acnt += 1;
    }
    printf("%lld", ans);
    return 0;
}