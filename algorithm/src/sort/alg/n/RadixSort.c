#include <math.h>
// Radix Sort: if we want to compare 102, 304, 991, 992,
// we can say that, 102 must be less than 304 because 
// 1 < 3 (100), but we don't know which one is bigger: 
// 991 or 992 because 9 == 9 (100). Only when we see 
// 1 < 2 (1) that we know 991 < 992. This is how Radix Sort
// works. As a matter of fact, the example above is 
// based on MSD(Most Significant Digital). There is another
// way called LSD(Least Significant Digital).
// Surprisingly, LSD is much easier (we will say it later.)

// the procedures of Radix Sort are as follow:
// 1. get the Max Digit Length ({1, 10, 100} then MDL is 3)
// 2. get the radix of each number in array
// 3. traverse the array for MDL times and sort it by radix each time.

// LSD version. for MSD, since the comparison should ONLY
// happen between two numbers with the SAME pre-radixes, it is
// much harder(because the sort on lower digit in MSD would
// change the sort result on higher digit). For example,
// {91, 92, 63} if we sort on 10, then the res is {63, 91, 92},
// and then if we sort on 1, then the res is {91, 92, 63}
void LSDRadixSort(int* arr, int len){
    // find the max number first.
    int max = 0;
    for(int i = 0;i < len;i++){
        max = fmax(abs(arr[i]), max);
    }

    // calculate the Max Digit Length.
    int maxDigLen = 0;
    while(max){
        maxDigLen++;
        max /= 10;
    }

    // take negative number into consideration.
    // we use Counting Sort here.
    // [-9, 9] -> [0, 18]
    int counting[19];
    int* temp = (int*)malloc(sizeof(int) * len);
    int dev = 1;
    for(int i = 0;i < maxDigLen; i++){
        // fill counting with 0.
        for(int j = 0;j < 19; j++) counting[j] = 0;

        for(int j = 0;j < len; j++){
            int radix = arr[j] / dev % 10 + 9;
            counting[radix]++;
        }

        counting[0]--;
        for(int j = 1;j < 19; j++) counting[j] += counting[j - 1];

        for(int j = len - 1;j >= 0;j--){
            int radix = arr[j] / dev % 10 + 9;
            temp[counting[radix]] = arr[j];
            counting[radix]--;
        }

        for(int j = 0;j < len; j++) arr[j] = counting[j];
        dev *= 10;
    }
} 