// problem link: https://leetcode.cn/problems/zero-array-transformation-iii/description/
#define VOL 100002
int cmp(const void* e1, const void* e2){
    int* a1 = *(int**)e1;
    int* a2 = *(int**)e2;
    return a1[0] > a2[0];
}

// the defition of heap. IGNORE it.
typedef struct HNode{
    int left;
    int right;
}HNode;

HNode heap[VOL];
int heapSize;

void up(int ind){
    HNode hn = heap[ind];
    while(ind && heap[(ind - 1) / 2].right < hn.right){
        heap[ind] = heap[(ind - 1) / 2];
        ind = (ind - 1) / 2;
    }
    heap[ind] = hn;
}
void down(int ind){
    while(1){
        int biggest = ind;
        int t = 2 * ind + 1;
        if(t < heapSize && heap[t].right > heap[biggest].right){
            biggest = t;
        }
        t++;
        if(t < heapSize && heap[t].right > heap[biggest].right){
            biggest = t;
        }
        if(biggest != ind){
            HNode hn = heap[biggest];
            heap[biggest] = heap[ind];
            heap[ind] = hn;
            ind = biggest;
        }
        else{
            return;
        }
    }
}
void in(int left, int right){
    heap[heapSize].left = left, heap[heapSize].right = right;
    heapSize++;
    up(heapSize - 1);
}
HNode delete(int ind){
    HNode ret = heap[ind];
    heap[ind] = heap[heapSize - 1];
    heapSize--;
    down(ind);
    return ret;
}

// key thought: we want that nums[i] <= 0, then we need find an inteval [l, r] that
// l <= i. When satisfying this, we hope r be AS LARGE AS POSSIBLE, since in that case,
// more nums[k] can reduce 1.

// Therefore, the solution is. For index i, we insert ALL intervals [lk, rk] whose lk <= i
// into the heap. The top of the heap has the BIGGEST rk. Then, we will try to pop top and 
// do reduction until nums[i] <= 0 or heap is empty.

// Caution: since we will do reduction on [lk, rk], we can use DIFF ARRAY.
int maxRemoval(int* nums, int numsSize, int** queries, int queriesSize, int* queriesColSize) {
    heapSize = 0;
    qsort(queries, queriesSize, sizeof(int*), cmp);
    int diff[VOL] = {0};
    diff[0] = nums[0];
    for(int i = 1; i < numsSize; i++){
        diff[i] = nums[i] - nums[i - 1];
    }

    int cursum = 0, qind = 0;
    int isOk = 1;
    for(int i = 0; i < numsSize; i++){
        while(qind < queriesSize && queries[qind][0] <= i){
            int l = queries[qind][0], r = queries[qind][1];
            in(l, r);
            qind++;
        }
        while(cursum + diff[i] > 0 && heapSize){
            HNode hn = delete(0);
            int l = hn.left, r = hn.right;
            diff[l] -= 1;
            if(l < i){
                cursum -= 1;
            }
            diff[r + 1] += 1;
            if(r + 1 < i){
                cursum += 1;
            }
        }
        if(cursum + diff[i] > 0){
            isOk = 0;
            break;
        }
        cursum += diff[i];
    }
    if(!isOk) return -1;
    return heapSize;
}