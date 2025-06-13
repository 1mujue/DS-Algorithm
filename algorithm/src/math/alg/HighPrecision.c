// #include <stdio.h>
// #include <math.h>
// #define sign(x) ((x) > (0) ? (1) : (-1))

// long long multi(int a, int b, int len1, int len2);

// long long multi(int a, int b, int len1, int len2)
// {
//     a = (a > 0 ? a : -a);
//     b = (b > 0 ? b : -b);
//     int s = sign(a) * sign(b);
//     if(len1 == 0 || len2 == 0)
//         return 0;
//     else if(len1 == 1 && len2 == 1)
//         return (long long)s * a * b;
//     int A, B, C, D;
//     int num1 = len1 / 2;
//     int num2 = len1 - num1;
//     int num3 = len2 / 2;
//     int num4 = len2 - num3;
//     A = a / pow(10, num1);
//     B = a - A;
//     C = b / pow(10, num2);
//     D = b - C;
//     long long AC = multi(A, C, num1, num3);
//     long long BD = multi(B, D, num2, num4);
//     long long delta = multi((int)(A*pow(10,num1))-B,num2,(D-(int)(C*pow(10,num3))),num4);
//     long long res = AC * (long long)pow(10,num1 + num3) * 2 + delta + 2 * BD ;
//     return s * res;
// }

// the code above aims to illustrate how the programming work.

#include <stdio.h>
#include <string.h>
#define LENGTH 2007
char num1[LENGTH],num2[LENGTH];
int num3[2 * LENGTH];
int main()
{
    scanf(" %s",num1);
    scanf(" %s",num2);
    int len1 = strlen(num1),len2 = strlen(num2);
    int len3 = len1 + len2; + 1;
    for(int i = len1 - 1;i >= 0;i--)
        for(int j = len2 - 1;j >= 0;j--)
            num3[len1 - 1 - i + len2 - 1 - j] += (num1[i] - '0') * (num2[j] - '0');
    for(int i = 1;i < len3;i++)
    {
        num3[i] += num3[i - 1] / 10;
        num3[i - 1] = num3[i - 1] % 10;
    }
    while(num3[len3 - 1] == 0 && len3 > 1)
        len3 = len3 - 1;
    for(int i = len3 - 1;i >= 0;i--)
        printf("%d",num3[i]);
    return 0;
}