#include <stdlib.h>
// question: given a tree represented by an array of edges, find the diameter of the tree.
// the diameter of a tree is the longest path between two nodes in a tree.
#define NODE_CNT 10002

// the node in the graph. We will handle the tree
// as a graph since the diameter has no direction.
typedef struct TNode{
    int to;
    struct TNode* next;
}TNode;

// the constructor of the node in the graph.
TNode* new(int to, TNode* next){
    TNode* ans = (TNode*)malloc(sizeof(TNode));
    ans->to = to;
    ans->next = next;
    return ans;
}

// BFS return value. We will return the MOST faraway node
// and the distance from the ROOT node.
typedef struct {
    int node;
    int dis;
} BFSRet;

BFSRet bfs(int root, TNode* graph[], int* vis){
   int queue[NODE_CNT];
   int slow = 0, fast = 0;
   queue[fast++] = root;
   vis[root] = 1;
   int dis = -1;
   BFSRet ret;
   while(slow < fast){
        dis++;
        ret.dis = dis;
        // you need to record how many nodes in the current layer.
        // These nodes have SAME distance to the root node !!
        int layerCnt = fast - slow;
        for(int i = 0;i < layerCnt; i++){
            int node = queue[slow + i];
            ret.node = node;
            for(TNode* p = graph[node]; p; p = p->next){
                if(!vis[p->to]){
                    vis[p->to] = 1;
                    queue[fast++] = p->to;
                }
            }
        }
        slow += layerCnt;
   }
   return ret;
}

int treeDiameterBFS(int** edges, int edgesSize, int* edgesColSize) {
    TNode* graph[NODE_CNT];
    int vis[NODE_CNT];
    for(int i = 0;i < NODE_CNT; i++) {
        graph[i] = NULL;
        vis[i] = 0;
    }
    for(int i = 0;i < edgesSize; i++){
        int u = edges[i][0], v = edges[i][1];
        TNode* n1 = new(v, graph[u]), *n2 = new(u, graph[v]);
        graph[u] = n1;
        graph[v] = n2;
    }

    // the first BFS would get the node that is the "border" of the tree.
    BFSRet r1 = bfs(0, graph, vis);
    for(int i = 0;i < NODE_CNT; i++) vis[i] = 0;
    // from the "border" node, we can get the most faraway node, and the 
    // distance would be the diameter of the tree.
    BFSRet r2 = bfs(r1.node, graph, vis);

    return r2.dis;
}

int ans;

int dfs(int root, TNode* graph[], int* vis){
    int firstMax = INT_MIN, secondMax = INT_MIN;
    for(TNode* p = graph[root]; p; p = p->next){
        if(!vis[p->to]){
            vis[p->to] = 1;
            int ret = dfs(p->to, graph, vis);
            if(ret > firstMax){
                secondMax = firstMax;
                firstMax = ret;
            }
            else if(ret > secondMax){
                secondMax = ret;
            }
        }
    }
    // the node is a leaf node.
    if(firstMax == INT_MIN && secondMax == INT_MIN){
        return 0;
    }
    int len = 0;

    if(firstMax != INT_MIN){
        len += firstMax + 1;
    }
    if(secondMax != INT_MIN){
        len += secondMax + 1;
    }
    ans = fmax(ans, len);
    return firstMax + 1;
}

int treeDiameterDFS(int** edges, int edgesSize, int* edgesColSize) {
    ans = 0;
    TNode* graph[NODE_CNT];
    int vis[NODE_CNT];
    for(int i = 0;i < NODE_CNT; i++){
        graph[i] = NULL;
        vis[i] = 0;
    }

    for(int i = 0;i < edgesSize; i++){
        int u = edges[i][0], v = edges[i][1];
        TNode* n1 = new(v, graph[u]), *n2 = new(u, graph[v]);
        graph[u] = n1;
        graph[v] = n2;
    }
    
    vis[0] = 1;
    dfs(0, graph, vis);
    return ans;
}