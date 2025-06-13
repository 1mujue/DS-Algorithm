// Counting Sort: if each element in array is in a 
// small range, then we can use counting sort.
// the key thought of counting sort is, we will record
// the times of an element showed in the array, and then
// we print each element from small to big (or instead)
// BASED on how many times the element showed in the array.
// For example, {1, 2, 2, 3, 1, 3, 1}, then the record array
// would be: rec[3] = {3, 2, 2} (1 for 3 times, 2 for 2 times, etc.)
// therefore, we just need to print 1 for 3 times, print 2 for 2 times,
// and print 3 for 2 times, and the array is sorted.

// assume that the element in the array belongs to [0, 9999]
#define COUNTING_SORT_RANGE 10000

void countingSort(int* arr, int len){
    int counting[COUNTING_SORT_RANGE];
    for(int i = 0;i < COUNTING_SORT_RANGE; i++) counting[i] = 0;
    for(int i = 0;i < len; i++) counting[arr[i]]++;
    int ind = 0;
    // you can do an optimization: record the min and the max
    // element of the array, and then the loop's range would be
    // [min, max] rather than [0, COUNTING_SORT_RANGE]
    for(int i = 0;i < COUNTING_SORT_RANGE; i++){
        while(counting[i]){
            arr[ind++] = i;
            counting[i]--;
        }
    }
}

// Real Counting Sort: If we just want to sort a pure 
// number array, then counting sort works. However, 
// the counting sort we write above is NOT steady.
// Of course we can define a struct or use sth like
// unordered_map<int, vector<int>> in C++ to make a 
// detailed record, it is not effective. Instead, we just 
// need to know the FIRST location of element ei in sorted array. 
// For example, [1, 1, 2, 2, 2, 2], then the 1st 2 
// should be at arr[2](arr[0] and arr[1] are for 1),
// and the 2nd should be at arr[3].

void realCountingSort(int* arr, int len){
    int counting[COUNTING_SORT_RANGE];
    for(int i = 0;i < COUNTING_SORT_RANGE; i++) counting[i] = 0;
    for(int i = 0;i < len; i++) counting[arr[i]]++;

    // rec how many numbers less than myself(myself is a number)
    int preCounts = 0;
    for(int i = 0;i < COUNTING_SORT_RANGE;i++){
        // the sum of all numbers less or equal to i.
        preCounts += counting[i];
        // the sum of all numbers less than i.
        counting[i] = preCounts - counting[i];
    }

    int* temp = (int*)malloc(sizeof(int) * len);
    for(int i = 0;i < len; i++){
        temp[counting[arr[i]]] = arr[i];
        counting[arr[i]]++;
    }
    for(int i = 0;i < len; i++) arr[i] = temp[i];
}

// in reverse counting sort, we will record the LAST
// location of element ei in sorted array. The method 
// is almost same as the previous one instead it is 
// MORE effective for computer.
void reverseCountingSort(int* arr, int len){
    int counting[COUNTING_SORT_RANGE];
    for(int i = 0;i < COUNTING_SORT_RANGE; i++) counting[i] = 0;
    for(int i = 0;i < len; i++) counting[arr[i]]++;
    // the last location of ei should be the sum of number
    // less or equal to ei minus 1.
    // since 0 is the minimum(assume it), so
    counting[0]--;
    for(int i = 1;i < COUNTING_SORT_RANGE; i++) counting[i] += counting[i - 1];

    int* temp = (int*)malloc(sizeof(int) * len);
    for(int i = len -1; i >= 0; i--){
        temp[counting[arr[i]]] = arr[i];
        counting[arr[i]]--;
    }
    for(int i = 0;i < len; i++) arr[i] = temp[i];
}

// TIPS: if the number is too big, then use unordered_map
// in C++ (or something similar) is a good choice.