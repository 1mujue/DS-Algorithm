#include <stdbool.h>
// Problem: given an array of non-negative integers, you are initially positioned at the first index of the array.
// Each element in the array represents your MAXIMUM JUMP DISTANCE at that position.
// You need to judge whether you can reach the last index.

// the length of nums is in [1, 10^4]
// 0 <= nums[i] <= 10^5

// Algorithm: we just need to calculate the FARTEST position we can reach.
// IF we have reached a position that is greater than the farthest position we can reach, 
// then we can't reach the last index. If the farthest position we can reach is 
// greater than or equal to the last index, then we can reach the last index.
// The time complexity is O(n) and the space complexity is O(1).
bool canJump(int* nums, int numsSize) {
    int reach = 0;
    for(int i = 0; i < numsSize; i++){
        if(i > reach) return false;
        reach = fmax(reach, nums[i] + i);
    }
    return reach >= numsSize - 1;
}