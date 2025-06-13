#include <stdio.h>
#include <stdlib.h>
#define VOL 40004
#define EDGE 100002

// The use of Extended Union.

int root[VOL];
int findRoot(int x){
    if(root[x] != x){
        root[x] = findRoot(root[x]);
    }
    return root[x];
}
void merge(int x, int y){
    int rx = findRoot(x), ry = findRoot(y);
    if(rx != ry){
        root[rx] = ry;
    }
}

int cmp(const void* e1, const void* e2){
    int* a1 = (int*)e1;
    int* a2 = (int*)e2;
    return a1[2] < a2[2];
}   

int main(){
    int nn, mm;
    scanf("%d%d", &nn, &mm);

    for(int i = 1; i <= 2 * nn; i++){
        root[i] = i;
    }

    int edges[EDGE][3];
    for(int i = 0; i < mm; i++){
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        edges[i][0] = a;
        edges[i][1] = b;
        edges[i][2] = c;
    }

    qsort(edges, mm, sizeof(int[3]), cmp);

    int ans = 0;
    for(int i = 0; i < mm; i++){
        int u = edges[i][0], v = edges[i][1];
        merge(u, v + nn);
        merge(v, u + nn);
        if(findRoot(u) == findRoot(u + nn) || findRoot(v) == findRoot(v + nn)){
            ans = edges[i][2];
            break;
        }
    }

    printf("%d\n", ans);
    return 0;
}