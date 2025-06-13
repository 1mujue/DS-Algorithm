#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define VOLUME 1000007

typedef struct GraphNode
{
    int target;
    int weight;
    struct GraphNode *next;
} GNode;

typedef struct HeapNode
{
    int u;
    int distance;
}HNode;

GNode* graph[VOLUME];
int pre[VOLUME];
int visited[VOLUME];
int distance[VOLUME]; // 从给定起点起算的最短距离

HNode Heap[VOLUME];
int Heap_Size;
void insertHeap(int u,int distance);
void keepHeap(int id);
HNode deleteHeap();
void init(int n, int s);
void insertNode(int u, int v, int w);
void dijkstra(int n, int s);

int main()
{
    int n, m, s;
    scanf("%d%d%d", &n, &m, &s);
    int u, v, w;
    init(n, s);
    for (int i = 0; i < m; i++)
    {
        scanf("%d%d%d", &u, &v, &w);
        insertNode(u, v, w);
    }
    dijkstra(n, s);
    for (int i = 1; i <= n; i++)
        printf("%d ", distance[i]);
    return 0;
}

void init(int n, int s)
{
    for (int i = 1; i <= n; i++)
    {
        if (i == s)
        {
            pre[i] = i;
            distance[i] = 0;
            visited[i] = 0;
        }
        else
        {
            pre[i] = -1;
            distance[i] = INT_MAX
            ;
            visited[i] = 0;
        }
    }
}

void insertNode(int u, int v, int w)
{
    GNode* p = (GNode*)malloc(sizeof(GNode));
    p->target = v;
    p->weight = w;
    p->next = graph[u];
    graph[u] = p;
}

void dijkstra(int n, int s)
{
    int min = INT_MAX;
    insertHeap(s,distance[s]);
    HNode temp;
    int u,dis;
    while(Heap_Size != 0)
    {
        temp = deleteHeap();
        u = temp.u;
        if(visited[u] != 0)
            continue;
        visited[u] = 1;
        for(GNode* p = graph[u];p != NULL;p = p->next)
        {
            int v = p->target;
            if(distance[v] > distance[u] + p->weight)
            {
                distance[v] = distance[u] + p->weight;
                if(!visited[v])
                    insertHeap(v,distance[v]);
            }
        }
    }
}

void insertHeap(int u,int distance)
{
    Heap_Size++;
    int i = Heap_Size - 1;
    while(i > 0)
    {
        if(Heap[(i - 1) / 2].distance > distance)
        {
            Heap[i] = Heap[(i - 1) / 2];
            i = (i - 1) / 2;
        }
        else
            break;
    }
    Heap[i].u = u;
    Heap[i].distance = distance;
}

void keepHeap(int id)
{
    int smallest = id;
    if(id * 2 + 1 < Heap_Size)
    {
        if(Heap[id * 2 + 1].distance < Heap[smallest].distance)
            smallest = id * 2 + 1;
    }
    if(id * 2 + 2 < Heap_Size)
    {
        if(Heap[id * 2 + 2].distance < Heap[smallest].distance)
            smallest = id * 2 + 2;
    }
    if(smallest != id)
    {
        HNode temp = Heap[id];
        Heap[id] = Heap[smallest];
        Heap[smallest] = temp;
        keepHeap(smallest);
    }
}
HNode deleteHeap()
{
    Heap_Size--;
    HNode temp = Heap[0];
    Heap[0] = Heap[Heap_Size];
    keepHeap(0);
    return temp;
}