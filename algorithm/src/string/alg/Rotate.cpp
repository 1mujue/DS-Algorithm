#include <string>
#include <vector>

void get90(std::vector<std::string>& rec, int cx, int cy, int n){
    if(n <= 1) return;
    for(int i = 0; i < n - 1; i++){
        int t = rec[cx][cy + i];
        rec[cx][cy + i] = rec[cx + n - 1 - i][cy];
        rec[cx + n - 1 - i][cy] = rec[cx + n - 1][cy + n - 1 - i];
        rec[cx + n - 1][cy + n - 1 - i] = rec[cx + i][cy + n - 1];
        rec[cx + i][cy + n - 1] = t;
    }
    get90(rec, cx + 1, cy + 1, n - 2);
}