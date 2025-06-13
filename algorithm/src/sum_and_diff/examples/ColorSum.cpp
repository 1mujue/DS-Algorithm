// problem link: https://www.luogu.com.cn/problem/P2671
#include <bits/stdc++.h>
#include <unordered_map>
#include <unordered_set>

#define MOD 10007
using namespace std;
using ll = long long;

// The main quesion is, can we calculate this in O(n)??
// (A1 + A2) * (B1 + B2) + (A1 + A3) + (B1 + B3) + (A2 + A3) * (B2 + B3) +..
// The answer is, YES!!
// it can be approved that it is equals to sum(Ai) * sum(Bi) + (n - 2)sum(AiBi).
// Therefore, we can use presum to do this.

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> colors(2 * m);
    vector<ll> numbers(n);

    for(int i = 0; i < n; i++){
        cin >> numbers[i];
    }

    for(int i = 0; i < n; i++){
        int color;
        cin >> color;
        color -= 1;
        colors[2 * color + (i & 1)].push_back(i);
    }

    ll ans = 0;
    vector<vector<ll>> valpresum(2 * m);
    vector<vector<ll>> indpresum(2 * m);
    vector<vector<ll>> mulpresum(2 * m);
    for(int i = 0; i < 2 * m; i++){
        int cursize = colors[i].size();
        valpresum[i].resize(cursize + 1);
        indpresum[i].resize(cursize + 1);
        mulpresum[i].resize(cursize + 1);

        valpresum[i][0] = indpresum[i][0] = mulpresum[i][0] = 0;
        for(int j = 0; j < cursize; j++){
            indpresum[i][j + 1] = (indpresum[i][j] + colors[i][j] + 1) % MOD;
            valpresum[i][j + 1] = (valpresum[i][j] + numbers[colors[i][j]]) % MOD;
            mulpresum[i][j + 1] = (mulpresum[i][j] + (colors[i][j] + 1) * numbers[colors[i][j]] % MOD) % MOD;
        }

        ans = (ans + indpresum[i][cursize] * valpresum[i][cursize] % MOD + (cursize - 2) * mulpresum[i][cursize] % MOD) % MOD;
    }
    cout << ans;
    return 0;
}