// problem link: https://leetcode.cn/problems/maximum-number-of-events-that-can-be-attended/
#include <bits/stdc++.h>
using namespace std;

// the key thought: since the attended meeting's number will plus 1 if we 
// attend the meeting for AT LEAST 1 day, we can have such greedy thought:

// 1. if a meeting starts VERY early, such like at day 1 and ens at day 2, while other meetings 
// start at day 100+, Of COURSE we should attend this meeting;
// 2. if many meetings have the same start day, the MOST ENMERGENCY meeting is the meeting
// that ends the EARLIEST, and we should attend that meeting.

// Therefore, we can solve the problem in this way:
// 0: build a priority queue that is sorted by the end time of the meetings.
// 1. sort the meetings by their start day. At each day 'cday', we push in ALL meetings 
// whose start time is less than or equal to 'cday' into a priority queue; 
// 2. pop meetings from priority queue if the top meeting's end time is less than 'cday'.
// 3. if the priority queue is not empty, we pop the top meeting from the priority queue,
// and this means we can attend this meeting, and the answer plus 1.

struct Node{
    int start;
    int end;
};
struct NodeCmp{
    bool operator()(const Node& e1, const Node& e2) const{
        if(e1.end == e2.end){
            return e1.start > e2.start;
        }
        return e1.end > e2.end;
    }
};

bool sortCmp(const vector<int>& e1, const vector<int>& e2){
    if(e1[0] == e2[0]){
        return e1[1] < e2[1];
    }
    return e1[0] < e2[0];
}
class Solution {
public:
    int maxEvents(vector<vector<int>>& events) {
        sort(events.begin(), events.end(), sortCmp);
        priority_queue<Node, vector<Node>, NodeCmp> pq;

        int esize = events.size();
        int cind = 0;
        int ans = 0;
        for(int cday = 1; cday <= 100000; cday++){
            while(cind < esize && events[cind][0] <= cday){
                pq.push({events[cind][0], events[cind][1]});
                cind++;
            }
            while(pq.size() && pq.top().end < cday){
                pq.pop();
            }
            if(pq.size()){
                ans++;
                pq.pop();
            }
        }
        return ans;
    }
};