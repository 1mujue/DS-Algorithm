#include <stdio.h>
char a[1000],ch,stock;
int i=-1,mark,wei,zero,dezero,time,judge,times;
int main()
{
    for(int i1 = 0;i1 < 1000;i1++)
    {
        a[i1]='-';
    }
    while((ch=getchar())!=EOF)
    {
        i++;
        if(i==0)
        {
            stock=ch;
        }
        if(ch=='.')
        {
            mark=i;
            a[i]='d';
            continue;
        }
        if(ch!='0'&&ch!='.')
        {
            dezero=1;
        }
        if(ch=='0'&&dezero==0&&mark!=0&&stock=='0')
        {
            a[0]='-';
            zero++;
            continue;
        }
        a[i]=ch;
    }
        if(mark!=0&&stock=='0')
    {
        a[0]='-';
        judge=1;
    }
    if(zero!=0)
    {
        wei=-(zero+1);
    }
    else if(zero==0&&mark!=0&&judge==0)
    {
        wei=mark-1;
    }
    else if(zero==0&&mark!=0&&judge!=0)
    {
        wei=-1;
    }
    else if(zero==0&&mark==0)
    {
        wei=i-1;
    }
    for(int i1 = 0;i1 < i;i1++)
    {
        if(a[i1]=='-')
            continue;
        if(a[i1]>='0'&&a[i1]<='9')
        {
            printf("%c",a[i1]);
            time++;
        }
        if(time!=0&&(a[i1+1]>='1'&&a[i1+1]<='9')&&times!=1)
        {
            printf(".");
            times=1;
        }
    }
    printf("e%d",wei);
    return 0;
}
