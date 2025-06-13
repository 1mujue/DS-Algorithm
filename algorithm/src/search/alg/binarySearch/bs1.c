// the first version of binary search. 
// if you want to use binary search, you have to make sure
// the array is "sorted".

// return the index of fitted element. If there is no such
// element, then return -1.
int bs1(int* nums, int numsSize, int target){
    int ret = -1;
    // The search range would be [left, right].
    int left = 0, right = numsSize - 1;
    while(left <= right){
        int mid = (right - left) / 2 + left;
        if(nums[mid] == target) {
            ret = mid;
            break;
        }
        // in this case, [left, mid] is ALL smaller than target
        // so the search range should be [mid + 1, right]
        else if(nums[mid] < target) left = mid + 1;
        // similarily, [mid, right] is ALL larger than target
        // so the search range should be [left, mid - 1]
        else right = mid - 1;
    }
    // end condition: left == right + 1
    return ret;
}