#include <limits.h>
// Problem: given an array of non-negative integers, you are initially positioned at the first index of the array.
// Each element in the array represents your MAXIMUM JUMP DISTANCE at that position.
// Your goal is to reach the last index in the MINIMUM number of jumps.
// You can assume that you can always reach the last index.

// the length of nums is in [1, 10^4],
// 0 <= nums[i] <= 10^5

// Algorithm: We can use the greedy algorithm to solve this problem.
// For each jump, we should choose the postion that, after we jump to it,
// then we can jump to the FARTHEST position. 
int jump2(int* nums, int numsSize) {
    if(numsSize == 1) return 0;
    int jumpInd = 0;
    int step = 0;
    while(1){
        int jumpLen = nums[jumpInd];
        if(jumpInd + jumpLen >= numsSize - 1) return step + 1;
        int nextJumpInd = jumpInd, maxDis = INT_MIN;
        for(int i = jumpInd; i <= jumpInd + jumpLen; i++){
            if(i + nums[i] > maxDis){
                maxDis = i + nums[i];
                nextJumpInd = i;
            }
        }
        step++;
        jumpInd = nextJumpInd;
    }
    return step;
}