// problem link: https://www.luogu.com.cn/problem/P1072
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#define ll long long
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define VOL 200004

// gcd(x, y) == k -> gcd(x / k, y / k) == 1.
// gcd(x, y) == x * y / lcm(x, y) -> gcd(lcm(x, y) / y, lcm(x, y) / x) == 1!

ll getGCD(ll mx, ll mn){
    while(mx % mn != 0){
        ll t = mn;
        mn = mx % mn;
        mx = t;
    }
    return mn;
}
ll getLCM(ll mx, ll mn){
    return mx / getGCD(mx, mn) * mn;
}

int main(){
    int n;
    scanf("%d", &n);
    while(n--){
        int a0, a1, b0, b1;
        scanf("%d%d%d%d", &a0, &a1, &b0, &b1);
        int amul = a0 / a1;
        int bmul = b1 / b0;
        int limit = sqrt(b1);
        int ans = 0;
        for(int i = 1; i <= limit; i++){
            if(b1 % i == 0 && i % a1 == 0) {
                int amul2 = i / a1, bmul2 = b1 / i;
                ans += getGCD(MAX(amul2, amul), MIN(amul2, amul)) == 1 && getGCD(MAX(bmul2, bmul), MIN(bmul2, bmul)) == 1;
            }

            int i2 = b1 / i;
            if(i2 != i && b1 % i == 0 && i2 % a1 == 0){
                int amul3 = i2 / a1, bmul3 = b1 / i2;
                ans += getGCD(MAX(amul3, amul), MIN(amul3, amul)) == 1 && getGCD(MAX(bmul3, bmul), MIN(bmul3, bmul)) == 1;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}