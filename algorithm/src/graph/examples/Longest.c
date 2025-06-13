#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <limits.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) > (b) ? (b) : (a))

#define NODE_CNT 1502
#define EDGE_CNT 50003

int tot;
int head[NODE_CNT];
int to[EDGE_CNT];
int weight[EDGE_CNT];
int next[EDGE_CNT];

void inEdge(int src, int tar, int wei){
    tot++;
    to[tot] = tar;
    weight[tot] = wei;
    next[tot] = head[src];
    head[src] = tot;
}


int main(){
    int n, m;
    scanf("%d%d", &n, &m);

    int in[NODE_CNT] = {0};
    int isHeadZero[NODE_CNT] = {0};
    int dis[NODE_CNT];
    for(int i = 0; i < NODE_CNT; i++){
        dis[i] = INT_MIN;
    }

    isHeadZero[0] = 1;
    dis[0] = 0;
    
    while(m--){
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        u--;
        v--;
        inEdge(u, v, w);
        in[v]++;
    }

    int queue[NODE_CNT];
    int slow = 0, fast = 0;

    for(int i = 0; i < n; i++){
        if(!in[i]){
            queue[fast++] = i;
        }
    }

    while(slow != fast){
        int curnode = queue[slow++];
        for(int eind = head[curnode]; eind; eind = next[eind]){
            int nextnode = to[eind];
            if(isHeadZero[curnode]){
                dis[nextnode] = MAX(dis[nextnode], dis[curnode] + weight[eind]);
                isHeadZero[nextnode] = 1;
            }
            in[nextnode]--;
            if(!in[nextnode]){
                queue[fast++] = nextnode;
            }
        }
    }

    if(dis[n - 1] == INT_MIN){
        printf("%d", -1);
    }
    else{
        printf("%d", dis[n - 1]);
    }
    return 0;
}