#include <stdio.h>
int main(){
    int a = 1;
    if(a)a = 2, a =4;
    a = a = 1, a + 2;
    printf("%d", a);
    return 0;
}