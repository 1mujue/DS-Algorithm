// Problem: given an int array 'nums', you should return how many
// SUB ARRAYS of it whose odd number count is EXACTLY k.
// the length of nums (numsSize) is in [1, 50000],
// nums[i] is in [1, 10^5], and k is in [1, numsSize].
#define BUCKET_VOL 50002
#define LEN 50001
// key thought: if nums[i,...,j] has exactly k odd numbers, then
// we know, the odd number count in  nums[0, j] minus odd number count
// in nums[0, i - 1] equals to k. 

// I use pre[i + 1] to represent the odd count of nums[0,..., i], then
// at index i, we just need to find the count of j that satisfy
// pre[i + 1] - prev[j + 1] == k, (j <= i), then prev[j + 1] == prev[i + 1] - k.

// Therefore, at index i, we need to get the count of j with prev[j + 1] = prev[i + 1] - k,
// and we can do that by create a 'bucket' array to record how the count of prev[i + 1] - k.
int numberOfSubarrays(int* nums, int numsSize, int k) {
    int bucket[BUCKET_VOL] = {0};
    int pre[LEN] = {0};
    int ans = 0;
    bucket[0] = 1;
    for(int i = 0; i < numsSize; i++){
        pre[i + 1] = pre[i] + (nums[i] & 1);
        if(pre[i + 1] - k >= 0)
            ans += bucket[pre[i + 1] - k];
        bucket[pre[i + 1]]++;
    }
    return ans;
}