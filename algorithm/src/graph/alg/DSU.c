#include <stdio.h>
#define LENGTH 1007
int count;        // the count of connected components
int root[LENGTH]; // the root node of each node


int quickFind(int x){
    return root[x];
}

void slowMerge(int x, int y){
    int rootx = quickFind(x);
    int rooty = quickFind(y);
    if(rootx == rooty)
        return ;
    // change the root node of another sub tree.
    for(int i = 0; i < LENGTH; i++){
        if(root[i] == rootx)
            root[i] = rooty;
    }
    // after merging, the count of connected components should decrease.
    count--;
}

void slowFind(int x){
    // find the root node of the connected component.
    while(x != root[x]){
        x = root[x];
    }
    return x;
}

void quickMerge(int x, int y){
    int rootx = quickFind(x);
    int rooty = quickFind(y);
    if(rootx == rooty)
        return ;
    root[rootx] = rooty;
    count--;
}

// However, the two methods above are not efficient enough.
// The worst time complexity of both methods are O(n^2).
// So we need a new method to solve this problem.

// the first method is "rank".

int rank[LENGTH]; // the rank of each node. You can think rank is the height of a tree.

int rankFind(int x){
    return root[x];
}

void rankMerge(int x, int y){
    int rootx = rankFind(x);
    int rooty = rankFind(y);
    if(rootx == rooty)
        return ;
    // it can be easily proved that, if the height of two trees are different,
    // then we can merge the shorter one to the taller one and the height will
    // NOT change.
    // Only when the height of two trees are the same, the height of the new tree
    // will increase by 1.
    if(rank[rootx] < rank[rooty]){
        root[rootx] = rooty;
    }
    else if(rank[rootx] > rank[rooty]){
        root[rooty] = rootx;
    }
    else{
        root[rootx] = rooty;
        rank[rooty]++;
    }
}

int compactFind(int x)
{
    if(x != root[x]){
        root[x] = compactFind(root[x]);
    }
    return root[x];
}

void compactMerge(int x, int y)
{
    int rootx = findRoot(x);
    int rooty = findRoot(y);
    if(rootx == rooty){
        return ;
    }
    root[rootx] = rooty; 
    count--;
}

void initiate(int n)
{
    for (int i = 1; i <= n; i++){
        // at the begginning, each node is a connected component,
        // and its root node is itself.
        root[i] = i;
        // at the beginning, the rank(height) of each node is 0.
        rank[i] = 0;
    }
    count = n;
}