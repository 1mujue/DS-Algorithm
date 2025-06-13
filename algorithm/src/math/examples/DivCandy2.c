// problem link: https://leetcode.cn/problems/distribute-candies-among-children-ii/
#define ll long long
long long distributeCandies(int n, int limit) {
    ll ans = 0;
    // i + j + k <= n, i <= limit, j <= limit, k <= limit.
    // clearly, i is in [0, fmin(limit, n)].
    // i + j <= n, therefore, j <= n - i. Also, j <= limit and j >= 0.
    // for k, k == n - i - j and k <= limit. Therefore, n - i - j <= limit.

    // 1. i >= 0, i <= fmin(limit, n)
    // 2. i + j <= n, j >= 0, j <= limit
    // 3. n - i - j <= limit, n - i - j >= 0.

    // if i is certain: j >= n - i - limit. j >= 0
    // j <= n - i, j <= limit. Therefore, we just need to iterate 0 to fmin(n, limit) as i,
    // and count the number of j.

    for(int i = 0; i <= fmin(limit, n); i++){
        ans += fmax((fmin(n - i, limit) - fmax(n - i - limit, 0) + 1), 0);
    }
    return ans;
}