#include <stdio.h>
#include <stdlib.h>
#define MAXM 407
#define MAXN 407
#define LENGTH 407
//二分图匹配！！
typedef struct charm
{
    int self_charm;
    int expected_charm;
    // int target;
    // struct charm *next;
} C, *Cp;

C males[LENGTH], females[LENGTH];
int M, N;            // 分别代表左右测集合的数量，此题未用到，这样写是作为模板
int map[MAXM][MAXN]; // 邻接矩阵存图
int pre[MAXN];       // 右侧元素对应的左侧元素
int visited[MAXN];   // 记右侧元素是否被访问

int match(int i, int n); // 找到左侧元素编号为i的匹配项

int main()
{
    int n;
    int cnt = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &males[i].self_charm);
    for (int i = 1; i <= n; i++)
        scanf("%d", &males[i].expected_charm);
    for (int i = 1; i <= n; i++)
        scanf("%d", &females[i].self_charm);
    for (int i = 1; i <= n; i++)
        scanf("%d", &females[i].expected_charm);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (females[j].self_charm >= males[i].expected_charm && males[i].self_charm >= females[j].expected_charm)
                map[i][j] = 1;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        if (match(i, n) == 1)
            cnt++;
    }
    printf("%d", cnt);
    return 0;
}

int match(int i, int n)
{
    for (int j = 1; j <= n; j++)
    {
        if (map[i][j] && !visited[j])
        {
            visited[j] = 1;
            if (pre[j] == 0 || match(pre[j], n))
            {
                pre[j] = i;
                return 1;
            }
        }
    }
    return 0;
}