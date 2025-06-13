// problem link: https://www.luogu.com.cn/problem/B3647

// the template of Floyd. The algorithm could fit ALL KINDS OF graph
// EXCEPT there is a negative ring (shortest path doesn't exist)

// definition of f[k][x][y]: you can ONLY pass the node 1 to k,
// and the shortest path from x to y.
// Obviously, f[n][x][y] is the shortest path from x to y (assume
// there are n nodes.)
// The way to update f[k][x][y] is very easily:
// f[k][x][y] = fmin(f[k - 1][x][y], f[k - 1][x][k] + f[k - 1][k][y])
// However, the first dimension can be DELETED !!!

// Moreover

#include <stdio.h>
#include <limits.h>
#include <math.h>
#define SIDE 104

int graph[SIDE][SIDE];
int dis[SIDE][SIDE];

int main(){
    int n, m;
    scanf("%d%d", &n, &m);

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(i == j) graph[i][j] = 0;
            else graph[i][j] = INT_MAX / 2;
        }
    }

    for(int i = 0; i < m; i++){
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        u--, v--;
        graph[u][v] = graph[v][u] = fmin(graph[u][v], w);
    }

    // Floyd. The time conplex is O(n^3).
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            dis[i][j] = graph[i][j];
        }
    }

    for(int k = 0; k < n; k++){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                dis[i][j] = fmin(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%d ", dis[i][j]);
        }
        printf("\n");
    }
    return 0;
}