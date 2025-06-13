// the third version of binary search.

int bs3(int* nums, int numsSize, int target){
    int ret = -1;
    int left = 0, right = numsSize - 1;
    while(left + 1 < right){
        int mid = (right - left) / 2 + left;
        if(nums[mid] == target) {
            ret = mid;
            break;
        }
        else if(nums[mid] < target) left = mid;
        else right = mid;
    }
    if(nums[left] == target) ret = left;
    else if(nums[right] == target) ret = right;
    return ret;
}