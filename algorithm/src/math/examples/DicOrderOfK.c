// problem link: https://leetcode.cn/problems/k-th-smallest-in-lexicographical-order/description/

// THIS IS VERY BEAUTIFUL! It is a use of Trie Tree!!
// For example, let's take a look at the tree starts with 1.
// Its children will include 10, 11, 12, ..., 19
// Do this recursively: 100, 101, ..., 190, 191, ..., 199

// Now, for kth number in n, if the size of the tree starts
// with m is less OR equal to k, then the number CAN'T be in the tree
// starts with m, therefore, we can let k = k - m.
// If the size of the tree starts with m is greater than k,
// then the number must be in the SUBTREE of the tree.

// Two situations operation can be simplified like this:
// 1. k = k - size of tree m, and m = m + 1 (the brother of m)
// 2. k--, m = m * 10.


#define ll long long
// if n = 15, curr = 1, then the fit numbers are 1, 10, 11, 12, 13, 14, 15
// therefore, we will return 7.
int getStep(int curr, int n){
    ll start = curr, last = curr;
    int ans = 0;
    while(start <= n){
        ans += (last - start + 1);
        start = start * 10, last = fmin(last * 10 + 9, n);
    }
    return ans;
}

int findKthNumber(int n, int k) {
    // start with 1.
    int curr = 1;
    k--;
    while(k){
        int step = getStep(curr, n);
        // in this case, the answer WOULD'T be in the tree begins with curr.
        if(k >= step){
            k -= step;
            curr++;
        }
        // in this case, the answer MUST be in the subtree of tree begins with curr.
        else{
            curr = curr * 10;
            k--;
        }
    }
    return curr;
}