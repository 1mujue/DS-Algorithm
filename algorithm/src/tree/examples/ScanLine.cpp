// problem link: https://www.luogu.com.cn/problem/P1884
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Event{
    int y, x1, x2, type;
    bool operator<(const Event& e) const {
        return y < e.y;
    }
};

vector<int> xs; // all x loc.
vector<Event> events;

inline int leftChild(int root){
    return root * 2 + 1;
}
inline int rightChild(int root){
    return root * 2 + 2;
}

struct SegmentTree{
    int n;
    // 覆盖次数
    vector<int> coverCnt;
    // 覆盖总长度
    vector<int> len;
    SegmentTree(int size) : n(size), coverCnt(4 * size), len(4 * size){}

    void update(int root, int left, int right, int uleft, int uright, int type){
        if(left > uright || right < uleft){
            return;
        }
        if(left >= uleft && right <= uright){
            coverCnt[root] += type;
        }
        else{
            int mid = (left + right) / 2;
            int lc = leftChild(root), rc = rightChild(root);
            update(lc, left, mid, uleft, uright, type);
            update(rc, mid + 1, right, uleft, uright, type);
        }

        if(coverCnt[root]){
            len[root] = xs[right + 1] - xs[left];
        }
        else{
            int lc = leftChild(root), rc = rightChild(root);
            len[root] = len[lc] + len[rc];
        }
    }

    int query(){
        return len[0];
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int nn;
    cin >> nn;

    xs.resize(2 * nn);
    events.resize(2 * nn);

    for(int i = 0; i < nn; i++){
        int x1, x2, y1, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        
        xs[2 * i] = x1;
        xs[2 * i + 1] = x2;

        events[2 * i].x1 = events[2 * i + 1].x1 = x1;
        events[2 * i].x2 = events[2 * i + 1].x2 = x2;

        events[2 * i].y = y2;
        events[2 * i].type = 1;
        
        events[2 * i + 1].y = y1;
        events[2 * i + 1].type = -1;
    }

    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());

    auto getIndex = [](int x){
        return lower_bound(xs.begin(), xs.end(), x) - xs.begin();
    };

    sort(events.begin(), events.end());
    for(auto& event : events){
        event.x1 = getIndex(event.x1);
        event.x2 = getIndex(event.x2);
    }

    SegmentTree st(xs.size());
    ll ans = 0;
    for(int i = 0; i < events.size() - 1; i++){
        int x1 = events[i].x1, x2 = events[i].x2, y = events[i].y, type = events[i].type;
        st.update(0, 0, xs.size() - 1, x1, x2 - 1, type);
        int coverLen = st.query();
        int deltaY = events[i + 1].y - y;
        ans += 1ll * coverLen * deltaY;
    }
    cout << ans;
    return 0;
}