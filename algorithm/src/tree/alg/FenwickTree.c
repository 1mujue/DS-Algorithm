// problem link: https://www.luogu.com.cn/problem/P3368

// This is the ADVANCED template of Fenwick Tree.
// Why it is advanced? Because elements in Fenwick Tree nodes
// are DIFFERENTIAL values.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define ll long long
#define LEN 500003

inline int getLB(int val){
    return val & -val;
}

ll ft[LEN];

void update(int ind, ll val, int size){
    while(ind <= size){
        ft[ind] += val;
        ind += getLB(ind);
    }
}

ll query(int ind){
    ll ans = 0;
    while(ind){
        ans += ft[ind];
        ind -= getLB(ind);
    }
    return ans;
}

int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++){
        int val;
        scanf("%d", &val);
        update(i + 1, val, n);
        update(i + 2, -val, n);
    }

    while(m--){
        int op;
        scanf("%d", &op);
        if(op == 1){
            int x, y, k;
            scanf("%d%d%d", &x, &y, &k);
            update(x, k, n);
            update(y + 1, -k, n);
        }
        else{
            int x;
            scanf("%d",&x);
            printf("%lld\n", query(x));
        }
    }
    return 0;
}