#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define VOLUME 300007

typedef struct complex
{
    double x;
    double y;
} C, *Cp;

C addComplex(C a1, C a2);
C subComplex(C a1, C a2);
C mulComplex(C a1, C a2);
C divComplex(C a1, C a2);
void init();
void FFT(C a[], int inv);
void workFFT(C a[], C b[], C c[], int len1, int len2);
void reverse(int n);

double PI;
int bit, total;
int rev[VOLUME];
int res[VOLUME];

C a[VOLUME];//注意每一个元素的定义：a[0]表示的是指数为0的项，a[0].x表示其实部的系数，a[0].y表示其
//虚部的系数。
//FFT的应用情形:
/*
1.高精度乘法；-> 123 = 1 * 10^2 + 2 * 10^1 + 3 * 10^0，因此两个大数相乘，就是将每个数位
作为指数为k - 1位的数的系数，然后相乘，然后逆变换，然后就可以得出结果。
2.卷积：实际上卷积才是FFT的底层原理。
*/
C b[VOLUME];
C c[VOLUME];

int main()
{
    PI = acos(-1);
    char tempa[VOLUME], tempb[VOLUME];
    int len1, len2;
    int T;
    scanf("%d", &T);
    while (T--)
    {   
        init();
        scanf(" %s %s", tempa, tempb);
        len1 = strlen(tempa) - 1;
        len2 = strlen(tempb) - 1;
        
        for (int i = 0; i <= len1; i++)
        {
            a[i].x = tempa[len1 - i] - '0';
            a[i].y = 0;
        }
        for (int i = 0; i <= len2; i++)
        {
            b[i].x = tempb[len2 - i] - '0';
            b[i].y = 0;
        }
        workFFT(a, b, c, len1, len2);

        int len = len1 + len2;
        int i = 0;
        while (i <= len)
        {
            if (res[i] >= 10)
            {
                res[i + 1] += res[i] / 10;
                if (i == len)
                    len++;
                res[i] %= 10;
            }
            i++;
        }

        while (res[len] == 0 && len > 0)
            len--;
        for (int i = len; i >= 0; i--)
            printf("%d", res[i]);
        printf("\n");
    }
    return 0;
}
void init()
{
    bit = 0,total = 0;
    for(int i = 0;i < VOLUME;i++)
    {
        res[i] = 0;
        a[i].x = b[i].x = 0;
        a[i].y = b[i].y = 0;//需要注意的是，因为FFT涉及到补位问题，因此，
        //虽然我们输入的是n位，但是在过程中会进行拓展，因此需要刷新
    }
}
C addComplex(C a1, C a2)
{
    C temp;
    temp.x = a1.x + a2.x;
    temp.y = a1.y + a2.y;
    return temp;
}
C subComplex(C a1, C a2)
{
    C temp;
    temp.x = a1.x - a2.x;
    temp.y = a1.y - a2.y;
    return temp;
}
C mulComplex(C a1, C a2)
{
    C temp;
    temp.x = a1.x * a2.x - a1.y * a2.y;
    temp.y = a1.x * a2.y + a1.y * a2.x;
    return temp;
}
C divComplex(C a1, C a2)
{
    C temp;
    temp.x = (a1.x * a2.x + a1.y * a2.y) / (a2.x * a2.x + a2.y + a2.y);
    temp.y = (-a1.x * a2.y + a1.y * a2.x) / (a2.x * a2.x + a2.y + a2.y);
    return temp;
}
void FFT(C a[], int inv)//迭代实现FFT
{
    C temp;
    C w1, wk, wt1, wt2;
    for (int i = 0; i < total; i++)
    {
        if (i < rev[i])
        {
            temp = a[i];
            a[i] = a[rev[i]];
            a[rev[i]] = temp;
        }
    }

    for (int mid = 1; mid < total; mid <<= 1)
    {
        w1.x = cos(PI / mid);
        w1.y = inv * sin(PI / mid);

        for (int i = 0; i < total; i += mid * 2)
        {
            wk.x = 1;
            wk.y = 0;
            for (int j = 0; j < mid; j++, wk = mulComplex(wk, w1))
            {
                wt1 = a[i + j];
                wt2 = a[i + j + mid];
                wt2 = mulComplex(wt2, wk);
                a[i + j] = addComplex(wt1, wt2);
                a[i + j + mid] = subComplex(wt1, wt2);
            }
        }
    }
}
void workFFT(C a[], C b[], C c[], int len1, int len2)
{
    while ((1 << bit) < len1 + len2 + 1)
        bit++;
    total = 1 << bit;
    reverse(total);

    FFT(a, 1);
    FFT(b, 1);

    for (int i = 0; i < total; i++)
        c[i] = mulComplex(a[i], b[i]);

    FFT(c, -1);//FFT逆变换
    for (int i = 0; i <= len1 + len2; i++)
        res[i] = (int)(c[i].x / total + 0.5);//取整数
}
void reverse(int n)
{
    for (int i = 0; i < n; i++)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
}