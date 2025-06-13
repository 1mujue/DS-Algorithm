// https://leetcode.cn/problems/distribute-candies-among-children-iii/
#include <math.h>

#define ll long long 
long long distributeCandies(int n, int limit) {
    ll ans = 0;
    // i >= 0, i <= fmin(n, limit)
    // j >= 0, j <= fmin(n, limit), i + j <= n
    // k = n - i - j, k >= 0, k <= fmin(n, limit).
    // once i, j is determined, k is determined.
    // for a fixed i:
    // i + j <= n, j <= n - i.
    // j <= fmin(n, limit), so j <= fmin(n - i, limit)
    // k <= fmin(n, limit), n - i - j <= limit,
    // j >= n - i - limit, so j >= fmax(0, n - i - limit)

    // there are 4 situations.

    // 1 n - i is min, 0 is max -> n - i <= limit, n - i - limit <= 0. this is very GOOD !!
    // 2 n - i is min, n - i - limit is max -> n - i <= limit, n - i - limit > 0. This is impossible.
    // 3 limit is min, 0 is max -> n - i > limit, n - i - limit <= 0. this is impossible.
    // 4 limit is min, n - i - limit is max -> n - i > limit, n - i - limit > 0. This is very GOOD.

    // in 1, the delta is n - i - 0 + 1 = n - i + 1.
    // in 4, the delta is limit - (n - i - limit) + 1 = 2 * limit + 1 + i - n.
    // Therefore, we can do MATH.
    
    // in 1: n - i <= limit, i >= n - limit. i >= 0, therefore, i >= fmax(n - limit, 0),
    // i <= fmin(limit, n).
    int s1lower = fmax(n - limit, 0), s1upper = fmin(limit, n);
    int cnt1 = s1upper - s1lower + 1;
    // in 4: n - i > limit, i < n - limit, therefore, i >= 0, i <= fmin(n - limit - 1, limit).
    // Additionally, n - i - limit <= limit, i >= n - 2 * limit.
    // we need to calc the sum from fmax(0, n - 2 * limit) to fmin(n - limit - 1, limit).
    int s4lower = fmax(0, n - 2 * limit), s4upper = fmin(n - limit - 1, limit);
    int cnt4 = s4upper - s4lower + 1;

    if(cnt1 >= 0){
        ans += (ll)cnt1 * (n + 1);
        ans -= ((ll)s1lower + s1upper) * cnt1 / 2;
    }
    
    if(cnt4 >= 0){
        ans += (ll)cnt4 * (2 * limit - n + 1);
        ans += ((ll)s4lower + s4upper) * cnt4 / 2;
    }

    return ans;
}