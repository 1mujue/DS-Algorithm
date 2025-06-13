// problem link: https://www.luogu.com.cn/problem/P3373
#include <bits/stdc++.h>
using namespace std;

#define ll long long

#define LAZY_ADD_TAG 0
#define LAZY_MUL_TAG 1


struct STNode{
    ll value;
    ll lazyAddTag;
    ll lazyMulTag;
};

vector<STNode> st;

inline int leftChild(int root){
    return root * 2 + 1;
}
inline int rightChild(int root){
    return root * 2 + 2;
}

void lazyAddUpdate(int root, int left, int right, ll val, int mod){
    st[root].lazyAddTag = (st[root].lazyAddTag + val) % mod;
    st[root].value = (st[root].value + (right - left + 1) * val) % mod;
}

void lazyMulUpdate(int root, int left, int right, ll val, int mod){
    st[root].lazyAddTag = st[root].lazyAddTag * val % mod;
    st[root].lazyMulTag = st[root].lazyMulTag * val % mod;
    st[root].value = st[root].value * val % mod;
}

void pushDown(int root, int left, int right, int mod){
    int lc = leftChild(root), rc = rightChild(root);
    int mid = (left + right) / 2;

    ll lazyAdd = st[root].lazyAddTag;
    ll lazyMul = st[root].lazyMulTag;

    if(lazyMul != LAZY_MUL_TAG){
        lazyMulUpdate(lc, left, mid, lazyMul, mod);
        lazyMulUpdate(rc, mid + 1, right, lazyMul, mod);
    }
    if(lazyAdd != LAZY_ADD_TAG){
        lazyAddUpdate(lc, left, mid, lazyAdd, mod);
        lazyAddUpdate(rc, mid + 1, right, lazyAdd, mod);
    }
    

    st[root].lazyAddTag = LAZY_ADD_TAG;
    st[root].lazyMulTag = LAZY_MUL_TAG;
}

void build(int root, int left, int right, vector<int>& arr, int mod){
    st[root].lazyAddTag = LAZY_ADD_TAG;
    st[root].lazyMulTag = LAZY_MUL_TAG;
    if(left == right){
        st[root].value = arr[left] % mod;
        return;
    }
    int lc = leftChild(root), rc = rightChild(root);
    int mid = (left + right) / 2;

    build(lc, left, mid, arr, mod);
    build(rc, mid + 1, right, arr, mod);

    st[root].value = (st[lc].value + st[rc].value) % mod;
}

void updateAddRange(int root, int left, int right, int uleft, int uright, ll val, int mod){
    if(left > uright || right < uleft){
        return;
    }
    if(left >= uleft && right <= uright){
        lazyAddUpdate(root, left, right, val, mod);
        return;
    }
    int lc = leftChild(root), rc = rightChild(root);
    int mid = (left + right) / 2;

    pushDown(root, left, right, mod);
    updateAddRange(lc, left, mid, uleft, uright, val, mod);
    updateAddRange(rc, mid + 1, right, uleft, uright, val, mod);

    st[root].value = (st[lc].value + st[rc].value) % mod;
}

void updateMulRange(int root, int left, int right, int uleft, int uright, ll val, int mod){
    if(left > uright || right < uleft){
        return;
    }
    if(left >= uleft && right <= uright){
        lazyMulUpdate(root, left, right, val, mod);
        return;
    }
    int lc = leftChild(root), rc = rightChild(root);
    int mid = (left + right) / 2;

    pushDown(root, left, right, mod);
    updateMulRange(lc, left, mid, uleft, uright, val, mod);
    updateMulRange(rc, mid + 1, right, uleft, uright, val, mod);

    st[root].value = (st[lc].value + st[rc].value) % mod;
}

ll query(int root, int left, int right, int qleft, int qright, int mod){
    if(left > qright || right < qleft){
        return 0;
    }
    if(left >= qleft && right <= qright){
        return st[root].value;
    }
    int lc = leftChild(root), rc = rightChild(root);
    int mid = (left + right ) / 2;

    pushDown(root, left, right, mod);

    ll ans = 0;
    ans += query(lc, left, mid, qleft, qright, mod);
    ans = (ans + query(rc, mid + 1, right, qleft, qright, mod)) % mod;
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n, q, m;
    cin >> n >> q >> m;

    vector<int> arr(n);
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }
    
    st.resize(4 * n);
    build(0, 0, n - 1, arr, m);

    while(q--){
        int op, x, y;
        cin >> op >> x >> y;
        x--;
        y--;
        if(op == 1){
            ll k;
            cin >> k;
            updateMulRange(0, 0, n - 1, x, y, k, m);
        }
        else if(op == 2){
            ll k;
            cin >> k;
            updateAddRange(0, 0, n - 1, x, y, k, m);
        }
        else if(op == 3){
            ll que = query(0, 0, n - 1, x, y, m);
            cout << que << '\n';
        }
    }
    return 0;
}