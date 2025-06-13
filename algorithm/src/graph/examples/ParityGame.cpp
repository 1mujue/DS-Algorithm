// problem link: https://www.luogu.com.cn/problem/P5937

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define VOL 20004

int root[VOL];

void init(int bound){
    for(int i = 0; i < bound; i++){
        root[i] = i;
    }
}

int findRoot(int x){
    if(root[x] != x){
        root[x] = findRoot(root[x]);
    }
    return root[x];
}

void merge(int x, int y){
    int rx = findRoot(x), ry = findRoot(y);
    if(rx != ry){
        root[ry] = rx;
    }
}

// the use of EXTENTED UNION.
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    
    vector<int> lefts(m), rights(m);
    vector<int> discrete(2 * m);
    vector<int> ops(m);

    int left, right;
    string op;

    for(int i = 0; i < m; i++){
        cin >> left >> right >> op;
        if(op == "even") ops[i] = 1;
        else ops[i] = 0;
        lefts[i] = left - 1;
        rights[i] = right;
        discrete[2 * i] = left - 1;
        discrete[2 * i + 1] = right;
    }

    sort(discrete.begin(), discrete.end());
    int dissize = unique(discrete.begin(), discrete.end()) - discrete.begin();
    init(2 * dissize);

    for(int i = 0; i < m; i++){
        lefts[i] = lower_bound(discrete.begin(), discrete.begin() + dissize, lefts[i]) - discrete.begin();
        rights[i] = lower_bound(discrete.begin(), discrete.begin() + dissize, rights[i]) - discrete.begin();
    }

    for(int i = 0; i < m; i++){
        if(ops[i] == 1){
            if(findRoot(lefts[i]) == findRoot(rights[i] + dissize)) {
                cout << i;
                return 0;
            }
            merge(lefts[i], rights[i]);
            merge(lefts[i] + dissize, rights[i] + dissize);
        }
        else{
            if(findRoot(lefts[i]) == findRoot(rights[i])){
                cout << i;
                return 0;
            }
            merge(lefts[i], rights[i] + dissize);
            merge(lefts[i] + dissize, rights[i]);
        }
    }

    cout << m;
    return 0;
}