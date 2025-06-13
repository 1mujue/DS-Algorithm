#include <stdio.h>

#define KMP_O0
#define KMP_O1
#define KMP_O2
#define KMP_STR_LEN 100007

// the definition of pi[i]: the max length of same REAL 
// prefix and suffix of string s[0...i] (caution: i is index, not length!!)
// for example, if s = "abcabcd", then the pi should be
// {0, 0, 0, 1, 2, 3, 0}

// we say that, the function to calculate pi is a prefix function. 
//The key of KMP is about how to calculate pi[i] effectively.

// the plain version:
void prefixFunO0(char* str, int* prefix)
{
    int len = strlen(str);
    prefix[0] = 0;
    // i represents the index of str.
    for(int i = 1;i < len; i++){
        int sameLen = 0;
        for(int j = i; j >= 0; j--){
            int isSame = 1;
            for(int k = 0; k < j; k++){
                if(str[k] != str[i - j + 1 + k]){
                    isSame = 0;
                    break;
                }
            }
            if(isSame){
                sameLen = j;
                break;
            }
        }
        prefix[i] = sameLen;
    }
}

// first optimization: pi[i + 1] <= pi[i] + 1. 
// if s[pi[i]](next char of prefix) == s[i + 1](next char of suffix)
// then pi[i + 1] = pi[i] + 1. For example, s = "abcab"
//  i = 4, then pi[i] = 2, now s[pi[i]] = 'c' = s[i + 1],
// therefore, pi[i + 1] = pi[i] + 1.
// 

void prefixFunO1(char* str, int* prefix){
    int len = strlen(str);
    prefix[0] = 0;
    // i represents the index of str.
    for(int i = 1;i < len; i++){
        int sameLen = 0;
        for(int j = prefix[i - 1] + 1; j >= 0; j--){
            int isSame = 1;
            for(int k = 0; k < j; k++){
                if(str[k] != str[i - j + 1 + k]){
                    isSame = 0;
                    break;
                }
            }
            if(isSame){
                sameLen = j;
                break;
            }
        }
        prefix[i] = sameLen;
    }
}

// second optimization: what if s[i + 1] != s[pi[i]]??
// this time, we need to find a LENGTH j that,
// s[0...j - 1] = s[i - j + 1...i], in this case,
// if s[j] == s[i + 1], then pi[i + 1] = j + 1, else
// we will repeat the process.

// additionally, s[0...pi[i] - 1] = s[i - pi[i] + 1...i],
// s[0...j - 1] == s[i - j + 1...i], therefore,
// s[0...j - 1] = s[pi[i] - j...pi[i] - 1],
// and j = pi[pi[i] - 1]

void prefixFunO2(char* str, int* prefix){
    int len = strlen(str);
    prefix[0] = 0;
    for(int i = 1;i < len; i++){
        int j = prefix[i - 1];
        while(j > 0 && str[i] != str[j]) j = prefix[j - 1];
        if(str[i] == str[j]) j++;
        prefix[i] = j;
    }
}

// we will concat pattern, a delimeter and str together.
// for example, if we want to find ALL locations of "abc"(pattern) 
// in "abcabc" (str), then we will create a string "abc#abcabc", and we name it s.
// once the pi[i] (of s) equals to the length of pattern(we call it n
// here n == 3), we find a same pattern in str, and 
// the location of it(in str) is i - (n - 1) - (n + 1) = i - 2n.
// n + 1 is the length of pattern + delimeter.
void kmp(char* str, char* pattern, int* loc){
    int prefix[KMP_STR_LEN];
    char s[KMP_STR_LEN];
    int sLen = 0;
    // assume there is no '#' in neither str nor pattern.
    char div = '#';

    int patLen = 0;
    char* it = pattern;
    while(*it != '\0'){
        s[sLen++] = *it;
        it++;
        patLen++;
    }
    s[sLen++] = div;
    
    it = str;
    while(*it != '\0'){
        s[sLen++] = *it;
        it++;
    }
    s[sLen] = '\0';

    int locIndex = 0;
    prefixFunO2(s, prefix);
    for(int i = patLen + 1; i < sLen; i++){
        if(prefix[i] == patLen) loc[locIndex++] = i - 2 * patLen;
    }
}