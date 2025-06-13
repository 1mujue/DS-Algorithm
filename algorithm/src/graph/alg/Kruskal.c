#include <stdio.h>
#include <stdlib.h>

#define VOLUME 500007
#define LENGTH 100007

typedef struct Edge//克鲁斯卡尔算法是基于边的求最小生成树的贪心算法，每一次都选择一条权重最小的
//边，然后看看这个边的两个端点是否在一个通路中（并查集的运用），如果在就不能选（否则会形成环，就不是
//最小生成树了），直到选的这些边能够把所有的定点都连接起来
{
    int u;
    int v;
    int w;
}E,*Ep;

E edges[VOLUME];
int root[LENGTH];

int cmp(const void *e1,const void *e2);
void initiate(int n);
int findRoot(int x);
void merge(int x,int y);

int main()
{
    int T;
    scanf("%d",&T);
    int n,m;
    long long sum = 0;
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(int i = 1;i <= m;i++)
            scanf("%d%d%d",&edges[i].u,&edges[i].v,&edges[i].w);
        initiate(n);
        qsort(edges,m + 1,sizeof(E),cmp);
        for(int i = 1;i <= m;i++)
        {
            if(findRoot(edges[i].u) != findRoot(edges[i].v))
            {
                merge(edges[i].u,edges[i].v);
                sum += edges[i].w;
            }
        }
        printf("%lld\n",sum);
        sum = 0;
    }
    return 0;
}

int cmp(const void *e1,const void *e2)
{
    Ep a1 = (Ep)e1;
    Ep a2 = (Ep)e2;
    if(a1->w < a2->w)
        return -1;
    else
        return 1;
}

void initiate(int n)
{
    for(int i = 1;i <= n;i++)
    {
        root[i] = i;
    }
}
int findRoot(int x)
{
    if(root[x] == x)
        return x;
    else
    {
        root[x] = findRoot(root[x]);
        return root[x];
    }
}
void merge(int x,int y)
{
    int rx = findRoot(x);
    int ry = findRoot(y);
    if(rx == ry)
        return ;
    else
        root[rx] = ry;
}