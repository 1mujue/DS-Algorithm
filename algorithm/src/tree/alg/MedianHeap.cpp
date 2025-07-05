// unrecorded problem link: https://www.luogu.com.cn/problem/P1168
#include <bits/stdc++.h>


// a VERY IMPORTANT usage of heap.
// How to calculate a medium number of an array DYNAMICALLY (insert gradually) ?
// We can use TWO HEAPS to maintain it. The first heap is a MAX heap which contains
// the SMALLER half of the numbers, and the second heap is a MIN heap which contains
// the LARGER half of the numbers. For convienience, the size of 1st heap is (n + 1) / 2,
// and the size of 2nd heap is n / 2. In this case, if n is an odd, then we can return
// the top of the 1st heap; otherwise, we can return the average of the tops of both heaps.

// Let 1st heap's size is s1, and 2nd heap's size is s2. Clearly,
// s1 == s2 or s1 == s2 + 1. If the equation is voliated, we need to BALANCE the two heaps.
// You can read the code to better understand the algorithm.
using namespace std;
using ll = long long;

class MedianHeap{
private:
    // less part.
    priority_queue<int, vector<int>, less<int>> pq1;
    // greater part.
    priority_queue<int, vector<int>, greater<int>> pq2;
    void makeBalance(){
        if(pq2.size() > pq1.size()){
            int ele = pq2.top();
            pq2.pop();
            pq1.push(ele);
        }
        else if(pq1.size() > pq2.size() + 1){
            int ele = pq1.top();
            pq1.pop();
            pq2.push(ele);
        }
    }
    void doInsert(int val){
        if(!pq1.size() && !pq2.size()){
            pq1.push(val);
        }
        else if(pq1.size() && !pq2.size()){
            if(val >= pq1.top()){
                pq2.push(val);
            }
            else{
                pq1.push(val);
            }
        }
        else if(!pq1.size() && pq2.size()){
            if(val > pq2.top()){
                pq2.push(val);
            }
            else{
                pq1.push(val);
            }
        }
        else{
            if(val > pq1.top()){
                pq2.push(val);
            }
            else{
                pq1.push(val);
            }
        }
        makeBalance();
    }
public:
    void insert(int val){
        doInsert(val);
    }
    int getMedian(){
        return pq1.top();
    }
};

int main(){
    int nn;
    cin >> nn;
    MedianHeap mh;

    for(int i = 0; i < nn; i++){
        int val;
        cin >> val;
        mh.insert(val);
        if(i % 2 == 0){
            cout << mh.getMedian() << '\n';
        }
    }
    return 0;
}