// problem link: https://www.luogu.com.cn/problem/P4552

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#define ll long long
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define VOL 100002

int diff[VOL];
int arr[VOL];

int main(){
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d", arr + i);
    }

    diff[0] = arr[0];
    for(int i = 1; i < n; i++){
        diff[i] = arr[i] - arr[i - 1];
    }

    // key idea: we want to make diff[1, n - 1] ALL zero!!
    // we know that, if arr[l...r] += 1, then diff[l] += 1, diff[r + 1] -=1,
    // and arr[l...r] -= 1, then diff[l] -= 1, diff[r + 1] += 1.
    // Therefore, if positive number and negative number appears in diff at the same time,
    // we can let positive number minus 1 and negative number plus 1.

    // If all numbers in diff are positive or negative, 
    // then we can only let positive number minus 1 or negative number plus 1.
    // Note that arr[l...r] +-= 1, diff[l] +-= 1, diff[r + 1] -+= 1, 
    // if we let r == n - 1, then we can let diff[l] plus or minus 1 solely!!

    // so the total opertation times is MIN(|positive sum|, |negative sum|) + 
    // ||positive sum| - |negative sum|| = MAX(|positive sum|, |negative sum|)
    
    // what about the second quesion? it can be converted as how many possible values can diff[0] be!!
    // When let diff[l] plus 1 or minus 1, we can ALSO let diff[0] plus 1 or minus 1. So the possible 
    // count of values of diff[0] is ||positive sum| - |negative sum|| + 1.
    ll posSum = 0, negSum = 0;

    for(int i = 1; i < n; i++){
        if(diff[i] > 0){
            posSum += diff[i];
        }
        else{
            negSum += -diff[i];
        }
    }

    ll ans1 = MAX(posSum, negSum);
    ll ans2 = llabs(posSum - negSum) + 1;
    printf("%lld\n%lld", ans1, ans2);
    return 0;
}
