// problem link: https://www.luogu.com.cn/problem/P2168
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

struct TrieNode{
    ll val;
    ll h;
    int k;
    TrieNode(ll val, ll h, int k): val(val), h(h), k(k){}
};

struct TrieCmp{
    bool operator()(const TrieNode* e1, const TrieNode* e2) const {
        if(e1->val == e2->val){
            return e1->h > e2->h;
        }
        return e1->val > e2->val;
    }
};


int main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int n, k;
    cin >> n >> k;

    priority_queue<TrieNode*, vector<TrieNode*>, TrieCmp> pq;
    for(int i = 0; i < n; i++){
        ll val;
        cin >> val;
        pq.push(new TrieNode(val, 0, 0));
    }

    while((pq.size() - 1) % (k - 1)){
        pq.push(new TrieNode(0, 0, 0));
    }

    ll ans = 0;
    while(pq.size() >= k){
        int lim = min(k, (int)pq.size());
        ll fh = -1;
        ll w = 0;
        TrieNode* v = new TrieNode(0, 0, lim);

        for(int i = 0; i < lim; i++){
            TrieNode* nv = pq.top();
            pq.pop();
            v->val += nv->val;
            w += nv->val;
            fh = max(fh, nv->h + 1);
        }
        ans += w;
        v->h = fh;
        v->val = w;
        pq.push(v);
    }
    cout << ans << '\n' << pq.top()->h;
    return 0;
}