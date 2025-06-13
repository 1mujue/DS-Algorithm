// Forward Star is a method to store graph. It is a "simulation":
// we will use array to represent the graph AS IF it is a linked list.

#define NODE_CNT 100001
#define EDGE_CNT 100001
// the number of edges
int tot = 0;
// to[i] is the TO NODE of an edge whose index is i.
int to[EDGE_CNT];
// weights[i] is the weight of an edge whose index is i.
int weights[EDGE_CNT];
// head[i] is the index of the first EDGE of NODE i.
int head[NODE_CNT];
// next[i] is the index of the next EDGE of EDGE i.
int next[EDGE_CNT];

// clearly, the sequence of any node's edge is the REVERSE of the sequence of insertion.
void insert(int start, int end, int weight){
    // the new index of an edge.
    ++tot;
    // set the to node 'end' of the new edge.
    to[tot] = end;
    // set the weight of the new edge.
    weights[tot] = weight;
    // the next edge of the new edge is the first edge of NODE 'start',
    // since they belong to node 'start' !!! -> like a linked list !!
    next[tot] = head[start];
    // the first edge of NODE 'start' is the new edge.
    head[start] = tot;
}

// since we NEVER use the index 0 as edge's index, 
// if the index reached 0, it means the end of the linked list.
void traverse(int cur){
    // i is the index of an edge.
    for(int i = head[cur]; i != 0; i = next[i]){
        int v = to[i];
        int weight = weights[i];
    }
}