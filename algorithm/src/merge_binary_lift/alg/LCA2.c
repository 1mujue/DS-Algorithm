// https://www.luogu.com.cn/problem/P3379

// the template of BOTH LCA and Binary Lifting.
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#define ll long long
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) > (b) ? (b) : (a))

#define NODE_CNT 500003
#define EDGE_CNT 500003
#define LOGN 20

int tot;
int head[NODE_CNT];
int to[2 * EDGE_CNT];
int next[2 * EDGE_CNT];

int ancestor[NODE_CNT][LOGN];
int depth[NODE_CNT];

int vis[NODE_CNT];

void inEdge(int u, int v){
    tot++;
    to[tot] = v;
    next[tot] = head[u];
    head[u] = tot;
}

void calcDepth(int root, int* vis){
    for(int eind = head[root]; eind; eind = next[eind]){
        int child = to[eind];
        if(!vis[child]){
            ancestor[child][0] = root;
            vis[child] = 1;
            depth[child] = depth[root] + 1;
            calcDepth(child, vis);
        }
    }
}

int query(int a, int b){
    if(depth[a] < depth[b]){
        int t = a;
        a = b;
        b = t;
    }
    for(int i = LOGN - 1; i >= 0; i--){
        if(depth[ancestor[a][i]] >= depth[b]){
            a = ancestor[a][i];
        }
    }

    if(a == b) return a;

    for(int i = LOGN - 1; i >= 0; i--){
        if(ancestor[a][i] != ancestor[b][i]){
            a = ancestor[a][i];
            b = ancestor[b][i];
        }
    }
    return ancestor[a][0];
}

int main(){
    int nn, mm, ss;
    scanf("%d%d%d", &nn, &mm, &ss);

    for(int i = 0; i < nn - 1; i++){
        int x, y;
        scanf("%d%d", &x, &y);
        inEdge(x, y);
        inEdge(y, x);
    }

    depth[ss] = 0;
    vis[ss] = 1;
    ancestor[ss][0] = ss;
    calcDepth(ss, vis);

    for(int i = 1; i < LOGN; i++){
        for(int j = 1; j <= nn; j++){
            ancestor[j][i] = ancestor[ancestor[j][i - 1]][i - 1];
        }
    }

    while(mm--){
        int a, b;
        scanf("%d%d", &a, &b);
        printf("%d\n", query(a, b));
    }
    return 0;
}