// Problem: given an array, and we will take 3 indexs: i, j, k, 0 <= i < j <= k,
// let a = arr[i] ^ arr[i + 1] ^ ... ^ arr[j - 1],
// b = arr[j] ^ arr[j + 1] ^ ... ^ arr[k],
// if a == b, we will say (i, j, k) is the target.
// You need to find how many such (i, j, k) and return it.
// The length of the array is in [1, 300], and the element's value
// is in [1, 10^8]
#define LEN 302
int countTriplets(int* arr, int arrSize) {
    // key idea: if a == b, then a ^ b == 0,
    // so arr[i - 1] ^ a ^ b == arr[k], that is arr[i - 1] == arr[k].
    // for each j in [i + 1, k], (i, j, k) is the answer.
    int xor[LEN] = {0};
    for(int i = 0; i < arrSize; i++){
        xor[i + 1] = xor[i] ^ arr[i];
    }
    int ans = 0;
    for(int i = 0;i < arrSize; i++){
        for(int k = i + 1; k < arrSize; k++){
            if(xor[i] == xor[k + 1]) ans += k - i;
        }
    }
    return ans;
}