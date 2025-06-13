// problem link: https://www.luogu.com.cn/problem/P1714
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#define ll long long
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define VOL 500005

// Key thought: for index i, the presum[i + 1] is determinated,
// and we want to find index j in [MAX(0, i - m), i - 1] that presum[j + 1] 
// is the smallest, and then presum[i + 1] - presum[j + 1] would be the max.

// For j1 < j2, if presum[j2 + 1] < presum[j1 + 1], then presum[j1 + 1] CAN'T 
// be the smallest one, since j2 is closer to i and presum[j2 + 1] is smaller,
// therefore, we don't need to consider j1. Only when presum[j2 + 1] > presum[j1 + 1]
// shall we need to talk.

// Although presum[j1 + 1] < presum[j2 + 1], j1 might NOT in [MAX(0, i - m), i - 1] since
// it is smaller, and then we might need to remove it.
// Otherwise, the answer is STILL presum[i + 1] - presum[j1 + 1].

// This is Monotonic Queue!! If j2 > j1 and presum[j2 + 1] < presum[j1 + 1],
// then we let right ptr minus 1 (pop_back); If j1 not in [MAX(0, i - m), i - 1],
// then we let left ptr plus 1 (pop_front).

// Then, the element j in Monotonic Queue satisfy two characters:
// 1. j is in [MAX(0, i - m), i - 1]
// 2. for any j1 and j2, if the index of j1 is less than j2 (index in Monotonic Queue),
// then presum[j1] < presum[j2].

int cakes[VOL];
ll presum[VOL];
ll queue[VOL];

int main(){
    int n, m;
    scanf("%d%d", &n, &m);

    ll ans = LLONG_MIN;
    for(int i = 0; i < n; i++){
        scanf("%d", cakes + i);
        presum[i + 1] = presum[i] + cakes[i];
        // This is because we must at least eat one cake.
        ans = MAX(ans, cakes[i]);
    }

    int left = 0, right = 0;
    // caution: presum[i + 1] = sum(cakes[0...i]), and the queue stocks
    // i + 1 !! Therefore, presum[0] here means sums(cakes[0, -1]), which is 0.
    queue[right++] = 0;

    for(int i = 0; i < n; i++){
        // satisfy character 1.
        while(i + 1 - queue[left] > m){
            left++;
        }
        if(right != left){
            ans = MAX(ans, presum[i + 1] - presum[queue[left]]);
        }
        // satisfy character 2.
        while(right != left && presum[i + 1] < presum[queue[right - 1]]){
            right--;
        }
        // the queue stocks i + 1 !!
        queue[right++] = i + 1;
    }
    printf("%lld", ans);
    return 0;
}   