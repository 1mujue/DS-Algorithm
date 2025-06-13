// Shell Sort is a KEY sort algorithm which first
// break the O(n^2)'s curse.
// generally speaking, Shell Sort would repeat Select
// Sort for many times, but each time the object arrays
// are different. 
// The object array is decided by interval. for i in 
// [0, interval - 1], we will take arr[i], arr[i + interval],
// arr[i + 2 * interval], ... as the object array.
// The last interval of select sort is 1.
// For example, [84,83,88,87,61,50,70,60,80,99], intervals are
// [5, 2, 1], then the first object array is:
// [84, 50], [83, 70], [88, 60], [87, 80], [61, 99],
// after insert sort, the array would be 
// [50, 84], [70, 83], [60, 88], [80, 87], [61, 99].
// the second object array would be:
// [50, 70, 60, 80, 61], [84, 83, 88, 87, 99].

void shellSort(int* arr, int len){
    for(int gap = len / 2; gap > 0; gap /= 2){
        // in humans' habit, we might like to sort one 
        // object array before another, but it is not 
        // effective.
        for(int i = gap; i < len; i++){
            int curNum = arr[i];
            int prevInd = i - gap;
            while(prevInd >= 0 && curNum < arr[prevInd]){
                arr[prevInd + gap] = arr[prevInd];
                prevInd -= gap;
            }
            arr[prevInd + gap] = curNum;
        }
    }
}

// However, the time complex of Shell Sort mainly depends on
// values of intervals. There are three famous interval sequnces:
// Hibbard: Dk = 2^k - 1, [1, 3, 7, 15, ...]
// Knuth: D1 = 1, D(k+1) = 3 * Dk + 1, [1, 4, 13, 40,...]
// Sedgewick: [1, 5, 19, 41, 109, ...], and the element of the seq
// is calculated by 9 * 4^k - 9 * 2^k + 1  or 4^k - 3 * 2^k + 1.
