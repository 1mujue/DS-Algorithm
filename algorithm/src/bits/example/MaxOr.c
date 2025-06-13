// problem: given an int nums and an int k, you should
// return the maxinum of nums[0] | nums[1] | ... | nums[n-1]
// (where n is the length of the nums) AFTER you LEFT SHIFT
// ANY element in the nums for k TIMES.
// for example, if nums = [1, 2, 3], k = 1, then the result
// should be 3, since 1 | 2 | (3 << 1) = 7, which is the max.

// n is in [1, 10^5], nums[i] is in [1, 10^9], k is in [1, 15]


#define LEN 100002
#define MAX(a, b) ((b) > (a) ? (b) : (a))

// Although we can left shift any element each time, and just need
// to make sure the total number of left shift is k, since we are 
// doing OR operation, it would be better to left shift one element
// ONLY.

// Therefore, the quesions is to find the maximum of nums[0] | nums[1] | ... | 
// (nums[i] << k) | ... | nums[n - 1], where i is in [0, n - 1].
// Clearly, we can use a prefix sum and suffix sum array to record the OR result
// of nums[0, i - 1] and nums[i + 1, numsSize - 1] respectively, and the ans 
// whould be the max of (((long long)nums[i]) << k) | pre[i] | suf[i + 1].

// The time complexity is O(n), and the space complexity is O(n).
long long maximumOr1(int* nums, int numsSize, int k) {
    // pre[i + 1]: the or result of nums[0, i].
    // suf[i]: the or result of nums[i, numsSize - 1].
    long long pre[LEN] = {0}, suf[LEN] = {0};
    for(int i = 0; i < numsSize; i++){
        pre[i + 1] = pre[i] | nums[i];
        suf[numsSize - 1 - i] = suf[numsSize - i] | nums[numsSize - 1 - i];
    }
    long long ans = 0;
    for(int i = 0;i < numsSize; i++){
        ans = fmax(ans, (((long long)nums[i]) << k) | pre[i] | suf[i + 1]);
    }
    return ans;
}

// The reason we create prefix and suffix sum array is that we need to record
// the OR result when we remove nums[i]. Can we do that in O(1) space? Of course!
// In OR operation, if there is at least two '1' in the same bit, then after removing
// any ONE element, the bit will still be '1'. Therefore, we can use a variable(allOr) to
// record the OR result of all elements, and another variable(fixed) to record those
// '1' bits. 
long long maximumOr2(int* nums, int numsSize, int k) {
    int allOr = 0, fixed = 0;
    for(int i = 0;i < numsSize; i++){
        int n = nums[i];
        // if allOr and n has same '1' bits, then the bit is fixed.
        fixed |= allOr & n;
        allOr |= n;
    }
    long long ans = 0;
    for(int i = 0; i < numsSize; i++){
        long long n = nums[i];
        // remove n from allOr might remove some '1' bits, so we need to add them back.
        // That is, (allOr ^ n) | fixed.
        ans = MAX(ans, (allOr ^ n) | fixed | (n << k));
    }
    return ans;
}