#include <stdio.h>
#include <stdlib.h>
#define LENGTH 100007
//此题的题设是，有一些的事件需要解决，且有些事件的发生必须要等到其所有的准备工作全部完成
//（比如，我们一定要等穿好袜子之后再穿鞋子），每做一件事情都需要一定的时间，那么现在要求求出
//做完这些事件至少需要的时间。很显然，一件事开始做的最早时间，是这件事情的所有准备工作中完成
//的最晚时间；将这个时间加上做这件事本身需要的时间，就是做完这件事至少需要的时间，很显然我们
//可以从后往前推，运用类似于动态规划的算法，就可以解决这道题目。
typedef struct pointer
{
    int x;
    struct pointer *next;
} P, *Pp;

Pp graph[LENGTH];
int max[LENGTH];

void insertLink(int start, int end);
void DFS(int id, int max);

int main()
{
    int N, M;
    scanf("%d%d", &N, &M);
    int start, end;
    while (M--)
    {
        scanf("%d%d", &start, &end);
        insertLink(end, start);
    }
    // for(int i = 1;i <= N;i++)
    // {
    //     printf("%d : ",i);
    //     for(Pp p = graph[i];p != NULL;p = p->next)
    //         printf("%d ",p->x);
    //     printf("\n");
    // }
    for (int i = N; i >= 1; i--)
        DFS(i, i);
    for (int i = 1; i <= N; i++)
        printf("%d ", max[i]);
    return 0;
}

void insertLink(int start, int end)
{
    Pp p = (Pp)malloc(sizeof(P));
    p->x = end;
    p->next = NULL;
    if (graph[start] != NULL)
        p->next = graph[start];
    graph[start] = p;
    return;
}

void DFS(int id, int MAX)
{
    if (max[id] == 0)
    {
        max[id] = MAX;
        for (Pp p = graph[id]; p != NULL; p = p->next)
            DFS(p->x, MAX);
    }
}

#define LENGTH 5007
#define MOD 80112002
//此题是在计算在一个DAG图（有向无环图）中，到达所有出度为0的点的所有路径；
//核心思路是（其实很多DAG图的核心思路都是这样),将所有入度为0的点的路径数设置为1，
//然后，移除这些入度为0的点即其所有的边，那么很显然总是会有新的入度为0的点产生，
//那么很显然，到达一个点的路径数一定等于所有可以到达这个点的点的路径数之和，因此
//我们在按照上述方法移除一个点的时候，就需要将这个点所有可以到达的点的路径数加上
//到达这个点的路径数，一直到只剩下几个出度为0的点，然后再将其路径数相加，便可以得到
//正确答案！
typedef struct point
{
    int rear;
    struct point *next;
} P, *Pp;

Pp graph[LENGTH];
long long routeNum[LENGTH];
int in[LENGTH];
int out[LENGTH];

void insertElement(int id, int item);

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    int front, rear;
    while (m--)
    {
        scanf("%d%d", &front, &rear);
        insertElement(front, rear);
    }
    // for(int i = 1;i <= n;i++)
    // {
    //     printf("%d : ",i);
    //     for(Pp p = graph[i];p != NULL;p = p->next)
    //         printf("%d ",p->rear);
    //     printf("\n");
    // }
    front = 0, rear = 0;
    int queue[LENGTH];
    for (int i = 1; i <= n; i++)
    {
        if (in[i] == 0)
        {
            routeNum[i] = 1;
            queue[rear++] = i;
        }
    }
    while (front < rear)
    {
        for (Pp p = graph[queue[front]]; p != NULL; p = p->next)
        {
            routeNum[p->rear] += routeNum[queue[front]];
            routeNum[p->rear] %= MOD;
            in[p->rear]--;
            if (in[p->rear] == 0)
                queue[rear++] = p->rear;
        }
        front++;
    }
    long long sum = 0;
    for (int i = 1; i <= n; i++)
    {
        if (out[i] == 0)
        {
            sum += routeNum[i];
            sum %= MOD;
        }
    }
    printf("%lld", sum);
    return 0;
}

void insertElement(int id, int item)
{
    Pp p = (Pp)malloc(sizeof(P));
    p->rear = item;
    p->next = NULL;
    if (graph[id] != NULL)
        p->next = graph[id];
    graph[id] = p;
    out[id]++;
    in[item]++;
    return;
}
