// the second version of binary search.

int bs2(int* nums, int numsSize, int target){
    int ret = -1;
    // the search range would be [left, right)
    int left = 0, right = numsSize;
    while(left < right){
        int mid = (right - left) / 2 + left;
        if(nums[mid] == target) {
            ret = mid;
            break;
        }
        // in this case, [left, mid] is ALL smaller than target
        // so the search range should be [mid + 1, right)
        else if(nums[mid] < target) left = mid + 1;
        // similarily, [mid, right) is ALL larger than target
        // so the search range should be [left, mid)
        else right = mid;
    }
    // end condition: left == right, and apparently,
    // we miss the element nums[left] !!
    // Therefore, we have to check if nums[left] == target
    // if you have broken the loop in advance, then it will change
    // NOTHING.
    if(left < numsSize && nums[left] == target) ret = left;
    return ret;
}