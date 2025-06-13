#include <math.h>

// 对double类型判断是否为0
#define EPS 1e-6
int isZero(double v)
{
	return fabs(v) < EPS;
}

// 最大公约数
int gcd(int a, int b)
{
    int tmp;
	while (b != 0) {
		tmp = a;
        a = b;
		b = tmp % b;
	}
	return a;
}

// 最小公倍数 注意如果a和b都可能取到int最大值则要取longlong
int lcm(int a, int b)
{
    return a / gcd(a, b) * b;
}
