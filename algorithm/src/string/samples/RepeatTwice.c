// problem link: https://www.luogu.com.cn/problem/P4391
// The solution to this problem is WELL illustrated by others,
// and see that is enough.

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

#define ll long long
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define LEN 1000002

int sta[LEN];

void func(char* str, int* prefix){
    int slen = strlen(str);
    prefix[0] = 0;
    for(int i = 1; i < slen; i++){
        int curpi = prefix[i - 1];
        while(curpi && str[curpi] != str[i]) curpi = prefix[curpi - 1];
        if(str[i] == str[curpi]) curpi++;
        prefix[i] = curpi;
        sta[prefix[i]]++;
    }
}

char s1[LEN];
int pi[LEN];

int main(){
    sta[0] = 1;
    int l;
    scanf("%d", &l);
    scanf(" %s", s1);

    func(s1, pi);
    printf("%d", l - pi[l - 1]);

    return 0;
}