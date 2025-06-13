#include <stdio.h>
#include <string.h>
#define MAX(a, b) (a) > (b) ? (a) : (b)
#define VOLUME 2007

char str1[VOLUME], str2[VOLUME];

int dpC[VOLUME][VOLUME], dpD[VOLUME][VOLUME];

int max_conse;

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        max_conse = 0;
        scanf(" %s %s", str1, str2);
        int len1 = strlen(str1);
        int len2 = strlen(str2);


        for(int i = 0;i < len1;i++)
            dpC[i][0] = dpD[i][0] = 0;
        for(int i = 0;i < len2;i++)
            dpC[0][len2] = dpD[0][len2] = 0;
        for (int i = 1; i <= len1; i++)
        {
            for (int j = 1; j <= len2; j++)
            {
                if (str1[i - 1] == str2[j - 1])//最长公共子串
                {
                    dpC[i][j] = dpC[i - 1][j - 1] + 1;
                    if (dpC[i][j] > max_conse)
                        max_conse = dpC[i][j];
                }
                else
                {
                    dpC[i][j] = 0;
                }

                if (str1[i - 1] == str2[j - 1])//这是最长公共子序列
                {
                    dpD[i][j] = dpD[i - 1][j - 1] + 1;
                }
                else
                {
                    dpD[i][j] = MAX(dpD[i - 1][j], dpD[i][j - 1]);
                }
            }
        }


        printf("%d %d\n", max_conse, dpD[len1][len2]);
    }
    return 0;
}
