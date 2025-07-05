// problem link: https://leetcode.cn/problems/count-the-number-of-arrays-with-k-matching-adjacent-elements/
#define MOD 1000000007
#define ll long long

ll fastPow(ll val, ll index){
    ll ans = 1;
    ll base = val;
    while(index){
        if(index & 1) ans = ans * base % MOD;
        base = base * base % MOD;
        index >>= 1;
    }
    return ans;
}
ll calcStep(ll val){
    ll ans = 1;
    while(val){
        ans = ans * val % MOD;
        val -= 1;
    }
    return ans;
}
ll calcRecv(ll val){
    return fastPow(val, MOD - 2);
}
// 这个题目对于排列组合的理解十分关键。
// 由于有k个相等的对子，所以整个数组可以被拆分为n - k个块，每一个块的
// 内部取值都是相等的。需要注意到，一个块可以只包含一个元素，所以必定满足上述描述。
// 那么对于arr[i] != arr[i + 1]的这种情况，其实就可以把它看作是“隔板”。注意，这个隔板
// 是“插在arr[i]和arr[i + 1]之间”的，表示arr[i]和arr[i + 1]不可能是一个块。
// 那么现在问题就变成了经典的排列组合问题。首先，arr[i]和arr[i + 1]之间的“间隙”一共有n - 1个，
// 而有k个i满足arr[i] == arr[i + 1]，所以隔板的数量就是n - 1 - k。
// 于是，我们就直接计算C_{n-1}^{n-1-k}便可。
// 接着，我们来考虑第一个块。显然，第一个块可以选取m个值中的任意一个，所以是m个选择。
// 之后，后续的每一个块的取值都必须和前一个块不一样，也就是(m - 1) ^ {n - k - 1}中选择。
// 所以最终答案是 C_{n-1}^{n-1-k} * m * (m - 1) ^ {n - k - 1}.
// 这道题需要掌握快速幂和乘法逆元。
int countGoodArrays(int n, int m, int k) {
    ll c1 = calcStep(n - 1);
    ll c2 = calcStep(n - 1 - k);
    ll c3 = calcStep(k);
    ll c = c1 * calcRecv(c2) % MOD * calcRecv(c3) % MOD;
    ll mpow = fastPow(m - 1, n - k - 1);
    ll ans = c * m % MOD * mpow % MOD;
    return ans;
}