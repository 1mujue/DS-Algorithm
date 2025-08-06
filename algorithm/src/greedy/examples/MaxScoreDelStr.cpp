// problem link: https://leetcode.cn/problems/maximum-score-from-removing-substrings/

// This is a GREEDY PROBLEM.
// For "abab", we can remove "ba", and then remove "ab", or remove "ab" twice.
// Generally, for a string consists of 'a' and 'b', the total remove count 
// will NOT change whether we remove "ab" or "ba". 
// Therefore, for a string consists of 'a' and 'b', we should remove the one with 
// higher score first, and then remove the other one.
// Note that there are other latters in the string, we should ONLY focus on a sub string
// ONLY consists of 'a' and 'b'.
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int maximumGain(string s, int x, int y) {
        string ns = s + "#";
        int len = ns.size();

        array<array<int, 3>, 2> arr;
        if(x > y){
            arr[0][0] = 0, arr[0][1] = 1;
            arr[0][2] = x;
            arr[1][0] = 1, arr[1][1] = 0;
            arr[1][2] = y;
        }
        else{
            arr[0][0] = 1, arr[0][1] = 0;
            arr[0][2] = y;
            arr[1][0] = 0, arr[1][1] = 1;
            arr[1][2] = x;
        }

        int ans = 0;
        vector<int> stack;
        for(int i = 0; i < len; i++){
            int v = ns[i] - 'a';
            if(v != 0 && v != 1){
                array<int, 3> cur = arr[0];
                int slen = stack.size();
                int top = 0;
                for(int j = 0; j < slen; j++){
                    if(top && stack[top - 1] == cur[0] && stack[j] == cur[1]){
                        ans += cur[2];
                        top--;
                    }
                    else{
                        stack[top++] = stack[j];
                    }
                }
                slen = top;
                top = 0;
                cur = arr[1];
                for(int j = 0; j < slen; j++){
                    if(top && stack[top - 1] == cur[0] && stack[j] == cur[1]){
                        ans += cur[2];
                        top--;
                    }
                    else{
                        stack[top++] = stack[j];
                    }
                }
                stack.resize(0);
            }
            else{
                stack.push_back(v);
            }
        }
        return ans;
    }
};