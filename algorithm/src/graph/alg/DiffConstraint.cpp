//problem link: https://www.luogu.com.cn/problem/P5960
#include <bits/stdc++.h>

using namespace std;

// this is the template of difference constraint problem.
// as we can see, if a - b <= c, then a <= b + c;
// If there are many equations like:
// a - b1 <= c1, a - b2 <= c2, ..., a - bk <= ck,
// then, a = min(b1 + c1, b2 + c2, ..., bk + ck).
// Therefore, we can build a directed graph, and let bi points 
// to a with weight ci. Now, the problem is transformed to
// calculate the SHORTEST PATH in a directed path.
// Since there might be a NAGATIVE RING, we can use SPFA to solve it.

struct Edge{
    int v;
    int w;
};

vector<vector<Edge>> graph;
vector<int> dis;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int n, m;
    cin >> n >> m;
    graph.resize(n + 1);
    dis.resize(n + 1, INT_MAX);

    while(m--){
        int c1, c2, y;
        cin >> c1 >> c2 >> y;
        graph[c2].push_back({c1, y});
    }

    for(int i = 1; i <= n; i++){
        graph[0].push_back({i, 0});
    }

    deque<int> q;
    vector<int> vis(n + 1, 0);
    vector<int> cnt(n + 1, 0);

    q.push_back(0);
    dis[0] = 0;
    vis[0] = 1;

    int isNegRing = 0;

    while(!q.empty()){
        int curr = q.front();
        q.pop_front();
        vis[curr] = 0;

        for(const Edge& e : graph[curr]){
            int next = e.v;
            if(dis[next] > dis[curr] + e.w){
                dis[next] = dis[curr] + e.w;
                cnt[next] = cnt[curr] + 1;
                if(cnt[next] >= n + 1){
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
        cout << "NO";
    }
    else{
        for(int i = 1; i <= n; i++){
            cout << dis[i] << ' ';
        }
    }
    return 0;
}