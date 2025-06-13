// Problem: given an array composed by 0 and 1, you can reverse
// 0 to 1 or 1 to 0 each step. What's is the least step to make
// the front of the array are ALL 0 and the back of the array are
// ALL 1? The length of the array is in [1, 10^5].
#include <limits.h>
#define LEN 100002
int minFlipsMonoIncr(char* s) {
    // There must be a border, where [0, border) is all 0, and
    // [border, slen - 1] is all 1. Now every index i can be the answer,
    // so we just need to calculate how many 1 is in [0, i), and how many
    // zero is in [i, slen - 1], and the ans would be the minimum of 
    // the sum of them.

    // Here, oneCnt[i] is the number of 1 in [0, i - 1] ([0, i))
    // zeroCnt[i] is the number of 0 in [i, slen - 1].
    int oneCnt[LEN] = {0}, zeroCnt[LEN] = {0};
    int slen = strlen(s);
    for(int i = 0;i < slen; i++){
        oneCnt[i + 1] = oneCnt[i] + s[i] - '0';
        zeroCnt[slen - 1 - i] = zeroCnt[slen - i] + 1 - (s[slen - 1 - i] - '0');
    }
    int ans = INT_MAX;
    // Here we will traverse each border and take the minimum of sum of
    // oneCnt and zeroCnt as the answer.
    for(int i = 0;i <= slen; i++){
        ans = fmin(ans, oneCnt[i] + zeroCnt[i]);
    }
    return ans;
}