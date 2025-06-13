//
// Created by 赵龙淳 on 2023/11/15.
//
#include <queue>
#include <iostream>
#include <cstring>
#define N 10007
#define INF 0x11111111
using namespace std;
struct MF {
    struct edge {
        int v, nxt, cap, flow;
    } e[N];

    int fir[N], cnt = 0;

    int n, S, T;
    long long maxflow = 0;
    int dep[N], cur[N];

    void init(int n,int S,int T) {
        memset(fir, -1, sizeof fir);
        cnt = 0;
        maxflow = 0;
        this->n = n;
        this->S = S;
        this->T = T;
    }

    void addedge(int u, int v, int w) {
        e[cnt] = {v, fir[u], w, 0};
        fir[u] = cnt++;
        e[cnt] = {u, fir[v], 0, 0};
        fir[v] = cnt++;
    }

    bool bfs() {
        queue<int> q;
        memset(dep, 0, sizeof(int) * (n + 1));

        dep[S] = 1;
        q.push(S);
        while (q.size()) {
            int u = q.front();
            q.pop();
            for (int i = fir[u]; ~i; i = e[i].nxt) {
                int v = e[i].v;
                if ((!dep[v]) && (e[i].cap > e[i].flow)) {
                    dep[v] = dep[u] + 1;
                    q.push(v);
                }
            }
        }
        return dep[T];
    }

    int dfs(int u, int flow) {
        if ((u == T) || (!flow)) return flow;

        int ret = 0;
        for (int& i = cur[u]; ~i; i = e[i].nxt) {
            int v = e[i].v, d;
            if ((dep[v] == dep[u] + 1) &&
                (d = dfs(v, min(flow - ret, e[i].cap - e[i].flow)))) {
                ret += d;
                e[i].flow += d;
                e[i ^ 1].flow -= d;
                if (ret == flow) return ret;
            }
        }
        return ret;
    }

    void dinic() {
        while (bfs()) {
            memcpy(cur, fir, sizeof(int) * (n + 1));
            maxflow += dfs(S, INF);
        }
    }
} mf;

int main(){
    int t;
    scanf("%d",&t);
    int n,m,S,T;
    int u,v,w;
    while(t--)
    {
        scanf("%d%d%d%d",&n,&m,&S,&T);
        mf.init(n,S,T);
        while(m--)
        {
            scanf("%d%d%d",&u,&v,&w);
            mf.addedge(u,v,w);
        }
        mf.dinic();
        printf("%lld\n",mf.maxflow);
    }
}