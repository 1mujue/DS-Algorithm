// problem link: https://leetcode.cn/problems/maximum-number-of-tasks-you-can-assign/description/

#define VOL 50004
int cmp(const void* e1, const void* e2){
    return *(int*)e1 > *(int*)e2;
}
int maxTaskAssign(int* tasks, int tasksSize, int* workers, int workersSize, int pills, int strength) {
    qsort(tasks, tasksSize, sizeof(int), cmp);
    qsort(workers, workersSize, sizeof(int), cmp);

    int queue[VOL];

    int ans = -1;
    int left = 0, right = fmin(tasksSize, workersSize);
    int mid;

    while(left <= right){
        int mid = (left + right) / 2;
        
        int slow = 0, fast = 0;
        int wind = workersSize - mid, tind = 0;
        int leftPills = pills;
        int curcnt = 0;
        while(wind < workersSize){
            while(tind < mid && workers[wind] + strength >= tasks[tind]){
                queue[fast++] = tasks[tind];
                tind++;
            }
            if(slow == fast) {
                break;
            }
            if(workers[wind] >= queue[slow]){
                curcnt++;
                wind++;
                slow++;
            }
            else if(leftPills){
                leftPills--;
                curcnt++;
                fast--;
                wind++;
            }
            else{
                break;
            }
        }
        if(curcnt < mid){
            right = mid - 1;
        }
        else{
            ans = mid;
            left = mid + 1;
        }
    }
    return ans;
}