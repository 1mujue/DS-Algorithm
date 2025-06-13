// problem link: https://leetcode.cn/problems/maximum-difference-between-even-and-odd-frequency-ii/description/

#include <limits.h>
#include <math.h>
#define BUCK 5
#define LEN 30005

int getBin(int first, int second){
    int ans = 0;
    ans |= (first & 1) << 1;
    ans |= (second & 1);
    return ans;
}
int getTar(int bin){
    return (bin + 2) % 4;
}
int maxDifference(char* s, int k) {
    int rec[BUCK][LEN] = {0};
    int slen = strlen(s);
    for(int i = 0; i < slen; i++){
        int ind = s[i] - '0';
        for(int j = 0; j < BUCK; j++){
            rec[j][i + 1] = rec[j][i] + (j == ind);
        }
    }
    // for the r:
    // find the l, that rec[i][r] - rec[i][l] is odd,
    // and rec[j][r] - rec[j][l] is even,
    // and rec[i][r] - rec[j][r] - (rec[i][l] - rec[j][l]) is the max.
    // Therefore, we can maintain the MINIMUM of rec[i][k] - rec[j][k] where
    // k is in [0, m - 1], and the m is the right point.
    // Also, we need to mark the odd and even situation.

    int delta[LEN][2] = {0};
    int minSum[4][LEN];
    int top[4][2] = {0};

    int ans = INT_MIN;
    // The first is odd, the second is even.
    for(int i = 0; i < BUCK; i++){
        for(int j = 0; j < BUCK; j++){
            if(i == j) continue;
            // let 0 represent even, 1 represent odd.
            // then 00, 01, 10, 11 can represent 4 situations.
            memset(top, 0, sizeof(int) * 8);
            minSum[0][top[0][1]++] = 0;

            for(int it = 0; it < slen; it++){
                delta[it + 1][0] = rec[i][it + 1] - rec[j][it + 1];
                delta[it + 1][1] = getBin(rec[i][it + 1], rec[j][it + 1]);
            }
            for(int it = 0; it < slen; it++){
                int sit = delta[it + 1][1];
                int tar = getTar(sit);
                int l, r;

                l = top[tar][0], r = top[tar][1];
                while(l + 1 < r && it - minSum[tar][l + 1] + 1 >= k){
                    l++;
                }
                int minInd = minSum[tar][l];
                if(l != r && rec[j][it + 1] - rec[j][minInd] != 0 && it -minInd + 1 >= k){
                    ans = fmax(ans, delta[it + 1][0] - delta[minInd][0]);
                }
                top[tar][0] = l, top[tar][1] = r;

                l = top[sit][0], r = top[sit][1];

                if(l == r || delta[minSum[sit][r - 1]][0] > delta[it + 1][0]){
                    minSum[sit][r++] = it + 1;
                }
                top[sit][0] = l, top[sit][1] = r;
            }
        }
    }
    return ans;
}