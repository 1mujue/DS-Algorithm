// problem link: https://www.luogu.com.cn/problem/P3865
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

#define ll long long
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) > (b) ? (b) : (a))

// the template of sparse table.
// it CAN'T do update. Meanwhile, you have to make sure
// the operation has such character:
// x op x = x. For example, max(x, x) = x, gcd(x, x) = x.
// sparse table is faster than segment tree when query.
// since x op x = x, then the query range can OVERLAP !!
// Therefore, the time complexity of sparse table is O(1).

// However, for x + x != x, x * x != x, sparse table can't 
// work anymore.

#define MAXN 100001
#define LOGN 22
int logn[MAXN];
// func[i][j]: the max value in [i, i + 2^{j} - 1]
int func[MAXN][LOGN];

void pre(){
    logn[1] = 0;
    logn[2] = 1;
    for(int i = 3; i < MAXN; i++){
        logn[i] = logn[i / 2] + 1;
    }
}

int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++){
        scanf("%d", &func[i][0]);
    }
    pre();
    for(int ind = 1; ind < LOGN; ind++){
        for(int i = 1; i + (1 << ind) - 1 <= n; i++){
            // quite similar with segment tree!!
            func[i][ind] = MAX(func[i][ind - 1], func[i + (1 << (ind - 1))][ind - 1]);
        }
    }
    for(int i = 0; i < m; i++){
        int l, r;
        scanf("%d%d", &l, &r);
        // this index will make sure there is OVERLAP.
        int s = logn[r - l + 1];
        printf("%d\n", MAX(func[l][s], func[r - (1 << s) + 1][s]));
    }
    return 0;
}