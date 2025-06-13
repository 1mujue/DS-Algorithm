#include <math.h>
// the problem: given a number n, k and maxPts. From 0 start, each time
// you can add a number in [1, maxPts]. If the num is bigger than k, you CAN'T
// add anymore. The question is, what's the probability that the end number is
// not bigger than n.
double new21Game(int n, int k, int maxPts) {
    // dp[i]: start from i, the probability that the end number is not bigger than n. 
    double dp[k + maxPts + 1];
    double fix = 1.0 / maxPts;
    for(int i = 0; i <= k + maxPts; i++) dp[i] = 0.0;
    for(int i = k; i <= k + maxPts; i++){
        dp[i] = i <= n;
    }
    // dp[k - 1] = dp[k ... k - 1 + maxPts] -> 
    // only when i is in [k, min(n, k - 1 + maxPts)], dp[i] is 1.
    // so the count of dp[i] == 1 is min(n - k + 1, k - 1 + maxPts - k + 1)
    // = min(n - k + 1, maxPts).
    if(k - 1 >= 0) dp[k - 1] = fmin(maxPts, n - k + 1) / (maxPts);
    for(int i = k - 2; i >= 0; i--){
        // dp[i] = dp[i + 1... i + maxPts] * fix
        // dp[i - 1] = dp[i ... i + maxPts - 1] * fix
        // dp[i - 1] = (dp[i] - dp[i + maxPts] + dp[i]) * fix
        dp[i] = dp[i + 1] + (dp[i + 1] - dp[i + 1 + maxPts]) * fix;      
    }
    return dp[0];
}

int main(){
    return 0;
}