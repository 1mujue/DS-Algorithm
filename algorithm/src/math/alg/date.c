#include <stdio.h>
int getweek(int day)
{
    int c,y,m,d,w;
    y = day/10000;
    m = (day%10000)/100;
    d = day%100;
    if(m < 3)
    {
         y = y-1;
         m =m + 12;
    }
    c = y/100;
    y = y %100;
    w=(y+y/4+c/4-2*c+(13*(m+1))/5+d-1)%7;
    if(w<0)
        w+=7;
    return w;
}
int main()
{
    int a;
    scanf("%d",&a);
    switch(getweek(a))
    {
    case 0:
        printf("Sun\n");
        break;
    case 1:
        printf("Mon\n");
        break;
    case 2:
        printf("Tue\n");
        break;
    case 3:
        printf("Wed\n");
        break;
    case 4:
        printf("Thu\n");
        break;
    case 5:
        printf("Fri\n");
        break;
    case 6:
        printf("Sat\n");
        break;
    }
    return 0;
}