// problem link: https://www.luogu.com.cn/problem/P3371

// SPFA is an impletation of Bellman-Ford. It could calculate
// the shortest path in a NAGATIVE graph, and judge whether there 
// is a NAGATIVE RING!!

// Relaxation: dix(v) = min(dis(v), dis(u) + w(u, v))
// At each relaxation, the length of shortest path will AT
// LEAST increase 1, and the minimum length of shortest path
// is n - 1, therefore, the time complex is O(nm) or O(VE).

// Then what is SPFA ?? As we can see, in many situations, we 
// DON'T have to do a lot of relaxations(they are useless), and 
// clearly, only those nodes relaxed last time will lead to 
// the relaxation of its edge.
// Therefore, we can use a QUEUE to maintain nodes that might lead
// to relaxation.

// Caution: SPFA starts with a src node, therefore, it can ONLY
// judge whether there is a nagative ring that can be reached by the src node.
// If you want to judge whether there is a nagative ring in the WHOLE graph,
// you should build a SUPER node that connects all other nodes, and 
// run SPFA on it. 

#include <stdio.h>
#include <limits.h>
#include <math.h>

#define NODE_CNT 10004
#define EDGE_CNT 500004
#define NEXT(curr, MOD) (((curr) + 1) % MOD)

int tot;
int head[NODE_CNT];
int to[EDGE_CNT];
int weight[EDGE_CNT];
int next[EDGE_CNT];

void inEdge(int u, int v, int w){
    tot++;
    to[tot] = v;
    weight[tot] = w;
    next[tot] = head[u];
    head[u] = tot;
}

int dis[NODE_CNT], cnt[NODE_CNT], vis[NODE_CNT];
int queue[NODE_CNT];


// judge whether there is a nagative ring and calculate
// the shortest path begins at s.
int SPFA(int n, int s){
    for(int i = 0; i < n; i++){
        dis[i] = INT_MAX;
    }
    dis[s] = 0, vis[s] = 1;

    int slow = 0, fast = 0;
    queue[fast] = s;
    fast = NEXT(fast, n);

    while(slow != fast){
        int u = queue[slow];
        slow = NEXT(slow, n);
        vis[u] = 0;

        for(int eind = head[u]; eind; eind = next[eind]){
            int v = to[eind], w = weight[eind];

            if(dis[v] > dis[u] + w){
                dis[v] = dis[u] + w;
                cnt[v] = cnt[u] + 1;

                // In this case, a nagative ring exists.
                if(cnt[v] >= n) return 0;

                if(!vis[v]){
                    queue[fast] = v;
                    vis[v] = 1;
                    fast = NEXT(fast, n);
                }
            }
        }
    }

    return 1;
}

int main(){
    int n, m, s;
    scanf("%d%d%d", &n, &m, &s);
    s--;

    for(int i = 0; i < m; i++){
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        u--, v--;
        inEdge(u, v, w);
    }

    SPFA(n, s);

    for(int i = 0; i < n; i++){
        printf("%d ", dis[i]);
    }

    return 0;
}
