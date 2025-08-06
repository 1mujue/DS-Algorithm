// problem link: https://www.luogu.com.cn/problem/P1966
#include <bits/stdc++.h>

// this problem would help you to understand the meaning of "SORT".
// It can be easily proven that, only when a and b is in increasing order will
// the sum be the minimum. Therefore, the direct way to do it is:

// sort a and b, and then caculate the step for a and b to be in increasing order.

// However, if a is [1, 3, 2, 4], b is ALSO [1, 3, 2, 4], then we DON'T need to 
// sort a and b. That is to tell us, if we want the answer to be minimum, we need 
// to make sure that, ith element in a is in the SAME POSITION as ith element in b.

// Therefore, we can sort a and b FIRST, but record the original index. In this case,
// the answer MUST be the same. Now that we have the original index, if we fix b, and 
// what we need to do is to CHANGE array a to be in the same order as b.

// For example, if a is [1, 3, 2, 4], b is [4, 2, 1, 3], after sort, the ORIGIN INDEX is
// [0, 2, 1, 3] and [2, 1, 3, 0]. Now, let arr[b[i]] = a[i], then we JUST NEED to 
// calculate the number of inversions in arr.

// Why this is true? Because if we want to fix b, then we need to change the order of 
// [0, 2, 1, 3] to be [2, 1, 3, 0]. We can "think" b is SORTED, and we need to "SORT" a.
// We can do a transfer. Let b be [k1, k2, k3, k4], then a' is [k4, l1, k2, k3].
// and we will get a' by a'[b[i]] = a[i].

using namespace std;
using ll = long long;

#define MOD 99999997
#define VOL 100004

vector<int> t1(VOL, 0), t2(VOL, 0);
ll merge(vector<int>& arr, int left, int right){
    int mid = (left + right) / 2;

    int l1 = mid - left + 1, l2 = right - mid;
    for(int i = 0; i < l1; i++){
        t1[i] = arr[i + left];
    }
    for(int i = 0; i < l2; i++){
        t2[i] = arr[i + mid + 1];
    }

    ll ans = 0;

    int t1ind = 0, t2ind = 0, arrInd = left;
    while(t1ind < l1 && t2ind < l2){
        if(t1[t1ind] < t2[t2ind]){
            arr[arrInd++] = t1[t1ind++];
        }
        else{
            ans = (ans + l1 - t1ind) % MOD;
            arr[arrInd++] = t2[t2ind++];
        }
    }

    while(t1ind < l1){
        arr[arrInd++] = t1[t1ind++];
    }
    while(t2ind < l2){
        arr[arrInd++] = t2[t2ind++];
    }

    return ans;
}
ll mergeSort(vector<int>& arr, int left, int right){
    if(left >= right) return 0;
    ll ans = 0;
    int mid = (left + right) / 2;
    ans = (ans + mergeSort(arr, left, mid)) % MOD;
    ans = (ans + mergeSort(arr, mid + 1, right)) % MOD;
    ans = (ans + merge(arr, left, right)) % MOD;
    return ans;
}

bool cmp(const pair<int, int>& e1, const pair<int, int>& e2){
    return e1.first < e2.first;
}

int main(){
    int n;
    cin >> n;

    vector<pair<int, int>> aa(n), bb(n);
    
    for(int i = 0; i < n; i++){
        cin >> aa[i].first;
        aa[i].second = i;
    }
    for(int i = 0; i < n; i++){
        cin >> bb[i].first;
        bb[i].second = i;
    }

    sort(aa.begin(), aa.end(), cmp);
    sort(bb.begin(), bb.end(), cmp);

    vector<int> naa(n);
    for(int i = 0; i < n; i++){
        naa[bb[i].second] = aa[i].second;
    }

    ll ans = mergeSort(naa, 0, n - 1);
    cout << ans;
    return 0;
}   

