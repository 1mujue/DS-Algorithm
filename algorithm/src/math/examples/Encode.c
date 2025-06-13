// problem link: https://www.luogu.com.cn/problem/P1866

#include <stdio.h>
#include <string.h>
#include <math.h>
#define LEN 1002
#define VOL 30
#define ll long long

ll comb[VOL][VOL];
void init(){
    comb[0][0] = 1;
    for(int i = 1; i <= 27; i++){
        for(int j = 1; j <= i; j++){
            comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
        }
    }
}

int main(){
    char buf[LEN];
    scanf("%s", buf);
    int blen = strlen(buf);

    if(blen > 6){
        printf("0");
        return 0;
    }

    int prev = 0;
    for(int i = 0; i < blen; i++){
        if(buf[i] <= prev){
            printf("0");
            return 0;
        }
        prev = buf[i];
    }

    // comb[i + 1][j + 1]: Cij.
    init();

    ll ans = 0;
    for(int i = 1; i < blen; i++){
        // all character: 26
        // you have to select: i.
        ans += comb[27][i + 1];
    }
    for(int i = 0; i < blen; i++){
        int ch = buf[i] - 'a' + 1;
        int prev = i == 0 ? 0 : buf[i - 1] - 'a' + 1;
        for(int j = prev + 1; j < ch; j++){
            // left character: 26 - j.
            // you have to select: blen - i - 1.
            ans += comb[27 - j][blen - i];
        }
    }
    printf("%ld", ans + 1);
    return 0;
}