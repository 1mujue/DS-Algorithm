#include <stdio.h>
//快速幂法
long long binpow(long long a,long long b);

int main()
{
    long long a,b;
    scanf("%lld%lld",&a,&b);
    printf("%lld",binpow(a,b));
    return 0;
}

long long binpow(long long a,long long b)
{
    if(b == 0)
        return 1;
    long long res = binpow(a, b / 2);//实质上是将指数部分不断二分，实质上
    //就是将指数拆分成若干个2的次幂之和(可以这样想，每当二分一次，因为接下来还要乘2,
    //所以如果可以一直二分，将结果反向整理（乘2的次幂），就可以得到原本的指数部分）
    //而很显然这样的时间复杂度就只有O(log2n)
    if(b % 2 != 0)
        return res * res * a;
    else
        return res * res;
}
//拓展：因为乘法并不会影响取模，所以再进行乘法运算时可以取模，保证数据的范围。