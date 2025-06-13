// problem link: https://www.luogu.com.cn/problem/P1572

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define ll long long
#define LEN 103

int getGCD(int mx, int mn){
    if(!mn) return 1;
    while(mx % mn){
        int t = mn;
        mn = mx % mn;
        mx = t;
    }
    return mn;
}

int getLCM(int mx, int mn){
    return mx / getGCD(mx, mn) * mn;
}

int getOpRes(int v1, int v2, int op){
    if(op == '+'){
        return v1 + v2;
    }
    else{
        return v1 - v2;
    }
}

int main(){
    char buf[LEN];
    scanf(" %s", buf);
    int blen = strlen(buf);

    int fenzi[LEN];
    int fenmu[LEN];
    int ftop = 0;
    int ops[LEN];
    int otop = 0;
    for(int i = 0; i < blen; i++){
        int val1 = 0, val2 = 0;
        int isNeg = 0;
        if(buf[i] == '-'){
            isNeg = 1;
            i++;
        }
        while(i < blen && isdigit(buf[i])){
            val1 = val1 * 10 + buf[i] - '0';
            i++;
        }
        if(isNeg){
            val1 = -val1;
        }
        i++;
        while(i < blen && isdigit(buf[i])){
            val2 = val2 * 10 + buf[i] - '0';
            i++;
        }
        int gcd = getGCD(MAX(val1, val2), MIN(val1, val2));
        fenzi[ftop] = val1 / gcd;
        fenmu[ftop] = val2 / gcd;
        ftop++;
        
        if(i != blen){
            ops[otop++] = buf[i];
        }
    }

    for(int i = 0; i < otop; i++){
        int fz1 = fenzi[i], fz2 = fenzi[i + 1];
        int fm1 = fenmu[i], fm2 = fenmu[i + 1];
        int tfz = getOpRes(fz1 * fm2, fz2 * fm1, ops[i]);
        int tfm = fm1 * fm2;
        int gcd = getGCD(MAX(abs(tfz), abs(tfm)), MIN(abs(tfz), abs(tfm)));
        int rfz = tfz / gcd;
        int rfm = tfm / gcd;
        fenzi[i + 1] = rfz;
        fenmu[i + 1] = rfm;
    }
    if(fenzi[otop] == 0){
        printf("0");
        return 0;
    }
    else if(fenmu[otop] == 1){
        printf("%d", fenzi[otop]);
        return 0;
    }
    printf("%d/%d", fenzi[otop], fenmu[otop]);
    return 0;
}