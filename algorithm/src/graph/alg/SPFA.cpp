// problem link: https://www.luogu.com.cn/problem/P3385

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

#include <bits/stdc++.h>

using namespace std;

struct Edge{
    int v;
    int w;
};

vector<vector<Edge>> graph;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int tt;
    cin >> tt;

    while(tt--){
        int n, m;
        cin >> n >> m;
        graph.clear();
        graph.resize(n + 1);
        while(m--){
            int u, v, w;
            cin >> u >> v >> w;
            if(w >= 0){
                graph[u].push_back({v, w});
                graph[v].push_back({u, w});
            }
            else{
                graph[u].push_back({v, w});
            }
        }

        vector<int> dis(n + 1, INT_MAX);
        // caution: the vis here is to ** prevent ** the same node appearing
        // in the queue for multiple times. After we pop it from the queue,
        // the vis tag could be 0.
        vector<int> vis(n + 1, 0);
        // the count here represents the count of relaxation.
        vector<int> cnt(n + 1, 0);

        deque<int> q;
        q.push_back(1);
        dis[1] = 0;
        vis[1] = 1;

        int isNegRing = 0;
        while(!q.empty()){
            int curr = q.front();
            q.pop_front();
            vis[curr] = 0;

            for(const Edge& e : graph[curr]){
                int next = e.v;
                if(dis[curr] + e.w < dis[next]){
                    dis[next] = dis[curr] + e.w;
                    cnt[next] = cnt[curr] + 1;
                    if(cnt[next] >= n){
                        isNegRing = 1;
                        break;
                    }
                    
                    if(!vis[next]){
                        vis[next] = 1;
                        q.push_back(next);
                    }
                }
            }
            if(isNegRing) break;
        }
        if(isNegRing){
            cout << "YES\n";
        }
        else{
            cout << "NO\n";
        }
    }
    return 0;
}