#include <stdio.h>

int main()
{
    return 0;
}
//////////////////////////////////////////
int i, n;
scanf("%d", &n);

for(i = 0; i < n; i++)
{
	
}

//////////////////////////////////////////
int t;
scanf("%d", &t);
while(t--)
{
	
}

//////////////////////////////////////////
int t;
while(scanf("%d", &t) != EOF)
{
	
}

//////////////////////////////////////////
int n, m;
while(scanf("%d%d", &n, &m) != EOF)
{
	
}

//////////////////////////////////////////
int n, m;
scanf("%d%d", &n, &m);


//////////////////////////////////////////
#include <stdio.h>

int main()
{
    int t;
    int n, m;

    scanf("%d", &t);
    while(t--)
    {
        scanf("%d%d", &n, &m);

    }
    return 0;
}


//////////////////////////////////////////
// scanf
char 		: %c
short 		: %hd
int  		: %d
unsigned int: %u
long long 	: %lld
unsigned long long 	: %llu
float		: %f
double		: %lf
// printf
char 		: %c
short 		: %hd
int  		: %d
unsigned int: %u
long long 	: %lld
unsigned long long 	: %llu
float		: %f
double		: %f

//////////////////////////////////////////
char* s_gets(char * str)
{
    int len;
    gets(str);
    len = strlen(str);
    if(str[len - 1] == '\r')
    {
        str[len - 1] = '\0';
    }
	return str;
}


