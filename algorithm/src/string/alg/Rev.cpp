#include <iostream>
#include <string>

// flag == 1, reverse integer part.
// flag == 0, reverse decimal part.
std::string rev(std::string s, int flag){
    if(flag){
        while(s.size() > 1 && s.back() == '0'){
            s.pop_back();
        }
    }
    
    int slen = s.size();
    for(int i = 0; i < slen / 2; i++){
        int t = s[i];
        s[i] = s[slen - 1 - i];
        s[slen - 1 - i] = t;
    }

    if(!flag){
        while(s.size() > 1 && s.back() == '0'){
            s.pop_back();
        }
    }

    return s;
}