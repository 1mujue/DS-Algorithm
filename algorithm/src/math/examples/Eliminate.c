// problem link: https://leetcode.cn/problems/elimination-game/
int lastRemaining(int n) {
    // take the first element AFTER kth delete is a1k, the last element is ank, the count of 
    // element is cntk, and the step(delta) is stepk.
    // Clearly, cntk = cnt(k-1) / 2. (down round), and
    // step0 = 2, step1 = 4, ..., stepk = step(k-1) * 2.

    // if k = 2 * t:
    //      if cntk = 2 * m + 1, then a1(k+1) = a1k + stepk / 2, an(k+1) = ank - stepk / 2.
    //      else, a1(k+1) = a1k + stepk / 2, an(k+1) = ank.
    // if k = 2 * t + 1:
    //      if cntk = 2 * m + 1, then a1(k+1) = a1k + stepk / 2, an(k+1) = ank - stepk / 2.
    //      else, a1(k+1) = a1k, an(k+1) = ank - stepk / 2.
    

    int a1 = 1, an = n;
    int cnt = n;
    int step = 2;
    int k = 0;

    while(cnt != 1){
        if(k & 1){
            if(cnt & 1){
                a1 += step / 2;
                an -= step / 2;
            }
            else{
                an -= step / 2;
            }
        }
        else{
            if(cnt & 1){
                a1 += step / 2;
                an -= step / 2;
            }
            else{
                a1 += step / 2;
            }
        }
        cnt >>= 1;
        step <<= 1;
        k++;
    }
    return an;
}