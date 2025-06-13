#define VOL 10001

int root[VOL];
int rootCnt;

int init(int n){
    for(int i = 0; i < n; i++){
        root[i] = i;
    }
    rootCnt = n;
}

int findRoot(int n){
    if(root[n] != n){
        root[n] = findRoot(root[n]);
    }
    return root[n];
}

void merge(int x, int y){
    int rx = findRoot(x), ry = findRoot(y);
    if(rx != ry){
        root[ry] = rx;
        rootCnt--;
    }
}