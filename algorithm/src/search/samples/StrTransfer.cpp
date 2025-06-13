//#include <bits/stdc++.h>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <deque>
#include <iostream>
#include <vector>
using namespace std;

struct Node{
    string str;
    int step;
};

int main(){
    string src, tar;
    cin >> src >> tar;

    unordered_map<string, vector<string>> map;
    string ra, rb;
    while(cin >> ra >> rb){
        map[ra].push_back(rb);
    }

    unordered_set<string> rec;
    deque<Node> q;
    q.push_back({src, 0});
    rec.insert(src);

    while(!q.empty()){
        Node cur = q.front();
        string curstr = cur.str;
        q.pop_front();
        if(cur.step > 10) break;
        if(curstr == tar){
            cout << cur.step;
            return 0;
        }
        for(auto it = map.begin(); it != map.end(); it++){
            int pos = curstr.find(it->first);
            while(pos != string::npos){
                for(const string& match : it->second){
                    string newstr = curstr.substr(0, pos);
                    newstr += match;
                    newstr += curstr.substr(pos + it->first.size());
                    if(!rec.count(newstr)){
                        rec.insert(newstr);
                        q.push_back({newstr, cur.step + 1});
                    }
                }
                pos = curstr.find(it->first, pos + it->first.size());
            }
        }
    }
    cout << "NO ANSWER!";
    return 0;
}