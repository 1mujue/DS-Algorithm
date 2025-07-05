// problem link: https://www.luogu.com.cn/problem/P4568
#include <bits/stdc++.h>
using namespace std;

// the classic practice of graph with MULTIPLE layers.
// Since we can take at most k times FREE flight, we can build
// k + 1 layers graph. When there is an edge between node 'a' and 'b',
// we can connect 'a' and 'b' in ALL LAYERS, and connect 'a' in ith layer
// with 'b' in (i + 1)th layer, and connect 'b' in the ith layer with
// 'a' in (i + 1)th layer. When crossing the layer, the weight of edge 
// is 0 (since it is free).

const int MAXN = 100005;
const int MAXK = 11;
const int INF = INT_MAX;

struct Edge {
    int to, w;
};

vector<Edge> adj[MAXN * MAXK];

int d[MAXN * MAXK];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n, m, k;
    cin >> n >> m >> k;

    int s, t;
    cin >> s >> t;

    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        for (int j = 0; j <= k; j++) {
            adj[a + j * n].push_back({b + j * n, c});
            adj[b + j * n].push_back({a + j * n, c});
        }
        for (int j = 0; j < k; j++) {
            adj[a + j * n].push_back({b + (j+1)*n, 0});
            adj[b + j * n].push_back({a + (j+1)*n, 0});
        }
    }

    // Usually, d[t + k * n] MUST be the smallest node, but there might be 
    // some confusing test case that break the case, we we can connect 
    // t in ALL layers.
    for(int i = 0; i <= k - 1; i++){
        adj[t + i * n].push_back({t + (i + 1) * n, 0});
    }

    if(s == t){
        cout << 0;
        return 0;
    }

    int total_nodes = n * (k+1);

    for (int i = 0; i < total_nodes; i++) {
        d[i] = INF;
    }

    using PII = pair<int,int>;
    priority_queue<PII, vector<PII>, greater<PII>> pq;

    d[s] = 0;
    pq.push({0, s});

    while (!pq.empty()) {
        auto [dist, u] = pq.top(); pq.pop();
        if (d[u] < dist) continue;
        for (auto e : adj[u]) {
            int v = e.to;
            int w = e.w;
            if (d[u] + w < d[v]) {
                d[v] = d[u] + w;
                pq.push({d[v], v});
            }
        }
    }

    int ans = d[t + k * n];
    if (ans == INF)
        cout << "INF\n";
    else
        cout << ans << "\n";

    return 0;
}
