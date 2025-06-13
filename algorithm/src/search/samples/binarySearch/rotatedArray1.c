// Given a sorted array which is ROTATED, that is, an array like [1, 2, 3, 4, 5],
// if rotated by 2 positions, becomes [3, 4, 5, 1, 2]. Now, given a target value,
// you should judge whether the target is in the array. If it is in the array, return
// its index, otherwise return -1. You must write an algorithm with O(log n) runtime
// complexity. It is guaranteed that the array does not contain duplicates.

int search(int* nums, int numsSize, int target) {
    int left = 0, right = numsSize - 1;
    while(left <= right){
        int mid = (left + right) / 2;
        if(nums[mid] == target) return mid;
        // [left, mid] is ordered.
        if(nums[left] <= nums[mid]){
            // in this case, target CAN'T be in [left, mid],
            // therefore, the next searching area
            // is [mid + 1, right].
            if(target < nums[left] || target > nums[mid]){
                left = mid + 1;
            }
            // else, target is in [left, mid]. Since we have judged
            // that nums[mid] != target, the next searching area 
            // is [left, mid - 1]
            else {
                right = mid - 1;
            }
        }
        // [mid, right] is ordered.
        else if(nums[mid] <= nums[right]){
            // in this case, target CAN'T be in [mid, right],
            // therefore, the next searching area
            // is [left, mid - 1].
            if(target < nums[mid] || target > nums[right]){
                right = mid - 1;
            }
            // else, target is in [mid, right]. Since Since we have judged
            // that nums[mid] != target, the next searching area
            // is [mid + 1, right]
            else {
                left = mid + 1;
            }
        }
    }
    return -1;
}