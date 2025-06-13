// problem link: https://leetcode.cn/problems/minimum-moves-to-make-array-complementary/

#include <limits.h>
#define VOL 100007

int minMoves(int* nums, int numsSize, int limit) {
    // key: if we want to minimize the operation time, AT THE FIRST GLANCE, 
    // we should find the MOST frequently apprear sum value of nums[i] + nums[n - 1 - i].

    // However, we can find that, if the sum value is V, for nums[i]:
    // if nums[i] + nums[n - 1 - i] == V, then we DON'T need to change, the ans is 0;
    // if 1 + fmin(nums[i], nums[n - 1 - i]) <= V <= limit + fmax(nums[i], nums[n - 1 - i]),
    // then we ONLY need to change one number, the ans is 1;
    // Otherwise, the ans is 2.

    // Therefore, we can create an array to record for each V, how many operations we need 
    // to do. Since nums[i] < limit, the smallest and the biggest value is 2 and 2 * limit.

    // THen we can find that, we need to change A RANGE OF consecutive V, therefore, we can
    // use DIFF array.

    int rec[2 * VOL] = {0};
    int ml = 2, mr = 2 * limit;

    for(int i = 0; i < numsSize / 2; i++){
        rec[ml] += 2;
        rec[mr + 1] -= 2;

        int ul = 1 + fmin(nums[i], nums[numsSize - 1 - i]);
        int ur = limit + fmax(nums[i], nums[numsSize - 1 - i]);
        rec[ul] -= 1;
        rec[ur + 1] += 1;

        int cursum = nums[i] + nums[numsSize - 1 - i];
        rec[cursum] -= 1;
        rec[cursum + 1] += 1;
    }

    int ans = INT_MAX;
    int curans = 0;
    for(int i = 2; i <= 2 * limit; i++){
        curans += rec[i];
        ans = fmin(ans, curans);
    }
    return ans;
} 