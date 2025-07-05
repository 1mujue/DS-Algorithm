// problem link: https://www.luogu.com.cn/problem/P1637
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

// this is a very classic application for fenwick tree to 
// slove the problem of counting the number of inversions.
// For arr[i], we  want to know how many elements in arr[0...i-1] is larger than arr[i],
// and let the answer be less[i];
// and how many elements in arr[i+1...n-1] is smaller than arr[i],
// and let the answer be larger[i].
// Then, the answer is the sum of less[i] * larger[i] for all i in [0, n-1].

// It is obvious that 'larger' is similar with 'smaller', so we can focus on 'smaller'.
// for number val ranged in [1, n], we can PLUS fenwick tree at INDEX val with value 1,
// and the sum of fenwick tree in [1, val - 1] is the number of elements smaller than val!

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define ll long long
#define SIDE 30005

inline int getLowBit(int val){
    return val & -val;
}

int lftree[SIDE], rftree[SIDE];

void update(int* ft, int ind, int val, int n){
    while(ind <= n){
        ft[ind] += val;
        ind += getLowBit(ind);
    }
}

int query(int* ft, int ind){
    int ans = 0;
    while(ind){
        ans += ft[ind];
        ind -= getLowBit(ind);
    }
    return ans;
}

int lowb(int* arr, int l, int r, int tar){
    int ans = -1;
    while(l <= r){
        int m = (l + r) / 2;
        if(arr[m] >= tar){
            if(arr[m] == tar) ans = m;
            r = m - 1;
        }
        else{
            l = m + 1;
        }
    }
    return ans;
}
int cmp(const void* e1, const void* e2){
    return *(int*)e1 > *(int*)e2;
}
int arr[SIDE];
int narr[SIDE];
int less[SIDE], larger[SIDE];

int main(){
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
        narr[i] = arr[i];
    }
    qsort(arr, n, sizeof(int), cmp);
    for(int i = 0; i < n; i++){
        narr[i] = lowb(arr, 0, n - 1, narr[i]) + 1;
    }
    for(int i = 0; i < n; i++){
        less[i] = query(lftree, narr[i] - 1);
        update(lftree, narr[i], 1, n);
    }
    for(int i = n - 1; i >= 0; i--){
        larger[i] = n - 1 - i - query(rftree, narr[i]);
        update(rftree, narr[i], 1, n);
    }
    ll ans = 0;
    for(int i = 0; i < n; i++){
        ans += (ll) less[i] * larger[i];
    }
    printf("%lld\n", ans);
    return 0;
}